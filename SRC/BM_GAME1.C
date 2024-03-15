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

/*
=============================================================================

             GLOBAL VARIABLES

=============================================================================
*/

extern Uint16 word_391BC;
extern Uint16 word_399FA;
extern Uint16 word_3FA56;
extern Uint16 word_3FA66;
extern Uint8 byte_3FA6E;

Uint16 fadecount;
Sint16 mapon;

/*
=============================================================================

             LOCAL VARIABLES

=============================================================================
*/

const char FILE_ID_MISSING[] =
  "Critical file FILE_ID.DIZ missing\n"
  "or modified.  If you purchased the\n"
  "game from Apogee simply reinstall\n"
  "the game.  You can call Apogee at\n"
  "(214) 278-5655 or refer to\n"
  "Ordering Info for more details.\n";

char far EASY[] = "easy";
char far NORMAL[] = "normal";
char far HARD[] = "hard";
char far GAME_OVER[] = "Game Over!";
char far NOT_ENOUGH_MEM[] = "Not enough memory\nto load game!";
char far DIDNT_MAKE_IT_PAST[] = "You didn't make it past";
char far TRY_AGAIN[] = "Try Again";
char far INSUFFICIENT_MEM[] = "Insufficient memory\nto load level!";
char far ONE_MOMENT[] = "One moment";
char far GOD_MODE_ON[] = "God mode ON";
char far GOD_MODE_OFF[] = "God mode OFF";
char far FREE_ITEMS[] = "Free items!";
char far JUMP_CHEAT_ON[] = "Jump cheat ON";
char far JUMP_CHEAT_OFF[] = "Jump cheat OFF";
char far WARP_LEVEL_PROMPT[] = "  Warp to which level(1-17): ";
char far PRACTICE_LEVEL_PROMPT[] = "  Practice which level (1-11): ";

void FadeAndUnhook(void);

//===========================================================================

/*
============================
=
= FreeGraphics
=
============================
*/

void FreeGraphics(void)
{
  Sint16 i;
  for (i=STARTSPRITES; i<STARTSPRITES+NUMSPRITES; i++)
  {
    if (grsegs[i])
    {
      MM_SetPurge(&grsegs[i], PURGE_LAST);
    }
  }
  for (i=STARTTILE16; i<STARTEXTERNS; i++)
  {
    if (grsegs[i])
    {
      MM_SetPurge(&grsegs[i], PURGE_LAST);
    }
  }
}

//===========================================================================

/*
=====================
=
= NewGame
=
= Set up new game to start from the beginning
=
=====================
*/

void NewGame(void)
{
  if (playstate != ex_loadedgame)
  {
    gamestate.mapon = 0;
    gamestate.score = 0;
    gamestate.nextextra = 20000;
    gamestate.lives = 3;
    gamestate.gems = 0;
    gamestate.nuke = false;
    gamestate.var16 = 0;
  }

  gamestate.maxhealth = 4;
  gamestate.var20 = 0;
  gamestate.var23 = 0;
  memset(gamestate.var1, 0, sizeof(gamestate.var1));
  gamestate.var21 = 0;
  gamestate.var22 = 0;
  gamestate.blueshard = false;
  gamestate.greenshard = false;
  gamestate.redshard = false;
  gamestate.cyanshard = false;
  gamestate.exitkey = false;
  gamestate.var14 = 0;
  gamestate.specialkey = false;
  gamestate.radpill = false;
  gamestate.var24 = 0;
  gamestate.secretlevelgem = false;
}

//===========================================================================

/*
============================
=
= GameOver
=
============================
*/

void GameOver(void)
{
  VW_FixRefreshBuffer();
  US_CenterWindow(16, 3);
  US_PrintCentered("GAME OVER");
  VW_UpdateScreen();
  IN_ClearKeysDown();
  IN_UserInput(4*TickBase, false);
}

//===========================================================================

/*
============================
=
= ResetGame
=
============================
*/

void ResetGame(void)
{
  Sint16 practicelevel;
  boolean inputfailed;

  NewGame();
  ca_levelnum--;
  ca_levelbit >>= 1;
  CA_ClearMarks();
  ca_levelbit <<= 1;
  ca_levelnum++;

  if (restartgame != gd_Continue)
  {
    if (word_3A77C == true)
    {
      word_389A0 = gamestate.mapon;

      VW_FixRefreshBuffer();
      US_CenterWindow(26, 3);
      PrintY += 6;

      _fstrcpy(str, PRACTICE_LEVEL_PROMPT);
      US_Print(str);
      VW_UpdateScreen();
      inputfailed = !US_LineInput(px, py, str, NULL, true, 2, 0);

      if (!inputfailed)
      {
        practicelevel = atoi(str);

        if (practicelevel > 0 && practicelevel <= 11)
        {
          gamestate.mapon = practicelevel - 1;
        }
      }

      word_3A77C = false;
      word_389A2 = 500;
    }
    else
    {
      if (word_389A2 >= 0)
      {
        word_389A2 = -1;
      }
    }

    playstate = ex_resetgame;
  }
  else if (loadedgame)
  {
    playstate = ex_loadedgame;
    word_389A2 = -1;
  }

  VW_FadeOut();
}

//===========================================================================

/*
============================
=
= SaveTheGame
=
============================
*/

boolean SaveTheGame(Sint16 handle)
{
  gametype state;

  gamestate.riding = NULL;
  word_389A2 = -1;
  word_3A77C = 0;

  memcpy(&state, &gamestate, sizeof(gamestate));
  memset(&state.keyitems, 0, sizeof(state.keyitems));
  state.blueshard = false;
  state.greenshard = false;
  state.redshard = false;
  state.cyanshard = false;
  state.exitkey = false;
  state.var14 = 0;
  state.specialkey = false;
  state.radpill = false;
  state.var15 = 0;
  state.var24 = 0;
  state.var22 = 0;
  state.var21 = 0;
  state.var23 = 0;
  memset(&state.var1, 0, sizeof(state.var1));

  switch (state.difficulty)
  {
    case gd_Easy:
      state.maxhealth = 8;
      break;

    case gd_Normal:
      state.maxhealth = 4;
      break;

    case gd_Hard:
      state.maxhealth = 4;
      break;

    default:
      state.maxhealth = 4;
      break;
  }

  word_3FA66 = 0;
  if (!CA_FarWrite(handle, (byte far *)&state, sizeof(state)))
    return false;

  return true;
}

//===========================================================================

/*
============================
=
= LoadTheGame
=
============================
*/

boolean LoadTheGame(Sint16 handle)
{
  if (!CA_FarRead(handle, (byte far *)&gamestate, sizeof(gamestate)))
    return false;

  playstate = ex_loadedgame;
  player->health = gamestate.maxhealth;
  word_389A2 = -1;
  word_3A77C = 0;
  return true;
}

//===========================================================================

/*
==========================
=
= DelayedFade
=
= Fades out and latches FadeAndUnhook onto the refresh
=
==========================
*/

void DelayedFade(void)
{
  VW_FadeOut();
  fadecount = 0;
  RF_SetRefreshHook(&FadeAndUnhook);
}

/*
==========================
=
= FadeAndUnhook
=
= Latch this onto the refresh so the screen only gets faded in after two
= refreshes.  This lets all actors draw themselves to both pages before
= fading the screen in.
=
==========================
*/

void FadeAndUnhook(void)
{
  if (++fadecount == 2)
  {
    VW_FadeIn();
    RF_SetRefreshHook(NULL);
    TimeCount = lasttimecount;  // don't adaptively time the fade
  }
}

//===========================================================================


/*
==========================
=
= SetupGameLevel
=
= Load in map mapon and cache everything needed for it
=
==========================
*/

void SetupGameLevel(boolean loadnow)
{
  playerrestorex = 0;
  playerrestorey = 0;

  SD_FadeOutMusic();
  CA_SetAllPurge();

//
// randomize if not a demo
//
  if (DemoMode)
  {
    US_InitRndT(false);
    gamestate.difficulty = gd_Normal;
  }
  else
  {
    US_InitRndT(true);
  }

//
// load the level header and three map planes
//
  CA_CacheMap(gamestate.mapon);

//
// let the refresh manager set up some variables
//
  RF_NewMap();

//
// decide which graphics are needed and spawn actors
//
  CA_ClearMarks();
  ScanInfoPlane();
  RF_MarkTileGraphics();

//
// have the caching manager load and purge stuff to make sure all marks
// are in memory
//
  CA_LoadAllSounds();
  if (loadnow)
  {
    if (scorescreenkludge || gamestate.mapon == 13)
    {
      CA_CacheMarks(NULL);
    }
    else if (gamestate.mapon >= 20)
    {
      CA_CacheMarks("Secret Level");
    }
    else if (DemoMode)
    {
      CA_CacheMarks("DEMO");
    }
    else
    {
      CA_CacheMarks(levelnames[mapon]);
    }
  }

  if (loadnow)
  {
    DelayedFade();
  }
}

//===========================================================================

boolean RespawnPlayer(void)
{
  if (playerrestorex > 0 && playerrestorey > 0)
  {
    player->y = playerrestorey;
    player->x = playerrestorex;
    player->priority = 1;

    player->needtoclip = false;
    ChangeState(player, &s_player_standing);

    player->needtoclip = true;
    CenterActor(player);

    ytry = 15;
    player->obclass = playerobj;
    player->active = ac_yes;
    player->needtoclip = true;

    switch (gamestate.difficulty)
    {
      case gd_Easy:
        player->health = 8;
        break;

      case gd_Normal:
        player->health = 4;
        break;

      case gd_Hard:
        player->health = 2;
        break;

      default:
        player->health = 4;
        break;
    }

    gamestate.maxhealth = player->health;
    word_3FA56 = 50;
    byte_3FA6E = 0;
    return true;
  }

  return false;
}

//==========================================================================

/*
============================
=
= GameLoop
=
= A game has just started (after the cinematic or load game)
=
============================
*/

void GameLoop(void)
{
  register Uint16 oldbufferofs;

#define ENTER_SECRET_LEVEL(n)  \
  playstate = ex_stillplaying; \
  RunDemo(4); \
  gamestate.mapon = (n - 1); \
  gamestate.secretlevelgem = false;


start:
  if (playstate != ex_loadedgame)
  {
    gamestate.difficulty = restartgame;
  }

  restartgame = gd_Continue;

restart:
  SetupGameLevel(true);

loaded:
  word_3FA66 = 0;
  word_399FA = 0;
  word_391BC = 0;
  word_389A8 = 999;
  SD_WaitSoundDone();


  PlayLoop();


  if (playstate == ex_died && gamestate.lives >= 0 && RespawnPlayer())
  {
    playstate = ex_stillplaying;
    goto loaded;
  }

  gamestate.maxhealth = player->health;
  memset(&gamestate.keyitems, 0, sizeof(gamestate.keyitems));
  gamestate.blueshard = false;
  gamestate.greenshard = false;
  gamestate.redshard = false;
  gamestate.cyanshard = false;
  gamestate.exitkey = false;
  gamestate.var14 = 0;
  gamestate.specialkey = false;
  gamestate.radpill = false;
  gamestate.var15 = 0;
  gamestate.var24 = 0;
  gamestate.var22 = 0;
  gamestate.var21 = 0;
  gamestate.var23 = 0;
  memset(gamestate.var1, 0, sizeof(gamestate.var1));

  word_3FA66 = 0;

  VW_FixRefreshBuffer();

  if (tedlevel)
  {
    if (playstate == ex_loadedgame)
    {
      goto loaded;
    }
    else if (playstate == ex_died)
    {
      goto restart;
    }
    else
    {
      TEDDeath();
    }
  }

  switch (playstate)
  {
  case ex_resetgame:
    goto start;

  case ex_loadedgame:
    goto start;

  case ex_completed:
    // Shareware nag timer
    if (gamestate.mapon >= 4 && gamestate.mapon < 11 && !debugok)
    {
      nagtimer = (gamestate.mapon - 4) * 5 + 30;

      if (nagtimer > 60)
      {
        nagtimer = 60;
      }

      HelpScreens();
    }

    // Return from secret bonus level
    if (gamestate.mapon > 13)
    {
      switch (gamestate.mapon)
      {
        case 20:
          gamestate.mapon = 2;
          break;

        case 21:
          gamestate.mapon = 5;
          break;

        case 22:
          gamestate.mapon = 8;
          break;

        case 23:
          gamestate.mapon = 10;
          break;
      }
    }

    // Enter secret bonus level
    if (gamestate.secretlevelgem == true)
    {
      switch (gamestate.mapon)
      {
        case 2:
          ENTER_SECRET_LEVEL(20);
          break;

        case 5:
          ENTER_SECRET_LEVEL(21);
          break;

        case 8:
          ENTER_SECRET_LEVEL(22);
          break;

        case 10:
          ENTER_SECRET_LEVEL(23);
          break;
      }
    }

    // Advance to next level
    gamestate.mapon++;

    if (gamestate.mapon == 12)
    {
      // Game beaten!
      FreeGraphics();
      RF_FixOfs();
      VW_FixRefreshBuffer();
      EpisodeEndScreens();
      CheckHighScore(gamestate.score, 0);
      return;
    }

    if (storedemo && mapon == 2)
    {
      // Demo recording finished
      IN_ClearKeysDown();
      return;
    }

    oldbufferofs = bufferofs;
    bufferofs = displayofs;
    US_CenterWindow(15, 2);
    PrintY += 2;
    US_CPrint("One moment...\n\n");
    bufferofs = oldbufferofs;
    break;

  case ex_abortgame:
    IN_ClearKeysDown();
    StopMusic();
    CA_SetAllPurge();
    return;
  }

  if (gamestate.lives >= 0)
  {
    goto restart;
  }

  StopMusic();
  CA_SetAllPurge();
  GameOver();
  CheckHighScore(gamestate.score, mapon);

#undef ENTER_SECRET_LEVEL
}
