/***************************************************************************\
| type.c - part of Nexus Of Hades                                           |
| Copyright (c) 2016-17 Pete Favelle <ahnlak@gmail.com>                     |
| Licensed under the MIT License; see LICENSE.txt for details.              |
+---------------------------------Overview----------------------------------+
| This file handles item types; everything in NexHad has a type, which is   |
| defined within the main type file. This allows for some common aspects to |
| things, and saves a lot of faffing about!                                 |
+---------------------------------Changelog---------------------------------+
| 05/01/17 PF: Initial Version                                              |
\***************************************************************************/

/* System headers. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Local headers. */
#include "libtcod.h"
#include "nexhad.h"

/* Local functions. */

/***************************************************************************\
| type_load - loads the type file and stores it internally, available to be |
|             searched or referenced as required. Any types provided are    |
|             added to the main list.                                       |
+--------------------------------Parameters---------------------------------+
| const char * - the name of the type file to load.                         |
+----------------------------------Returns----------------------------------+
| Returns - false if an error occurs.                                       |
\***************************************************************************/
int type_load( const char *p_filename ) {

}

/* End of file type.c */