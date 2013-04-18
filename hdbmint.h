/*******************WARNING*********************

This is a *MODIFIED* version of Geoff Coller's proof-of-concept NOV
implementation.

It has been modified to support threading directly from a file handle
to a NNTP server without a temporary file.

This is not a complete distribution.  We have only distributed enough
to support NN's needs.

The original version came from world.std.com:/src/news/nov.dist.tar.Z
and was dated 11 Aug 1993.

In any case, bugs you find here are probably my fault, as I've trimmed
a fair bit of unused code.

-Peter Wemm  <peter@DIALix.oz.au>
*/

/*
 * Copyright (c) Geoffrey Collyer 1992, 1993.
 * All rights reserved.
 * Written by Geoffrey Collyer.
 * Thanks to UUNET Communications Services Inc for financial support.
 *
 * This software is not subject to any license of the American Telephone
 * and Telegraph Company, the Regents of the University of California, or
 * the Free Software Foundation.
 *
 * Permission is granted to anyone to use this software for any purpose on
 * any computer system, and to alter it and redistribute it freely, subject
 * to the following restrictions:
 *
 * 1. The authors are not responsible for the consequences of use of this
 *    software, no matter how awful, even if they arise from flaws in it.
 *
 * 2. The origin of this software must not be misrepresented, either by
 *    explicit claim or by omission.  Since few users ever read sources,
 *    credits must appear in the documentation.
 *
 * 3. Altered versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.  Since few users
 *    ever read sources, credits must appear in the documentation.
 *
 * 4. This notice may not be removed or altered.
 */

/*
 * general-purpose in-core hashing, dbm interface (internals)
 */

#define	STREQ(a, b)	(*(a) == *(b) && strcmp((a), (b)) == 0)

#define BADTBL(tbl)	(((tbl)->ht_magic&BYTEMASK) != HASHMAG)

#define HASHMAG  0257
#define BYTEMASK 0377

#define HASHENT struct hashent

HASHENT {
    HASHENT        *he_next;	/* in hash chain */
    HDBMDATUM       he_key;	/* to verify a match */
    HDBMDATUM       he_data;
};

HASHTABLE {
    HASHENT       **ht_addr;	/* array of HASHENT pointers */
    unsigned        ht_size;
    unsigned char   ht_magic;
    unsigned        (*ht_hash) ();
};
