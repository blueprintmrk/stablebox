/* vi: set sw=4 ts=4: */
/*
 * ftpget
 *
 * Mini implementation of FTP to retrieve a remote file.
 *
 * Copyright (C) 2002 Jeff Angielski, The PTR Group <jeff@theptrgroup.com>
 * Copyright (C) 2002 Glenn McGrath <bug1@iinet.net.au>
 *
 * Based on wget.c by Chip Rosenthal Covad Communications
 * <chip@laserlink.net>
 *
 * Licensed under GPLv2, see file LICENSE in this tarball for details.
 */

#include <sys/ioctl.h>

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>

#include "resolv6.h"
#include "busybox.h"

typedef struct ftp_host_info_s {
	char *user;
	char *password;
//#ifdef CONFIG_FEATURE_IPV6
	struct sockaddr_in6 s_in;
//#else
//	struct sockaddr_in *s_in;
//#endif
} ftp_host_info_t;

static char verbose_flag = 0;
static char do_continue = 0;

static int ftpcmd(const char *s1, const char *s2, FILE *stream, char *buf)
{
	if (verbose_flag) {
		bb_error_msg("cmd %s%s", s1, s2);
	}

	if (s1) {
		if (s2) {
			fprintf(stream, "%s%s\r\n", s1, s2);
		} else {
			fprintf(stream, "%s\r\n", s1);
		}
	}
	do {
		char *buf_ptr;

		if (fgets(buf, 510, stream) == NULL) {
			bb_perror_msg_and_die("fgets()");
		}
		buf_ptr = strstr(buf, "\r\n");
		if (buf_ptr) {
			*buf_ptr = '\0';
		}
	} while (! isdigit(buf[0]) || buf[3] != ' ');

	return atoi(buf);
}

static int xconnect_ftpdata(ftp_host_info_t *server, const char *buf)
{
	char *buf_ptr;
	unsigned short port_num;

	buf_ptr = strrchr(buf, ',');
	*buf_ptr = '\0';
	port_num = atoi(buf_ptr + 1);

	buf_ptr = strrchr(buf, ',');
	*buf_ptr = '\0';
	port_num += atoi(buf_ptr + 1) * 256;

#ifdef CONFIG_FEATURE_IPV6
	server->s_in.sin6_port=htons(port_num);
	return(xconnect2(&server->s_in));
#else
	server->s_in->sin_port=htons(port_num);
	return(xconnect(server->s_in));
#endif
}

static FILE *ftp_login(ftp_host_info_t *server)
{
	FILE *control_stream;
	char buf[512];

	/* Connect to the command socket */
#ifdef CONFIG_FEATURE_IPV6
	control_stream = fdopen(xconnect2(&server->s_in), "r+");
#else
	control_stream = fdopen(xconnect(server->s_in), "r+");
#endif
	if (control_stream == NULL) {
		bb_perror_msg_and_die("Couldnt open control stream");
	}

	if (ftpcmd(NULL, NULL, control_stream, buf) != 220) {
		bb_error_msg_and_die("%s", buf + 4);
	}

	/*  Login to the server */
	switch (ftpcmd("USER ", server->user, control_stream, buf)) {
	case 230:
		break;
	case 331:
		if (ftpcmd("PASS ", server->password, control_stream, buf) != 230) {
			bb_error_msg_and_die("PASS error: %s", buf + 4);
		}
		break;
	default:
		bb_error_msg_and_die("USER error: %s", buf + 4);
	}

	ftpcmd("TYPE I", NULL, control_stream, buf);

	return(control_stream);
}

#if !ENABLE_FTPGET
#define ftp_receive 0
#else
static int ftp_receive(ftp_host_info_t *server, FILE *control_stream,
		const char *local_path, char *server_path)
{
	char buf[512];
	off_t filesize = 0;
	int fd_data;
	int fd_local = -1;
	off_t beg_range = 0;

	/* Connect to the data socket */
	if (ftpcmd("PASV", NULL, control_stream, buf) != 227) {
		bb_error_msg_and_die("PASV error: %s", buf + 4);
	}
	fd_data = xconnect_ftpdata(server, buf);

	if (ftpcmd("SIZE ", server_path, control_stream, buf) == 213) {
		unsigned long value=filesize;
		if (safe_strtoul(buf + 4, &value))
			bb_error_msg_and_die("SIZE error: %s", buf + 4);
		filesize = value;
	} else {
		filesize = -1;
		do_continue = 0;
	}

	if ((local_path[0] == '-') && (local_path[1] == '\0')) {
		fd_local = STDOUT_FILENO;
		do_continue = 0;
	}

	if (do_continue) {
		struct stat sbuf;
		if (lstat(local_path, &sbuf) < 0) {
			bb_perror_msg_and_die("fstat()");
		}
		if (sbuf.st_size > 0) {
			beg_range = sbuf.st_size;
		} else {
			do_continue = 0;
		}
	}

	if (do_continue) {
		sprintf(buf, "REST %ld", (long)beg_range);
		if (ftpcmd(buf, NULL, control_stream, buf) != 350) {
			do_continue = 0;
		} else {
			filesize -= beg_range;
		}
	}

	if (ftpcmd("RETR ", server_path, control_stream, buf) > 150) {
		bb_error_msg_and_die("RETR error: %s", buf + 4);
	}

	/* only make a local file if we know that one exists on the remote server */
	if (fd_local == -1) {
		if (do_continue) {
			fd_local = bb_xopen(local_path, O_APPEND | O_WRONLY);
		} else {
			fd_local = bb_xopen(local_path, O_CREAT | O_TRUNC | O_WRONLY);
		}
	}

	/* Copy the file */
	if (filesize != -1) {
		if (-1 == bb_copyfd_size(fd_data, fd_local, filesize))
			exit(EXIT_FAILURE);
	} else {
		if (-1 == bb_copyfd_eof(fd_data, fd_local))
			exit(EXIT_FAILURE);
	}

	/* close it all down */
	close(fd_data);
	if (ftpcmd(NULL, NULL, control_stream, buf) != 226) {
		bb_error_msg_and_die("ftp error: %s", buf + 4);
	}
	ftpcmd("QUIT", NULL, control_stream, buf);

	return(EXIT_SUCCESS);
}
#endif

#if !ENABLE_FTPPUT
#define ftp_send 0
#else
static int ftp_send(ftp_host_info_t *server, FILE *control_stream,
		const char *server_path, char *local_path)
{
	struct stat sbuf;
	char buf[512];
	int fd_data;
	int fd_local;
	int response;

	/*  Connect to the data socket */
	if (ftpcmd("PASV", NULL, control_stream, buf) != 227) {
		bb_error_msg_and_die("PASV error: %s", buf + 4);
	}
	fd_data = xconnect_ftpdata(server, buf);

	/* get the local file */
	if ((local_path[0] == '-') && (local_path[1] == '\0')) {
		fd_local = STDIN_FILENO;
	} else {
		fd_local = bb_xopen(local_path, O_RDONLY);
		fstat(fd_local, &sbuf);

		sprintf(buf, "ALLO %lu", (unsigned long)sbuf.st_size);
		response = ftpcmd(buf, NULL, control_stream, buf);
		switch (response) {
		case 200:
		case 202:
			break;
		default:
			close(fd_local);
			bb_error_msg_and_die("ALLO error: %s", buf + 4);
			break;
		}
	}
	response = ftpcmd("STOR ", server_path, control_stream, buf);
	switch (response) {
	case 125:
	case 150:
		break;
	default:
		close(fd_local);
		bb_error_msg_and_die("STOR error: %s", buf + 4);
	}

	/* transfer the file  */
	if (bb_copyfd_eof(fd_local, fd_data) == -1) {
		exit(EXIT_FAILURE);
	}

	/* close it all down */
	close(fd_data);
	if (ftpcmd(NULL, NULL, control_stream, buf) != 226) {
		bb_error_msg_and_die("error: %s", buf + 4);
	}
	ftpcmd("QUIT", NULL, control_stream, buf);

	return(EXIT_SUCCESS);
}
#endif

#define FTPGETPUT_OPT_CONTINUE	1
#define FTPGETPUT_OPT_VERBOSE	2
#define FTPGETPUT_OPT_USER	4
#define FTPGETPUT_OPT_PASSWORD	8
#define FTPGETPUT_OPT_PORT	16

#if ENABLE_FEATURE_FTPGETPUT_LONG_OPTIONS
static const struct option ftpgetput_long_options[] = {
	{"continue", 1, NULL, 'c'},
	{"verbose", 0, NULL, 'v'},
	{"username", 1, NULL, 'u'},
	{"password", 1, NULL, 'p'},
	{"port", 1, NULL, 'P'},
	{0, 0, 0, 0}
};
#else
#define ftpgetput_long_options 0
#endif

int ftpgetput_main(int argc, char **argv)
{
	/* content-length of the file */
	unsigned long opt;
	char *port = "ftp";

	/* socket to ftp server */
	FILE *control_stream;

	/* continue a prev transfer (-c) */
	ftp_host_info_t *server;

	int (*ftp_action)(ftp_host_info_t *, FILE *, const char *, char *) = NULL;

	/* Check to see if the command is ftpget or ftput */
	if (ENABLE_FTPPUT && (!ENABLE_FTPGET || bb_applet_name[3] == 'p')) {
		ftp_action = ftp_send;
	}
	if (ENABLE_FTPGET && (!ENABLE_FTPPUT || bb_applet_name[3] == 'g')) {
		ftp_action = ftp_receive;
	}

	/* Set default values */
	server = xmalloc(sizeof(ftp_host_info_t));
	server->user = "anonymous";
	server->password = "busybox@";
	verbose_flag = 0;

	/*
	 * Decipher the command line
	 */
	if (ENABLE_FEATURE_FTPGETPUT_LONG_OPTIONS)
		bb_applet_long_options = ftpgetput_long_options;

	opt = bb_getopt_ulflags(argc, argv, "cvu:p:P:", &server->user, &server->password, &port);

	/* Process the non-option command line arguments */
	if (argc - optind != 3) {
		bb_show_usage();
	}

	if (opt & FTPGETPUT_OPT_CONTINUE) {
		do_continue = 1;
	}
	if (opt & FTPGETPUT_OPT_VERBOSE) {
		verbose_flag = 1;
	}

	/* We want to do exactly _one_ DNS lookup, since some
	 * sites (i.e. ftp.us.debian.org) use round-robin DNS
	 * and we want to connect to only one IP... */
#ifdef CONFIG_FEATURE_IPV6
	memset(&server->s_in, 0, sizeof(server->s_in));
	server->s_in.sin6_family = AF_INET6;
	server->s_in.sin6_port = bb_lookup_port(port, "tcp", 21);
	(void)ResolveAddress(argv[optind], RESOLVE_ANY, 0, &server->s_in.sin6_addr);
#else
	{
		struct sockaddr_in s_in;
	
		server->s_in = &s_in;
		bb_lookup_host(&s_in, argv[optind]);
		s_in.sin_port = bb_lookup_port(port, "tcp", 21);
		if (verbose_flag) {
			printf("Connecting to %s[%s]:%d\n",
				argv[optind], inet_ntoa(s_in.sin_addr), ntohs(s_in.sin_port));
		}
	}
#endif

	/*  Connect/Setup/Configure the FTP session */
	control_stream = ftp_login(server);

	return(ftp_action(server, control_stream, argv[optind + 1], argv[optind + 2]));
}
