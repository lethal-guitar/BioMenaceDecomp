/* Copyright (C) 2024 Nikolai Wuttke-Hohendorf
 *
 * Based on reconstructed Commander Keen 4-6 Source Code
 * Copyright (C) 2021 K1n9_Duk3
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


Sint16 TABLE3[] = {
  0, 0, 0, 0, 0, 0, 0, 0, 7, 6, 5, 4, 3, 2, 1, 0, 5, 4,
  3, 2, 1, 0, 15, 14, 5, 4, 3, 2, 1, 0, 15, 14, 3, 2,
  1, 0, 15, 14, 13, 12, 9, 8, 7, 6, 5, 4, 3, 2, 9, 8,
  7, 6, 5, 4, 3, 2, 11, 10, 9, 8, 7, 6, 5, 4,
};

Sint16 bonuspoints[] = {
  100, 200, 500, 800, 1000, 1500, 2000, 5000, 20000, 50000
};

extern Uint16 invincible;

statetype far s_86 = {
  // TODO
  348, 350,
  think, false, ps_none, 0, 0, 0,
  NULL, NULL, NULL, NULL};
statetype far s_203 = {
  // TODO
  348, 350,
  think, false, ps_none, 0, 0, 0,
  NULL, NULL, NULL, NULL};
statetype far s_206 = {
  // TODO
  348, 350,
  think, false, ps_none, 0, 0, 0,
  NULL, NULL, NULL, NULL};


void SnakeContact(objtype* ob, objtype* hit)
{
  switch (hit->obclass)
  {
    case pickupobj:
      switch (hit->temp2)
      {
        case 9:
          SD_PlaySound(14);
          hit->shapenum = GRENADE_GREEN1_SPR;

          gamestate.explosives.grenades++;

          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_203);

          if (!gamestate.var26)
          {
            ShowHelpMessage("Throw grenades to blow up monsters!\n");
            gamestate.var26 = true;
          }
          break;

        case 16:
          SD_PlaySound(14);
          hit->shapenum = 144;

          if (gamestate.ammoinclip > 0 || gamestate.ammotype != 0)
          {
            gamestate.clips++;
          }
          else
          {
            gamestate.rapidfire = 1;

            if (gamestate.difficulty == gd_Hard)
            {
              gamestate.ammoinclip = 45;
            }
            else
            {
              gamestate.ammoinclip = 90;
            }
          }

          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_203);

          if (!gamestate.var27)
          {
            ShowHelpMessage("Collect machine guns for automatic fire.\n");
            gamestate.var27 = true;
          }
          break;

        case 17:
          if (c.yaxis == -1)
          {
            SD_PlaySound(15);
            hit->shapenum = 154;

            gamestate.keyitems.keycards++;

            hit->obclass = inertobj;
            hit->priority = 3;
            ChangeState(hit, &s_203);

            if (!gamestate.var28)
            {
              ShowHelpMessage("Use keycards to turn off electric beams.\n");
              gamestate.var28 = true;
            }
          }
          break;

        case 18:
          SD_PlaySound(15);
          hit->shapenum = 156;

          gamestate.keyitems.keys++;

          hit->obclass = inertobj;
          hit->priority = 3;

          if (!gamestate.var29)
          {
            ShowHelpMessage("Push <UP> and use key to open door.\n");
            gamestate.var29 = true;
          }

          ChangeState(hit, &s_203);
          break;

        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
          if (c.yaxis == -1)
          {
            SD_PlaySound(14);
            hit->shapenum = hit->temp1 + 181;

            GivePoints(bonuspoints[hit->temp1 - 19]);

            hit->obclass = inertobj;
            hit->priority = 3;
            ChangeState(hit, &s_203);
          }
          break;

        case 25:
          if (c.yaxis == -1)
          {
            SD_PlaySound(16);
            hit->shapenum = 199;

            if (gamestate.lives < 9)
            {
              gamestate.lives++;
            }

            hit->obclass = inertobj;
            hit->priority = 3;
            ChangeState(hit, &s_203);
          }
          break;

        case 26:
          if (c.yaxis == -1 || gamestate.mapon == 6 || gamestate.mapon == 11)
          {
            SD_PlaySound(15);
            hit->shapenum = 185;

            gamestate.blueshard++;

            hit->obclass = inertobj;
            hit->priority = 3;
            ChangeState(hit, &s_203);

            if (!gamestate.var30)
            {
              ShowHelpMessage("Find out where these crystal shards go.\n");
              gamestate.var30 = true;
            }
          }
          break;

        case 27:
          if (c.yaxis == -1)
          {
            SD_PlaySound(15);
            hit->shapenum = 187;

            gamestate.greenshard++;

            hit->obclass = inertobj;
            hit->priority = 3;
            ChangeState(hit, &s_203);

            if (!gamestate.var30)
            {
              ShowHelpMessage("Find out where these crystal shards go.\n");
              gamestate.var30 = true;
            }
          }
          break;

        case 28:
          if (c.yaxis == -1)
          {
            SD_PlaySound(15);
            hit->shapenum = 189;

            gamestate.redshard++;

            hit->obclass = inertobj;
            hit->priority = 3;
            ChangeState(hit, &s_203);

            if (!gamestate.var30)
            {
              ShowHelpMessage("Find out where these crystal shards go.\n");
              gamestate.var30 = true;
            }
          }
          break;

        case 29:
          if (c.yaxis == -1)
          {
            SD_PlaySound(15);
            hit->shapenum = 191;

            gamestate.cyanshard++;

            hit->obclass = inertobj;
            hit->priority = 3;
            ChangeState(hit, &s_203);

            if (!gamestate.var30)
            {
              ShowHelpMessage("Find out where these crystal shards go.\n");
              gamestate.var30 = true;
            }
          }
          break;

        case 30:
          if (c.yaxis == -1)
          {
            SD_PlaySound(15);
            hit->shapenum = 209;

            gamestate.specialkey++;

            hit->obclass = inertobj;
            hit->priority = 3;
            ChangeState(hit, &s_203);

            ShowHelpMessage("Hmm....What a strange key!\n");
          }
          break;

        case 36:
          hit->shapenum = GRENADE_RED1_SPR;
          SD_PlaySound(14);

          gamestate.explosives.redgrenades++;

          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_203);

          if (!gamestate.var26)
          {
            ShowHelpMessage("Throw grenades to blow up monsters!\n");
            gamestate.var26 = true;
          }
          break;

        case 37:
          SD_PlaySound(15);
          hit->shapenum = 217;

          gamestate.rapidfire = true;
          gamestate.ammotype = AMMO_SUPERBULLET;

          if (gamestate.ammoinclip > 0)
          {
            gamestate.clips++;
          }

          if (gamestate.difficulty == gd_Hard)
          {
            gamestate.ammoinclip = 45;
          }
          else
          {
            gamestate.ammoinclip = 90;
          }

          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_203);

          if (!gamestate.var31)
          {
            ShowHelpMessage("Super Gun!  Bullets do 5x the damage!\n");
            gamestate.var31 = true;
          }
          break;

        case 38:
          SD_PlaySound(27);
          hit->shapenum = 219;

          if (gamestate.difficulty == gd_Hard)
          {
            gamestate.explosives.landmines = 5;
          }
          else
          {
            gamestate.explosives.landmines = 10;
          }

          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_203);

          if (!gamestate.var32)
          {
            ShowHelpMessage("Cool!  Land mines!\n");
            gamestate.var32 = true;
          }
          break;

        case 39:
          SD_PlaySound(27);
          hit->shapenum = 215;

          gamestate.rapidfire = false;
          gamestate.ammotype = AMMO_PLASMABOLT;

          if (gamestate.ammoinclip > 0)
          {
            gamestate.clips++;
          }

          if (gamestate.difficulty == gd_Hard)
          {
            gamestate.ammoinclip = 10;
          }
          else
          {
            gamestate.ammoinclip = 20;
          }

          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_203);

          if (!gamestate.var41)
          {
            ShowHelpMessage("Plasma Bolts!  Burn holes through enemies!\n");
            gamestate.var41 = true;
          }
          break;

        case 52:
          SD_PlaySound(27);
          hit->shapenum = 166;

          gamestate.gems++;

          hit->obclass = inertobj;
          hit->priority = 3;

          if (gamestate.gems == 50)
          {
            gamestate.lives++;
            gamestate.gems = 0;
            SD_PlaySound(16);

            hit->shapenum = 199;
          }

          ChangeState(hit, &s_203);

          if (!gamestate.var33)
          {
            ShowHelpMessage("Collect 50 gems for an extra life!\n");
            gamestate.var33 = true;
          }
          break;

        case 53:
          SD_PlaySound(27);
          hit->shapenum = 168;

          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_203);

          SD_PlaySound(28);

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

          if (!gamestate.var34)
          {
            ShowHelpMessage("First Aid Kit restores you to full health.\n");
            gamestate.var34 = true;
          }
          break;

        case 54:
          SD_PlaySound(16);
          hit->shapenum = 180;

          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_203);

          gamestate.secretlevelgem = true;

          if (!gamestate.var42)
          {
            ShowHelpMessage("You found a secret level warp gem!\n");
            gamestate.var42 = true;
          }
          break;

        case 75:
          SD_PlaySound(27);
          hit->shapenum = 170;

          gamestate.nukestate = ns_collected;

          hit->obclass = inertobj;
          hit->priority = 3;

          ShowHelpMessage("Oh look! What a cute little nuclear bomb!\n");

          ChangeState(hit, &s_203);
          break;

        case 76:
          SD_PlaySound(27);
          hit->shapenum = 172;

          gamestate.radpill = true;

          hit->obclass = inertobj;
          hit->priority = 3;

          ShowHelpMessage("It's an anti-radiation pill!\n");

          ChangeState(hit, &s_203);
          break;

        case 77:
          SD_PlaySound(31);
          hit->shapenum = 174;

          gamestate.var16++;

          if (gamestate.var16 >= 1)
          {
            gamestate.var16 = 0;
            invincible = 1500;

            StartMusic(17);
          }

          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_203);

          if (!gamestate.var35)
          {
            ShowHelpMessage("Now you're invincible to monster attacks!\n");
            gamestate.var35 = true;
          }
          break;

        case 78:
          SD_PlaySound(33);
          hit->shapenum = 207;

          GivePoints(5000);

          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_203);
          break;

        case 79:
          SD_PlaySound(33);
          hit->shapenum = 208;

          GivePoints(50000);

          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_203);
          break;

        case 80:
          SD_PlaySound(15);

          gamestate.exitkey = true;

          hit->shapenum = 211;
          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_203);
          break;

      }
      break;

    case platformobj:
      if (!gamestate.riding)
      {
        ClipToSpriteTop(ob, hit);
      }
      break;

    case hostageobj:
      gamestate.hostagerescued = true;

      HostageDialog();

      SD_PlaySound(14);

      hit->shapenum = 207;

      GivePoints(bonuspoints[7]);

      hit->obclass = pickupobj;
      hit->ydir = -1;
      ChangeState(hit, &s_203);
      sub_21473(ob->tilemidx, ob->tiletop, 80);
      break;

    case 29:
      gamestate.var14++;

      SD_PlaySound(14);

      hit->shapenum = 214;
      hit->obclass = pickupobj;
      hit->ydir = -1;
      ChangeState(hit, &s_203);
      break;

    case robopalobj:
      if (!gamestate.hasrobopal && (invincible == 0 || invincible > 50))
      {
        SD_PlaySound(33);

        gamestate.hasrobopal = true;

        ChangeState(hit, &s_206);
      }

      if (!gamestate.var36)
      {
        ShowHelpMessage("RoboPal gives you extra fire power!\n");
        gamestate.var36 = true;
      }
      break;

    case 20:
      DamagePlayer(ob, 50);
      break;

    case 21:
      if (gamestate.mapon != 13)
      {
        sub_18B3F(ob, hit, 0);
      }
      break;

    case bounderobj:
      ClipToSprite(ob, hit, false);
      break;

    case 27:
      ClipToSprite(ob, hit, true);
      break;

    case 5:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 13:
    case 19:
    case 23:
    case 24:
    case 25:
    case 26:
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 36:
    case 39:
    case 40:
    case 41:
    case 42:
      if (hit->var2 == 1) break;

      if (!invincible)
      {
        DamagePlayer(ob, 1);
      }
      break;
  }
}


void SpawnScore(void)
{
  scoreobj->obclass = inertobj;
  scoreobj->active = ac_allways;
  scoreobj->needtoclip = cl_noclip;
  *((Sint32*)&scoreobj->temp1) = -1;
  scoreobj->temp3 = -1;
  scoreobj->temp4 = -1;
  scoreobj->temp5 = -1;
  scoreobj->temp6 = -1;

  NewState(scoreobj, &s_86);
}


void MemDrawChar(Sint16 char8, Uint8 far *dest, Uint16 width, Uint16 planesize)
{
  Uint16 source = (Uint16)grsegs[STARTTILE8];

  asm mov si,[char8]
  asm shl si,1
  asm shl si,1
  asm shl si,1
  asm shl si,1
  asm shl si,1    // index into char 8 segment

  asm mov ds,[WORD PTR source]
  asm mov es,[WORD PTR dest+2]

  asm mov cx,4    // draw four planes
  asm mov bx,[width]
  asm dec bx

  planeloop:

  asm mov di,[WORD PTR dest]

  asm movsb
  asm add di,bx
  asm movsb
  asm add di,bx
  asm movsb
  asm add di,bx
  asm movsb
  asm add di,bx
  asm movsb
  asm add di,bx
  asm movsb
  asm add di,bx
  asm movsb
  asm add di,bx
  asm movsb

  asm mov ax,[planesize]
  asm add [WORD PTR dest],ax

  asm loop  planeloop

  asm mov ax,ss
  asm mov ds,ax
}


void ShiftScore (void)
{
  spritetabletype far *spr;
  spritetype _seg *dest;

  spr = &spritetable[SCOREBOXSPR-STARTSPRITES];
  dest = (spritetype _seg *)grsegs[SCOREBOXSPR];

  CAL_ShiftSprite (FP_SEG(dest),dest->sourceoffset[0],
    dest->sourceoffset[1],spr->width,spr->height,2);

  CAL_ShiftSprite (FP_SEG(dest),dest->sourceoffset[0],
    dest->sourceoffset[2],spr->width,spr->height,4);

  CAL_ShiftSprite (FP_SEG(dest),dest->sourceoffset[0],
    dest->sourceoffset[3],spr->width,spr->height,6);
}


void ResetScoreBox(void)
{
  scoreobj->temp1 =
  scoreobj->temp2 =
  scoreobj->temp3 =
  scoreobj->temp4 =
  scoreobj->temp5 =
  scoreobj->temp6 =
  scoreobj->temp7 = -1;
// PLACEHOLDER
"99";
"99";
"ChunkBloom: Bad dir!";
"FragBloom: Bad dir!";
"ThrowPower: Bad dir!";
"SpawnShot: Bad dir!";
"SpawnLaserShot: Bad dir!";
"SpawnLaserShot: Bad dir!";
}


void UpdateScore(objtype *ob)
{
}


void sub_1D2B5(objtype* ob)
{
}


void sub_1E21D(Sint16 x, Sint16 y, Sint16 t)
{
}


void sub_1D51D()
{
}


void sub_1D7E4()
{
}


void sub_1DD25()
{
}


void sub_1EA04()
{
}
