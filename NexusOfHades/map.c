/***************************************************************************\
| map.c - part of Nexus Of Hades                                            |
| Copyright (c) 2016-17 Pete Favelle <ahnlak@gmail.com>                     |
| Licensed under the MIT License; see LICENSE.txt for details.              |
+---------------------------------Overview----------------------------------+
| This file deals with all the map handling; loading of static maps, and of |
| course the generation of random ones.                                     |
+---------------------------------Changelog---------------------------------+
| 21/12/16 PF: Initial Version                                              |
\***************************************************************************/

/* System headers. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Local headers. */
#include "nexhad.h"

/* Local functions. */

/***************************************************************************\
| map_load - Reads map data from the named file and returns a map structure |
|            which is dynamically allocated.                                |
+--------------------------------Parameters---------------------------------+
| char *   - the name of the file to be read                                |
+----------------------------------Returns----------------------------------+
| const nhmap * - pointer to the newly allocated map, or NULL on failure.   |
\***************************************************************************/
const nhmap_t *map_load( const char *p_filename ) {
    nhmap_t    *l_new_map = NULL;
    FILE       *l_fptr;
    char       *l_charptr;
    char        l_buffer[1024];
    int         l_index;
    size_t      l_buflen;
    short       l_currline;
    nhsection_t l_section = SECTION_NONE;
    nhtile_t   *l_worktile;

    /* Check that we can open the map, otherwise nothing else matters. */
    l_fptr = fopen( p_filename, "r" );
    if ( l_fptr == NULL ) {
        return NULL;
    }

    /* Good, we can safely create the new map object then. */
    l_new_map = (nhmap_t *)calloc( 1, sizeof( nhmap_t ) );
    if ( l_new_map == NULL ) {
        return NULL;
    }

    /* The map format is split into sections, see Wiki. */
    while ( fgets( l_buffer, 1000, l_fptr ) != NULL ) {
        /* Trim off any trailing newline. */
        if ( l_buffer[strlen( l_buffer ) - 1] == '\n' ) {
            l_buffer[strlen( l_buffer ) - 1] = '\0';
        }
        /* Check for a section header. */
        if ( ( l_buffer[0] == '[' ) && ( l_buffer[strlen(l_buffer)-1] == ']' ) ) {
            if ( strncmp( l_buffer, "[overview]", 10 ) == 0 ) {
                l_section = SECTION_OVERVIEW;
                continue;
            }
            else if ( strncmp( l_buffer, "[layout]", 8 ) == 0 ) {
                l_section = SECTION_LAYOUT;
                l_currline = 0;
                continue;
            }
        }

        /* Are we currently in a section? */
        switch ( l_section ) {
            case SECTION_NONE:           /* Not yet in a section, skip it. */
                break;
            case SECTION_OVERVIEW:             /* Simple overview section. */
                l_charptr = strchr( l_buffer, ':' );
                if ( l_charptr != NULL ) {
                    *l_charptr++ = '\0';
                    if ( strcmp( l_buffer, "title" ) == 0 ) {
                        l_new_map->title = (char *)calloc( 1, strlen( l_charptr ) + 1 );
                        if ( l_new_map->title == NULL ) {
                            map_free( l_new_map );
                            return NULL;
                        }
                        strcpy( l_new_map->title, l_charptr );
                    }
                    else if ( strcmp( l_buffer, "width" ) == 0 ) {
                        l_new_map->width = atoi( l_charptr );
                    }
                    else if ( strcmp( l_buffer, "height" ) == 0 ) {
                        l_new_map->height = atoi( l_charptr );
                    }
                }
                break;
            case SECTION_LAYOUT:            /* The basic layout map layer. */
                /* Check that we have space allocated. */
                if ( l_new_map->tiles == NULL ) {
                    l_new_map->tiles = (nhtile_t *)calloc( sizeof( nhtile_t ), l_new_map->width*l_new_map->height );
                    if ( l_new_map->tiles == NULL ) {
                        map_free( l_new_map );
                        return NULL;
                    }
                }

                /* Check that the line is what we expected. */
                l_buflen = strlen( l_buffer );
                if ( l_buflen > l_new_map->width || l_currline > l_new_map->height ) {
                    map_free( l_new_map );
                    return NULL;
                }

                /* Work through the line then, one tile at a time. */
                for ( l_index = 0; l_index < l_buflen; l_index++ ) {
                    /* Fetch the tile. */
                    l_worktile = map_get_tile( l_new_map, l_index, l_currline );
                    if ( l_worktile == NULL ) {
                        map_free( l_new_map );
                        return NULL;
                    }

                    /* And set the content. */
                    l_worktile->content = l_buffer[l_index];
                }

                /* Don't forget to keep count of the lines we're working with! */
                l_currline++;
                break;
            default:                        /* Something BAD has happened! */
                map_free( l_new_map );
                return NULL;
        }
    }

    return l_new_map;
}

/***************************************************************************\
| map_free - Frees the memory associated with the map provided.             |
+--------------------------------Parameters---------------------------------+
| const nhmap * - pointer to the map to delete.                             |
+----------------------------------Returns----------------------------------+
| None                                                                      |
\***************************************************************************/
void map_free( const nhmap_t *p_map ) {
    /* We can only do this if we're given a map to work with! */
    if ( p_map ) {
        /* Free up the title, if allocated. */
        if ( p_map->title != NULL ) {
            free( p_map->title );
        }

        /* And the same for the tiles. */
        if ( p_map->tiles != NULL ) {
            free( p_map->tiles );
        }

        /* 
         * Apologies for the ugly cast; the pointer really *is* const in 
         * just about every other sense. Sorry.
         */
        free( (void *)p_map );
    }
}

/***************************************************************************\
| map_get_tile - Returns a pointer to the tile at a given location.         |
+--------------------------------Parameters---------------------------------+
| const nhmap * - pointer to the map to work with.                          |
| short         - the x position of the tile to find.                       |
| short         - the y position of the tile to find.                       |
+----------------------------------Returns----------------------------------+
| nhtile_t * - pointer to the tile in question, or NULL on error.           |
\***************************************************************************/
nhtile_t *map_get_tile( const nhmap_t *p_map, short p_x, short p_y ) {
    /* Validate the map. */
    if ( p_map == NULL ) {
        return NULL;
    }

    /* And validate the location on that map. */
    if ( ( p_x >= p_map->width ) || ( p_y >= p_map->height ) ) {
        return NULL;
    }

    /* Fairly simple maths then! */
    return &( p_map->tiles[p_x+(p_y*p_map->width)] );
}

/* End of file map.c */