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

enum {
  CONTROLS_LUMP = 0,
  PLAYER_LUMP = 1,
  HOSTAGE_LUMP = 2,
  SLUG_LUMP = 3,
  BRAWLER_LUMP = 5,
  CEILING_WALKER_LUMP = 6,
  BOMB_LUMP = 7,
  SPITTER_SNAKE_LUMP = 8,
  FIRE_IMP_LUMP = 9,
  GHOSTLY_SLUG_LUMP = 10,
  SEWER_MUTANT_LUMP = 11,
  LUMP_12 = 12,
  CRAWLING_SLIME_LUMP = 13,
  HEDGEHOG_LUMP = 14,
  LUMP_15 = 15,
  SKULLMAN_LUMP = 16,
  LUMP_17 = 17,
  BOUNCE_BOT_LUMP = 18,
  ELEVATOR_LUMP = 19,
  LASER_TURRET_LUMP = 21,
  LASER_GUNNER_LUMP = 22,
  LUMP_24 = 24,
  LUMP_25 = 25,
  LUMP_26 = 26,
  LUMP_27 = 27,
  LUMP_28 = 28,
  LUMP_29 = 29,
  INTRO_LUMP = 30,
  LUMP_31 = 31,
  RESPAWN_BEACON_LUMP = 32,
  NUMLUMPS = 33
};

boolean lumpneeded[NUMLUMPS];
boolean firerobopal;

Uint16 lumpstart[] = {
  CONTROLS_LUMP_START,
  PLAYER_LUMP_START,
  223, 229, 235, 235, 249, 267, 275, 285, 294,
  298, 306, 316, 321, 331, 331, 337, 364, 369, 370, 370,
  376, 380, 384, 386, 387, 397, 398, 399, 406, 351, 359
};

Uint16 lumpend[] = {
  CONTROLS_LUMP_END,
  222, 228, 234, 234, 248, 266, 274, 284, 293, 297,
  305, 315, 320, 330, 330, 336, 350, 368, 369, 369, 375,
  379, 383, 385, 386, 396, 397, 398, 404, 410, 358, 363
};

char* levelnames[GAMELEVELS] = {
  "DownTown Metro",
  "High Rise",
  "City Park",
  "South Side",
  "Sewer",
  "Cave",
  "Skull Man",
  "Elevator",
  "No Man's Land",
  "Lab Entrance",
  "Computer Core",
  "Mangle's Last Stand",
};


// seg128
char far HOSTAGEDLG1[] =
  "Somewhere in each level, there\n"
  "is someone like me who holds a key\n"
  "to each exit.  You must find them!\n";

char far HOSTAGEDLG2[] =
  "Thanks for the key.  I'll use\n"
  "this to go on to the next level\n"
  "and rescue your friends.\n\n";

char far HOSTAGEDLG3[] =
  "Thank you. Dr. Mangle has captured\n"
  "others like me. He said it would be\n"
  "a trail for you to follow so that\n"
  "you could find him and meet your\n"
  "final fate. Be careful!\n\n";

char far HOSTAGEDLG4[] =
  "I'm gonna dust that little dweeb!\n"
  "He can't do this and escape!\n\n";

char far HOSTAGEDLG5[] =
  "Thank you, Sir!\n"
  "I can't believe what has\n"
  "happened to our beautiful city!\n"
  "They've destroyed everything!\n"
  "Please!  You have to stop them!\n\n";

char far HOSTAGEDLG6[] =
  "Ya, it's really a pile!  I'll do\n"
  "my best to clear these mutants out\n"
  "of here. Mangle WON'T succeed!\n\n";

char far HOSTAGEDLG7[] =
  "Hey, be careful buddy! These\n"
  "buildings are, excuse the pun,\n"
  "crawling with, like, these weird\n"
  "creature-things, man! Hey, WOW!\n"
  "What a cool gun! Can I try it out?\n\n";

char far HOSTAGEDLG8[] =
  "Na, you'd probably shoot your foot\n"
  "off or something. You'd better get\n"
  "out of here before the mutants\n"
  "come creeping back this way....\n\n";

char far HOSTAGEDLG9[] =
  "Aaaaaaaahhhhhhh! AAAAAAaaaahhhh!\n"
  "Help! Those green things spit\n"
  "slime on me!  I just know I will\n"
  "dissolve or something, right?\n\n";

char far HOSTAGEDLG10[] =
  "Geez, take a valium or something!\n"
  "You look all right to me....\n\n";

char far HOSTAGEDLG11[] =
  "Thank you, Mr. Logan!  I can't\n"
  "wait to get home and take a nice,\n"
  "hot bath!  I've been locked in\n"
  "here for days waiting for\n"
  "someone to show up and get\n"
  "me out of here.\n\n";

char far HOSTAGEDLG12[] =
  "Heh...Um, well, I hate to be the\n"
  "one to give you the news...but...\n"
  "there are no houses left in this\n"
  "entire city.  Sorry...\n\n";

char far HOSTAGEDLG13[] =
  "WOW! What a light show!  I saw you\n"
  "kick'n robotic butt a mile away!\n"
  "I love this destruction stuff!\n\n";

char far HOSTAGEDLG14[] =
  "Ya, me too.  Those parachuting\n"
  "robots were a new one on me.\n"
  "Fun to kill though.\n\n";

char far HOSTAGEDLG15[] =
  "Mangle is somewhere in this\n"
  "complex. Be very careful!  I've\n"
  "seen him setting up all kinds of\n"
  "traps around here.\n"
  "He must be expecting you.\n\n";

char far HOSTAGEDLG16[] =
  "Yes, he knows I'm coming for him.\n"
  "But he's not expecting what I'm\n"
  "going to do to him when I\n"
  "get my hands on him!\n\n";

char far HOSTAGEDLG17[] =
  "Thank God you're here!  I know\n"
  "that Dr. Mangle is in the next\n"
  "room waiting for you.  But be\n"
  "careful!  Not everything is as\n"
  "it seems.  I think it's a trap!\n\n";

char far HOSTAGEDLG18[] =
  "Thanks for the tip....  But I've\n"
  "learned the way this creep works.\n"
  "He's not going to get away with\n"
  "this!  His luck's just run out!\n\n";

char far COMPATIBILITYINFO[] =
  "If you have a SuperVGA graphics card\n"
  "and experience video problems such\n"
  "as garbage on the screen, select\n"
  "the <compatability mode> option from\n"
  "the main menu CONFIGURE/OPTIONS.\n\n";
;

char far BOSSDIALOG1[] =
  "Greetings Mr. Logan!\n"
  "You will never stop me!\n"
  "I will kill you and toss\n"
  "your bones to my critters.\n\n";

char far BOSSDIALOG2[] =
  "And then the world will bow to the\n"
  "will of Master Cain and Dr. Mangle!\n"
  "Ha ha ha ha ha....\n\n";

char far BOSSDIALOG3[] =
  "Well, well, well....Here we are,\n"
  "Mr. Logan.  It has come down to just\n"
  "you...and to me.  I hope you have\n"
  "enjoyed the little party I've thrown\n\n";

char far BOSSDIALOG4[] =
  "for you today.  I hope you've had fun\n"
  "with my little friends. But now, I'm\n"
  "afraid, it is time for you to die!\n\n";

char far BOSSDIALOG5[] =
  "Mr. Logan, listen to me carefully.\n"
  " *-COUGH-* I am beaten, I'm going to\n"
  "die. *-ACK!-*, so I have nothing to\n"
  "hide and I owe nothing to that creep,\n";

char far BOSSDIALOG6[] =
  "Master Cain. I only did this because\n"
  "he promised me wealth and power, and\n"
  "he also said he'd kill me if I didn't\n"
  "help him. So you can see how I might\n";

char far BOSSDIALOG7[] =
  "be compelled to create these mutants\n"
  "for him.  *-COUGH-* I have gotten\n"
  "what I deserve for my crimes. But you\n"
  "must stop Cain to stop this madness!\n";

char far BOSSDIALOG8[] =
  "There is an escape jet just through\n"
  "that door. I've uploaded navigation\n"
  "coordinates to get you to the next\n"
  "lab.  Enter and destroy it to stop\n";

char far BOSSDIALOG9[] =
  "the production of the mutant army.\n"
  "But be careful, a deadly computer\n"
  "guards the whole complex.\n"
  "You must then go on and find Cain's\n";

char far BOSSDIALOG10[] =
  "secret fortress. Seek him out and\n"
  "destroy him or he will be a plague\n"
  "of destruction to this earth!\n"
  "Goodbye, Snake Logan, *-Hack-*,\n";

char far BOSSDIALOG11[] =
  "and good luck...you will need it.\n"
  "*-Aaaaaarrrggg!-*  <sigh>.......\n\n";

char far BOSSDIALOG12[] =
  "I am Skullman!  I shall kill\n"
  "you and collect your skull as I\n"
  "have with all these others!\n"
  "Prepare to die, sub-creature!\n\n";


void ScanInfoPlane(void)
{
  objtype *ob;
  Uint16 i, x, y, chunk;
  Sint16 info;
  Uint16 far *map;

  InitObjArray(); // start spawning things with a clean slate

  memset(lumpneeded, 0, sizeof(lumpneeded));
  map = mapsegs[2];

  for (y=0; y<mapheight; y++)
  {
    for (x=0; x<mapwidth; x++)
    {
      info = *map++;

      if (info == 0)
        continue;

      switch (info)
      {
        case 1:
          SpawnPlayer(x, y, -1);
          lumpneeded[PLAYER_LUMP] = true;
          break;

        case 2:
          SpawnPlayer(x, y, 1);
          lumpneeded[PLAYER_LUMP] = true;
          break;

        case 3:
          SpawnSlug(x, y);
          lumpneeded[SLUG_LUMP] = true;
          new->active = ac_no;
          break;

        case 4:
          SpawnFireImp(x, y);
          lumpneeded[FIRE_IMP_LUMP] = true;
          new->active = ac_no;
          break;

        case 5:
          SpawnGhostlySlug(x, y);
          lumpneeded[GHOSTLY_SLUG_LUMP] = true;
          new->active = ac_no;
          break;

        case 7:
          SpawnSewerMutant(x, y);
          lumpneeded[SEWER_MUTANT_LUMP] = true;
          break;

        case 8:
          SpawnCrawlingSlime(x, y);
          lumpneeded[CRAWLING_SLIME_LUMP] = true;
          break;

        case 9:
          SpawnPickup(x, y, 9);
          lumpneeded[PLAYER_LUMP] = true;
          new->active = ac_no;
          break;

        case 10:
          SpawnBrawler(x, y);
          lumpneeded[BRAWLER_LUMP] = true;
          break;

        case 11:
          SpawnCeilingWalker(x, y);
          lumpneeded[CEILING_WALKER_LUMP] = true;
          break;

        case 12:
          SpawnSpitterSnake(x, y);
          lumpneeded[SPITTER_SNAKE_LUMP] = true;
          break;

        case 13:
          SpawnHedgehog(x, y);
          lumpneeded[HEDGEHOG_LUMP] = true;
          break;

        case 16:
          SpawnPickup(x, y, 16);
          new->active = ac_no;
          break;

        case 17:
          SpawnPickup(x, y, 17);
          new->active = ac_no;
          break;

        case 18:
          SpawnPickup(x, y, 18);
          new->active = ac_no;
          break;

        case 19:
          SpawnPickup(x, y, 19);
          new->active = ac_no;
          break;

        case 20:
          SpawnPickup(x, y, 20);
          new->active = ac_no;
          break;

        case 21:
          SpawnPickup(x, y, 21);
          new->active = ac_no;
          break;

        case 22:
          SpawnPickup(x, y, 22);
          new->active = ac_no;
          break;

        case 23:
          SpawnPickup(x, y, 23);
          new->active = ac_no;
          break;

        case 24:
          SpawnPickup(x, y, 24);
          new->active = ac_no;
          break;

        case 25:
          SpawnPickup(x, y, 25);
          new->active = ac_no;
          break;

        case 26:
          SpawnPickup(x, y, 26);
          new->active = ac_no;
          break;

        case 27:
          SpawnPickup(x, y, 27);
          new->active = ac_no;
          break;

        case 28:
          SpawnPickup(x, y, 28);
          new->active = ac_no;
          break;

        case 29:
          SpawnPickup(x, y, 29);
          new->active = ac_no;
          break;

        case 30:
          SpawnPickup(x, y, 30);
          new->active = ac_no;
          break;

        case 31:
          SpawnHostage(x, y, 0);
          lumpneeded[HOSTAGE_LUMP] = true;
          break;

        case 32:
          SpawnHostage(x, y, 1);
          lumpneeded[HOSTAGE_LUMP] = true;
          break;

        case 33:
          SpawnHostage(x, y, 2);
          lumpneeded[HOSTAGE_LUMP] = true;
          break;

        case 34:
          RF_SetScrollBlock(x, y, true);
          break;

        case 35:
          RF_SetScrollBlock(x, y, false);
          break;

        case 36:
          SpawnPickup(x, y, 36);
          lumpneeded[PLAYER_LUMP] = true;
          break;

        case 37:
          SpawnPickup(x, y, 37);
          lumpneeded[PLAYER_LUMP] = true;
          break;

        case 38:
          SpawnPickup(x, y, 38);
          lumpneeded[PLAYER_LUMP] = true;
          break;

        case 39:
          SpawnPickup(x, y, 39);
          lumpneeded[PLAYER_LUMP] = true;
          break;

        case 40:
          SpawnSkullman(x, y);
          lumpneeded[SKULLMAN_LUMP] = true;
          break;

        case 41:
          SpawnSkullmanHand(x, y, 0);
          lumpneeded[SKULLMAN_LUMP] = true;
          break;

        case 42:
          SpawnSkullmanHand(x, y, 1);
          lumpneeded[SKULLMAN_LUMP] = true;
          break;

        case 43:
          SpawnAsteroid(x, y);
          lumpneeded[INTRO_LUMP] = true;
          break;

        case 44:
          SpawnDrMangleHologram(x, y);
          lumpneeded[LUMP_17] = true;
          break;

        case 45:
          SpawnDrMangle(x, y);
          lumpneeded[LUMP_17] = true;
          break;

        case 46:
          SpawnBounceBot(x, y);
          lumpneeded[BOUNCE_BOT_LUMP] = true;
          break;

        case 48:
          SpawnLaserTurret(x, y);
          lumpneeded[LASER_TURRET_LUMP] = true;
          break;

        case 49:
          SpawnLaserGunner(x, y);
          lumpneeded[LASER_GUNNER_LUMP] = true;
          break;

        case 51:
          SpawnBomb(x, y);
          lumpneeded[BOMB_LUMP] = true;
          break;

        case 52:
          SpawnPickup(x, y, 52);
          new->active = ac_no;
          break;

        case 53:
          SpawnPickup(x, y, 53);
          new->active = ac_no;
          break;

        case 54:
          SpawnPickup(x, y, 54);
          new->active = ac_no;
          break;

        case 55:
          SpawnRespawnBeacon(x, y);
          lumpneeded[RESPAWN_BEACON_LUMP] = true;
          break;

        case 66:
        case 67:
        case 68:
        case 69:
          SpawnElevator(x, y, info - 66);
          lumpneeded[ELEVATOR_LUMP] = true;
          break;

        case 72:
          SpawnSparkShooter(x, y);
          lumpneeded[LUMP_24] = true;
          break;

        case 74:
          SpawnRobopal(x, y);
          lumpneeded[LUMP_26] = true;
          break;

        case 75:
          SpawnPickup(x, y, 75);
          new->active = ac_no;
          break;

        case 76:
          SpawnPickup(x, y, 76);
          new->active = ac_no;
          break;

        case 77:
          SpawnPickup(x, y, 77);
          new->active = ac_no;
          break;

        case 78:
          SpawnPickup(x, y, 78);
          new->active = ac_no;
          break;

        case 79:
          SpawnPickup(x, y, 79);
          new->active = ac_no;
          break;

        case 80:
          SpawnTankBot(x, y);
          lumpneeded[LUMP_29] = true;
          break;

        case 81:
          SpawnPushBlock(x, y);
          lumpneeded[LUMP_25] = true;
          break;

        case 82:
          SpawnSlimeDropper(x, y);
          lumpneeded[LUMP_12] = true;
          break;

        case 83:
          SpawnHelicopter(x, y, 0);
          lumpneeded[LUMP_31] = true;
          break;

        case 87:
          SpawnCrusher(x, y);
          lumpneeded[LUMP_27] = true;
          break;

        case 88:
          SpawnFallingBlock(x, y);
          lumpneeded[LUMP_28] = true;
          break;

        case 89:
          SpawnApogeeLogo(x, y, 0);
          lumpneeded[INTRO_LUMP] = true;
          break;
      }

      if (new->active != ac_allways)
      {
        new->active = ac_no;
      }
    }
  }


  CA_MarkGrChunk(SCOREBOXSPR);
  SpawnScoreBox();

  for (i = 0; i < NUMLUMPS; i++)
  {
    if (lumpneeded[i])
    {
      for (chunk = lumpstart[i]; chunk <= lumpend[i]; chunk++)
      {
        CA_MarkGrChunk(chunk);
      }
    }
  }
}


void HostageDialog(void)
{
  char buffer[200];
  Sint16 numsteps;
  Sint16 oldmusic;
  Sint16 i;
  Sint16 index;

  oldmusic = curmusic;

  switch (gamestate.mapon)
  {
    case 0: index = 0; numsteps = 2; break;
    case 1: index = 2; numsteps = 2; break;
    case 2: index = 4; numsteps = 2; break;
    case 3: index = 6; numsteps = 2; break;
    case 4: index = 8; numsteps = 2; break;
    case 5: index = 10; numsteps = 2; break;
    case 8: index = 12; numsteps = 2; break;
    case 9: index = 14; numsteps = 2; break;
    case 10: index = 16; numsteps = 2; break;
  }

  CA_UpLevel();
  CA_MarkGrChunk(HOSTAGE1PIC);
  CA_MarkGrChunk(HOSTAGE2PIC);
  CA_MarkGrChunk(HOSTAGE3PIC);
  CA_MarkGrChunk(SNAKETALKPIC);
  CA_CacheMarks(0);

  VW_FixRefreshBuffer();
  StartMusic(15);

  for (i = index; i < index + numsteps; i++)
  {
    US_CenterWindow(36, 9);

    switch (i)
    {
      case  0: VWB_DrawPic(WindowX, WindowY+4, HOSTAGE1PIC); break;
      case  1: VWB_DrawPic(WindowX, WindowY+4, SNAKETALKPIC); break;
      case  2: VWB_DrawPic(WindowX, WindowY+4, HOSTAGE3PIC); break;
      case  3: VWB_DrawPic(WindowX, WindowY+4, SNAKETALKPIC); break;
      case  4: VWB_DrawPic(WindowX, WindowY+4, HOSTAGE2PIC); break;
      case  5: VWB_DrawPic(WindowX, WindowY+4, SNAKETALKPIC); break;
      case  6: VWB_DrawPic(WindowX, WindowY+4, HOSTAGE1PIC); break;
      case  7: VWB_DrawPic(WindowX, WindowY+4, SNAKETALKPIC); break;
      case  8: VWB_DrawPic(WindowX, WindowY+4, HOSTAGE3PIC); break;
      case  9: VWB_DrawPic(WindowX, WindowY+4, SNAKETALKPIC); break;
      case 10: VWB_DrawPic(WindowX, WindowY+4, HOSTAGE2PIC); break;
      case 11: VWB_DrawPic(WindowX, WindowY+4, SNAKETALKPIC); break;
      case 12: VWB_DrawPic(WindowX, WindowY+4, HOSTAGE1PIC); break;
      case 13: VWB_DrawPic(WindowX, WindowY+4, SNAKETALKPIC); break;
      case 14: VWB_DrawPic(WindowX, WindowY+4, HOSTAGE2PIC); break;
      case 15: VWB_DrawPic(WindowX, WindowY+4, SNAKETALKPIC); break;
      case 16: VWB_DrawPic(WindowX, WindowY+4, HOSTAGE2PIC); break;
      case 17: VWB_DrawPic(WindowX, WindowY+4, SNAKETALKPIC); break;
    }

    PrintY += 6;
    WindowW -= 48;
    WindowX += 48;

    switch (i)
    {
      case  0: _fstrcpy(buffer, HOSTAGEDLG1); break;
      case  1: _fstrcpy(buffer, HOSTAGEDLG2); break;
      case  2: _fstrcpy(buffer, HOSTAGEDLG3); break;
      case  3: _fstrcpy(buffer, HOSTAGEDLG4); break;
      case  4: _fstrcpy(buffer, HOSTAGEDLG5); break;
      case  5: _fstrcpy(buffer, HOSTAGEDLG6); break;
      case  6: _fstrcpy(buffer, HOSTAGEDLG7); break;
      case  7: _fstrcpy(buffer, HOSTAGEDLG8); break;
      case  8: _fstrcpy(buffer, HOSTAGEDLG9); break;
      case  9: _fstrcpy(buffer, HOSTAGEDLG10); break;
      case 10: _fstrcpy(buffer, HOSTAGEDLG11); break;
      case 11: _fstrcpy(buffer, HOSTAGEDLG12); break;
      case 12: _fstrcpy(buffer, HOSTAGEDLG13); break;
      case 13: _fstrcpy(buffer, HOSTAGEDLG14); break;
      case 14: _fstrcpy(buffer, HOSTAGEDLG15); break;
      case 15: _fstrcpy(buffer, HOSTAGEDLG16); break;
      case 16: _fstrcpy(buffer, HOSTAGEDLG17); break;
      case 17: _fstrcpy(buffer, HOSTAGEDLG18); break;
    }

    US_CPrint(buffer);
    VW_UpdateScreen();
    VW_WaitVBL(60);
    IN_ClearKeysDown();
    IN_Ack();
  }

  CA_DownLevel();
  RF_ForceRefresh();
  ResetScoreBox();
  StopMusic();
  StartMusic(oldmusic);
}


void ShowCompatibilityInfoMessage(void)
{
  char buffer[200];
  Sint16 numsteps;
  Sint16 i;
  Sint16 index;

  switch (gamestate.mapon)
  {
    case 0: index = 0; numsteps = 1; break;
  }

  VW_FixRefreshBuffer();

  if (gamestate.mapon != 6)
  {
    StartMusic(15);
  }

  for (i = index; i < index + numsteps; i++)
  {
    US_CenterWindow(30, 8);
    PrintY += 2;

    switch (i)
    {
      case 0: _fstrcpy(buffer, COMPATIBILITYINFO); break;
    }

    US_CPrint(buffer);
    VW_UpdateScreen();
    VW_WaitVBL(60);
    IN_ClearKeysDown();
    IN_Ack();

    RF_ForceRefresh();
  }

  if (gamestate.mapon != 6)
  {
    StopMusic();
    StartMusic(gamestate.mapon);
  }
}


void BossDialog(void)
{
  char buffer[200];
  Sint16 numsteps;
  Sint16 i;
  Sint16 index;

  switch (gamestate.mapon)
  {
    case 6: index = 11; numsteps = 1; break;
    case 9: index = 0; numsteps = 2; break;
    case 11: index = 2; numsteps = 2; break;
    case 12: index = 4; numsteps = 7; break;
  }

  CA_UpLevel();
  VW_FixRefreshBuffer();

  for (i = index; i < index + numsteps; i++)
  {
    US_CenterWindow(32, 6);
    PrintY += 2;

    switch (i)
    {
      case  0: _fstrcpy(buffer, BOSSDIALOG1); break;
      case  1: _fstrcpy(buffer, BOSSDIALOG2); break;
      case  2: _fstrcpy(buffer, BOSSDIALOG3); break;
      case  3: _fstrcpy(buffer, BOSSDIALOG4); SD_PlaySound(23); break;
      case  4: _fstrcpy(buffer, BOSSDIALOG5); break;
      case  5: _fstrcpy(buffer, BOSSDIALOG6); break;
      case  6: _fstrcpy(buffer, BOSSDIALOG7); break;
      case  7: _fstrcpy(buffer, BOSSDIALOG8); break;
      case  8: _fstrcpy(buffer, BOSSDIALOG9); break;
      case  9: _fstrcpy(buffer, BOSSDIALOG10); break;
      case 10: _fstrcpy(buffer, BOSSDIALOG11); break;
      case 11: _fstrcpy(buffer, BOSSDIALOG12); break;
      case 12: _fstrcpy(buffer, COMPATIBILITYINFO); break;
    }

    US_CPrint(buffer);
    VW_UpdateScreen();
    VW_WaitVBL(60);
    IN_ClearKeysDown();
    IN_Ack();
  }

  CA_DownLevel();
  ResetScoreBox();
  RF_ForceRefresh();
}
