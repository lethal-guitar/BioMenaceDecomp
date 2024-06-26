/* Copyright (C) 2024 Nikolai Wuttke-Hohendorf
 *
 * Based on reconstructed Commander Keen 4-6 Source Code
 * Copyright (C) 2021 K1n9_Duk3
 *
 * This file is loosely based on:
 * Keen Dreams Source Code
 * Copyright (C) 2014 Javier M. Chavez
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef __BM_DEF__
#define __BM_DEF__

#include <BIOS.H>
#include <CONIO.H>

#include "ID_HEADS.H"

/*
=============================================================================

             GLOBAL CONSTANTS & MACROS

=============================================================================
*/

#define MINMEMORY 250000l

#define HIGHSCORE_LEFT   40
#define HIGHSCORE_TOP    35
#define HIGHSCORE_RIGHT 280
#define HIGHSCORE_MAP    12

#define TECHHELPMUSIC    18
#define DEMOLOOPMUSIC    11
#define HELPSCREENSMUSIC  0
#define DIALOGMUSIC      15
#define INVINCIBLEMUSIC  17
#define ENDINGMUSIC      12
#define VICTORYMUSIC     14

#define INACTIVATEDIST 6

#define MAXACTORS 125

#define GAMELEVELS 25

#define CONVERT_GLOBAL_TO_TILE(x)  ((x)>>(G_T_SHIFT))
#define CONVERT_TILE_TO_GLOBAL(x)  ((x)<<(G_T_SHIFT))
#define CONVERT_GLOBAL_TO_PIXEL(x) ((x)>>(G_P_SHIFT))
#define CONVERT_PIXEL_TO_GLOBAL(x) ((x)<<(G_P_SHIFT))
#define CONVERT_PIXEL_TO_TILE(x)   ((x)>>(P_T_SHIFT))
#define CONVERT_TILE_TO_PIXEL(x)   ((x)<<(P_T_SHIFT))

#define SPAWN_ADJUST_Y(y, h) (CONVERT_TILE_TO_GLOBAL(y) + (CONVERT_PIXEL_TO_GLOBAL(16-(h))))

#define ARRAYLENGTH(x) (sizeof(x)/sizeof(*(x)))

#define CA_UnmarkGrChunk(num) (grneeded[num] &= ~ca_levelbit)

#define SetPalette(pal) {_ES=FP_SEG(pal); _DX=FP_OFF(pal); _AX=0x1002; geninterrupt(0x10);}
#define SetPaletteEx(pal) {(pal)[16] = bordercolor; SetPalette(pal);}

//HACK IMPORTS:
void RFL_InitAnimList(void);
void CA_FreeGraphics(void);
void CA_SetGrPurge(void);

/*
Note:

The ID software memory manager doesn't care about the different purge levels.
Using PURGE_FIRST is identical to using PURGE_LAST.
*/
#define PURGE_FIRST 3
#define PURGE_LAST 1

#define PLATFORMBLOCK 71
#define DIRARROWSTART 58
#define DIRARROWEND   (DIRARROWSTART+arrow_None)

/*
=============================================================================

               GLOBAL TYPES

=============================================================================
*/

//SDL-style integer types - just to make future SDL ports easier
typedef unsigned int Uint16;
typedef signed int Sint16;
typedef unsigned char Uint8;
typedef signed char Sint8;
typedef unsigned long Uint32;
typedef signed long Sint32;
//Note: only the game code (BM_*.C) uses these!

//some compile-time checks to make sure the ints have the correct size
#if (sizeof(Uint16) != 2)
#error 'Uint16' has wrong size
#elif (sizeof(Sint16) != 2)
#error 'Sint16' has wrong size
#elif (sizeof(Uint8) != 1)
#error 'Uint8' has wrong size
#elif (sizeof(Sint8) != 1)
#error 'Sint8' has wrong size
#elif (sizeof(Uint32) != 4)
#error 'Uint32' has wrong size
#elif (sizeof(Sint32) != 4)
#error 'Sint32' has wrong size
#endif

typedef enum {
  arrow_North,     // 0
  arrow_East,      // 1
  arrow_South,     // 2
  arrow_West,      // 3
  arrow_NorthEast, // 4
  arrow_SouthEast, // 5
  arrow_SouthWest, // 6
  arrow_NorthWest, // 7
  arrow_None       // 8
} arrowdirtype;

typedef enum {
  ex_stillplaying, // 0
  ex_died,         // 1
  ex_completed,    // 2
  ex_warped,       // 3
  ex_resetgame,    // 4
  ex_loadedgame,   // 5
  ex_abortgame,    // 6
  NUMEXITTYPES
} exittype;

typedef enum
{
  INTILE_NOTHING           = 0,
  INTILE_LADDER            = 1,
  INTILE_DAMAGING          = 2,
  INTILE_KEYCARD_SLOT      = 3,
  INTILE_DOORLOCK_TRIANGLE = 4,
  INTILE_DOORLOCK1         = 5,
  INTILE_DOORLOCK2         = 6,
  INTILE_DOOR              = 7,
  INTILE_DOORLOCK_SPECIAL  = 8,
  INTILE_SHARD_SLOT_BLUE   = 9,
  INTILE_SHARD_SLOT_GREEN  = 10,
  INTILE_SHARD_SLOT_RED    = 11,
  INTILE_SHARD_SLOT_CYAN   = 12,
  INTILE_RADIATION         = 13,
  INTILE_NUKE_SLOT         = 14,
  INTILE_EXITKEY_SLOT      = 15,
  INTILE_FORCEFIELD        = 16,
  INTILE_BRIDGE_SWITCH     = 18,
  INTILE_PLATFORM_SWITCH   = 19,
  INTILE_UNKNOWN           = 20,
  INTILE_TRIGGER_DRMANGLE  = 21,
  INTILE_TRIGGER_UNKNOWN   = 22,
  INTILE_COLOR_SEQ_SWITCH  = 23,
  INTILE_TRIGGER_CRUSHER   = 25,
  INTILE_FOREGROUND        = 0x80
} intiletype;

#define INTILE_TYPEMASK (INTILE_FOREGROUND-1)

typedef enum
{
  nothing = 0,
  playerobj = 1,
  inertobj = 2,
  grenadeobj = 3,
  fireballobj = 5,
  pickupobj   =  6,
  slugobj     =  7,
  obclass_8   = 8,
  brawlerobj  =  9,
  ceilingwalkerobj = 10,
  spittersnakeobj  = 11,
  hostageobj  = 12,
  drmangleobj  = 13,
  platformobj = 14,
  robopalobj  = 16,
  shotobj = 17,
  lasergunnerobj  = 19,
  tankbotobj = 20,
  pushblockobj = 21,
  bounderobj  = 22,
  bouncebotobj  = 23,
  slimedropperobj = 24,
  enemyprojectileobj = 25,
  obclass_26         = 26,
  crushblockobj = 27,
  laserturretobj  = 28,
  obclass_29      = 29,
  obclass_30      = 30,
  sewermutantobj = 31,
  hedgehogobj = 32,
  skullmanobj = 33,
  skullmanhandobj = 34,
  bombobj = 36,
  crawlingslimeobj = 39,
  fireimpobj  = 40,
  helicopterobj  = 41,
  parachutebotobj = 42,
  NUMCLASSTYPES
} classtype;

typedef struct statestruct
{
  Sint16 leftshapenum, rightshapenum;
  enum {step,slide,think,stepthink,slidethink} progress;
  boolean skippable;
  enum { ps_none, ps_tofloor, ps_toceiling } pushstyle;
  Sint16 tictime;
  Sint16 xmove;
  Sint16 ymove;
  void (*think) (struct objstruct*);
  void (*contact) (struct objstruct*, struct objstruct*);
  void (*react) (struct objstruct*);
  struct statestruct far *nextstate;
} statetype;

typedef struct objstruct
{
  classtype obclass;
  enum {ac_no, ac_yes, ac_allways, ac_removable} active;
  boolean needtoreact;
  enum {cl_noclip, cl_midclip, cl_fullclip} needtoclip;
  Uint16 nothink;
  Uint16 x, y;
  Sint16 xdir, ydir;
  Sint16 xmove, ymove;
  Sint16 xspeed, yspeed;
  Sint16 ticcount;
  statetype far *state;
  Uint16 shapenum;
  Uint16 priority;
  Uint16 left, top, right, bottom, midx;
  Uint16 tileleft, tiletop, tileright, tilebottom, tilemidx;
  Sint16 hitnorth, hiteast, hitsouth, hitwest;
  boolean shootable;
  enum {sb_any, sb_player} spawnedby;
  Sint16 health;
  Sint16 dmgflash;
  Sint16 temp1;
  Sint16 temp2;
  Sint16 temp3;
  Sint16 temp4;
  Sint16 temp5;
  Sint16 temp6;
  Sint16 temp7;
  void *sprite;
  struct objstruct *next, *prev;
} objtype;

#define AMMO_REGULAR     0
#define AMMO_SUPERBULLET 3
#define AMMO_PLASMABOLT  4


typedef struct
{
  Sint32 score;
  Sint32 nextextra;
  Sint16 mapon;
  struct {
    Sint8 landmines;
    Sint8 grenades;
    Sint8 redgrenades;
  } explosives;
  struct {
    Sint16 keycards;
    Sint16 keys;
  } keyitems;
  boolean blueshard;
  boolean greenshard;
  boolean redshard;
  boolean cyanshard;
  boolean specialkey;
  enum { ns_none, ns_collected, ns_placed } nukestate;
  boolean radpill;
  boolean exitkey;
  boolean trianglekeys;
  boolean hasrobopal;
  Sint8 potions;
  Sint8 lives;
  Sint8 gems;
  Sint8 maxhealth;
  Sint8 difficulty;
  Sint8 rapidfire;
  Sint8 ammoinclip;
  Sint8 clips;
  Sint8 ammotype;
  boolean hostagerescued;
  boolean secretlevelgem;
  boolean helpmsggrenades;
  boolean helpmsgclips;
  boolean helpmsgkeycards;
  boolean helpmsgdoors;
  boolean helpmsgshards;
  boolean helpmsgsupergun;
  boolean helpmsglandmines;
  boolean helpmsggems;
  boolean helpmsghealth;
  boolean helpmsginvincible;
  boolean helpmsgrobopal;
  boolean helpmsgbridgeswitch;
  boolean helpmsgplatformswitch;
  boolean helpmsgcolorseq;
  boolean helpmsgenterdoor;
  boolean helpmsgplasmabolts;
  boolean helpmsgsecretlevelgem;
  boolean helpmsgbeacon;
  boolean var44;
  objtype *riding;
} gametype;

/*
=============================================================================

            BM_MAIN DEFINITIONS

=============================================================================
*/

extern char str[80], str2[20];
extern boolean storedemo;
extern Sint16 hbardivisor;
extern Uint16 curmusic;
extern boolean debugcodeentered;
extern boolean showmenuhighscores;
extern boolean practicerestoremap;
extern Sint16 practicetimer;
extern Uint16 playerrestorex;
extern Uint16 playerrestorey;
extern Sint16 bosshealth;
extern Sint16 lastbosshealth;
extern Sint16 nagtimer;
extern boolean copyprotectionfailed;

void SizeText(char *text, Uint16 *width, Uint16 *height);

/*
=============================================================================

            BM_DEMO DEFINITIONS

=============================================================================
*/

extern boolean scorescreenkludge;

#define SCR_PREVIEW      0
#define SCR_CREDITS      1
#define SCR_NOTSHAREWARE 2
#define SCR_TECHHELP     3

void CheckLastScan(void);
void ShowTitle(Uint16 timeout);
void ShowScreen(Sint16 num);
void RunDemo(Sint16 num);
void DrawHighScores(void);
void CheckHighScore(Sint32 score, Sint16 completed);
void ShowHighScores(void);

/*
=============================================================================

            BM_GAME DEFINITIONS

=============================================================================
*/

void FreeGraphics(void);
void NewGame(void);
boolean SaveTheGame(Sint16 handle);
boolean LoadTheGame(Sint16 handle);
void ResetGame(void);
void SetupGameLevel(boolean loadnow);
void StartDemoRecord(void);
void EndDemoRecord(void);
void GameLoop(void);

extern boolean singlestep, godmode;
extern exittype playstate;
extern gametype gamestate;
extern objtype *new, *player, *scoreobj;
extern Uint16 originxtilemax, originytilemax;
extern ControlInfo c;
extern objtype dummyobj;
extern boolean helpmessages, showscorebox;
extern boolean debugok;
extern boolean firebutton, fireheld, upheld;


void CheckKeys(void);
void StatusWindow(void);
void CenterActor(objtype *ob);
void ScrollScreen(objtype *ob);
void InitObjArray(void);
Sint16 GetNewObj(boolean usedummy);
void RemoveObj(objtype *ob);
void GivePoints(Uint16 points);
void StopMusic(void);
void StartMusic(Uint16 num);
void PlayLoop(void);

/*
=============================================================================

            BM_TEXT DEFINITIONS

=============================================================================
*/

void ShowHelpMessage(char far* msg);
void HelpScreens(void);
void EpisodeEndScreens(void);

/*
=============================================================================

            BM_STATE DEFINITIONS

=============================================================================
*/

extern Sint16 wallclip[8][16];

extern Sint16 xtry;
extern Sint16 ytry;
extern boolean playerkludgeclipcancel;

void MoveObjVert(objtype *ob, Sint16 ymove);
void MoveObjHoriz(objtype *ob, Sint16 xmove);
void PlayerBottomKludge(objtype *ob);
void PlayerTopKludge(objtype *ob);
void ClipToEnds(objtype *ob);
void ClipToSides(objtype *ob);
boolean CheckPosition(objtype *ob);
boolean StatePositionOk(objtype *ob, statetype far *state);

void ClipToWalls(objtype *ob);
void FullClipToWalls(objtype *ob);
void PushObj(objtype *ob);
void ClipToSpriteSide(objtype *push, objtype *solid);
void ClipToSpriteTop(objtype *push, objtype *solid);
void ClipToSprite(objtype *push, objtype *solid, boolean squish);
void ClipToPushBlock(objtype *push, objtype *solid, boolean squish);
Sint16 DoActor(objtype *ob, Sint16 numtics);
void StateMachine(objtype *ob);
void NewState(objtype *ob, statetype far *state);
void ChangeState(objtype *ob, statetype far *state);
boolean OnScreen(objtype *ob);
void DoGravity(objtype *ob);
void DoWeakGravity(objtype *ob);
void DoTinyGravity(objtype *ob);
void AccelerateX(objtype *ob, Sint16 dir, Sint16 maxspeed);
void AccelerateXv(objtype *ob, Sint16 dir, Sint16 maxspeed);
void AccelerateY(objtype *ob, Sint16 dir, Sint16 maxspeed);
void FrictionX(objtype *ob);
void FrictionY(objtype *ob);
void T_Projectile(objtype *ob);
void T_WeakProjectile(objtype *ob);
void ProjectileThink1(objtype *ob);
void T_Velocity(objtype *ob);
void SetReactThink(objtype *ob);
void C_Lethal(objtype *ob, objtype *hit);
void R_Draw(objtype *ob);
void R_Walk(objtype *ob);
void R_WalkNormal(objtype *ob);
void BadState(void);

extern statetype far sc_deadstate;
extern statetype far sc_badstate;

/*
=============================================================================

            BM_PLAY DEFINITIONS

=============================================================================
*/

void DamagePlayer(objtype* ob, Sint16 amount);
void KillPlayer(void);
void SnakeContact2(objtype* o1, objtype* o2);
void HandleRiding(objtype *ob);
void CheckInTiles(objtype *ob);
void PollControls(void);

extern char *levelnames[GAMELEVELS];

void ScanInfoPlane(void);

void ResetScoreBox(void);
void UpdateScoreBox(objtype *ob);

extern statetype far s_player_standing;

extern boolean playerdied;

#endif
