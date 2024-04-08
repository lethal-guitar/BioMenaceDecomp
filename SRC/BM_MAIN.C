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

// BM_MAIN.C
/*
=============================================================================

                    BIOMENACE

          An Apogee Software production

=============================================================================
*/

#include "BM_DEF.H"

/*
=============================================================================

             GLOBAL VARIABLES

=============================================================================
*/

boolean tedlevel;
Uint16 tedlevelnum;

char str[80], str2[20];
boolean storedemo;

// Boss health divisor - see UpdateScoreBox() in BM_PLAY2.C
Sint16 hbardivisor;

Uint16 curmusic;

boolean unused3 = false;
boolean showmenuhighscores = false;
Uint16 unused1 = 0;
boolean practicerestoremap = 0;
Sint16 practicetimer = -1;
Uint16 playerrestorex = 0;
Uint16 playerrestorey = 0;
Sint16 bosshealth = -1;
Sint16 lastbosshealth = -1;
Sint16 nagtimer = -1;
Uint16 unused2 = 0;


/*
=============================================================================

             LOCAL VARIABLES

=============================================================================
*/

//===========================================================================

/*
=====================
=
= SizeText
=
= Calculates width and height of a string that contains line breaks
= (Note: only the height is ever used, width is NOT calculated correctly)
=
=====================
*/

void SizeText(char *text, Uint16 *width, Uint16 *height)
{
  register char *ptr;
  char c;
  Uint16 w, h;
  char strbuf[80];

  *width = *height = 0;
  ptr = &strbuf[0];
  while ((c=*(text++)) != '\0')
  {
    *(ptr++) = c;
    if (c == '\n' || !*text)
    {
      USL_MeasureString(strbuf, &w, &h);  // BUG: strbuf may not have a terminating '\0' at the end!
      *height += h;
      if (*width < w)
      {
        *width = w;
      }
      ptr = &strbuf[0];
    }
  }
}

//===========================================================================

/*
==========================
=
= ShutdownId
=
= Shuts down all ID_?? managers
=
==========================
*/

void ShutdownId(void)
{
  US_Shutdown();
  SD_Shutdown();
  IN_Shutdown();
  RF_Shutdown();
  VW_Shutdown();
  CA_Shutdown();
  MM_Shutdown();
}


//===========================================================================

/*
==========================
=
= InitGame
=
= Load a few things right away
=
==========================
*/

void InitGame(void)
{
  void MML_UseSpace (Uint16 segstart, Uint16 seglength);

  Uint16 segstart,seglength;
  Sint16 i;

  US_TextScreen();
  _setcursortype(_NOCURSOR);

  MM_Startup();
  VW_Startup();
  RF_Startup();
  IN_Startup();
  SD_Startup();
  US_Startup();

  US_UpdateTextScreen();

  CA_Startup();
  US_Setup();

  US_SetLoadSaveHooks(&LoadTheGame, &SaveTheGame, &ResetGame);

  CA_ClearMarks();

  CA_MarkGrChunk(STARTFONT);
  CA_MarkGrChunk(STARTTILE8);
  CA_MarkGrChunk(STARTTILE8M);

  CA_CacheMarks(NULL);

  MM_SetLock(&grsegs[STARTFONT], true);
  MM_SetLock(&grsegs[STARTTILE8], true);
  MM_SetLock(&grsegs[STARTTILE8M], true);

  fontcolor = WHITE;

  US_FinishTextScreen();

//
// reclaim the memory from the linked in text screen
//
  segstart = FP_SEG(&introscn);
  seglength = 4000/16;
  if (FP_OFF(&introscn))
  {
    segstart++;
    seglength--;
  }
  MML_UseSpace (segstart,seglength);

  VW_SetScreenMode(GRMODE);
  VW_ColorBorder(BLACK);
  VW_ClearVideo(BLACK);
}

//===========================================================================

/*
==========================
=
= Quit
=
==========================
*/

void Quit(char *error)
{
  Uint16 finscreen;

  if (!error)
  {
    CA_SetAllPurge();
    CA_CacheGrChunk(ORDERSCREEN);
    finscreen = (Uint16)grsegs[ORDERSCREEN];
  }

  // BUG: VW_ClearVideo may brick the system if screenseg is 0
  // (i.e. VW_SetScreenMode has not been executed) - this may
  // happen if the code runs into an error during InitGame
  // (EMS/XMS errors, files not found etc.)
  VW_ClearVideo(BLACK);
  VW_SetLineWidth(40);

  ShutdownId();
  if (error && *error)
  {
    puts(error);
    if (tedlevel)
    {
      getch();
      execlp("TED5.EXE", "TED5.EXE", "/LAUNCH", NULL);
    }
    exit(1);
  }

  if (!NoWait)
  {
    movedata(finscreen, 0, 0xB800, 0, 3780);
    textmode(C80);
    textcolor(WHITE);
    textbackground(BLACK);
    gotoxy(1, 24);
  }

  exit(0);
}

//===========================================================================

/*
==================
=
= TEDDeath
=
==================
*/

void TEDDeath(void)
{
  ShutdownId();
  execlp("TED5.EXE", "TED5.EXE", "/LAUNCH", NULL);
  // BUG: should call exit(1); here in case starting TED5 fails
}

//===========================================================================

/*
==================
=
= CheckMemory
=
==================
*/

void CheckMemory(void)
{
  Uint16 finscreen;

  if (mminfo.nearheap+mminfo.farheap+mminfo.EMSmem+mminfo.XMSmem >= MINMEMORY)
    return;

  CA_CacheGrChunk (OUTOFMEM);
  finscreen = (Uint16)grsegs[OUTOFMEM];
  ShutdownId();

  movedata(finscreen,7,0xb800,0,3780);
  textmode(C80);
  textcolor(WHITE);
  textbackground(BLACK);
  gotoxy(1,24);

  exit(1);
}

//===========================================================================

/*
=====================
=
= DemoLoop
=
=====================
*/

void DemoLoop(void)
{
  static char *ParmStrings[] = {"easy", "normal", "hard", ""};

  register Sint16 i, state;
  Sint16 level;
  boolean unusedvar = true;
  boolean donefirstrun = false;

//
// check for launch from ted
//
  if (tedlevel)
  {
    NewGame();
    CA_LoadAllSounds();
    gamestate.mapon = tedlevelnum;
    restartgame = gd_Normal;
    for (i = 1;i < _argc;i++)
    {
      if ( (level = US_CheckParm(_argv[i],ParmStrings)) == -1)
        continue;

      restartgame = level+gd_Easy;
      break;
    }
    GameLoop();
    TEDDeath();
  }

//
// demo loop
//
  state = 0;
  playstate = ex_stillplaying;
  while (1)
  {
    switch (state++)
    {
    case 0:
      RunDemo(1);
      IN_ClearKeysDown();
      LastScan = 0;

      if (!donefirstrun)
      {
        // TODO
        StartMusic(18);
        donefirstrun = true;
        ShowScreen(SCR_TECHHELP);
      }
      break;

    case 1:
      IN_ClearKeysDown();
      LastScan = 0;
      // TODO
      StartMusic(11);
      ShowTitle(40);
      break;

    case 2:
      // TODO
      if (curmusic != 11)
      {
        StartMusic(11);
      }

      ShowScreen(SCR_CREDITS);
      break;

    case 3:
      // TODO
      if (curmusic != 11)
      {
        StartMusic(11);
      }
      ShowScreen(SCR_PREVIEW);
      break;

    case 4:
      ShowHighScores();
      break;

    case 5:
      RunDemo(2);
      break;

    case 6:
      RunDemo(3);
      state = 0;
      break;
    }

    CheckLastScan();

    while (playstate == ex_resetgame || playstate == ex_loadedgame)
    {
      GameLoop();

      if (playstate == ex_resetgame || playstate == ex_loadedgame)
      {
        continue; // don't show title screen, go directly to GameLoop();
      }
      ///////////////
      // this is completely useless:
      if (playstate == ex_resetgame || playstate == ex_loadedgame)
      {
        continue;
      }
      ///////////////
    }
  }
}

//===========================================================================

#if (GRMODE == EGAGR)
/*
=====================
=
= CheckCutFile
=
=====================
*/

#define FILE_GR1 GREXT"1."EXTENSION
#define FILE_GR2 GREXT"2."EXTENSION
#define FILE_GRAPH GREXT"GRAPH."EXTENSION

static void CheckCutFile(void)
{
  register Sint16 ohandle, ihandle;
  Sint16 handle;
  Sint32 size;
  void far *buffer;

  if ( (handle = open(FILE_GRAPH, O_BINARY|O_RDONLY)) != -1)
  {
    close(handle);
    return;
  }
  puts("Combining "FILE_GR1" and "FILE_GR2" into "FILE_GRAPH"...");
  if (rename(FILE_GR1, FILE_GRAPH) == -1)
  {
    puts("Can't rename "FILE_GR1"!");
    exit(1);
  }
  if ( (ohandle = open(FILE_GRAPH, O_BINARY|O_APPEND|O_WRONLY)) == -1)
  {
    puts("Can't open "FILE_GRAPH"!");
    exit(1);
  }
  lseek(ohandle, 0, SEEK_END);
  if ( (ihandle = open(FILE_GR2, O_BINARY|O_RDONLY)) == -1)
  {
    puts("Can't find "FILE_GR2"!");
    exit(1);
  }
  size = filelength(ihandle);
  buffer = farmalloc(32000);
  while (size)
  {
    if (size > 32000)
    {
      CA_FarRead(ihandle, buffer, 32000);
      CA_FarWrite(ohandle, buffer, 32000);
      size -= 32000;
    }
    else
    {
      CA_FarRead(ihandle, buffer, size);
      CA_FarWrite(ohandle, buffer, size);
      size = 0;
    }
  }
  farfree(buffer);
  close(ohandle);
  close(ihandle);
  unlink(FILE_GR2);
}
#endif

//===========================================================================

/*
=====================
=
= CheckCopyProtection
=
=====================
*/

static boolean CheckCopyProtection(void)
{
  int i;
  Sint16 handle;
  char c1, c2;

  const char EXPECTED_FILE_ID_DIZ[443] =
    "\xdb\xdb\xdb\xdb\xb2\xb1\xb0  THIS IS PIRATED SOFTWARE!  \xb0\xb1\xb2\xdb\xdb\xdb\xdb  "
    "\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb  "
    "THIS FILE IS NOT SHAREWARE -- it is ILLEGAL  "
    "and forbidden to upload this copyrighted  "
    "software on bulletin boards.  If you see  "
    "this message on a BBS, please request that  "
    "the Sysop remove this software IMMEDIATELY.  "
    "\xdb\xb2\xb1\xb0 OR CONTACT APOGEE: (214) 278-5655 \xb0\xb1\xb2\xdb  "
    "IT IS ILLEGAL TO GET THIS FILE FROM A BBS!  "
    "\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb  ";
  char actualtext[sizeof(EXPECTED_FILE_ID_DIZ)];


  if ((handle = open("file_id.diz", O_BINARY | O_RDONLY))  == -1)
  {
    close(handle);
    return true;
  }

  if (filelength(handle) != sizeof(EXPECTED_FILE_ID_DIZ) - 1)
  {
    close(handle);
    return true;
  }

  if (read(handle, actualtext, sizeof(EXPECTED_FILE_ID_DIZ) - 1) == -1)
  {
    close(handle);
    return true;
  }
  else
  {
    close(handle);
  }

  for (i = 0; i < sizeof(EXPECTED_FILE_ID_DIZ) - 1; i++)
  {
    c1 = EXPECTED_FILE_ID_DIZ[i];
    c2 = actualtext[i];

    if (c2 != '\xD' && c2 != '\xA' && c1 != c2)
    {
      return true;
    }
  }

  return false;
}

//===========================================================================


/*
==========================
=
= main
=
==========================
*/

void main(void)
{
  static char *ParmStrings[] = {"sewerman", ""};

  CheckCutFile();

  storedemo = false;

  InitGame();
  CheckMemory();

  gamestate.var44 = 0;

  _setcursortype(_NORMALCURSOR);

  DemoLoop();
  Quit("Demo loop exited???");
}
