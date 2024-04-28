/* Copyright (C) 2024 Nikolai Wuttke-Hohendorf
 *
 * Based on reconstructed Commander Keen 4-6 Source Code
 * Copyright (C) 2021 K1n9_Duk3
 *
 * This file is primarily based on:
 * Wolfenstein 3-D Source Code
 * Copyright (C) 1992 id Software
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

TEXT FORMATTING COMMANDS
------------------------
^C<hex digit>       Change text color
^E[enter]       End of layout (all pages)
^G<y>,<x>,<pic>[enter]  Draw a graphic and push margins
^P[enter]       start new page, must be the first chars in a layout
^L<x>,<y>[ENTER]    Locate to a specific spot, x in pixels, y in lines

=============================================================================
*/

/*
=============================================================================

             LOCAL CONSTANTS

=============================================================================
*/

#define BACKCOLOR BLUE

#define WORDLIMIT 80
#define FONTHEIGHT 10
#define TOPMARGIN 10
#define BOTTOMMARGIN 10
#define LEFTMARGIN 10
#define RIGHTMARGIN 10
#define PICMARGIN 8
#define SPACEWIDTH 7
#define TEXTROWS ((200-TOPMARGIN-BOTTOMMARGIN)/FONTHEIGHT)
#define SCREENPIXWIDTH 320
#define SCREENMID (SCREENPIXWIDTH/2)

/*
=============================================================================

             LOCAL VARIABLES

=============================================================================
*/

boolean nagscreenshown = false;

Sint16 pagenum,numpages;
Uint16 leftmargin[TEXTROWS],rightmargin[TEXTROWS];
char far *text;
Uint16 rowon;
Sint16 picx,picy,picnum,picdelay;
boolean layoutdone;

Sint16 myhelpmenupos;


//===========================================================================

void ShowHelpMessage(char far* msg)
{
  if (!helpmessages || DemoMode) { return; }

  VW_FixRefreshBuffer();

  US_CenterWindow(35, 2);
  PrintY += 2;
  US_CPrint(msg);

  VW_UpdateScreen();
  VW_WaitVBL(50);
  IN_ClearKeysDown();
  IN_Ack();
  RF_ForceRefresh();
}


/*
=====================
=
= RipToEOL
=
=====================
*/

void RipToEOL(void)
{
  while (*text++ != '\n');
}


/*
=====================
=
= ParseNumber
=
=====================
*/

Sint16 ParseNumber(void)
{
  char c, buffer[80];
  char *bufptr;

//
// scan until a number is found
//
  c = *text;
  while (c < '0' || c > '9')
    c = *++text;

//
// copy the number out
//
  bufptr = buffer;
  do
  {
    *bufptr = c;
    bufptr++;
    text++;
    c = *text;
  } while (c >= '0' && c <= '9');
  *bufptr = 0;

  return atoi(buffer);
}


/*
=====================
=
= ParsePicCommand
=
= Call with text pointing just after a ^P
= Upon exit text points to the start of next line
=
=====================
*/

void ParsePicCommand(void)
{
  picy = ParseNumber();
  picx = ParseNumber();
  picnum = ParseNumber();
  RipToEOL();
}

void ParseTimedCommand(void)
{
  picy = ParseNumber();
  picx = ParseNumber();
  picnum = ParseNumber();
  picdelay = ParseNumber();
  RipToEOL();
}

/*
=====================
=
= TimedPicCommand
=
= Call with text pointing just after a ^P
= Upon exit text points to the start of next line
=
=====================
*/

void TimedPicCommand(void)
{
  ParseTimedCommand();

//
// update the screen, and wait for time delay
//
  VW_WaitVBL(1);
  VW_ScreenToScreen(bufferofs, displayofs, 40, 200);

//
// wait for time
//
  TimeCount = 0;
  while (picdelay > TimeCount)
  ;

//
// draw pic
//
  VWB_DrawPic(picx & ~7, picy, picnum);
}


/*
=====================
=
= HandleCommand
=
=====================
*/

void HandleCommand(void)
{
  Sint16 i,margin,top,bottom;
  Sint16 picwidth,picheight,picmid;

  switch (toupper(*(++text)))
  {
  case 'B':
    picy = ParseNumber();
    picx = ParseNumber();
    picwidth = ParseNumber();
    picheight = ParseNumber();
    VWB_Bar(picx, picy, picwidth, picheight, BACKCOLOR);
    RipToEOL();
    break;

  case 'P':   // ^P is start of next page, ^E is end of file
  case 'E':
    layoutdone = true;
    text--;
    break;

  case 'C':   // ^c<hex digit> changes text color
    i = toupper(*(++text));
    if (i >= '0' && i <= '9')
    {
      fontcolor = i + 0 - '0';
    }
    else if (i >= 'A' && i <= 'F')
    {
      fontcolor = i + 10 - 'A';
    }
    fontcolor ^= BACKCOLOR;
    text++;
    break;

  case 'L':
    py = ParseNumber();
    rowon = (py - FONTHEIGHT)/FONTHEIGHT;
    py = rowon * FONTHEIGHT + FONTHEIGHT;
    px = ParseNumber();
    while (*(text++) != '\n') // scan to end of line
    ;
    break;

  case 'T':   // ^Tyyy,xxx,ppp,ttt waits ttt tics, then draws pic
    TimedPicCommand();
    break;

  case 'G':   // ^Gyyy,xxx,ppp draws graphic
    ParsePicCommand();
    VWB_DrawPic(picx & ~7, picy, picnum);
    picwidth = pictable[picnum-STARTPICS].width * BYTEPIXELS;
    picheight = pictable[picnum-STARTPICS].height;
    picmid = picx + picwidth/2;
    //
    // adjust margins
    //
    if (picmid > SCREENMID)
    {
      margin = picx-PICMARGIN;      // new right margin
    }
    else
    {
      margin = picx+picwidth+PICMARGIN; // new left margin
    }
    top = (picy-TOPMARGIN)/FONTHEIGHT;
    if (top < 0)
    {
      top = 0;
    }
    bottom = (picy+picheight-TOPMARGIN)/FONTHEIGHT;
    if (bottom >= TEXTROWS)
    {
      bottom = TEXTROWS-1;
    }

    for (i=top; i<=bottom; i++)
    {
      if (picmid > SCREENMID)
      {
        rightmargin[i] = margin;
      }
      else
      {
        leftmargin[i] = margin;
      }
    }

    //
    // adjust this line if needed
    //
    if (leftmargin[rowon] > px)
    {
      px = leftmargin[rowon];
    }
    break;
  }
}


/*
=====================
=
= NewLine
=
=====================
*/

void NewLine(void)
{
  char c;

  if (++rowon == TEXTROWS)
  {
  //
  // overflowed the page, so skip until next page break
  //
    layoutdone = true;
    do
    {
      if (*text == '^')
      {
        c = toupper(text[1]);
        if (c == 'E' || c == 'P')
        {
          layoutdone = true;
          return;
        }
      }
      text++;
    } while (1);
  }
  px = leftmargin[rowon];
  py += FONTHEIGHT;
}


/*
=====================
=
= HandleCtrls
=
=====================
*/

void HandleCtrls(void)
{
  char c;

  c = *(text++);      // get the character and advance

  if (c == '\n')
  {
    NewLine();
    return;
  }
}

/*
=====================
=
= HandleWord
=
=====================
*/

void HandleWord(void)
{
  Uint16 wwidth, wheight, newpos, wordindex;
  char word[WORDLIMIT];

  //
  // copy the next word into [word]
  //
  word[0] = *(text++);
  wordindex = 1;
  while (*text > ' ')
  {
    word[wordindex] = *(text++);
    if (++wordindex == WORDLIMIT)
    {
      Quit("PageLayout: Word limit exceeded");
    }
  }
  word[wordindex] = 0;    // stick a null at end for C

  //
  // see if it fits on this line
  //
  VW_MeasurePropString(word, &wwidth, &wheight);
  
  while (rightmargin[rowon] < px+wwidth)
  {
    NewLine();
    if (layoutdone)
    {
      return;   // overflowed page
    }
  }

  //
  // print it
  //
  newpos = px+wwidth;
  VWB_DrawPropString(word);
  px = newpos;

  //
  // suck up any extra spaces
  //
  while (*text == ' ')
  {
    px += SPACEWIDTH;
    text++;
  }
}


static void DrawHighScores_HelpMenu(void)
{
  HighScore *entry;
  char* bufptr;

  Sint16 oldcolor;
  Uint16 i;
  Uint16 width, height;
  char buf[16];

  oldcolor = fontcolor;
  fontcolor = WHITE;

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

  fontcolor = oldcolor;
}


static void DrawNagScreenTimer(void)
{
  Sint16 oldcolor;
  oldcolor = fontcolor;

  VWB_DrawPic(16, 176, H_BOTTOMINFOPIC);

  strcpy(str, "Timer= ");

  if (nagtimer <= 0)
  {
    nagtimer = -1;
    strcat(str, "GO!");
    nagscreenshown = true;
    SD_PlaySound(SND_BEACONACTIVE);
  }
  else
  {
    itoa(nagtimer, str2, 10);
    strcat(str, str2);
    SD_PlaySound(SND_NAGTIMERTICK);
  }

  fontcolor = LIGHTMAGENTA;
  py = 186;
  px = 218;

  VWB_DrawPropString(str);

  fontcolor = oldcolor;
}

/*
=====================
=
= PageLayout
=
= Clears the screen, draws the pics on the page, and word wraps the text.
= Returns a pointer to the terminating command
=
=====================
*/

void PageLayout(boolean shownumber)
{
  Sint16 oldcolor, i;
  char c;

  oldcolor = fontcolor;

  fontcolor = YELLOW^BACKCOLOR;

//
// clear the screen
//
  VWB_Bar(0, 0, 320, 200, BACKCOLOR);
  VWB_DrawPic( 16, 0, H_TOPWINDOWPIC);
  VWB_DrawPic(  0, 0, H_LEFTWINDOWPIC);
  VWB_DrawPic(304, 0, H_RIGHTWINDOWPIC);
  if (shownumber)
  {
    VWB_DrawPic(16, 176, H_BOTTOMINFOPIC);
  }
  else
  {
    VWB_DrawPic(16, 192, H_TOPWINDOWPIC);
  }

  for (i=0; i<TEXTROWS; i++)
  {
    leftmargin[i] = LEFTMARGIN;
    rightmargin[i] = SCREENPIXWIDTH-RIGHTMARGIN;
  }

  px = LEFTMARGIN;
  py = TOPMARGIN;
  rowon = 0;
  layoutdone = false;

//
// make sure we are starting layout text (^P first command)
//
  while (*text <= ' ')
  {
    text++;
  }
  if (*text != '^' || toupper(*(++text)) != 'P')
  {
    Quit("PageLayout: Text not headed with ^P");
  }
  while (*(text++) != '\n')
  ;

//
// process text stream
//
  do
  {
    c = *text;
    if (c == '^')
    {
      HandleCommand();
    }
    else if (c <= ' ')
    {
      HandleCtrls();
    }
    else
    {
      HandleWord();
    }
  } while (!layoutdone);

  pagenum++;

  if (shownumber)
  {
    strcpy(str, "Pg ");
    itoa(pagenum, str2, 10);
    strcat(str, str2);
    strcat(str, " of ");
    itoa(numpages, str2, 10);
    strcat(str, str2);
    fontcolor = LIGHTRED^BACKCOLOR;
    py = 186;
    px = 218;
    VWB_DrawPropString(str);
  }

  fontcolor = oldcolor;
}

//===========================================================================

/*
=====================
=
= BackPage
=
= Scans for a previous ^P
=
=====================
*/

void BackPage(void)
{
  pagenum--;
  do
  {
    text--;
    if (text[0] == '^' && toupper(text[1]) == 'P')
    {
      return;
    }
  } while (1);
}

//===========================================================================


/*
=====================
=
= CacheLayoutGraphics
=
= Scans an entire layout file (until a ^E) marking all graphics used, and
= counting pages, then caches the graphics in
=
=====================
*/
void CacheLayoutGraphics(void)
{
  char  far *bombpoint, far *textstart;
  char  ch;

  textstart = text;
  bombpoint = text+30000;
  numpages = pagenum = 0;

  CA_MarkGrChunk(H_TOPWINDOWPIC);
  CA_MarkGrChunk(H_LEFTWINDOWPIC);
  CA_MarkGrChunk(H_RIGHTWINDOWPIC);
  CA_MarkGrChunk(H_BOTTOMINFOPIC);

  do
  {
    if (*text == '^')
    {
      ch = toupper(*(++text));
      if (ch == 'P')    // start of a page
      {
        numpages++;
      }
      if (ch == 'E')    // end of file, so load graphics and return
      {
        CA_CacheMarks(NULL);
        text = textstart;
        return;
      }
      if (ch == 'G')    // draw graphic command, so mark graphics
      {
        ParsePicCommand();
        CA_MarkGrChunk(picnum);
      }
      if (ch == 'T')    // timed draw graphic command, so mark graphics
      {
        ParseTimedCommand();
        CA_MarkGrChunk(picnum);
      }
    }
    else
    {
      text++;
    }

  } while (text < bombpoint);

  Quit("CacheLayoutGraphics: No ^E to terminate file!");
}

//===========================================================================

/*
=================
=
= HelpMenu
=
=================
*/
Sint16 HelpMenu(void)
{
  CursorInfo cursor;
  ControlInfo control;
  Sint16 ydelta;
  Uint16 key;

  VWB_Bar(0, 0, 320, 200, BACKCOLOR);

  CA_CacheGrChunk(H_HELPPIC);
  CA_CacheGrChunk(H_HANDPIC);
  CA_CacheGrChunk(H_TOPWINDOWPIC);
  CA_CacheGrChunk(H_LEFTWINDOWPIC);
  CA_CacheGrChunk(H_RIGHTWINDOWPIC);

  VWB_DrawPic( 16,   0, H_TOPWINDOWPIC);
  VWB_DrawPic(  0,   0, H_LEFTWINDOWPIC);
  VWB_DrawPic(304,   0, H_RIGHTWINDOWPIC);
  VWB_DrawPic( 16, 192, H_TOPWINDOWPIC);
  VWB_DrawPic( 88,   8, H_HELPPIC);

  ydelta = 0;
  IN_ClearKeysDown();
  do
  {
    if (myhelpmenupos < 0)
    {
      myhelpmenupos = 0;
    }
    else if (myhelpmenupos > 4)
    {
      myhelpmenupos = 4;
    }
    VWB_DrawPic(56, 24*myhelpmenupos+56, H_HANDPIC);
    VW_UpdateScreen();
    VWB_Bar(56, 24*myhelpmenupos+56, 31, 24, BACKCOLOR);
    IN_ReadControl(0, &control);
    IN_ReadCursor(&cursor);
    if (LastScan)
    {
      key = LastScan;
      IN_ClearKeysDown();
      switch (key)
      {
      case sc_UpArrow:
        myhelpmenupos--;
        break;
      case sc_DownArrow:
        myhelpmenupos++;
        break;
      case sc_Enter:
        VW_ClearVideo(BACKCOLOR);
        return myhelpmenupos;
      case sc_Escape:
        VW_ClearVideo(BACKCOLOR);
        return -1;
      }
    }
    ydelta += cursor.y;
    if (cursor.button0 || cursor.button1 || control.button0 || control.button1)
    {
      VW_ClearVideo(BACKCOLOR);
      return myhelpmenupos;
    }
    if (ydelta < -40)
    {
      ydelta += 40;
      myhelpmenupos--;
    }
    else if (ydelta > 40)
    {
      ydelta -= 40;
      myhelpmenupos++;
    }
  } while (1);
}

/*
=================
=
= HelpScreens
=
=================
*/
void HelpScreens(void)
{
  static Uint16 layouttable[] =
  {
    T_ORDERART,
    T_HELPART,
    T_STORYART,
    T_CONTRART,
    T_SCORESART,
    T_NAGSCREENART
  };

  Uint16 olddisplayofs, oldbufferofs, oldfontnumber;
  Sint16 pos;
  Uint16 oldmusic;
  boolean newpage;
  register Uint16 temp;

  oldfontnumber = fontnumber;
  olddisplayofs = displayofs;
  oldbufferofs = bufferofs;
  fontnumber = 0;
  oldmusic = curmusic;

  EGAMAPMASK(15);

  CA_UpLevel();
  CA_SetGrPurge();
  VW_ClearVideo(BACKCOLOR);

  RF_FixOfs();
  bufferofs = 0;
  displayofs = 0x8000;
  VW_SetScreen(displayofs, 0);

  StartMusic(HELPSCREENSMUSIC);
  TimeCount = 0;
  nagscreenshown = false;

  do
  {
    if (nagtimer == -1)
    {
      pos = HelpMenu();
    }
    else
    {
      pos = 5;
    }

    if (pos == 4)
    {
      showmenuhighscores = true;
    }

    VW_ClearVideo(BACKCOLOR);

    if (pos == -1)
    {
      CA_DownLevel();
      IN_ClearKeysDown();
      bufferofs = oldbufferofs;
      displayofs = olddisplayofs;
      fontnumber = oldfontnumber;
      VW_ClearVideo(BACKCOLOR);
      RF_FixOfs();

      SD_FadeOutMusic();
      while (SD_MusicPlaying());

      StopMusic();
      StartMusic(oldmusic);
      return;
    }

    pos = layouttable[pos];
    CA_CacheGrChunk(pos);
    text = grsegs[pos];
    CacheLayoutGraphics();

    newpage = true;
    while (true)
    {
      if (newpage)
      {
        newpage = false;
        PageLayout(true);

        if (showmenuhighscores == true)
        {
          DrawHighScores_HelpMenu();
          showmenuhighscores = false;
        }

        VW_SetScreen(bufferofs, 0);
        temp = displayofs;
        displayofs = bufferofs;
        bufferofs = temp;
      }

      LastScan = 0;

      //
      // Shareware episode nag timer
      //
      while (!LastScan)
      {
        if (TimeCount >= 70 && nagtimer != -1)
        {
          LastScan = sc_Bad - 1;
        }
      }

      if (TimeCount >= 70 && nagtimer > -1)
      {
        temp = displayofs;
        displayofs = bufferofs;
        bufferofs = temp;

        TimeCount = 0;
        DrawNagScreenTimer();

        VW_SetScreen(bufferofs, 0);

        temp = displayofs;
        displayofs = bufferofs;
        bufferofs = temp;

        if (nagtimer >= 0)
        {
          nagtimer--;
        }
      }

      switch (LastScan)
      {
      case sc_UpArrow:
      case sc_LeftArrow:
      case sc_PgUp:
        if (pagenum > 1)
        {
          BackPage();
          BackPage();
          newpage = true;
        }
        break;

      case sc_DownArrow:
      case sc_RightArrow:
      case sc_PgDn:
        if (pagenum < numpages)
        {
          newpage = true;
        }
        break;

      case sc_Escape:
        if (nagtimer == -1)
          goto stopLoop;
        break;
      }
    }

stopLoop:
    MM_FreePtr(&grsegs[pos]);
    IN_ClearKeysDown();

    if (nagscreenshown == true)
    {
      nagscreenshown = false;

      CA_DownLevel();
      IN_ClearKeysDown();
      bufferofs = oldbufferofs;
      displayofs = olddisplayofs;
      fontnumber = oldfontnumber;
      VW_ClearVideo(BACKCOLOR);
      RF_FixOfs();

      SD_FadeOutMusic();
      while (SD_MusicPlaying());

      StopMusic();
      break;
    }
  } while (true);

  while (false);
}


//===========================================================================

/*
=================
=
= EpisodeEndScreens
=
=================
*/
void EpisodeEndScreens(void)
{
  char _seg *textseg;
  Sint16 i;

  VW_ClearVideo(BACKCOLOR);
  RF_FixOfs();
  CA_UpLevel();
  CA_SetGrPurge();
  CA_CacheGrChunk(H_FLASHARROW2PIC);
  CA_CacheGrChunk(H_FLASHARROW1PIC);

  CA_CacheGrChunk(T_ENDART);
  textseg = grsegs[T_ENDART];

  text = textseg;
  CacheLayoutGraphics();

  StartMusic(ENDINGMUSIC);

  while (pagenum < numpages)
  {
    PageLayout(false);
    IN_ClearKeysDown();
    VW_SetScreen(bufferofs, 0);

    do
    {
      VWB_DrawPic(298, 184, H_FLASHARROW1PIC);
      for (i=0; i<TickBase; i++)
      {
        if (IN_IsUserInput())
        {
          goto nextpage;
        }
        VW_WaitVBL(1);
      }

      VWB_DrawPic(298, 184, H_FLASHARROW2PIC);
      for (i=0; i<TickBase; i++)
      {
        if (IN_IsUserInput())
        {
          goto nextpage;
        }
        VW_WaitVBL(1);
      }
    } while (1);

nextpage:
    ; // Borland C++ 2.0 needs a semicolon here...
  }

  StopMusic();

  MM_FreePtr(&grsegs[T_ENDART]);
  MM_FreePtr(&grsegs[H_FLASHARROW1PIC]);
  MM_FreePtr(&grsegs[H_FLASHARROW2PIC]);
  CA_DownLevel();
  IN_ClearKeysDown();
  VW_ClearVideo(BACKCOLOR);
  RF_FixOfs();
  CA_FreeGraphics();
}
