/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright by The HDF Group.                                               *
 * Copyright by the Board of Trustees of the University of Illinois.         *
 * All rights reserved.                                                      *
 *                                                                           *
 * This file is part of HDF5.  The full HDF5 copyright notice, including     *
 * terms governing use, modification, and redistribution, is contained in    *
 * the files COPYING and Copyright.html.  COPYING can be found at the root   *
 * of the source code distribution tree; Copyright.html can be found at the  *
 * root level of an installed copy of the electronic HDF5 document set and   *
 * is linked from the top-level documents page.  It can also be found at     *
 * http://hdfgroup.org/HDF5/doc/Copyright.html.  If you do not have          *
 * access to either file, you may request a copy from help@hdfgroup.org.     *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
 * Programmer:  Quincey Koziol <koziol@hdfgroup.org>
 *              Wednesday, March 17, 2010
 *
 * Purpose:     srcdir querying support.
 */
#ifndef _H5SRCDIR_H
#define _H5SRCDIR_H

/* Include the header file with the correct relative path for the srcdir string */
#include "H5srcdir_str.h"


/* TODO: Should not have statics in a header.  Make a H5srcdir.c. */

/* Buffer to construct path in and return pointer to */
static char srcdir_path[1024] = "";

/* Buffer to construct file in and return pointer to */
static char srcdir_testpath[1024] = "";

/* Append the test file name to the srcdir path and return the whole string */

/* TODO: This should be in a source file, not a header. */
#ifndef NO_GET_SRCDIR_FILENAME

#ifdef H5_VMS
static const char *H5_get_srcdir_filename(char *filename)
#else
static const char *H5_get_srcdir_filename(const char *filename)
#endif
{
    const char *srcdir = HDgetenv("srcdir");

    /* Check for using the srcdir from configure time */
    if(NULL == srcdir)
        srcdir = config_srcdir;

    /* Build path to test file */
    if((HDstrlen(srcdir) + HDstrlen(filename) + 2) < sizeof(srcdir_testpath)) {
#ifdef H5_VMS
        HDstrcpy(srcdir_testpath, srcdir);
        if(filename[0] == '[') {
            char *tmp = filename;

            srcdir_testpath[HDstrlen(srcdir) - 1] = '\0';
            HDstrcat(srcdir_testpath, ++tmp);
        } /* end if */
        else
            HDstrcat(srcdir_testpath, filename);
#else
        HDsnprintf(srcdir_testpath, sizeof(srcdir_testpath), "%s/%s", srcdir, filename);
#endif
        return(srcdir_testpath);
    } /* end if */
    else
        return(NULL);
}

#endif /* TODO: NO_GET_SRCDIR_FILENAME */

/* Just return the srcdir path */
/* TODO: This should be in a source file, not a header. */
#ifndef NO_GET_SRCDIR
static const char *H5_get_srcdir(void)
{
    const char *srcdir = HDgetenv("srcdir");

    /* Check for using the srcdir from configure time */
    if(NULL == srcdir)
        srcdir = config_srcdir;

    /* Build path to all test files */
    if((HDstrlen(srcdir) + 2) < sizeof(srcdir_path)) {
        HDsnprintf(srcdir_path, sizeof(srcdir_path), "%s/", srcdir);
        return(srcdir_path);
    } /* end if */
    else
        return(NULL);
}
#endif /* NO_GET_SRCDIR */

#endif /* _H5SRCDIR_H */

