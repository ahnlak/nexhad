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
| nhloc_t * - the location and size to display the map on the screen.       |
+----------------------------------Returns----------------------------------+
| Returns - false if an error occurs.                                       |
\***************************************************************************/
int display_map( const nhmap_t *p_map, const nhloc_t *p_location ) {

    short     l_map_x, l_map_y, l_map_top, l_map_left;
    short     l_line, l_column;
    int       l_mapchar;
    nhtile_t *l_worktile;
    nhloc_t   l_tileloc;

    /* Validate our parameters. */
    if ( p_map == NULL || p_location == NULL || 
        ( p_location->x + p_location->width > TCOD_console_get_width( NULL ) ) ||
        ( p_location->y + p_location->height > TCOD_console_get_height( NULL ) ) ) {
        return FALSE;
    }

    /* Centering the map - if it's screen size or less, just center it! */
    if ( p_location->width >= p_map->width ) {
        l_map_left = ( p_map->width - p_location->width ) / 2; /* Simples! */
    }
    else {
        /* Center it on the object of interest, as best we can, then. */
        l_map_left = 0;
    }
    if ( p_location->height >= p_map->height ) {
        l_map_top = ( p_map->height - p_location->height ) / 2; /* Simples! */
    }
    else {
        /* Center it on the object of interest, as best we can, then. */
        l_map_top = 0;
    }

    /* So, we know where the map sits in the screen; just work through it. */
    for ( l_line = 0; l_line < p_location->height; l_line++ ) {
        for ( l_column = 0; l_column < p_location->width; l_column++ ) {
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
                l_tileloc.x = l_map_x;
                l_tileloc.y = l_map_y;
                l_worktile = map_get_tile( p_map, &l_tileloc );

                /* Apply any lighting / visibility considerations... */
                l_mapchar = l_worktile->content;
                if ( l_worktile == NULL ) {
                    l_mapchar = '!';
                }
            }

            /* All done, so render this tile. */
            TCOD_console_set_char( NULL, p_location->x + l_column, 
                p_location->y + l_line, l_mapchar );
        }
    }

    /* Next, we have to process the various items on the map. */
    /*
    if ( p_map->items != NULL ) {

    }
    if ( p_map->beasts != NULL ) {

    }
    if ( p_map->beings != NULL ) {

    }
    */
    return FALSE;
}

/* End of file display.c */