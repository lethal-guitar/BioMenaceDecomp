/* Copyright (C) 2024 Nikolai Wuttke-Hohendorf
 *
 * Based on reconstructed Commander Keen 4-6 Source Code
 * Copyright (C) 2021 K1n9_Duk3
 *
 * This file is primarily based on:
 * Catacomb 3-D Source Code
 * Copyright (C) 1993-2014 Flat Rock Software
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

//
//  ID Engine
//  ID_US.h - Header file for the User Manager
//  v1.0d1
//  By Jason Blochowiak
//

#ifndef __TYPES__
#include "ID_Types.h"
#endif

#ifndef __ID_US__
#define __ID_US__

#ifdef  __DEBUG__
#define __DEBUG_UserMgr__
#endif

//#define HELPTEXTLINKED

#define MaxX  320
#define MaxY  200

#define MaxHelpLines  500

#define MaxHighName 57
#define MaxScores 8

typedef struct
    {
      char  name[MaxHighName + 1];
      long  score;
      word  completed;
    } HighScore;

#define MaxGameName   32
#define MaxSaveGames  6
typedef struct
    {
      char  signature[4];
      word  *oldtest;
      boolean present;
      char  name[MaxGameName + 1];
    } SaveGame;

#define MaxString 128 // Maximum input string size

typedef struct
    {
      int x,y,
        w,h,
        px,py;
    } WindowRec;  // Record used to save & restore screen windows

typedef enum
    {
      gd_Continue,
      gd_Easy,
      gd_Normal,
      gd_Hard
    } GameDiff;

//  Hack import for TED launch support
extern  boolean   tedlevel;
extern  word    tedlevelnum;
extern  void    TEDDeath(void);

extern  boolean   ingame,   // Set by game code if a game is in progress
          abortgame,  // Set if a game load failed
          loadedgame, // Set if the current game was loaded
          NoWait,
          HighScoresDirty;
extern  char    *abortprogram;  // Set to error msg if program is dying
extern boolean wantspractice;
extern  GameDiff  restartgame;  // Normally gd_Continue, else starts game
extern  word    PrintX,PrintY;  // Current printing location in the window
extern  word    WindowX,WindowY,// Current location of window
          WindowW,WindowH;// Current size of window

extern  boolean   Button0,Button1,
          CursorBad;
extern  ScanCode firescan;
extern  int     CursorX,CursorY;

extern  void    (*USL_MeasureString)(char far *,word *,word *),
          (*USL_DrawString)(char far *);

extern  boolean   (*USL_SaveGame)(int),(*USL_LoadGame)(int);
extern  void    (*USL_ResetGame)(void);
extern  SaveGame  Games[MaxSaveGames];
extern  HighScore Scores[];

#define US_HomeWindow() {PrintX = WindowX; PrintY = WindowY;}

extern  void  US_Startup(void),
        US_Setup(void),
        US_Shutdown(void),
        US_InitRndT(boolean randomize),
        US_SetLoadSaveHooks(boolean (*load)(int),
                  boolean (*save)(int),
                  void (*reset)(void)),
        US_TextScreen(void),
        US_UpdateTextScreen(void),
        US_FinishTextScreen(void),
        US_ControlPanel(int unkown),
        US_DrawWindow(word x,word y,word w,word h),
        US_CenterWindow(word,word),
        US_SaveWindow(WindowRec *win),
        US_RestoreWindow(WindowRec *win),
        US_ClearWindow(void),
        US_SetPrintRoutines(void (*measure)(char far *,word *,word *),
                  void (*print)(char far *)),
        US_PrintCentered(char *s),
        US_CPrint(char far *s),
        US_CPrintLine(char *s),
        US_Print(char *s),
        US_PrintUnsigned(longword n),
        US_PrintSigned(long n),
        US_StartCursor(void),
        US_ShutCursor(void),
        US_CheckHighScore(long score,word other),
        US_DisplayHighScores(int which);
extern  boolean US_UpdateCursor(void),
        US_LineInput(int x,int y,char *buf,char *def,boolean escok,
                int maxchars,int maxwidth);
extern  int   US_CheckParm(char *parm,char **strings),
        US_RndT(void);

extern  boolean US_ParmPresent(char *arg);

    void  USL_PrintInCenter(char *s,Rect r);
    char  *USL_GiveSaveName(word game);
#endif
