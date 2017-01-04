/***************************************************************************\
| display.c - part of Nexus Of Hades                                        |
| Copyright (c) 2016-17 Pete Favelle <ahnlak@gmail.com>                     |
| Licensed under the MIT License; see LICENSE.txt for details.              |
+---------------------------------Overview----------------------------------+
| This file handles all the display stuff; rendering of maps, the character |
| details and anything else display-y.                                      |
+---------------------------------Changelog---------------------------------+
| 01/01/17 PF: Initial Version                                              |
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
| display_map - renders the provided map, at the coordinates specified. The |
|               map is automatically centred on the player, if present, or  |
|               else just centred.                                          |
+--------------------------------Parameters---------------------------------+
| nhmap_t * - the map to be displayed.                                      |
| short x 4 - the location and size to display the map on the screen.       |
+----------------------------------Returns----------------------------------+
| Returns - false if an error occurs.                                       |
\***************************************************************************/
int display_map( const nhmap_t *p_map, short p_x, short p_y,
    short p_width, short p_height ) {

    short     l_map_x, l_map_y, l_map_top, l_map_left;
    short     l_line, l_column;
    int       l_mapchar;
    nhtile_t *l_worktile;

    /* Validate our parameters. */
    if ( p_map == NULL || p_x < 0 || p_y < 0 ||
        ( p_x + p_width > TCOD_console_get_width( NULL ) ) ||
        ( p_y + p_height > TCOD_console_get_height( NULL ) ) ) {
        return FALSE;
    }

    /* Centering the map - if it's screen size or less, just center it! */
    if ( p_width >= p_map->width ) {
        l_map_left = ( p_map->width - p_width ) / 2; /* Simples! */
    }
    else {
        /* Center it on the object of interest, as best we can, then. */
        l_map_left = 0;
    }
    if ( p_height >= p_map->height ) {
        l_map_top = ( p_map->height - p_height ) / 2; /* Simples! */
    }
    else {
        /* Center it on the object of interest, as best we can, then. */
        l_map_top = 0;
    }

    /* So, we know where the map sits in the screen; just work through it. */
    for ( l_line = 0; l_line < p_height; l_line++ ) {
        for ( l_column = 0; l_column < p_width; l_column++ ) {
            /* Get the map co-ordinates. */
            l_map_x = l_column + l_map_left;
            l_map_y = l_line + l_map_top;

            /* Handle areas outside of the map. */
            if ( ( l_map_x < 0 ) || ( l_map_x >= p_map->width ) ||
                ( l_map_y < 0 ) || ( l_map_y >= p_map->height ) ) {
                l_mapchar = ' ';
            }
            else {
                /* Good, so look up the map tile in question. */
                l_worktile = map_get_tile( p_map, l_map_x, l_map_y );

                /* Apply any lighting / visibility considerations... */
                l_mapchar = l_worktile->content;
                if ( l_worktile == NULL ) {
                    l_mapchar = '!';
                }
            }

            /* All done, so render this tile. */
            TCOD_console_set_char( NULL, p_x + l_column, p_y + l_line, l_mapchar );
        }
    }
    
    return FALSE;
}

/* End of file display.c */