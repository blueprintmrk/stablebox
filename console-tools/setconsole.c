/* vi: set sw=4 ts=4: */
/*
 *  setconsole.c - redirect system console output
 *
 *  Copyright (C) 2004,2005  Enrik Berkhan <Enrik.Berkhan@inka.de>
 *
 * Licensed under GPLv2, see file LICENSE in this tarball for details.
 */

#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <getopt.h> /* struct option */

#include "busybox.h"

#if ENABLE_FEATURE_SETCONSOLE_LONG_OPTIONS
static const struct option setconsole_long_options[] = {
	{ "reset", 0, NULL, 'r' },
	{ 0, 0, 0, 0 }
};
#endif

#define OPT_SETCONS_RESET 1

int setconsole_main(int argc, char **argv)
{
	unsigned long flags;
	const char *device = CURRENT_TTY;

#if ENABLE_FEATURE_SETCONSOLE_LONG_OPTIONS
	bb_applet_long_options = setconsole_long_options;
#endif
	flags = bb_getopt_ulflags(argc, argv, "r");

	if (argc - optind > 1)
		bb_show_usage();

	if (argc - optind == 1) {
		if (flags & OPT_SETCONS_RESET)
			bb_show_usage();
		device = argv[optind];
	} else {
		if (flags & OPT_SETCONS_RESET)
			device = CONSOLE_DEV;
	}

	if (-1 == ioctl(bb_xopen(device, O_RDONLY), TIOCCONS)) {
		bb_perror_msg_and_die("TIOCCONS");
	}
	return EXIT_SUCCESS;
}
