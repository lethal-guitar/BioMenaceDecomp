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

boolean scorescreenkludge;

/*
=============================================================================

             LOCAL VARIABLES

=============================================================================
*/

//===========================================================================

/*
============================
=
= CheckLastScan
=
============================
*/

void CheckLastScan(void)
{
  if (LastScan)
  {
    if (storedemo)
    {
      playstate = ex_resetgame;
      restartgame = gd_Normal;
      IN_ClearKeysDown();
      NewGame();
      return;
    }

    US_ControlPanel(0);
    ResetScoreBox();
  }
}


//===========================================================================

/*
============================
=
= ShowTitle
=
============================
*/

void ShowTitle(Uint16 timeout)
{
  VW_FadeOut();
  RF_FixOfs();

  panadjust = 0;

#ifdef SHAREWARE
  CA_CacheGrChunk(TITLESHAREWAREPIC);
  VWB_DrawPic(0, 0, TITLESHAREWAREPIC);
#else
  CA_CacheGrChunk(TITLEPIC);
  VWB_DrawPic(0, 0, TITLEPIC);
#endif

  VW_SetScreen(displayofs, 0);
  VW_ScreenToScreen(bufferofs, displayofs, 42, 224);
  VW_FadeIn();

  IN_UserInput(timeout*TickBase, false);

  CA_ClearMarks();
  CheckLastScan();
}

//===========================================================================

/*
============================
=
= ShowScreen
=
============================
*/

void ShowScreen(Sint16 num)
{
  VW_FadeOut();
  RF_FixOfs();

  panadjust = 0;

  if (num == 0)
  {
    CA_CacheGrChunk(PREVIEWPIC);
    VWB_DrawPic(0, 0, PREVIEWPIC);
  }
  else if (num == 1)
  {
    CA_CacheGrChunk(CREDITSPIC);
    VWB_DrawPic(0, 0, CREDITSPIC);
  }
  else if (num == 2)
  {
    CA_CacheGrChunk(NOTSHAREWAREPIC);
    VWB_DrawPic(0, 0, NOTSHAREWAREPIC);
  }
  else if (num == 3)
  {
    CA_CacheGrChunk(TECHHELPPIC);
    VWB_DrawPic(0, 0, TECHHELPPIC);
  }

  VW_SetScreen(displayofs, 0);
  VW_ScreenToScreen(bufferofs, displayofs, 42, 224);
  VW_FadeIn();

  if (num < 3)
  {
    IN_UserInput(6*TickBase, false);
  }
  else
  {
    IN_ClearKeysDown();
    IN_Ack();
  }

  CA_ClearMarks();
  CheckLastScan();
}

//===========================================================================

/*
============================
=
= RunDemo
=
============================
*/

void RunDemo(Sint16 num)
{
  Sint16 basenum;
  Uint16 far *demodata;
  gametype statecopy;

  basenum = num;

  if (basenum != 4)
  {
    NewGame();
  }
  else
  {
    memcpy(&statecopy, &gamestate, sizeof(gamestate));
  }

  num += DEMO0;
  CA_CacheGrChunk(num);
  demodata = grsegs[num];
  gamestate.mapon = demodata[0];
  DemoSize = demodata[1];
  MM_GetPtr(&(memptr)DemoBuffer, DemoSize);
  MM_SetLock(&(memptr)DemoBuffer, true);
  _fmemcpy(DemoBuffer, ((char _seg *)grsegs[num])+4, DemoSize);
  MM_FreePtr(&grsegs[num]);
  IN_StartDemoPlayback(DemoBuffer, DemoSize);
  SetupGameLevel(true);
  if (scorescreenkludge)
  {
    DrawHighScores();
  }
  PlayLoop();
  IN_StopDemo();
  MM_FreePtr(&(memptr)DemoBuffer);
  VW_FixRefreshBuffer();
  CA_ClearMarks();

  if (basenum != 1 && basenum != 4)
  {
    CheckLastScan();
  }

  if (basenum == 4)
  {
    memcpy(&gamestate, &statecopy, sizeof(gamestate));
  }
}

//===========================================================================

/*
============================
=
= DrawHighScores
=
============================
*/

void DrawHighScores(void)
{
  Uint16 i, n;
  Uint16 width, height;
  HighScore *entry;
  Uint16 oldbufferofs;
  char buf[16], *bufptr;

  RF_NewPosition(0, 0);
  oldbufferofs = bufferofs;
  bufferofs = masterofs;

  for (i=0, entry=&Scores[0]; i<MaxScores; i++, entry++)
  {
    PrintY = i*16 + HIGHSCORE_TOP;
    PrintX = HIGHSCORE_LEFT;
    US_Print(entry->name);
    ultoa(entry->score, buf, 10);
    for (bufptr=buf; *bufptr; bufptr++)
    {
      *bufptr = *bufptr + 81;
    }
    USL_MeasureString(buf, &width, &height);
    PrintX = HIGHSCORE_RIGHT - width;
    US_Print(buf);
  }

  fontcolor = WHITE;  // back to default color
  bufferofs = oldbufferofs;
}

//===========================================================================

/*
============================
=
= CheckHighScore
=
============================
*/

void CheckHighScore(Sint32 score, Sint16 completed)
{
  Uint16 i;
  Sint16 index;
  HighScore entry;

  strcpy(entry.name, ""); //Note: 'entry.name[0] = 0;' would be more efficient
  entry.score = score;
  entry.completed = completed;
  for (i=0, index=-1; i<MaxScores; i++)
  {
    if (Scores[i].score < entry.score ||
      (Scores[i].score == entry.score && Scores[i].completed < entry.completed))
    {
      register Uint16 n;

      n=MaxScores;
      while (--n > i)
      {
        Scores[n] = Scores[n-1];
      }
      Scores[i] = entry;
      index = i;
      HighScoresDirty = true;
      break;
    }
  }

  if (index != -1)
  {
    scorescreenkludge = true;
    gamestate.mapon = HIGHSCORE_MAP;
    SetupGameLevel(true);
    DrawHighScores();
    RF_Refresh();
    RF_Refresh();
    PrintY = i*16 + HIGHSCORE_TOP;
    PrintX = HIGHSCORE_LEFT;
    US_LineInput(PrintX, PrintY, Scores[index].name, NULL, true, MaxHighName, 112);
    scorescreenkludge = false;
  }
}

//===========================================================================

/*
============================
=
= ShowHighScores
=
============================
*/

void ShowHighScores(void)
{
  scorescreenkludge = true;
  IN_ClearKeysDown();
  RunDemo(0);
  scorescreenkludge = false;
}
