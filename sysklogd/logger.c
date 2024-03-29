/* vi: set sw=4 ts=4: */
/*
 * Mini logger implementation for busybox
 *
 * Copyright (C) 1999-2004 by Erik Andersen <andersen@codepoet.org>
 *
 * Licensed under GPLv2, see file LICENSE in this tarball for details.
 */

#include "busybox.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#if !defined CONFIG_SYSLOGD

#define SYSLOG_NAMES
#include <sys/syslog.h>

#else
#include <sys/syslog.h>
#  ifndef __dietlibc__
	/* We have to do this since the header file defines static
	 * structures.  Argh.... bad libc, bad, bad...
	 */
	typedef struct _code {
		char *c_name;
		int c_val;
	} CODE;
	extern CODE prioritynames[];
	extern CODE facilitynames[];
#  endif
#endif

/* Decode a symbolic name to a numeric value
 * this function is based on code
 * Copyright (c) 1983, 1993
 * The Regents of the University of California.  All rights reserved.
 *
 * Original copyright notice is retained at the end of this file.
 */
static int decode(char *name, CODE * codetab)
{
	CODE *c;

	if (isdigit(*name))
		return (atoi(name));
	for (c = codetab; c->c_name; c++) {
		if (!strcasecmp(name, c->c_name)) {
			return (c->c_val);
		}
	}

	return (-1);
}

/* Decode a symbolic name to a numeric value
 * this function is based on code
 * Copyright (c) 1983, 1993
 * The Regents of the University of California.  All rights reserved.
 *
 * Original copyright notice is retained at the end of this file.
 */
static int pencode(char *s)
{
	char *save;
	int lev, fac = LOG_USER;

	for (save = s; *s && *s != '.'; ++s);
	if (*s) {
		*s = '\0';
		fac = decode(save, facilitynames);
		if (fac < 0)
			bb_error_msg_and_die("unknown facility name: %s", save);
		*s++ = '.';
	} else {
		s = save;
	}
	lev = decode(s, prioritynames);
	if (lev < 0)
		bb_error_msg_and_die("unknown priority name: %s", save);
	return ((lev & LOG_PRIMASK) | (fac & LOG_FACMASK));
}


int logger_main(int argc, char **argv)
{
	int pri = LOG_USER | LOG_NOTICE;
	int option = 0;
	int c, i, opt;
	char buf[1024], name[128];

	/* Fill out the name string early (may be overwritten later) */
	bb_getpwuid(name, geteuid(), sizeof(name));

	/* Parse any options */
	while ((opt = getopt(argc, argv, "p:st:")) > 0) {
		switch (opt) {
			case 's':
				option |= LOG_PERROR;
				break;
			case 'p':
				pri = pencode(optarg);
				break;
			case 't':
				safe_strncpy(name, optarg, sizeof(name));
				break;
			default:
				bb_show_usage();
		}
	}

	openlog(name, option, 0);
	if (optind == argc) {
		do {
			/* read from stdin */
			i = 0;
			while ((c = getc(stdin)) != EOF && c != '\n' &&
					i < (sizeof(buf)-1)) {
				buf[i++] = c;
			}
			if (i > 0) {
				buf[i++] = '\0';
				syslog(pri, "%s", buf);
			}
		} while (c != EOF);
	} else {
		char *message = NULL;
		int len = argc - optind; /* for the space between the args
					    and  '\0' */
		opt = len;
		argv += optind;
		for (i = 0; i < opt; i++) {
			len += strlen(*argv);
			message = xrealloc(message, len);
			if(!i)
				message[0] = 0;
			else
				strcat(message, " ");
			strcat(message, *argv);
			argv++;
		}
		syslog(pri, "%s", message);
	}

	closelog();
	return EXIT_SUCCESS;
}


/*-
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This is the original license statement for the decode and pencode functions.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. <BSD Advertising Clause omitted per the July 22, 1999 licensing change
 *		ftp://ftp.cs.berkeley.edu/pub/4bsd/README.Impt.License.Change>
 *
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */



