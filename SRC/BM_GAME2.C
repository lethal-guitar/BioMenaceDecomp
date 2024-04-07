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

#include "BM_DEF.H"


extern boolean GameIsDirty;
extern Uint16 extravbls;

/*
=============================================================================

             GLOBAL VARIABLES

=============================================================================
*/

exittype playstate;
gametype gamestate;

objtype *new, *player, *scoreobj;

Uint16 originxtilemax;
Uint16 originytilemax;

ControlInfo c;

objtype dummyobj;

boolean button0held, button1held, upheld, fireheld;


/*
=============================================================================

             LOCAL VARIABLES

=============================================================================
*/

Uint16 centerlevel;

Uint16 objectcount;
objtype objarray[MAXACTORS];
objtype *lastobj;
objtype *objfreelist;

Sint16 inactivateleft;
Sint16 inactivateright;
Sint16 inactivatetop;
Sint16 inactivatebottom;

extern Sint16 supermoveTimeout;
extern Uint16 invincible;
extern Uint8 unktime;


Sint16 MUSIC_TABLE[21] = {
  17,
  1,
  2,
  17,
  4,
  5,
  10,
  6,
  7,
  8,
  9,
  10,
  11,
  12,
  13,
  14,
  15,
  16,
  -1,
};



//===========================================================================

/*
==================
=
= PrintNumbers
=
==================
*/

void PrintNumbers(Sint16 x, Sint16 y, Sint16 maxlen, Sint16 basetile, Sint32 number)
{
  register Sint16 i;
  Sint16 len;
  char buffer[20];

  ltoa(number, buffer, 10);
  len = strlen(buffer);
  i = maxlen;
  while (i>len)
  {
    VWB_DrawTile8(x, y, basetile);
    i--;
    x += 8;
  }
  while (i>0)
  {
    VWB_DrawTile8(x, y, basetile+buffer[len-i]+(1-'0'));
    i--;
    x += 8;
  }
}

/*
==================
=
= DrawStatusWindow
=
==================
*/

#define BACKCOLOR LIGHTGRAY
#define TEXTBACK WHITE
#define NUMBERBACK BLACK

//seg27
char far PAUSED_LABEL[] = "PAUSED";

//seg28
char far LOCATION_LABEL[] = "LOCATION";

//seg29
char far SCORE_LABEL[] = "SCORE";

//seg30
char far EXTRA_LABEL[] = "EXTRA", far KEYCARDS_LABEL[] = "KEYCARDS";

//seg31
char far SHARDS_LABEL[] = "SHARDS";

//seg32
char far LEVEL_LABEL[] = "LEVEL";

char far EASY_LABEL[] = "Easy";
char far NORMAL_LABEL[] = "Normal";

//seg35
char far HARD_LABEL[] = "Hard";

char far KEYS_LABEL[] = "KEYS";
char far AMMO_LABEL[] = "AMMO";
char far LIVES_LABEL[] = "LIVES";

//seg36
char far CLIPS_LABEL[] = "CLIPS";

//seg37
char far GEMS_LABEL[] = "GEMS";
char far QUESTIONMARKS[] = "???";

//seg38
char far INSUFFICIENT_MUSIC_MEM[] = "Insufficient memory\nfor background music!";

char far FORGOT_SCIENTIST[] =
  "Oh NO! You forgot to rescue the\n"
  "scientist being held prisoner\n"
  "here. You'd better go get him!\n\n";


void DrawStatusWindow(void)
{
  Sint16 off, x, y, w, h, i;
  Uint16 width, height;
  char buffer[50];

  x = 64;
  y = 16;
  w = 184;
  h = 144;

  VWB_DrawTile8(x, y, 11);
  VWB_DrawTile8(x, y+h, 17);

  for (i=x+8; i<=x+w-8; i+=8)
  {
    VWB_DrawTile8(i, y, 12);
    VWB_DrawTile8(i, y+h, 18);
  }

  VWB_DrawTile8(i, y, 13);
  VWB_DrawTile8(i, y+h, 19);

  for (i=y+8; i<=y+h-8; i+=8)
  {
    VWB_DrawTile8(x,   i, 14);
    VWB_DrawTile8(x+w, i, 16);
  }

  VWB_Bar(72, 24, 176, 136, BACKCOLOR);

  PrintY = 28;
  WindowX = 80;
  WindowW = 160;
  US_CPrint(LOCATION_LABEL);
  VWB_Bar(79, 38, 162, 20, TEXTBACK);

  if (gamestate.mapon < 20)
  {
    _fstrcpy(buffer, levelnames[gamestate.mapon]);
  }
  else
  {
    _fstrcpy(buffer, "Secret Level");
  }

  SizeText(buffer, &width, &height);
  PrintY = (20-height)/2 + 40 - 2;
  US_CPrint(buffer);

  PrintY = 61;
  WindowX = 80;
  WindowW = 64;
  US_CPrint(SCORE_LABEL);
  VWB_Bar(79, 71, 66, 10, NUMBERBACK);
  PrintNumbers(80, 72, 8, 0, gamestate.score);

  PrintY = 61;
  WindowX = 176;
  WindowW = 64;
  US_CPrint(EXTRA_LABEL);
  VWB_Bar(175, 71, 66, 10, NUMBERBACK);
  PrintNumbers(176, 72, 8, 0, gamestate.nextextra);

  PrintY = 85;
  WindowX = 176;
  WindowW = 64;
  US_CPrint(LEVEL_LABEL);
  VWB_Bar(175, 95, 66, 10, TEXTBACK);

  PrintY = 96;
  WindowX = 176;
  WindowW = 64;

  switch (gamestate.difficulty)
  {
    case gd_Easy:
      US_CPrint(EASY_LABEL);
      break;

    case gd_Normal:
      US_CPrint(NORMAL_LABEL);
      break;

    case gd_Hard:
      US_CPrint(HARD_LABEL);
      break;
  }

  PrintX = 80;
  PrintY = 96;
  _fstrcpy(buffer, SHARDS_LABEL);
  US_Print(buffer);
  VWB_Bar(127, 95, 34, 10, NUMBERBACK);

  if (gamestate.blueshard)
  {
    VWB_DrawTile8(128, 96, 24);
  }

  if (gamestate.greenshard)
  {
    VWB_DrawTile8(136, 96, 25);
  }

  if (gamestate.redshard)
  {
    VWB_DrawTile8(144, 96, 26);
  }

  if (gamestate.cyanshard)
  {
    VWB_DrawTile8(152, 96, 27);
  }

  PrintX = 80;
  PrintY = 112;
  VWB_Bar(79, 111, 34, 10, NUMBERBACK);
  VWB_DrawTile8(84, 112, 22);
  PrintNumbers(96, 112, 2, 0, gamestate.keyitems.keys);

  PrintX = 128;
  PrintY = 112;
  VWB_Bar(127, 111, 34, 10, NUMBERBACK);
  VWB_DrawTile8(132, 112, 23);
  PrintNumbers(144, 112, 2, 0, gamestate.keyitems.keycards);

  PrintX = 184;
  PrintY = 112;
  _fstrcpy(buffer, GEMS_LABEL);
  US_Print(buffer);
  VWB_Bar(215, 111, 18, 10, NUMBERBACK);
  PrintNumbers(216, 112, 2, 0, gamestate.gems);

  PrintX = 152;
  PrintY = 128;
  US_Print("ITEMS");
  VWB_Bar(191, 127, 50, 10, NUMBERBACK);

  if (gamestate.var14)
  {
    VWB_DrawTile8(192, 128, 56);
  }

  if (gamestate.specialkey)
  {
    VWB_DrawTile8(200, 128, 28);
  }

  if (gamestate.nukestate == ns_collected)
  {
    VWB_DrawTile8(208, 128, 29);
  }

  if (gamestate.radpill)
  {
    VWB_DrawTile8(216, 128, 30);
  }

  if (gamestate.exitkey)
  {
    VWB_DrawTile8(224, 128, 32);
  }

  if (gamestate.secretlevelgem)
  {
    VWB_DrawTile8(232, 128, 65);
  }

  PrintX = 80;
  PrintY = 128;
  _fstrcpy(buffer, CLIPS_LABEL);
  US_Print(buffer);
  VWB_Bar(119, 127, 26, 10, NUMBERBACK);

  if (gamestate.rapidfire == true && gamestate.ammoinclip > 3)
  {
    PrintNumbers(128, 128, 2, 0, gamestate.clips + 1);
  }
  else
  {
    PrintNumbers(128, 128, 2, 0, gamestate.clips);
  }

  // draw the tiles for "PRESS A KEY":
  for (i = 0; i < 10; i++)
  {
    VWB_DrawTile8((i + 15)*8, 140, i+36);
    VWB_DrawTile8((i + 15)*8, 148, i+46);
  }
}


/*
==================
=
= StatusWindow
=
==================
*/

void StatusWindow(void)
{
  if (unused3 &&
      Keyboard[sc_J] && Keyboard[sc_I] && Keyboard[sc_M])
  {
    US_CenterWindow(20, 2);
    PrintY += 2;
    US_Print(" Debug keys active!");
    VW_UpdateScreen();
    IN_Ack();
    debugok = true;
  }

  WindowX = 0;
  WindowW = 320;
  WindowY = 0;
  WindowH = 200;
  DrawStatusWindow();
  VW_UpdateScreen();
  IN_ClearKeysDown();
  IN_Ack();
}

//===========================================================================

/*
==================
=
= CenterActor
=
==================
*/

void CenterActor(register objtype *ob)
{
  register Uint16 orgx;
  Uint16 orgy;

  centerlevel = 140;
  if (ob->x < 152*PIXGLOBAL)
  {
    orgx = 0;
  }
  else
  {
    orgx = ob->x - 152*PIXGLOBAL;
  }

  if (ob->bottom < 140*PIXGLOBAL)
  {
    orgy = 0;
  }
  else
  {
    orgy = ob->bottom - 140*PIXGLOBAL;
  }

  if (!scorescreenkludge)
  {
    RF_NewPosition(orgx, orgy);
  }

  //
  // update limits for onscreen and inactivate checks
  //
  originxtilemax = (originxtile + PORTTILESWIDE) - 1;
  originytilemax = (originytile + PORTTILESHIGH) - 1;
  inactivateleft = originxtile - INACTIVATEDIST;
  if (inactivateleft < 0)
  {
    inactivateleft = 0;
  }
  inactivateright = originxtilemax + INACTIVATEDIST;
  if (inactivateright < 0)
  {
    inactivateright = 0;
  }
  inactivatetop = originytile - INACTIVATEDIST;
  if (inactivatetop < 0)
  {
    inactivatetop = 0;
  }
  inactivatebottom = originytilemax + INACTIVATEDIST;
  if (inactivatebottom < 0)
  {
    inactivatebottom = 0;
  }
}

//===========================================================================

/*
==================
=
= ScrollScreen
=
= Scroll if player is nearing an edge
= Set playstate to ex_completed
=
==================
*/

void ScrollScreen(objtype *ob)
{
  Sint16 xscroll, yscroll, pix, speed;
  Uint16 bottom;

  if (gamestate.mapon == 13)
    return;

  //
  // walked off edge of map?
  //
  if (ob->left < originxmin || ob->right > originxmax + 320*PIXGLOBAL)
  {
    playstate = ex_completed;
    return;
  }

  //
  // fallen off bottom of world?
  //
  if (ob->bottom > originymax + 13*TILEGLOBAL && ob->health > 0)
  {
    ob->y -= ob->bottom - (originymax + 13*TILEGLOBAL);
    godmode = false;
    DamagePlayer(ob, 50);
    return;
  }

  xscroll=yscroll=0;

  if (ob->x < originxglobal + 8*TILEGLOBAL)
  {
    xscroll = ob->x - (originxglobal + 8*TILEGLOBAL);
  }
  else if (ob->x > originxglobal + 10*TILEGLOBAL)
  {
    xscroll = ob->x - (originxglobal + 10*TILEGLOBAL);
  }

  if (Keyboard[sc_PgUp] || (Keyboard[sc_RShift] && c.yaxis == -1))
  {
    if (centerlevel+tics > 157)
    {
      pix = 157-centerlevel;
    }
    else
    {
      pix = tics;
    }
    centerlevel += pix;
    yscroll = CONVERT_PIXEL_TO_GLOBAL(-pix);
  }
  else if (Keyboard[sc_PgDn] || (Keyboard[sc_RShift] && c.yaxis == 1))
  {
    if (centerlevel-tics < 43)
    {
      pix = centerlevel + -43;
    }
    else
    {
      pix = tics;
    }
    centerlevel -= pix;
    yscroll = CONVERT_PIXEL_TO_GLOBAL(pix);
  }

  if (ob->state->contact == SnakeContact2)
  {
    yscroll += ob->ymove;

    bottom = originyglobal + yscroll +
      CONVERT_PIXEL_TO_GLOBAL(centerlevel);
    if (ob->bottom == bottom)
    {
      // player didn't move, no additional scrolling
      goto noscroll;
    }

    if (ob->bottom < bottom)
    {
      pix = bottom - ob->bottom;
    }
    else
    {
      pix = ob->bottom - bottom;
    }
    speed = CONVERT_PIXEL_TO_GLOBAL(pix) >> 7;
    if (speed > 0x30)
    {
      speed = 0x30;
    }
    speed *= tics;
    if (speed < 0x10)
    {
      if (pix < 0x10)
      {
        speed = pix;
      }
      else
      {
        speed = 0x10;
      }
    }
    if (ob->bottom < bottom)
    {
      yscroll -= speed;
    }
    else
    {
      yscroll += speed;
    }
  }
  else
  {
    centerlevel = 140;
  }

noscroll:
  pix = (ob->bottom-32*PIXGLOBAL)-(originyglobal+yscroll);
  if (pix < 0)
  {
    yscroll += pix;
  }
  pix = (ob->bottom+32*PIXGLOBAL)-(originyglobal+yscroll+200*PIXGLOBAL);
  if (pix > 0)
  {
    yscroll += pix;
  }

  if (xscroll == 0 && yscroll == 0)
    return;

  //
  // don't scroll more than one tile per frame
  //
  if (xscroll >= 0x100)
  {
    xscroll = 0xFF;
  }
  else if (xscroll <= -0x100)
  {
    xscroll = -0xFF;
  }
  if (yscroll >= 0x100)
  {
    yscroll = 0xFF;
  }
  else if (yscroll <= -0x100)
  {
    yscroll = -0xFF;
  }
  RF_Scroll(xscroll, yscroll);

  //
  // update limits for onscreen and inactivate checks
  //
  originxtilemax = (originxtile + PORTTILESWIDE) - 1;
  originytilemax = (originytile + PORTTILESHIGH) - 1;
  inactivateleft = originxtile - INACTIVATEDIST;
  if (inactivateleft < 0)
  {
    inactivateleft = 0;
  }
  inactivateright = originxtilemax + INACTIVATEDIST;
  if (inactivateright < 0)
  {
    inactivateright = 0;
  }
  inactivatetop = originytile - INACTIVATEDIST;
  if (inactivatetop < 0)
  {
    inactivatetop = 0;
  }
  inactivatebottom = originytilemax + INACTIVATEDIST;
  if (inactivatebottom < 0)
  {
    inactivatebottom = 0;
  }
}

//===========================================================================


/*
#############################################################################

          The objarray data structure

#############################################################################

Objarray contains structures for every actor currently playing.  The structure
is accessed as a linked list starting at *player, ending when ob->next ==
NULL.  GetNewObj inserts a new object at the end of the list, meaning that
if an actor spawns another actor, the new one WILL get to think and react the
same frame.  RemoveObj unlinks the given object and returns it to the free
list, but does not damage the objects ->next pointer, so if the current object
removes itself, a linked list following loop can still safely get to the
next element.

<backwardly linked free list>

#############################################################################
*/


/*
=========================
=
= InitObjArray
=
= Call to clear out the entire object list, returning them all to the free
= list.  Allocates a special spot for the player.
=
=========================
*/

void InitObjArray(void)
{
  Sint16 i;

  for (i=0; i<MAXACTORS; i++)
  {
    objarray[i].prev = &objarray[i+1];
    objarray[i].next = NULL;
  }

  objarray[MAXACTORS-1].prev = NULL;

  objfreelist = &objarray[0];
  lastobj = NULL;

  objectcount = 0;

//
// give the player and score the first free spots
//
  GetNewObj(false);
  player = new;
  GetNewObj(false);
  scoreobj = new;
}

//===========================================================================

/*
=========================
=
= GetNewObj
=
= Sets the global variable new to point to a free spot in objarray.
= The free spot is inserted at the end of the liked list
=
= When the object list is full, the caller can either have it bomb out or
= return a dummy object pointer that will never get used
=
= Returns -1 when list was full, otherwise returns 0.
=
=========================
*/

Sint16 GetNewObj(boolean usedummy)
{
  if (!objfreelist)
  {
    if (usedummy)
    {
      new = &dummyobj;
      return -1;
    }
    Quit("GetNewObj: No free spots in objarray!");
  }
  new = objfreelist;
  objfreelist = new->prev;
  memset(new, 0, sizeof(*new));
  if (lastobj)
  {
    lastobj->next = new;
  }
  new->prev = lastobj;  // new->next is allready NULL from memset

  new->active = ac_yes;
  new->needtoclip = cl_midclip;
  lastobj = new;

  objectcount++;
  return 0;
}

//===========================================================================

/*
=========================
=
= RemoveObj
=
= Add the given object back into the free list, and unlink it from it's
= neighbors
=
=========================
*/

void RemoveObj(objtype *ob)
{
  if (ob == player && gamestate.mapon == 13)
    return;

  if (ob == player)
    Quit("RemoveObj: Tried to remove the player!");

  //
  // erase it from the refresh manager
  //
  RF_RemoveSprite(&ob->sprite);

  //
  // fix the next object's back link
  //
  if (ob == lastobj)
  {
    lastobj = ob->prev;
  }
  else
  {
    ob->next->prev = ob->prev;
  }

  //
  // fix the previous object's forward link
  //
  ob->prev->next = ob->next;

  //
  // add it back in to the free list
  //
  ob->prev = objfreelist;
  objfreelist = ob;
}

//==========================================================================

/*
====================
=
= GivePoints
=
= Grants extra lives at 20k,40k,80k,160k,320k
=
====================
*/

void GivePoints(Uint16 points)
{
  gamestate.score += points;
  if (!DemoMode && gamestate.score >= gamestate.nextextra)
  {
    gamestate.lives++;
    gamestate.nextextra *= 2;
  }
}

//==========================================================================


/*
=================
=
= StopMusic
=
=================
*/

void StopMusic(void)
{
  // Hmm... TODO: Comment
}

//==========================================================================

/*
=================
=
= StartMusic
=
=================
*/

void StartMusic(Uint16 num)
{
  Sint16 song;
  boolean wasfaded;

  curmusic = num;

  if (num >= 20 && num <= 24)
  {
    num = 6;
  }

  if (num >= ARRAYLENGTH(MUSIC_TABLE) && num != 0xFFFF)
  {
    Quit("StartMusic() - bad level number");
  }

  SD_MusicOff();

  song = MUSIC_TABLE[num];

  if (song == -1 || MusicMode != smm_AdLib)
  {
    return;
  }

  MM_BombOnError(false);
  CA_CacheAudioChunk(STARTMUSIC+song);
  MM_BombOnError(true);
  if (mmerror)
  {
    mmerror = false;
    if (!DemoMode)
    {
      US_CenterWindow(20, 8);
      PrintY += 20;
      US_CPrint(INSUFFICIENT_MUSIC_MEM);
      VW_UpdateScreen();
      wasfaded = screenfaded;
      if (wasfaded)
      {
        VW_SetDefaultColors();
      }
      IN_ClearKeysDown();
      IN_UserInput(3*TickBase, false);
      if (wasfaded)
      {
        VW_FadeOut();
      }
    }
  }
  else
  {
    SD_StartMusic((MusicGroup far *)audiosegs[STARTMUSIC+song]);
  }
}

//==========================================================================


/*
===================
=
= PlayLoop
=
===================
*/

void PlayLoop(void)
{
  objtype* obj;
  objtype *check;
  Sint16 var2;

  var2 = 25;
  StartMusic(gamestate.mapon);
  ingame = true;
  playstate = ex_stillplaying;
  upheld = button0held = button1held = fireheld = 0;

  CenterActor(player);

  if (DemoMode)
  {
    US_InitRndT(false);
  }
  else
  {
    US_InitRndT(true);
  }

  TimeCount = lasttimecount = tics = 3;

  ResetScoreBox();

  do
  {
    supermoveTimeout--;

    PollControls();

    if (unktime > 0)
    {
      unktime--;
      if (unktime <= 0)
      {
        unktime = 0;
      }
    }

    //
    // go through state changes and propose movements
    //
    for (obj=player; obj; obj=obj->next)
    {
      if (!obj->active && obj->tileright >= originxtile-1
        && obj->tileleft <= originxtilemax+1 && obj->tiletop <= originytilemax+1
        && obj->tilebottom >= originytile-1)
      {
        obj->needtoreact = true;
        obj->active = ac_yes;
      }

      if (obj->active)
      {
        if (obj->tileright < inactivateleft
          || obj->tileleft > inactivateright
          || obj->tiletop > inactivatebottom
          || obj->tilebottom < inactivatetop)
        {
          if (obj->active == ac_removable)
          {
            RemoveObj(obj);
            continue;
          }
          else if (obj->active != ac_allways)
          {
            if (US_RndT() < tics*2 || screenfaded || loadedgame)
            {
              RF_RemoveSprite(&obj->sprite);
              obj->active = ac_no;
              continue;
            }
          }
        }

        StateMachine(obj);
      }
    }

    if (gamestate.riding)
    {
      HandleRiding(player);
    }

    //
    // check for and handle collisions between objects
    //
    for (obj=player; obj; obj=obj->next)
    {
      if (obj->active)
      {
        for (check=obj->next; check; check=check->next)
        {
          if (
            check->active &&
            obj->right > check->left && obj->left < check->right
            && obj->top < check->bottom && obj->bottom > check->top)
          {
            if (obj->state->contact)
            {
              obj->state->contact(obj, check);
            }
            if (check->state->contact)
            {
              check->state->contact(check, obj);
            }
            if (obj->obclass == nothing)  //useless -- obclass is NOT set to nothing by RemoveObj
            {
              break;
            }
          }
        }
      }
    }

    //
    // check intiles
    //
    CheckInTiles(player);

    //
    // react to whatever happened, and post sprites to the refresh manager
    //
    for (obj=player; obj; obj=obj->next)
    {
      if (!obj->active)
      {
        continue;
      }

      if (obj->dmgflash)
      {
        obj->dmgflash = obj->dmgflash - tics;
        if (obj->dmgflash < 0)
        {
          obj->dmgflash = 0;
        }
      }

      if (obj->tilebottom >= mapheight-1)
      {
        if (obj == player)
        {
          playstate = ex_died;
        }
        else
        {
          RemoveObj(obj);
        }
        continue;
      }
      if (obj->needtoreact && obj->state->react)
      {
        obj->needtoreact = false;
        obj->state->react(obj);
      }
    }

    // Blink player sprite during invulnerability frames
    if (invincible)
    {
      invincible--;

      if (invincible & 1)
      {
        RF_RemoveSprite(&player->sprite);
      }
      else
      {
        RF_PlaceSprite(
          &player->sprite, player->x, player->y, player->shapenum,
          spritedraw, 1);
      }

      if ((invincible > 100 && invincible < 102) ||
          (invincible < 100 && curmusic != gamestate.mapon))
      {
        StartMusic(gamestate.mapon);
      }

      if (invincible <= 0)
      {
        invincible = 0;
      }
    }

    if (player->health > 0)
    {
      CheckInTiles(player);
    }

    if (player->temp7 > 0)
    {
      player->temp7--;

      if (player->temp7 <= 0)
      {
        player->temp7 = 0;
      }
    }

    //
    // scroll the screen and update the score box
    //
    ScrollScreen(player);
    UpdateScoreBox(scoreobj);
    if (loadedgame)
    {
      loadedgame = false;
    }

    //
    // update the screen and calculate the number of tics it took to execute
    // this cycle of events (for adaptive timing of next cycle)
    //
    RF_Refresh();

    //
    // single step debug mode
    //
    if (singlestep)
    {
      VW_WaitVBL(14); //reduces framerate to 5 fps on VGA or 4.3 fps on EGA cards
      lasttimecount = TimeCount;
    }

    //
    // extra VBLs debug mode
    //
    if (extravbls)
    {
      VW_WaitVBL(extravbls);
    }

    //
    // handle user inputs
    //
    if (DemoMode == demo_Playback)
    {
      if (gamestate.mapon != 13 && gamestate.mapon != 24 &&
          !screenfaded && IN_IsUserInput())
      {
        playstate = ex_completed;
        if (LastScan != sc_F1)
        {
          LastScan = sc_Space;
        }
      }
    }
    else if (DemoMode == demo_PlayDone)
    {
      playstate = ex_completed;
    }
    else
    {
      CheckKeys();
    }

    // Practice mode
    if (practicetimer == 0)
    {
      practicetimer = -1;
      NewGame();
      gamestate.mapon = practicerestoremap;
      playstate = ex_resetgame;
      gamestate.score = 0;
      US_ControlPanel(0);
      ingame = false;
      GameIsDirty = false;
    }
    else if (practicetimer > 0)
    {
      practicetimer--;
    }
  } while (playstate == ex_stillplaying);

  ingame = false;
  StopMusic();
}
