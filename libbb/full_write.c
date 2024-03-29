/* vi: set sw=4 ts=4: */
/*
 * Utility routines.
 *
 * Copyright (C) 1999-2004 by Erik Andersen <andersen@codepoet.org>
 *
 * Licensed under GPLv2, see file LICENSE in this tarball for details.
 */

#include <stdio.h>
#include <unistd.h>
#include "libbb.h"

/*
 * Write all of the supplied buffer out to a file.
 * This does multiple writes as necessary.
 * Returns the amount written, or -1 on an error.
 */
ssize_t bb_full_write(int fd, const void *buf, size_t len)
{
	ssize_t cc;
	ssize_t total;

	total = 0;

	while (len > 0) {
		cc = safe_write(fd, buf, len);

		if (cc < 0)
			return cc;		/* write() returns -1 on failure. */

		total += cc;
		buf = ((const char *)buf) + cc;
		len -= cc;
	}

	return total;
}
