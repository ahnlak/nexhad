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
    nhstate_t      l_state = STATE_SPLASH;
    const nhmap_t *l_splash_map = NULL;
    TCOD_event_t   l_event;
    nhloc_t        l_screenloc;

    /* Handle any command line arguments. */

    /* Great, now we set up TCOD. */
    TCOD_console_set_custom_font( NEXHAD_FONT_FNAME, TCOD_FONT_TYPE_GREYSCALE | TCOD_FONT_LAYOUT_ASCII_INROW, 0, 0 );
    TCOD_console_init_root( SCREEN_WIDTH, SCREEN_HEIGHT, "Nexus Of Hades v0.0.1", false, TCOD_RENDERER_SDL );
    TCOD_sys_set_fps( 20 );
    l_screenloc.x = 0;
    l_screenloc.y = 0;
    l_screenloc.width = SCREEN_WIDTH;
    l_screenloc.height = SCREEN_HEIGHT;

    /* And enter the main game loop. */
    while ( !TCOD_console_is_window_closed() && l_state != STATE_EXIT )
    {
        TCOD_key_t   lKeyStatus;
        TCOD_mouse_t lMouseStatus;

        /* Update the animation cycle, if we have anything running that way. */
        switch ( l_state ) {
            case STATE_SPLASH:
                /* Check we have a map loaded. */
                if ( l_splash_map == NULL ) {
                    l_splash_map = map_load( NEXHAD_SPLASHMAP_FNAME );
                    if ( l_splash_map == NULL ) {
                        l_state = STATE_EXIT;
                        break;
                    }
                }
                break;
            default: /* Something badly wrong here! */
                l_state = STATE_EXIT;
                break;
        }

        /* Render the appropriate view of the world, depending on the state. */
        switch ( l_state )
        {
            case STATE_SPLASH:
                TCOD_console_clear( NULL );
                display_map( l_splash_map, &l_screenloc );
                TCOD_console_flush();
                break;
            default:  /* Something badly wrong here! */
                l_state = STATE_EXIT;
                break;
        }

        /* Lastly, check to see if there are any events to handle. */
        l_event = TCOD_sys_check_for_event( TCOD_EVENT_KEY_PRESS | TCOD_EVENT_MOUSE_MOVE, &lKeyStatus, &lMouseStatus );

        /* If there isn't one to handle, move on. */
        if ( l_event != TCOD_EVENT_KEY_PRESS && l_event != TCOD_EVENT_MOUSE_MOVE ) {
            continue;
        }

        /* And respond to it appropriately! */
        switch ( l_state ) {
            case STATE_SPLASH:
                if ( l_event == TCOD_EVENT_KEY_PRESS ) {
                    map_free( l_splash_map );
                    l_state = STATE_EXIT;
                }
                break;
            default:  /* Something badly wrong here! */
                l_state = STATE_EXIT;
                break;
        }
    }
    
    /* All done. */
    return 0;
}

/* End of nexhad.c */