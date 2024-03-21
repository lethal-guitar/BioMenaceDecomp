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

#define PLACESPRITE \
  RF_PlaceSprite(&ob->sprite, ob->x, ob->y, ob->shapenum, \
    ob->dmgflash ? maskdraw : spritedraw, ob->priority);

Uint16 bounceangle[8][8] = {
  { 0,  0,  0,  0,  0,  0,  0,  0},
  { 7,  6,  5,  4,  3,  2,  1,  0},
  { 5,  4,  3,  2,  1,  0, 15, 14},
  { 5,  4,  3,  2,  1,  0, 15, 14},
  { 3,  2,  1,  0, 15, 14, 13, 12},
  { 9,  8,  7,  6,  5,  4,  3,  2},
  { 9,  8,  7,  6,  5,  4,  3,  2},
  {11, 10,  9,  8,  7,  6,  5,  4}
};

Sint16 bonuspoints[] = {
  100, 200, 500, 800, 1000, 1500, 2000, 5000, 20000, 50000
};

Uint8 unktime;
Uint16 colorstep;
Sint16 doordestx;
Sint16 doordesty;
Uint16 jumptime;

extern Uint16 invincible;
extern Sint16 word_399F8;
extern boolean robopalfire;

extern statetype far s_score;
extern statetype far s_87;
extern statetype far s_88;
extern statetype far s_89;
extern statetype far s_90;
extern statetype far s_91;
extern statetype far s_92;
extern statetype far s_93;
extern statetype far s_94;
extern statetype far s_95;
extern statetype far s_96;
extern statetype far s_97;
extern statetype far s_98;
extern statetype far s_99;
extern statetype far s_100;
extern statetype far s_101;
extern statetype far s_102;
extern statetype far s_103;
extern statetype far s_104;
extern statetype far s_105;
extern statetype far s_106;
extern statetype far s_107;
extern statetype far s_108;
extern statetype far s_109;
extern statetype far s_110;
extern statetype far s_111;
extern statetype far s_112;
extern statetype far s_113;
extern statetype far s_114;
extern statetype far s_115;
extern statetype far s_116;
extern statetype far s_117;
extern statetype far s_118;
extern statetype far s_119;
extern statetype far s_120;
extern statetype far s_121;
extern statetype far s_lasershot;
extern statetype far s_superplasmabolt;
extern statetype far s_124;
extern statetype far s_125;
extern statetype far s_126;
extern statetype far s_127;

extern statetype far s_player_place_mine;
extern statetype far s_173;
extern statetype far s_176;
extern statetype far s_186;
extern statetype far s_200;
extern statetype far s_201;
extern statetype far s_225;

void SpawnLaserShot(Uint16 x, Uint16 y, Sint16 dir);
void sub_1d9a4(objtype* ob);
void sub_1de52(objtype* ob, objtype* hit);
void sub_1dea7(objtype* ob);
void T_GrenadeExplosion(objtype* ob);
void sub_1e34c(objtype* ob);
void C_Grenade(objtype* ob, objtype* hit);
void C_GrenadeExplosion(objtype* ob, objtype* hit);
void R_Grenade(objtype* ob);
void C_Shot(objtype* ob, objtype* hit);
void C_LaserShot(objtype* ob, objtype* hit);
void ExplodeShot(objtype* ob);
void T_Shot(objtype* ob);
void R_Shot(objtype* ob);
void R_SuperPlasmaBolt(objtype* ob);
void ChunkBloom(objtype* ob, Uint16 x, Uint16 y, Direction dir);


statetype far s_score = { /* 30d00 */
  0, 0, think, false, ps_none, 0, 0, 0,
  NULL, NULL, NULL, NULL};

statetype far s_87 = { /* 30d20 */
  129, 129, step, false, ps_none, 5, 0, 0,
  NULL, NULL, R_Draw, &s_88};

statetype far s_88 = { /* 30d40 */
  130, 130, step, false, ps_none, 5, 0, 0,
  NULL, NULL, R_Draw, &s_89};

statetype far s_89 = { /* 30d60 */
  131, 131, step, false, ps_none, 5, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_90 = { /* 30d80 */
  134, 134, stepthink, false, ps_none, 6, 0, 0,
  T_Projectile, NULL, sub_1d9a4, &s_91};

statetype far s_91 = { /* 30da0 */
  135, 135, stepthink, false, ps_none, 6, 0, 0,
  T_Projectile, NULL, sub_1d9a4, &s_90};

statetype far s_92 = { /* 30dc0 */
  136, 136, stepthink, false, ps_none, 6, 0, 0,
  T_Projectile, NULL, sub_1d9a4, &s_93};

statetype far s_93 = { /* 30de0 */
  137, 137, stepthink, false, ps_none, 6, 0, 0,
  T_Projectile, NULL, sub_1d9a4, &s_92};

statetype far s_94 = { /* 30e00 */
  138, 138, stepthink, false, ps_none, 6, 0, 0,
  T_Projectile, NULL, sub_1d9a4, &s_95};

statetype far s_95 = { /* 30e20 */
  139, 139, stepthink, false, ps_none, 6, 0, 0,
  T_Projectile, NULL, sub_1d9a4, &s_94};

statetype far s_96 = { /* 30e40 */
  132, 133, stepthink, false, ps_none, 100, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_97 = { /* 30e60 */
  146, 150, stepthink, false, ps_none, 8, 0, 0,
  T_Projectile, NULL, sub_1d9a4, &s_98};

statetype far s_98 = { /* 30e80 */
  147, 151, stepthink, false, ps_none, 8, 0, 0,
  T_Projectile, NULL, sub_1d9a4, &s_99};

statetype far s_99 = { /* 30ea0 */
  148, 152, stepthink, false, ps_none, 8, 0, 0,
  T_Projectile, NULL, sub_1d9a4, &s_100};

statetype far s_100 = { /* 30ec0 */
  149, 153, stepthink, false, ps_none, 8, 0, 0,
  T_Projectile, NULL, sub_1d9a4, &s_97};

statetype far s_101 = { /* 30ee0 */
  149, 153, stepthink, false, ps_none, 100, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_102 = { /* 30f00 */
  121, 125, stepthink, false, ps_none, 6, 0, 0,
  T_Projectile, sub_1de52, sub_1dea7, &s_103};

statetype far s_103 = { /* 30f20 */
  122, 126, stepthink, false, ps_none, 6, 0, 0,
  T_Projectile, sub_1de52, sub_1dea7, &s_104};

statetype far s_104 = { /* 30f40 */
  123, 127, stepthink, false, ps_none, 6, 0, 0,
  T_Projectile, sub_1de52, sub_1dea7, &s_105};

statetype far s_105 = { /* 30f60 */
  124, 128, stepthink, false, ps_none, 6, 0, 0,
  T_Projectile, sub_1de52, sub_1dea7, &s_102};

statetype far s_106 = { /* 30f80 */
  105, 105, stepthink, false, ps_none, 10, 0, 0,
  T_Projectile, C_Grenade, R_Grenade, &s_107};

statetype far s_107 = { /* 30fa0 */
  106, 106, stepthink, false, ps_none, 10, 0, 0,
  T_Projectile, C_Grenade, R_Grenade, &s_108};

statetype far s_108 = { /* 30fc0 */
  107, 107, stepthink, false, ps_none, 10, 0, 0,
  T_Projectile, C_Grenade, R_Grenade, &s_109};

statetype far s_109 = { /* 30fe0 */
  108, 108, stepthink, false, ps_none, 10, 0, 0,
  T_Projectile, C_Grenade, R_Grenade, &s_106};

statetype far s_110 = { /* 31000 */
  109, 109, stepthink, false, ps_none, 10, 0, 0,
  T_Projectile, C_Grenade, R_Grenade, &s_111};

statetype far s_111 = { /* 31020 */
  110, 110, stepthink, false, ps_none, 10, 0, 0,
  T_Projectile, C_Grenade, R_Grenade, &s_112};

statetype far s_112 = { /* 31040 */
  111, 111, stepthink, false, ps_none, 10, 0, 0,
  T_Projectile, C_Grenade, R_Grenade, &s_113};

statetype far s_113 = { /* 31060 */
  112, 112, stepthink, false, ps_none, 10, 0, 0,
  T_Projectile, C_Grenade, R_Grenade, &s_110};

statetype far s_114 = { /* 31080 */
  115, 115, step, false, ps_none, 10, 0, 0,
  T_GrenadeExplosion, C_GrenadeExplosion, R_Draw, &s_115};

statetype far s_115 = { /* 310a0 */
  116, 116, step, false, ps_none, 10, 0, 0,
  NULL, C_GrenadeExplosion, R_Draw, &s_116};

statetype far s_116 = { /* 310c0 */
  117, 117, step, false, ps_none, 10, 0, 0,
  NULL, C_GrenadeExplosion, R_Draw, &s_117};

statetype far s_117 = { /* 310e0 */
  118, 118, step, false, ps_none, 10, 0, 0,
  NULL, C_GrenadeExplosion, R_Draw, &s_118};

statetype far s_118 = { /* 31100 */
  119, 119, step, false, ps_none, 10, 0, 0,
  NULL, C_GrenadeExplosion, R_Draw, &s_119};

statetype far s_119 = { /* 31120 */
  120, 120, step, false, ps_none, 10, 0, 0,
  NULL, C_GrenadeExplosion, R_Draw, NULL};

statetype far s_120 = { /* 31140 */
  393, 391, slide, false, ps_none, 6, 64, 64,
  T_Shot, C_Shot, R_Shot, &s_121};

statetype far s_121 = { /* 31160 */
  394, 392, slide, false, ps_none, 6, 64, 64,
  T_Shot, C_Shot, R_Shot, &s_120};

statetype far s_lasershot = { /* 31180 */
  63, 63, slide, false, ps_none, 6, 64, 64,
  T_Shot, C_LaserShot, R_Shot, &s_lasershot};

statetype far s_superplasmabolt = { /* 311a0 */
  65, 64, slide, false, ps_none, 2, 64, 64,
  T_Shot, C_LaserShot, R_SuperPlasmaBolt, &s_superplasmabolt};

statetype far s_124 = { /* 311c0 */
  395, 395, step, false, ps_none, 12, 0, 0,
  NULL, NULL, R_Draw, &s_125};

statetype far s_125 = { /* 311e0 */
  396, 396, step, false, ps_none, 12, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_126 = { /* 31200 */
  57, 57, step, false, ps_none, 12, 0, 0,
  NULL, NULL, R_Draw, &s_127};

statetype far s_127 = { /* 31220 */
  58, 58, step, false, ps_none, 12, 0, 0,
  NULL, NULL, R_Draw, NULL};



void SnakeContact(objtype* ob, objtype* hit)
{
  switch (hit->obclass)
  {
    case pickupobj:
      switch (hit->temp1)
      {
        case 9:
          SD_PlaySound(14);
          hit->shapenum = GRENADE_GREEN1_SPR;

          gamestate.explosives.grenades++;

          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_173);

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
          ChangeState(hit, &s_173);

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
            ChangeState(hit, &s_173);

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

          ChangeState(hit, &s_173);
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
            ChangeState(hit, &s_173);
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
            ChangeState(hit, &s_173);
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
            ChangeState(hit, &s_173);

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
            ChangeState(hit, &s_173);

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
            ChangeState(hit, &s_173);

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
            ChangeState(hit, &s_173);

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
            ChangeState(hit, &s_173);

            ShowHelpMessage("Hmm....What a strange key!\n");
          }
          break;

        case 36:
          hit->shapenum = GRENADE_RED1_SPR;
          SD_PlaySound(14);

          gamestate.explosives.redgrenades++;

          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_173);

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
          ChangeState(hit, &s_173);

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
          ChangeState(hit, &s_173);

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
          ChangeState(hit, &s_173);

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

          ChangeState(hit, &s_173);

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
          ChangeState(hit, &s_173);

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
          ChangeState(hit, &s_173);

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

          ChangeState(hit, &s_173);
          break;

        case 76:
          SD_PlaySound(27);
          hit->shapenum = 172;

          gamestate.radpill = true;

          hit->obclass = inertobj;
          hit->priority = 3;

          ShowHelpMessage("It's an anti-radiation pill!\n");

          ChangeState(hit, &s_173);
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
          ChangeState(hit, &s_173);

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
          ChangeState(hit, &s_173);
          break;

        case 79:
          SD_PlaySound(33);
          hit->shapenum = 208;

          GivePoints(50000);

          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_173);
          break;

        case 80:
          SD_PlaySound(15);

          gamestate.exitkey = true;

          hit->shapenum = 211;
          hit->obclass = inertobj;
          hit->priority = 3;
          ChangeState(hit, &s_173);
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
      ChangeState(hit, &s_173);
      sub_21473(ob->tilemidx, ob->tiletop, 80);
      break;

    case 29:
      gamestate.var14++;

      SD_PlaySound(14);

      hit->shapenum = 214;
      hit->obclass = pickupobj;
      hit->ydir = -1;
      ChangeState(hit, &s_173);
      break;

    case robopalobj:
      if (!gamestate.hasrobopal && (invincible == 0 || invincible > 50))
      {
        SD_PlaySound(33);

        gamestate.hasrobopal = true;

        ChangeState(hit, &s_176);
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

  NewState(scoreobj, &s_score);
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
}


void UpdateScore(objtype *ob)
{
}


void DealDamage(objtype* ob, Sint16 amount)
{
  Sint16 points = 0;

  ob->health = ob->health - amount;
  ob->needtoreact = true;

  if (ob->health <= 0)
  {

    switch (ob->obclass)
    {
      case 7:
      case 10:
      case 29:
      case 30:
      case 39:
        points = 50;
        break;

      case 8:
      case 32:
        points = 100;
        break;

      case 11:
        points = 200;
        break;

      case 9:
      case 31:
      case 40:
        points = 500;
        break;

      case 20:
        points = 2000;
        ob->var1 = 0;
        break;

      case 19:
        points = 800;
        ob->var1 = 0;
        break;

      case 23:
        points = 350;
        ob->var1 = 0;
        break;

      case 28:
        points = 500;
        ob->var1 = 0;
        break;

      case 24:
        points = 500;
        break;

      case 13:
        points = 34464;
        ob->var1 = 0;
        SD_PlaySound(23);
        ob->obclass = inertobj;
        word_389A8 = 999;
        break;

      case 33:
        points = 5000;
        ob->var1 = 0;
        sub_21473(ob->tilemidx, ob->tiletop, 26);
        StartMusic(14);
        word_399F8 = true;
        word_389A8 = 999;
        break;

      case 34:
        points = 1000;
        ob->var1 = 0;
        break;

      case 41:
        points = 1000;
        ob->var1 = 0;
        break;
    }

    if (
      ob->obclass == 23 ||
      ob->obclass == 28 ||
      ob->obclass == 13 ||
      ob->obclass == 36 ||
      ob->obclass == 41)
    {
      sub_22A0D(ob->x, ob->y + 16*PIXGLOBAL);
      goto loc_1d3c6;
    }
    else
    {
loc_1d3c6:
      ChunkBloom(ob, ob->midx, ob->y, dir_North);
      ChunkBloom(ob, ob->midx, ob->y, dir_South);
      ChunkBloom(ob, ob->midx, ob->y, dir_East);
      ChunkBloom(ob, ob->midx, ob->y, dir_West);

      if (ob->obclass != 20 && ob->obclass != inertobj)
      {
        RemoveObj(ob);
      }
    }


    GivePoints(points);
  }
  else
  {
    if (player->obclass == 18)
    {
      ob->dmgflash = 10;
    }
    else
    {
      ob->dmgflash = 4;
    }

    if ((ob->obclass == 33 || ob->obclass == 34) && word_399F8 < 0)
    {
      word_399F8++;
    }
  }
}


void SpawnBulletImpact(Uint16 x, Uint16 y)
{
  GetNewObj(true);
  new->obclass = inertobj;
  new->active = ac_removable;
  new->x = x - 4*PIXGLOBAL;
  new->y = y - 4*PIXGLOBAL;
  new->priority = 3;

  if (gamestate.ammotype == AMMO_SUPERBULLET ||
      gamestate.ammotype == AMMO_PLASMABOLT)
  {
    NewState(new, &s_225);
  }
  else
  {
    NewState(new, &s_87);
  }
}


void FireBullet(Uint16 x, Uint16 y, Sint16 xdir, Sint16 damage)
{
  objtype* ob;
  Uint16 tilex, tiley;
  Uint16 maptile;
  Uint16 top, bottom;
  Uint16 i;

  if (gamestate.ammoinclip > 0)
  {
    if (gamestate.difficulty == gd_Easy && gamestate.ammoinclip <= 1)
    {
      if (gamestate.ammotype == AMMO_SUPERBULLET ||
          gamestate.ammotype == AMMO_PLASMABOLT)
      {
        gamestate.ammotype = 0;
      }

      if (gamestate.clips > 0)
      {
        gamestate.ammoinclip = 90;
        gamestate.clips--;
      }
    }

    if (gamestate.ammotype != AMMO_PLASMABOLT)
    {
      SD_PlaySound(12);
    }

    gamestate.ammoinclip--;

    if (gamestate.ammotype == 0)
    {
      gamestate.rapidfire = true;
    }

    if ((gamestate.ammoinclip & 1) && gamestate.hasrobopal)
    {
      robopalfire = true;
    }
  }
  else
  {
    if (gamestate.ammotype == AMMO_SUPERBULLET ||
        gamestate.ammotype == AMMO_PLASMABOLT)
    {
      gamestate.ammotype = 0;
    }

    if (gamestate.clips > 0)
    {
      gamestate.ammoinclip = 90;
      gamestate.clips--;
      return;
    }

    if (gamestate.ammotype != AMMO_PLASMABOLT)
    {
      SD_PlaySound(12);
    }

    gamestate.rapidfire = false;

    if (gamestate.hasrobopal)
    {
      robopalfire = true;
    }
  }

  tilex = CONVERT_GLOBAL_TO_TILE(x);
  tiley = CONVERT_GLOBAL_TO_TILE(y);
  top = y - 4*PIXGLOBAL;
  bottom = y + 4*PIXGLOBAL;
  i = 20;

  if (gamestate.ammotype == AMMO_PLASMABOLT)
  {
    SpawnLaserShot(x, y - 2*PIXGLOBAL, xdir);
    return;
  }

  do
  {
    // Check if we've hit an actor
    for (ob = player->next; ob; ob = ob->next)
    {
      if (
        ob->active && ob->var1 &&
        ob->tileleft <= tilex && ob->tileright >= tilex &&
        ob->top <= bottom && ob->bottom >= top)
      {
        SpawnBulletImpact(ob->midx, y);

        switch (ob->obclass)
        {
          case 40:
            if (ob->state == &s_200 || ob->state == &s_201)
            {
              return;
            }
            break;

          case 36:
          case 21:
          case 27:
          case 39:
            return;
        }

        if (gamestate.ammotype == AMMO_SUPERBULLET)
        {
          DealDamage(ob, 2);
        }
        else
        {
          DealDamage(ob, damage);
        }

        return;
      }
    }

    // Check if we've hit a wall
    maptile = *(mapsegs[1] + mapbwidthtable[tiley]/2 + tilex);

    if ((tinf[NORTHWALL + maptile] & 7) > 1 || (tinf[SOUTHWALL + maptile] & 7) > 1)
    {
      SpawnBulletImpact(CONVERT_TILE_TO_GLOBAL(tilex) + 8*PIXGLOBAL, y);

      if (US_RndT() < 16)
      {
        SD_PlaySound(13);
      }

      return;
    }

    if (xdir == -1)
    {
      if (tinf[EASTWALL + maptile])
      {
        SpawnBulletImpact(CONVERT_TILE_TO_GLOBAL(tilex+1), y);
      }

      if (US_RndT() < 16)
      {
        SD_PlaySound(13);
      }

      return;
    }
    else
    {
      if (tinf[WESTWALL + maptile])
      {
        SpawnBulletImpact(CONVERT_TILE_TO_GLOBAL(tilex), y);
      }

      if (US_RndT() < 16)
      {
        SD_PlaySound(13);
      }

      return;
    }

    // Advance to next tile position
    tilex += xdir;
    i--;
  }
  while (i);
}


void ChunkBloom(objtype* ob, Uint16 x, Uint16 y, Direction dir)
{
  Sint16 temp;

  SD_PlaySound(8);

  GetNewObj(true);
  new->active = ac_removable;
  new->obclass = inertobj;
  new->x = x;
  new->y = y;
  new->ydir = -1;

  switch (dir)
  {
    case dir_North:
      new->xdir = 1;
      new->xspeed = 6;
      new->yspeed = -30;
      break;

    case dir_East:
      new->xdir = 1;
      new->xspeed = US_RndT() / 8 + 10;
      new->yspeed = US_RndT() / 8 - 20;
      break;

    case dir_South:
      new->xdir = -1;
      new->xspeed = -6;
      new->yspeed = -30;
      break;

    case dir_West:
      new->xdir = -1;
      new->xspeed = -10 - US_RndT() / 8;
      new->yspeed = US_RndT() / 8 - 20;
      break;

    default:
      Quit("ChunkBloom: Bad dir!");
  }

  switch (ob->obclass)
  {
    case 36:
    case 20:
    case 23:
    case 28:
    case 41:
    case 42:
      new->temp1 = true;
      NewState(new, &s_97);
      break;

    default:
      temp = US_RndT();

      if (temp < 85)
      {
        NewState(new, &s_90);
      }
      else if (temp > 85 && temp < 170)
      {
        NewState(new, &s_92);
      }
      else
      {
        NewState(new, &s_94);
      }
      break;
  }
}


void sub_1d9a4(objtype* ob)
{
  Uint16 wall, absx, absy, angle, newangle;
  Uint32 speed;

  PLACESPRITE;

  if (ob->hiteast || ob->hitwest)
  {
    ob->xspeed = -ob->xspeed/2;
    ob->obclass = 6;
  }

  wall = ob->hitnorth;
  if (wall)
  {
    ob->obclass = 6;

    if (ob->yspeed < 0)
      ob->yspeed = 0;

    absx = abs(ob->xspeed);
    absy = ob->yspeed;
    if (absx>absy)
    {
      if (absx>absy*2)  // 22 degrees
      {
        angle = 0;
        speed = absx*286; // x*sqrt(5)/2
      }
      else        // 45 degrees
      {
        angle = 1;
        speed = absx*362; // x*sqrt(2)
      }
    }
    else
    {
      if (absy>absx*2)  // 90 degrees
      {
        angle = 3;
        speed = absy*256;
      }
      else
      {
        angle = 2;    // 67 degrees
        speed = absy*286; // y*sqrt(5)/2
      }
    }
    if (ob->xspeed > 0)
      angle = 7-angle;

    speed >>= 1;
    newangle = bounceangle[ob->hitnorth][angle];
    switch (newangle)
    {
    case 0:
      ob->xspeed = speed / 286;
      ob->yspeed = -ob->xspeed / 2;
      break;
    case 1:
      ob->xspeed = speed / 362;
      ob->yspeed = -ob->xspeed;
      break;
    case 2:
      ob->yspeed = -(speed / 286);
      ob->xspeed = -ob->yspeed / 2;
      break;
    case 3:

    case 4:
      ob->xspeed = 0;
      ob->yspeed = -(speed / 256);
      break;
    case 5:
      ob->yspeed = -(speed / 286);
      ob->xspeed = ob->yspeed / 2;
      break;
    case 6:
      ob->xspeed = ob->yspeed = -(speed / 362);
      break;
    case 7:
      ob->xspeed = -(speed / 286);
      ob->yspeed = ob->xspeed / 2;
      break;

    case 8:
      ob->xspeed = -(speed / 286);
      ob->yspeed = -ob->xspeed / 2;
      break;
    case 9:
      ob->xspeed = -(speed / 362);
      ob->yspeed = -ob->xspeed;
      break;
    case 10:
      ob->yspeed = speed / 286;
      ob->xspeed = -ob->yspeed / 2;
      break;
    case 11:

    case 12:
      ob->xspeed = 0;
      ob->yspeed = -(speed / 256);
      break;
    case 13:
      ob->yspeed = speed / 286;
      ob->xspeed = ob->yspeed / 2;
      break;
    case 14:
      ob->xspeed = speed / 362;
      ob->yspeed = speed / 362;
      break;
    case 15:
      ob->xspeed = speed / 286;
      ob->yspeed = ob->xspeed / 2;
      break;
    }

    if (speed < 256*16)
    {
      ob->y += 8*PIXGLOBAL;

      if (!ob->temp1)
      {
        ChangeState(ob, &s_96);
      }
      else
      {
        ChangeState(ob, &s_101);
      }

      return;
    }
  }
}


void FragBloom(Uint16 x, Uint16 y, Direction dir)
{
  Sint16 speed = 1;

  GetNewObj(true);
  new->active = ac_removable;
  new->obclass = 5;
  new->temp1 = -1;
  new->temp2 = dir;
  new->x = x;
  new->y = y;
  new->ydir = -1;

  if (dir >= 20)
  {
    dir -= 20;
    new->var2 = 1;
    speed = US_RndT() / 4 + 15;
  }

  if (dir >= 10)
  {
    dir -= 10;
    new->var2 = 1;
  }

  switch (dir)
  {
    case dir_North:
      new->xspeed = 0;
      new->yspeed = -20;
      break;

    case dir_South:
      new->xspeed = 0;
      new->yspeed = 20;
      break;

    case dir_East:
      new->xdir = 1;
      new->xspeed = speed + 20;
      new->yspeed = -20;
      break;

    case dir_West:
      new->xdir = -1;
      new->xspeed = -20 - speed;
      new->yspeed = -20;
      break;

    default:
      Quit("FragBloom: Bad dir!");
  }

  NewState(new, &s_102);
}


void sub_1de52(objtype* ob, objtype* hit)
{
  if (
    !hit->var1 || hit->dmgflash || hit->obclass == 21 || hit->obclass == 20 ||
    hit->obclass == 27 || hit->obclass == 40 ||
    (hit->obclass == playerobj && ob->var2 == 1))
  {
    return;
  }

  DealDamage(hit, 1);
  hit->dmgflash = 25;
  RemoveObj(ob);
}


void sub_1dea7(objtype* ob)
{
  Uint16 wall, absx, absy, angle, newangle;
  Uint32 speed;

  PLACESPRITE;

  if (ob->hiteast || ob->hitwest)
  {
    ob->xspeed= -ob->xspeed/2;
  }

  if (ob->hitsouth)
  {
    ob->yspeed= -ob->yspeed/2;
  }

  wall = ob->hitnorth;
  if (wall)
  {
    if (ob->yspeed < 0)
      ob->yspeed = 0;

    absx = abs(ob->xspeed);
    absy = ob->yspeed;
    if (absx>absy)
    {
      if (absx>absy*2)  // 22 degrees
      {
        angle = 0;
        speed = absx*286; // x*sqrt(5)/2
      }
      else        // 45 degrees
      {
        angle = 1;
        speed = absx*362; // x*sqrt(2)
      }
    }
    else
    {
      if (absy>absx*2)  // 90 degrees
      {
        angle = 3;
        speed = absy*256;
      }
      else
      {
        angle = 2;    // 67 degrees
        speed = absy*286; // y*sqrt(5)/2
      }
    }
    if (ob->xspeed > 0)
      angle = 7-angle;

    speed >>= 1;
    newangle = bounceangle[ob->hitnorth][angle];
    switch (newangle)
    {
    case 0:
      ob->xspeed = speed / 286;
      ob->yspeed = -ob->xspeed / 2;
      break;
    case 1:
      ob->xspeed = speed / 362;
      ob->yspeed = -ob->xspeed;
      break;
    case 2:
      ob->yspeed = -(speed / 286);
      ob->xspeed = -ob->yspeed / 2;
      break;
    case 3:

    case 4:
      ob->xspeed = 0;
      ob->yspeed = -(speed / 256);
      break;
    case 5:
      ob->yspeed = -(speed / 286);
      ob->xspeed = ob->yspeed / 2;
      break;
    case 6:
      ob->xspeed = ob->yspeed = -(speed / 362);
      break;
    case 7:
      ob->xspeed = -(speed / 286);
      ob->yspeed = ob->xspeed / 2;
      break;

    case 8:
      ob->xspeed = -(speed / 286);
      ob->yspeed = -ob->xspeed / 2;
      break;
    case 9:
      ob->xspeed = -(speed / 362);
      ob->yspeed = -ob->xspeed;
      break;
    case 10:
      ob->yspeed = speed / 286;
      ob->xspeed = -ob->yspeed / 2;
      break;
    case 11:

    case 12:
      ob->xspeed = 0;
      ob->yspeed = -(speed / 256);
      break;
    case 13:
      ob->yspeed = speed / 286;
      ob->xspeed = ob->yspeed / 2;
      break;
    case 14:
      ob->xspeed = speed / 362;
      ob->yspeed = speed / 362;
      break;
    case 15:
      ob->xspeed = speed / 286;
      ob->yspeed = ob->xspeed / 2;
      break;
    }

    if (speed < 256*16)
    {
      RemoveObj(ob);
      return;
    }
  }
}


void T_GrenadeExplosion(objtype* ob)
{
  (void)ob;
  SD_PlaySound(7);
}


void ThrowGrenade(Uint16 x, Uint16 y, Direction dir)
{
  if (!gamestate.explosives.landmines && !gamestate.explosives.grenades &&
      !gamestate.explosives.redgrenades)
  {
    return;
  }

  if (gamestate.explosives.landmines > 0)
  {
    SpawnLandMine(x >> G_T_SHIFT, y >> G_T_SHIFT);
    gamestate.explosives.landmines--;
    ChangeState(player, &s_player_place_mine);
    return;
  }

  GetNewObj(true);
  new->obclass = 3;
  new->active = ac_allways;
  new->temp2 = dir;
  new->x = x;
  new->y = y;
  new->ydir = -1;

  if (gamestate.explosives.redgrenades > 0)
  {
    gamestate.explosives.redgrenades--;
    new->temp7 = true;
  }
  else
  {
    gamestate.explosives.grenades--;
  }

  switch (dir)
  {
    case dir_East:
      new->xspeed = 45;
      new->yspeed = -16;
      new->xdir = 1;
      break;

    case dir_West:
      new->xspeed = -45;
      new->yspeed = -16;
      new->xdir = -1;
      break;

    default:
      Quit("ThrowPower: Bad dir!");
  }

  new->temp1 = 9;
  new->var2 = 1;
  new->active = ac_removable;

  if (new->temp7)
  {
    NewState(new, &s_110);
    new->active = ac_allways;

    if (!StatePositionOk(new, &s_110))
    {
      new->hitnorth = 1;
    }

    return;
  }

  NewState(new, &s_106);

  if (!StatePositionOk(new, &s_106))
  {
    new->hitnorth = 1;
  }
}


void sub_1e34c(objtype* ob)
{
  ob->temp2 = ob->temp2 + tics;
  ob->shapenum = 0;

  if (ob->temp2 > 50)
  {
    RemoveObj(ob);
  }
}


void C_Grenade(objtype* ob, objtype* hit)
{
  if (hit->var1 && hit->obclass != 21)
  {
    FragBloom(ob->x + 2*PIXGLOBAL, ob->y - 8*PIXGLOBAL, 12);
    FragBloom(ob->x - 2*PIXGLOBAL, ob->y - 8*PIXGLOBAL, 16);

    ChangeState(ob, &s_114);

    ob->obclass = 5;

    SD_PlaySound(7);

    ob->needtoclip = true;
  }
}


void C_GrenadeExplosion(objtype* ob, objtype* hit)
{
  if (
    !hit->var1 || hit->dmgflash || hit->obclass == 21 || hit->obclass == 27 ||
    hit->obclass == 40 || (hit->obclass == playerobj && ob->var2 == 1))
  {
    return;
  }

  DealDamage(hit, 5);
  hit->dmgflash = 25;

  ob++;
}


void R_Grenade(objtype* ob)
{
  Uint16 wall, absx, absy, angle, newangle;
  Uint32 speed;

  PLACESPRITE;

  if (ob->hiteast || ob->hitwest)
  {
    ob->xspeed= -ob->xspeed/2;
  }

  if (ob->hitsouth)
  {
    ob->yspeed= -ob->yspeed/2;
  }

  wall = ob->hitnorth;
  if (wall)
  {
    if (ob->yspeed < 0)
      ob->yspeed = 0;

    absx = abs(ob->xspeed);
    absy = ob->yspeed;
    if (absx>absy)
    {
      if (absx>absy*2)  // 22 degrees
      {
        angle = 0;
        speed = absx*286; // x*sqrt(5)/2
      }
      else        // 45 degrees
      {
        angle = 1;
        speed = absx*362; // x*sqrt(2)
      }
    }
    else
    {
      if (absy>absx*2)  // 90 degrees
      {
        angle = 3;
        speed = absy*256;
      }
      else
      {
        angle = 2;    // 67 degrees
        speed = absy*286; // y*sqrt(5)/2
      }
    }
    if (ob->xspeed > 0)
      angle = 7-angle;

    speed >>= 1;
    newangle = bounceangle[ob->hitnorth][angle];
    switch (newangle)
    {
    case 0:
      ob->xspeed = speed / 286;
      ob->yspeed = -ob->xspeed / 2;
      break;
    case 1:
      ob->xspeed = speed / 362;
      ob->yspeed = -ob->xspeed;
      break;
    case 2:
      ob->yspeed = -(speed / 286);
      ob->xspeed = -ob->yspeed / 2;
      break;
    case 3:

    case 4:
      ob->xspeed = 0;
      ob->yspeed = -(speed / 256);
      break;
    case 5:
      ob->yspeed = -(speed / 286);
      ob->xspeed = ob->yspeed / 2;
      break;
    case 6:
      ob->xspeed = ob->yspeed = -(speed / 362);
      break;
    case 7:
      ob->xspeed = -(speed / 286);
      ob->yspeed = ob->xspeed / 2;
      break;

    case 8:
      ob->xspeed = -(speed / 286);
      ob->yspeed = -ob->xspeed / 2;
      break;
    case 9:
      ob->xspeed = -(speed / 362);
      ob->yspeed = -ob->xspeed;
      break;
    case 10:
      ob->yspeed = speed / 286;
      ob->xspeed = -ob->yspeed / 2;
      break;
    case 11:

    case 12:
      ob->xspeed = 0;
      ob->yspeed = -(speed / 256);
      break;
    case 13:
      ob->yspeed = speed / 286;
      ob->xspeed = ob->yspeed / 2;
      break;
    case 14:
      ob->xspeed = speed / 362;
      ob->yspeed = speed / 362;
      break;
    case 15:
      ob->xspeed = speed / 286;
      ob->yspeed = ob->xspeed / 2;
      break;
    }

    if (speed < 256*16)
    {
      if (ob->temp7)
      {
        FragBloom(ob->x + 2*PIXGLOBAL, ob->y - 8*PIXGLOBAL, 12);
        FragBloom(ob->x - 2*PIXGLOBAL, ob->y - 8*PIXGLOBAL, 16);

        ob->obclass = 5;
        ob->needtoclip = true;
        ob->x = ob->x - 8*PIXGLOBAL;
        ob->y = ob->y - 24*PIXGLOBAL;
        ob->temp7 = 50;

        ChangeState(ob, &s_186);
      }
      else
      {
        FragBloom(ob->x + 2*PIXGLOBAL, ob->y - 8*PIXGLOBAL, 12);
        FragBloom(ob->x - 2*PIXGLOBAL, ob->y - 8*PIXGLOBAL, 16);

        ob->obclass = 5;

        ChangeState(ob, &s_114);
      }

      return;
    }
  }
}


void SpawnShot(Uint16 x, Uint16 y, Sint16 dir)
{
  GetNewObj(true);
  new->x = x;
  new->y = y;
  new->priority = 0;
  new->obclass = 17;
  new->active = ac_allways;

  SD_PlaySound(29);

  switch (dir)
  {
    case 1:
      new->xdir = 1;
      new->ydir = 0;
      break;

    case -1:
      new->xdir = -1;
      new->ydir = 0;
      break;

    default:
      Quit("SpawnShot: Bad dir!");
  }

  NewState(new, &s_120);
}


void SpawnLaserShot(Uint16 x, Uint16 y, Sint16 dir)
{
  GetNewObj(true);
  new->x = x;
  new->y = y;
  new->priority = 0;
  new->obclass = 17;
  new->active = ac_allways;

  SD_PlaySound(21);

  new->temp7 = 1;

  switch (dir)
  {
    case 1:
      new->xdir = 1;
      new->ydir = 0;
      break;

    case -1:
      new->xdir = -1;
      new->ydir = 0;
      break;

    default:
      Quit("SpawnLaserShot: Bad dir!");
  }

  NewState(new, &s_lasershot);
}


void SpawnSuperPlasmaBolt(Uint16 x, Uint16 y, Sint16 dir)
{
  GetNewObj(true);
  new->x = x;
  new->y = y;
  new->priority = 2;
  new->obclass = 17;
  new->active = ac_allways;

  SD_PlaySound(7);

  new->temp7 = 0;

  switch (dir)
  {
    case 1:
      new->xdir = 1;
      new->ydir = 0;
      break;

    case -1:
      new->xdir = -1;
      new->ydir = 0;
      break;

    default:
      Quit("SpawnLaserShot: Bad dir!");
  }

  NewState(new, &s_superplasmabolt);
}


void C_Shot(objtype* ob, objtype* hit)
{
  if (hit->var1 && hit->obclass != 21 && hit->obclass != 27)
  {
    DealDamage(hit, 1);
    ChangeState(ob, &s_124);
  }

  ob++;
}


void C_LaserShot(objtype* ob, objtype* hit)
{
  if (hit->var1 && hit->obclass != 21 && hit->obclass != 27)
  {
    if (ob->temp7 == 1)
    {
      DealDamage(hit, 5);
      ChangeState(ob, &s_126);
    }
    else
    {
      DealDamage(hit, 2);
    }
  }

  ob++;
}


void ExplodeShot(objtype* ob)
{
  ob->obclass = inertobj;

  if (ob->temp7 == 1)
  {
    ChangeState(ob, &s_126);
  }
  else
  {
    ChangeState(ob, &s_124);
  }

  SD_PlaySound(30);
}


void T_Shot(objtype* ob)
{
  objtype *ob2;

  if (ob->tileright >= originxtile && ob->tilebottom >= originytile
    && ob->tileleft <= originxtilemax && ob->tiletop <= originytilemax)
  {
    //object is visible, so do nothing
    return;
  }

  if (ob->tileright+10 < originxtile
    || ob->tileleft-10 > originxtilemax
    || ob->tilebottom+6 < originytile
    || ob->tiletop-6 > originytilemax)
  {
    //shot is off-screen by more than half a screen, so remove it
    RemoveObj(ob);
    return;
  }

  //check for collisions with INACTIVE objects
  for (ob2 = player->next; ob2; ob2 = ob2->next)
  {
    if (!ob2->active && ob->right > ob2->left && ob->left < ob2->right
      && ob->top < ob2->bottom && ob->bottom > ob2->top)
    {
      if (ob2->state->contact)
      {
        ob2->state->contact(ob2, ob);
        ob2->needtoreact = true;
        ob2->active = ac_yes;
      }

      if (ob->obclass == nothing) //BUG: obclass is 'inertobj' for the exploded shot
        break;
    }
  }
}


void R_Shot(objtype* ob)
{
  if (ob->hitnorth || ob->hitsouth || ob->hiteast || ob->hitwest)
  {
    ExplodeShot(ob);
  }

  PLACESPRITE
}


void R_SuperPlasmaBolt(objtype* ob)
{
  if (ob->hitnorth || ob->hitsouth || ob->hiteast || ob->hitwest)
  {
    ChangeState(ob, &s_114);
  }

  PLACESPRITE
}
