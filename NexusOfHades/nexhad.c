/***************************************************************************\
| nexhad.c - part of Nexus Of Hades                                         |
| Copyright (c) 2016-17 Pete Favelle <ahnlak@gmail.com>                     |
| Licensed under the MIT License; see LICENSE.txt for details.              |
+---------------------------------Overview----------------------------------+
| This file provides the main entry to NexHad; as such it shouldn't get too |
| big or unmanageable (famous last words!)                                  |
+---------------------------------Changelog---------------------------------+
| 21/12/16 PF: Initial Version                                              |
\***************************************************************************/

/* System headers. */
#include <stdio.h>
#include <stdlib.h>

/* Local headers. */
#include "libtcod.h"
#include "nexhad.h"

/* Local functions. */

/***************************************************************************\
| main - The main entry function; everything starts here!                   |
+--------------------------------Parameters---------------------------------+
| int    argc - the number of command line arguments in argv                |
| char **argv - array of command line argument strings                      |
+----------------------------------Returns----------------------------------+
| int         - return value to pass back to calling process (0 on success) |
\***************************************************************************/

int main( int argc, char **argv )
{
    const nhmap_t *l_splash_map;

    /* Handle any command line arguments. */

    /* Great, now we set up TCOD. */
    TCOD_console_set_custom_font( NEXHAD_FONT_FNAME, TCOD_FONT_TYPE_GREYSCALE | TCOD_FONT_LAYOUT_ASCII_INROW, 0, 0 );
    TCOD_console_init_root( SCREEN_WIDTH, SCREEN_HEIGHT, "Nexus Of Hades v0.0.1", false, TCOD_RENDERER_SDL );

    /* Render an appropriate splash screen before we do anything else. */
    l_splash_map = map_load( NEXHAD_SPLASHMAP_FNAME );
    TCOD_console_clear( NULL );
    display_map( l_splash_map, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    TCOD_console_flush();

    map_free( l_splash_map );

    /* And enter the main game loop. */
    while ( !TCOD_console_is_window_closed() )
    {
        TCOD_key_t   lKeyStatus;
        TCOD_mouse_t lMouseStatus;

        /* Fetch the next event. */
        TCOD_sys_wait_for_event( TCOD_EVENT_KEY_PRESS | TCOD_EVENT_MOUSE_MOVE, &lKeyStatus, &lMouseStatus, true );

        /* And respond to it appropriately! */
        if ( lKeyStatus.vk == TCODK_ESCAPE ) {
            break;
        }
    }
    
    /* All done. */
    return 0;
}

/* End of nexhad.c */