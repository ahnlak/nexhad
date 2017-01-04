/***************************************************************************\
| nexhad.h - part of Nexus Of Hades                                         |
| Copyright (c) 2016-17 Pete Favelle <ahnlak@gmail.com>                     |
| Licensed under the MIT License; see LICENSE.txt for details.              |
+---------------------------------Overview----------------------------------+
| This file defines all the structures, enums and constants that are used   |
| throughout NexHad. It also provides function prototypes for everything.   |
+---------------------------------Changelog---------------------------------+
| 21/12/16 PF: Initial Version                                              |
\***************************************************************************/

#ifndef   NEXHAD_H
#define   NEXHAD_H

/* Constants. */
#define   SCREEN_WIDTH  120
#define   SCREEN_HEIGHT 48

#define   NEXHAD_FONT_FNAME         "data/terminal12x12_gs_ro.png"
#define   NEXHAD_SPLASHMAP_FNAME    "data/splash.map"

#ifndef   TRUE
#define   TRUE    ( 1 == 1 )
#endif /* TRUE */
#ifndef   FALSE
#define   FALSE   ( ! TRUE )
#endif /* FALSE */

/* Enums. */
typedef enum { SECTION_NONE, SECTION_OVERVIEW, SECTION_LAYOUT, SECTION_MOVEMENT } nhsection_t;
//typedef enum { MENU_MAIN, GAME, EXIT } mainstate_t;
typedef enum { CLASS_WAR, CLASS_KN, CLASS_CLR, CLASS_DK, CLASS_NEC, CLASS_MNK, CLASS_DRU } nhclass_t;

/* Structures. */
typedef struct {
    char      content;
} nhtile_t;

typedef struct {
    short     width;
    short     height;
    char     *title;
    nhtile_t *tiles;
} nhmap_t;

typedef struct {
    char       *name;
    char       *description;
} nhthing_t;

typedef struct {
    float       hp;
    float       hp_regen;
    float       ap;
    float       ap_regen;
    short       att_str;
    short       att_con;
    short       att_sta;
    short       att_dex;
    nhthing_t  *thing;
} nhliving_t;

typedef struct {
    short       att_wis;
    short       att_int;
    short       att_cha;
    nhclass_t   class;
    nhliving_t *living;
} nhsentient_t;

/* Function prototypes. */
int             display_map( const nhmap_t *, short, short, short, short );
const nhmap_t  *map_load( const char * );
void            map_free( const nhmap_t * );
nhtile_t       *map_get_tile( const nhmap_t *, short, short );

#endif /* NEXHAD_H */

/* End of file nexhad.h */