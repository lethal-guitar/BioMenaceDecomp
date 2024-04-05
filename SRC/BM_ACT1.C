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

#include "BM_ACT.H"
#include "BM_DEF.H"


Sint16 pdirx[] = {  0, 1, 0, -1,  1, 1, -1, -1 };
Sint16 pdiry[] = { -1, 0, 1,  0, -1, 1,  1, -1 };

extern statetype far s_128;
extern statetype far s_129;
extern statetype far s_130;
extern statetype far s_131;
extern statetype far s_132;
extern statetype far s_133;
extern statetype far s_134;
extern statetype far s_135;
extern statetype far s_136;
extern statetype far s_137;
extern statetype far s_138;
extern statetype far s_139;
extern statetype far s_140;
extern statetype far s_141;
extern statetype far s_142;
extern statetype far s_143;
extern statetype far s_144;
extern statetype far s_145;
extern statetype far s_146;
extern statetype far s_147;
extern statetype far s_148;
extern statetype far s_149;
extern statetype far s_150;
extern statetype far s_151;
extern statetype far s_152;
extern statetype far s_153;
extern statetype far s_154;
extern statetype far s_155;
extern statetype far s_156;
extern statetype far s_157;
extern statetype far s_158;
extern statetype far s_159;
extern statetype far s_160;
extern statetype far s_161;
extern statetype far s_162;
extern statetype far s_163;
extern statetype far s_164;
extern statetype far s_165;
extern statetype far s_166;
extern statetype far s_167;
extern statetype far s_168;
extern statetype far s_169;
extern statetype far s_170;
extern statetype far s_171;
extern statetype far s_172;
extern statetype far s_173;
extern statetype far s_174;
extern statetype far s_175;
extern statetype far s_176;
extern statetype far s_177;
extern statetype far s_178;
extern statetype far s_179;
extern statetype far s_180;
extern statetype far s_181;
extern statetype far s_182;
extern statetype far s_183;
extern statetype far s_184;
extern statetype far s_185;
extern statetype far s_186;
extern statetype far s_187;
extern statetype far s_188;
extern statetype far s_189;
extern statetype far s_190;
extern statetype far s_191;
extern statetype far s_192;
extern statetype far s_193;
extern statetype far s_194;
extern statetype far s_195;
extern statetype far s_196;
extern statetype far s_197;
extern statetype far s_198;
extern statetype far s_199;
extern statetype far s_200;
extern statetype far s_201;
extern statetype far s_202;
extern statetype far s_203;
extern statetype far s_204;
extern statetype far s_205;
extern statetype far s_206;
extern statetype far s_207;
extern statetype far s_208;
extern statetype far s_209;
extern statetype far s_210;
extern statetype far s_211;
extern statetype far s_212;
extern statetype far s_213;
extern statetype far s_214;
extern statetype far s_215;
extern statetype far s_216;
extern statetype far s_217;
extern statetype far s_218;
extern statetype far s_219;
extern statetype far s_220;
extern statetype far s_221;
extern statetype far s_222;
extern statetype far s_223;
extern statetype far s_224;
extern statetype far s_225;
extern statetype far s_226;
extern statetype far s_227;
extern statetype far s_228;
extern statetype far s_229;
extern statetype far s_230;
extern statetype far s_231;
extern statetype far s_232;
extern statetype far s_233;
extern statetype far s_234;
extern statetype far s_235;
extern statetype far s_236;
extern statetype far s_237;
extern statetype far s_238;
extern statetype far s_239;
extern statetype far s_240;
extern statetype far s_241;
extern statetype far s_242;
extern statetype far s_243;
extern statetype far s_244;
extern statetype far s_245;
extern statetype far s_246;
extern statetype far s_247;
extern statetype far s_248;
extern statetype far s_249;
extern statetype far s_250;
extern statetype far s_251;
extern statetype far s_252;
extern statetype far s_253;
extern statetype far s_254;
extern statetype far s_255;
extern statetype far s_256;
extern statetype far s_257;
extern statetype far s_258;
extern statetype far s_259;
extern statetype far s_260;
extern statetype far s_261;
extern statetype far s_262;
extern statetype far s_263;
extern statetype far s_264;
extern statetype far s_265;
extern statetype far s_266;
extern statetype far s_267;
extern statetype far s_268;
extern statetype far s_269;
extern statetype far s_270;
extern statetype far s_271;
extern statetype far s_272;
extern statetype far s_273;
extern statetype far s_274;
extern statetype far s_275;
extern statetype far s_276;
extern statetype far s_277;
extern statetype far s_278;
extern statetype far s_279;
extern statetype far s_280;
extern statetype far s_281;
extern statetype far s_282;
extern statetype far s_283;
extern statetype far s_284;
extern statetype far s_285;
extern statetype far s_286;
extern statetype far s_287;
extern statetype far s_288;
extern statetype far s_289;
extern statetype far s_290;
extern statetype far s_291;
extern statetype far s_292;
extern statetype far s_293;
extern statetype far s_294;
extern statetype far s_295;
extern statetype far s_296;
extern statetype far s_297;
extern statetype far s_298;
extern statetype far s_299;
extern statetype far s_300;
extern statetype far s_301;
extern statetype far s_302;
extern statetype far s_303;
extern statetype far s_304;
extern statetype far s_305;
extern statetype far s_306;
extern statetype far s_307;
extern statetype far s_308;

extern boolean bossactivated;
extern Sint16 unknown;
extern Sint16 word_389AA;


void R_EnemyProjectile(objtype* ob);
void T_Platform(objtype* ob);
void T_GoPlat(objtype* ob);
void R_Helicopter(objtype* ob);
void SpawnParachuteBot(objtype* ob);
void T_ParachuteBot(objtype* ob);
void C_ParachuteBotAttack(objtype* ob, objtype* hit);
void R_ParachuteBot(objtype* ob);
void R_ParachuteBotAttack(objtype* ob);
void T_SpitterSnake2(objtype* ob);
void SpitterSnakeSpit(objtype* ob);
void T_SpitterSnake(objtype* ob);
void SewerMutantThrow(objtype* ob);
void T_SewerMutant(objtype* ob);
void T_DrMangleHologram(objtype* ob);
void sub_20f20(objtype* ob);
void sub_2106d(objtype* ob);
void T_DrMangle();
void DrMangleDefeated(objtype* ob);
void R_DrMangleJumping();

void C_GrenadeExplosion(objtype* ob, objtype* hit);

statetype far s_128 = { /* 32250 */
  PLATFORMSPR, PLATFORMSPR,
  think, false, ps_none, 0, 0, 0,
  T_Platform, NULL, R_Draw, NULL};

statetype far s_129 = { /* 32270 */
  APOGEELOGOSPR, APOGEELOGOSPR,
  think, false, ps_none, 0, 0, 0,
  T_Platform, NULL, R_Draw, NULL};

statetype far s_130 = { /* 32290 */
  HELICOPTER2_SPR, HELICOPTER2_SPR,
  stepthink, false, ps_none, 1, 0, 0,
  T_GoPlat, NULL, R_Helicopter, &s_130};

statetype far s_131 = { /* 322b0 */
  HELICOPTER1_SPR, HELICOPTER1_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  T_GoPlat, NULL, R_Helicopter, &s_130};

statetype far s_132 = { /* 322d0 */
  HELICOPTER1_SPR, HELICOPTER1_SPR,
  stepthink, false, ps_none, 1, 0, 0,
  T_GoPlat, NULL, SpawnParachuteBot, &s_130};

statetype far s_133 = { /* 322f0 */
  PARACHUTEBOT_WALK1_L_SPR, PARACHUTEBOT_WALK1_R_SPR,
  step, false, ps_tofloor, 10, 128, 0,
  T_ParachuteBot, NULL, R_Walk, &s_134};

statetype far s_134 = { /* 32310 */
  PARACHUTEBOT_WALK2_L_SPR, PARACHUTEBOT_WALK2_R_SPR,
  step, false, ps_tofloor, 10, 128, 0,
  T_ParachuteBot, NULL, R_Walk, &s_133};

statetype far s_135 = { /* 32330 */
  PARACHUTEBOT_WALK2_L_SPR, PARACHUTEBOT_WALK2_R_SPR,
  think, false, ps_none, 0, 0, 0,
  T_Projectile, C_ParachuteBotAttack, R_ParachuteBotAttack, &s_135};

statetype far s_136 = { /* 32350 */
  PARACHUTEBOT_FALLING_L_SPR, PARACHUTEBOT_FALLING_R_SPR,
  stepthink, false, ps_none, 10, 8, 32,
  NULL, C_ParachuteBotAttack, R_ParachuteBot, &s_136};

statetype far s_137 = { /* 32370 */
  SPITSNAKE_WALK1_L_SPR, SPITSNAKE_WALK1_R_SPR,
  step, false, ps_tofloor, 10, 128, 0,
  T_SpitterSnake, NULL, R_Walk, &s_138};

statetype far s_138 = { /* 32390 */
  SPITSNAKE_WALK2_L_SPR, SPITSNAKE_WALK2_R_SPR,
  step, false, ps_tofloor, 10, 128, 0,
  T_SpitterSnake, NULL, R_Walk, &s_137};

statetype far s_139 = { /* 323b0 */
  SPITSNAKE_WALK1_L_SPR, SPITSNAKE_WALK1_R_SPR,
  step, true, ps_tofloor, 5, 128, 0,
  T_SpitterSnake2, NULL, R_Walk, &s_140};

statetype far s_140 = { /* 323d0 */
  SPITSNAKE_WALK2_L_SPR, SPITSNAKE_WALK2_R_SPR,
  step, true, ps_tofloor, 5, 128, 0,
  T_SpitterSnake2, NULL, R_Walk, &s_139};

statetype far s_141 = { /* 323f0 */
  SPITSNAKE_ATTACK_L_SPR, SPITSNAKE_ATTACK_R_SPR,
  step, false, ps_none, 10, 0, 0,
  SpitterSnakeSpit, NULL, R_Draw, &s_142};

statetype far s_142 = { /* 32410 */
  SPITSNAKE_ATTACK_L_SPR, SPITSNAKE_ATTACK_R_SPR,
  step, false, ps_none, 10, 65408, 0,
  NULL, NULL, R_Draw, &s_137};

statetype far s_143 = { /* 32430 */
  SPITSNAKE_SPIT1_L_SPR, SPITSNAKE_SPIT1_R_SPR,
  stepthink, false, ps_none, 4, 0, 0,
  T_Projectile, NULL, R_EnemyProjectile, &s_144};

statetype far s_144 = { /* 32450 */
  SPITSNAKE_SPIT2_L_SPR, SPITSNAKE_SPIT2_R_SPR,
  stepthink, false, ps_none, 4, 0, 0,
  T_Projectile, NULL, R_EnemyProjectile, &s_143};

statetype far s_145 = { /* 32470 */
  SEWERMUTANT_WALK1_L_SPR, SEWERMUTANT_WALK1_R_SPR,
  step, false, ps_tofloor, 20, 128, 0,
  T_SewerMutant, NULL, R_Walk, &s_146};

statetype far s_146 = { /* 32490 */
  SEWERMUTANT_WALK2_L_SPR, SEWERMUTANT_WALK2_R_SPR,
  step, false, ps_tofloor, 20, 128, 0,
  T_SewerMutant, NULL, R_Walk, &s_145};

statetype far s_147 = { /* 324b0 */
  SEWERMUTANT_ATTACK_L_SPR, SEWERMUTANT_ATTACK_R_SPR,
  step, false, ps_tofloor, 10, 0, 0,
  SewerMutantThrow, NULL, R_Walk, &s_145};

statetype far s_148 = { /* 324d0 */
  SEWERMUTANT_SPIT1_SPR, SEWERMUTANT_SPIT1_SPR,
  stepthink, false, ps_none, 4, 0, 0,
  T_Projectile, NULL, R_EnemyProjectile, &s_149};

statetype far s_149 = { /* 324f0 */
  SEWERMUTANT_SPIT2_SPR, SEWERMUTANT_SPIT2_SPR,
  stepthink, false, ps_none, 4, 0, 0,
  T_Projectile, NULL, R_EnemyProjectile, &s_148};

statetype far s_150 = { /* 32510 */
  HOSTAGE1_1_SPR, HOSTAGE1_1_SPR,
  step, false, ps_tofloor, 40, 0, 0,
  NULL, NULL, R_Draw, &s_151};

statetype far s_151 = { /* 32530 */
  HOSTAGE1_2_SPR, HOSTAGE1_2_SPR,
  step, false, ps_tofloor, 40, 0, 0,
  NULL, NULL, R_Draw, &s_150};

statetype far s_152 = { /* 32550 */
  HOSTAGE2_1_SPR, HOSTAGE2_1_SPR,
  step, false, ps_tofloor, 40, 0, 0,
  NULL, NULL, R_Draw, &s_153};

statetype far s_153 = { /* 32570 */
  HOSTAGE2_2_SPR, HOSTAGE2_2_SPR,
  step, false, ps_tofloor, 40, 0, 0,
  NULL, NULL, R_Draw, &s_152};

statetype far s_154 = { /* 32590 */
  HOSTAGE3_1_SPR, HOSTAGE3_1_SPR,
  step, false, ps_tofloor, 40, 0, 0,
  NULL, NULL, R_Draw, &s_155};

statetype far s_155 = { /* 325b0 */
  HOSTAGE3_2_SPR, HOSTAGE3_2_SPR,
  step, false, ps_tofloor, 40, 0, 0,
  NULL, NULL, R_Draw, &s_154};

statetype far s_156 = { /* 325d0 */
  MANGLE_HOLOGRAM1_SPR, MANGLE_HOLOGRAM1_SPR,
  step, false, ps_none, 10, 0, 0,
  T_DrMangleHologram, NULL, R_Draw, &s_156};

statetype far s_157 = { /* 325f0 */
  MANGLE_HOLOGRAM2_SPR, MANGLE_HOLOGRAM2_SPR,
  step, false, ps_none, 10, 0, 0,
  T_DrMangleHologram, NULL, R_Draw, &s_156};

statetype far s_158 = { /* 32610 */
  MANGLE_HOLOGRAM3_SPR, MANGLE_HOLOGRAM3_SPR,
  step, false, ps_none, 200, 0, 0,
  T_DrMangleHologram, NULL, R_Draw, &s_156};

statetype far s_159 = { /* 32630 */
  MANGLE_HOLOGRAM_FADE1_SPR, MANGLE_HOLOGRAM_FADE1_SPR,
  step, false, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, &s_156};

statetype far s_160 = { /* 32650 */
  MANGLE_HOLOGRAM_FADE2_SPR, MANGLE_HOLOGRAM_FADE2_SPR,
  step, false, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, &s_157};

statetype far s_161 = { /* 32670 */
  MANGLE_HOLOGRAM_FADE3_SPR, MANGLE_HOLOGRAM_FADE3_SPR,
  step, false, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, &s_158};

statetype far s_162 = { /* 32690 */
  MANGLE_HOLOGRAM_ATTACK_SPR, MANGLE_HOLOGRAM_ATTACK_SPR,
  step, false, ps_none, 3, 0, 0,
  sub_20f20, NULL, sub_2106d, &s_162};

statetype far s_163 = { /* 326b0 */
  MANGLE_TYPING1_SPR, MANGLE_TYPING1_SPR,
  step, false, ps_tofloor, 20, 0, 0,
  T_DrMangle, NULL, R_Draw, &s_164};

statetype far s_164 = { /* 326d0 */
  MANGLE_TYPING2_SPR, MANGLE_TYPING2_SPR,
  step, false, ps_tofloor, 20, 0, 0,
  T_DrMangle, NULL, R_Draw, &s_163};

statetype far s_165 = { /* 326f0 */
  MANGLE_MONSTER1_L_SPR, MANGLE_MONSTER1_R_SPR,
  step, false, ps_tofloor, 10, 128, 0,
  T_DrMangle, NULL, R_Walk, &s_166};

statetype far s_166 = { /* 32710 */
  MANGLE_MONSTER2_L_SPR, MANGLE_MONSTER2_R_SPR,
  step, false, ps_tofloor, 10, 128, 0,
  T_DrMangle, NULL, R_Walk, &s_165};

statetype far s_167 = { /* 32730 */
  MANGLE_MONSTER2_L_SPR, MANGLE_MONSTER2_R_SPR,
  think, false, ps_none, 0, 0, 0,
  T_Projectile, NULL, R_DrMangleJumping, &s_167};

statetype far s_168 = { /* 32750 */
  MANGLE_DEFEATED_SPR, MANGLE_DEFEATED_SPR,
  step, false, ps_tofloor, 200, 0, 0,
  NULL, NULL, R_Draw, &s_169};

statetype far s_169 = { /* 32770 */
  MANGLE_DEFEATED_SPR, MANGLE_DEFEATED_SPR,
  step, false, ps_tofloor, 2, 0, 0,
  DrMangleDefeated, NULL, R_Draw, &s_169};

statetype far s_170 = { /* 32790 */
  MANGLE_DEFEATED_SPR, MANGLE_DEFEATED_SPR,
  think, false, ps_tofloor, 0, 0, 0,
  NULL, NULL, R_Draw, &s_170};



void R_EnemyProjectile(objtype* ob)
{
  Uint16 wall, absx, absy, angle, newangle;
  Uint32 speed;

  PLACESPRITE;

  if (ob->hiteast || ob->hitwest)
  {
    ob->xspeed = -ob->xspeed/2;
  }

  if (ob->hitsouth)
  {
    ob->yspeed = -ob->yspeed/2;
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
    }
  }
}


void SpawnElevator(Sint16 x, Sint16 y, arrowdirtype dir)
{
  GetNewObj(false);

  new->obclass = platformobj;
  new->active = ac_allways;
  new->priority = 1;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y);

  switch (dir)
  {
    case arrow_North:
      new->xdir = 0;
      new->ydir = -1;
      break;

    case arrow_East:
      new->xdir = 1;
      new->ydir = 0;
      break;

    case arrow_South:
      new->xdir = 0;
      new->ydir = 1;
      break;

    case arrow_West:
      new->xdir = -1;
      new->ydir = 0;
      break;

  }

  NewState(new, &s_128);
}


void SpawnApogeeLogo(Sint16 x, Sint16 y, arrowdirtype dir)
{
  GetNewObj(false);

  new->obclass = platformobj;
  new->active = ac_allways;
  new->priority = 0;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y);

  switch (dir)
  {
    case arrow_North:
      new->xdir = 0;
      new->ydir = -1;
      break;

    case arrow_East:
      new->xdir = 1;
      new->ydir = 0;
      break;

    case arrow_South:
      new->xdir = 0;
      new->ydir = 1;
      break;

    case arrow_West:
      new->xdir = -1;
      new->ydir = 0;
      break;

  }

  NewState(new, &s_129);
}


void T_Platform(objtype* ob)
{
  Uint16 newpos, newtile;

  if (xtry || ytry)
    return;

  xtry = ob->xdir * 12 * tics;
  ytry = ob->ydir * 12 * tics;

  if (ob->ydir == 1)
  {
    newpos = ob->bottom + ytry;
    newtile = CONVERT_GLOBAL_TO_TILE(newpos);

    if (ob->tilebottom != newtile)
    {
      if (*(mapsegs[2]+mapbwidthtable[newtile]/2+ob->tileleft) == PLATFORMBLOCK)
      {
        ytry = 0;
        ob->needtoreact = true;
        return;
      }
    }

    if (ob->tilebottom != newtile)
    {
      if (*(mapsegs[2]+mapbwidthtable[newtile]/2+ob->tileleft) ==
          PLATFORMBLOCK-1)
      {
        if (*(mapsegs[2]+mapbwidthtable[newtile-2]/2+ob->tileleft) ==
            PLATFORMBLOCK-1)
        {
          ytry = 0;
          ob->needtoreact = true;
          return;
        }
        else
        {
          ob->ydir = -1;
          ytry = ytry - (newpos & 0xFF);
        }
      }
    }
  }
  else if (ob->ydir == -1)
  {
    newpos = ob->top + ytry;
    newtile = CONVERT_GLOBAL_TO_TILE(newpos);

    if (ob->tiletop != newtile)
    {
      if (*(mapsegs[2]+mapbwidthtable[newtile]/2+ob->tileleft) == PLATFORMBLOCK)
      {
        ytry = 0;
        ob->needtoreact = true;
        return;
      }
    }

    if (ob->tiletop != newtile)
    {
      if (*(mapsegs[2]+mapbwidthtable[newtile]/2+ob->tileleft) == PLATFORMBLOCK-1)
      {
        if (*(mapsegs[2]+mapbwidthtable[newtile+2]/2+ob->tileleft) == PLATFORMBLOCK-1)
        {
          ytry = 0;
          ob->needtoreact = true;
          return;
        }
        else
        {
          ob->ydir = 1;
          ytry = ytry + (0x100 - (newpos & 0xFF));
        }
      }
    }
  }
}


void SpawnHelicopter(Sint16 x, Sint16 y, arrowdirtype dir)
{
  GetNewObj(false);

  new->obclass = helicopterobj;
  new->active = ac_allways;
  new->priority = 3;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y);
  new->xdir = 0;
  new->ydir = 1;
  new->needtoclip = cl_noclip;
  new->shootable = true;

  switch (gamestate.difficulty)
  {
    case gd_Hard:
      new->health = 50;
      break;

    default:
      new->health = 25;
      break;
  }

  new->temp6 = 15;
  new->temp7 = 40;

  NewState(new, &s_130);

  *(mapsegs[2] + mapbwidthtable[y]/2 + x) = DIRARROWSTART + dir;

  new->temp1 = dir;
  new->temp2 = 0x100;
}


void T_GoPlat(objtype* ob)
{
  Uint16 move;
  Uint16 tx, ty;
  Sint16 dir;

  //
  // this code could be executed twice during the same frame because the
  // object's animation/state changed during that frame, so don't update
  // anything if we already have movement for the current frame i.e. the
  // update code has already been executed this frame
  if (xtry || ytry)
    return;

  move = tics * 24;
  if (ob->temp2 > move)
  {
    ob->temp2 = ob->temp2 - move;

    dir = pdirx[ob->temp1];
    if (dir == 1)
    {
      xtry = xtry + move;
    }
    else if (dir == -1)
    {
      xtry = xtry + -move;
    }

    dir = pdiry[ob->temp1];
    if (dir == 1)
    {
      ytry = ytry + move;
    }
    else if (dir == -1)
    {
      ytry = ytry + -move;
    }
  }
  else
  {
    dir = pdirx[ob->temp1];
    if (dir == 1)
    {
      xtry += ob->temp2;
    }
    else if (dir == -1)
    {
      xtry += -ob->temp2;
    }

    dir = pdiry[ob->temp1];
    if (dir == 1)
    {
      ytry += ob->temp2;
    }
    else if (dir == -1)
    {
      ytry += -ob->temp2;
    }

    tx = CONVERT_GLOBAL_TO_TILE(ob->x + xtry);
    ty = CONVERT_GLOBAL_TO_TILE(ob->y + ytry);
    ob->temp1 = *(mapsegs[2]+mapbwidthtable[ty]/2 + tx) - DIRARROWSTART;
    if (ob->temp1 < arrow_North || ob->temp1 > arrow_None)
    {
      char error[60] = "Goplat moved to a bad spot: ";
      char buf[5] = "";

      strcat(error, itoa(ob->x, buf, 16));
      strcat(error, ",");
      strcat(error, itoa(ob->y, buf, 16));
      Quit(error);
    }

    move -= ob->temp2;
    ob->temp2 = TILEGLOBAL - move;

    dir = pdirx[ob->temp1];
    if (dir == 1)
    {
      xtry = xtry + move;
    }
    else if (dir == -1)
    {
      xtry = xtry - move;
    }

    dir = pdiry[ob->temp1];
    if (dir == 1)
    {
      ytry = ytry + move;
    }
    else if (dir == -1)
    {
      ytry = ytry - move;
    }
  }
}


void R_Helicopter(objtype* ob)
{
  if (--ob->temp6 <= 0)
  {
    ob->state = &s_131;
    ob->temp6 = 15;
  }

  if (--ob->temp7 <= 0)
  {
    ob->temp7 = 40;

    if (OnScreen(ob))
    {
      SpawnParachuteBot(ob);
    }
  }

  PLACESPRITE;
}


void SpawnParachuteBot(objtype* ob)
{
  SD_PlaySound(13);

  GetNewObj(true);

  new->obclass = parachutebotobj;
  new->priority = 2;
  new->active = ac_allways;
  new->x = ob->x + 24*PIXGLOBAL;
  new->y = ob->y + 8*PIXGLOBAL;
  new->xdir = 1;
  new->ydir = 1;
  new->shootable = true;

  switch (gamestate.difficulty)
  {
    case gd_Hard:
      new->health = 20;
      break;

    default:
      new->health = 10;
      break;
  }

  new->temp5 = 75;

  NewState(new, &s_136);
}


void T_ParachuteBot(objtype* ob)
{
  Sint16 xdelta;

  if (--ob->temp5 <= 0)
  {
    ob->shootable = false;
    ChangeState(ob, &s_grenadeexplosion1);
    return;
  }

  if (ob->top > player->bottom || ob->bottom < player->top)
    return;

  if (ob->xdir == -1)
  {
    xdelta = ob->left - player->right;

    if (xdelta > 32*PIXGLOBAL)
      return;

    if (xdelta < -8*PIXGLOBAL)
    {
      ob->xdir = 1;
      return;
    }

    ob->yspeed = -24 - US_RndT() / 16;
    ob->xspeed = -32;
    ob->state = &s_135;
    return;
  }
  else
  {
    xdelta = player->left - ob->right;

    if (xdelta > 32*PIXGLOBAL)
      return;

    if (xdelta < -8*PIXGLOBAL)
    {
      ob->xdir = -1;
    }
    else
    {
      ob->yspeed = -24 - US_RndT() / 16;
      ob->xspeed = 32;
      ob->state = &s_135;
      return;
    }
  }
}


void C_ParachuteBotAttack(objtype* ob, objtype* hit)
{
  if (hit->obclass == playerobj)
  {
    ob->shootable = false;
    ChangeState(ob, &s_grenadeexplosion1);
  }
}


void R_ParachuteBot(objtype* ob)
{
  if (!ob->hitnorth)
  {
    if (US_RndT() < 100)
    {
      ob->xdir = -ob->xdir;
    }
  }
  else
  {
    ChangeState(ob, &s_133);
    ob->y += 16*PIXGLOBAL;
  }

  PLACESPRITE;
}


void R_ParachuteBotAttack(objtype* ob)
{
  if (ob->hitsouth)
  {
    ob->yspeed = 0;
  }

  if (ob->hitnorth)
  {
    ChangeState(ob, &s_grenadeexplosion1);
    ob->shootable = false;
    ob->nothink = 12;
  }

  PLACESPRITE;
}


void SpawnSpitterSnake(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = spittersnakeobj;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y) - 8*PIXGLOBAL;
  new->xdir = 1;
  new->ydir = 1;
  new->shootable = true;

  switch (gamestate.difficulty)
  {
    case gd_Hard:
      new->health = 6;
      break;

    default:
      new->health = 3;
      break;
  }

  NewState(new, &s_137);
}


void T_SpitterSnake2(objtype* ob)
{
  ob->state = &s_137;
}


void SpitterSnakeSpit(objtype* ob)
{
  GetNewObj(true);

  new->obclass = enemyprojectileobj;

  if (ob->xdir == 1)
  {
    new->x = ob->x + 24*PIXGLOBAL;
    new->y = ob->y + 8*PIXGLOBAL;
  }
  else
  {
    new->x = ob->x;
    new->y = ob->y + 8*PIXGLOBAL;
  }

  new->xdir = ob->xdir;
  new->ydir = 1;
  new->xspeed = ob->xdir * 40 - (US_RndT() >> 4);
  new->yspeed = -20;
  new->active = ac_removable;

  NewState(new, &s_143);

  ob->nothink = 2;
}


void T_SpitterSnake(objtype* ob)
{
  Sint16 xdelta;

  if (abs(ob->y - player->y) > 48*PIXGLOBAL)
  {
    if (US_RndT() < 8)
    {
      ob->xdir = -ob->xdir;
    }
  }
  else
  {
    xdelta = player->x - ob->x;

    if (xdelta < -128*PIXGLOBAL)
    {
      ob->xdir = -1;
    }

    if (xdelta < -64*PIXGLOBAL)
    {
      SD_PlaySound(9);
      ob->xdir = -1;
      ob->state = &s_141;
      return;
    }

    if (xdelta < 0)
    {
      ob->xdir = 1;
      ob->state = &s_139;
      ob->nothink = 8;
      return;
    }

    if (xdelta < 64*PIXGLOBAL)
    {
      ob->xdir = -1;
      ob->state = &s_139;
      ob->nothink = 8;
      return;
    }

    if (xdelta < 128*PIXGLOBAL)
    {
      SD_PlaySound(9);
      ob->xdir = 1;
      ob->state = &s_141;
      return;
    }

    ob->xdir = 1;
  }
}


void SpawnSewerMutant(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = sewermutantobj;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y) - 32*PIXGLOBAL;
  new->xdir = 1;
  new->ydir = 1;
  new->shootable = true;

  switch (gamestate.difficulty)
  {
    case gd_Hard:
      new->health = 30;
      break;

    default:
      new->health = 15;
      break;
  }

  NewState(new, &s_145);
}


void SewerMutantThrow(objtype* ob)
{
  GetNewObj(true);

  new->obclass = enemyprojectileobj;

  if (ob->xdir == 1)
  {
    new->x = ob->x + 24*PIXGLOBAL;
    new->y = ob->y + 8*PIXGLOBAL;
  }
  else
  {
    new->x = ob->x;
    new->y = ob->y + 8*PIXGLOBAL;
  }

  new->xdir = ob->xdir;
  new->ydir = 1;
  new->xspeed = ob->xdir * 30 - (US_RndT() >> 4);
  new->yspeed = -20;
  new->active = ac_removable;

  NewState(new, &s_148);

  ob->nothink = 2;
}


void T_SewerMutant(objtype* ob)
{
  Sint16 xdelta;

  if (abs(ob->y - player->y) > 48*PIXGLOBAL)
  {
    if (US_RndT() < 8)
    {
      ob->xdir = -ob->xdir;
    }
  }
  else
  {
    xdelta = player->x - ob->x;

    if (xdelta < -128*PIXGLOBAL)
    {
      ob->xdir = -1;
    }

    if (xdelta < -64*PIXGLOBAL)
    {
      SD_PlaySound(38);
      ob->xdir = -1;
      ob->state = &s_147;
      return;
    }

    if (xdelta < 0)
    {
      ob->xdir = 1;
      ob->state = &s_145;
      ob->nothink = 8;
      return;
    }

    if (xdelta < 64*PIXGLOBAL)
    {
      ob->xdir = -1;
      ob->state = &s_145;
      ob->nothink = 8;
      return;
    }

    if (xdelta < 128*PIXGLOBAL)
    {
      SD_PlaySound(38);
      ob->xdir = 1;
      ob->state = &s_147;
      return;
    }

    ob->xdir = 1;
  }
}


void SpawnHostage(Sint16 x, Sint16 y, Sint16 type)
{
  GetNewObj(false);

  new->obclass = hostageobj;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y) - 24*PIXGLOBAL;

  switch (type)
  {
    case 0:
      NewState(new, &s_150);
      break;

    case 1:
      NewState(new, &s_152);
      break;

    case 2:
      NewState(new, &s_154);
      break;
  }

  new->hitnorth = 1;
  new->shootable = false;
}


void SpawnDrMangleHologram(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = drmangleobj;
  new->active = ac_allways;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y) - 16*PIXGLOBAL;
  NewState(new, &s_156);
  new->priority = 3;
  new->shootable = false;
  new->needtoclip = cl_noclip;
  bossactivated = false;
}


void T_DrMangleHologram(objtype* ob)
{
  // Randomized animation
  if (US_RndT() > 220)
  {
    if (ob->state == &s_156)
    {
      ChangeState(ob, &s_159);
      return;
    }

    if (ob->state == &s_157)
    {
      ChangeState(ob, &s_160);
      return;
    }

    if (ob->state == &s_158)
    {
      ChangeState(ob, &s_161);
      return;
    }
  }
  else if (US_RndT() > 110)
  {
    ChangeState(ob, &s_157);
    return;
  }

  if (US_RndT() > 250 && ob->state != &s_158)
  {
    ChangeState(ob, &s_158);
  }

  // Never true, unless the actor were to be placed in level 11, which is not
  // the case in the shipping game. See code in SnakeInteractThink().
  if (bossactivated)
  {
    Sint16 rand = US_RndT();

    if (rand > 120)
    {
      // What the heck?
      ThrowGrenade(ob->midx, ob->top, dir_West);
    }
    else
    {
      sub_22db0(ob);
    }

    ob->state = &s_162;
  }
}


void sub_20f20(objtype* ob)
{
  Sint16 rand, xdelta;

  rand = US_RndT();

  AccelerateY(ob, ob->y > player->y ? -1 : 1, US_RndT() / 8 + 4);

  if (ob->yspeed > 0)
  {
    ob->ydir = 1;
  }
  else
  {
    ob->ydir = -1;
  }

  AccelerateX(ob, ob->xdir, US_RndT() / 8 + 4);

  if (ob->xspeed < 0)
  {
    xdelta = ob->left - player->right;

    if (xdelta < -8*PIXGLOBAL)
    {
      ob->xdir = 1;
    }
    else
    {
      ob->xdir = -1;
    }
  }
  else
  {
    xdelta = player->left - ob->right;

    if (xdelta < -8*PIXGLOBAL)
    {
      ob->xdir = -1;
    }
    else
    {
      ob->xdir = 1;
    }
  }

  if (rand > 150 && rand < 200)
  {
    if (ob->top > player->bottom || ob->bottom < player->top)
      return;

    if (sub_22a7a(ob->midx, ob->y + 15*PIXGLOBAL, &s_252) == -1)
      return;

    {
      new->xspeed = ob->xdir * 60;
      new->yspeed = 0;
      SD_PlaySound(6);
    }
  }
  else if (rand > 250)
  {
    // What the heck?
    ThrowGrenade(ob->midx, ob->top, dir_West);
    ThrowGrenade(ob->midx, ob->top, dir_East);
  }
}


void sub_2106d(objtype* ob)
{
  if (ob->top > player->top + 24)
  {
    ob->ydir = -1;
  }
  else if (ob->top < player->top + 24)
  {
    ob->ydir = 1;
  }

  PLACESPRITE;
}


void SpawnDrMangle(Sint16 x, Sint16 y)
{
  GetNewObj(false);

  new->obclass = drmangleobj;
  new->active = ac_allways;
  new->priority = 2;
  new->x = CONVERT_TILE_TO_GLOBAL(x);
  new->y = CONVERT_TILE_TO_GLOBAL(y) - 24*PIXGLOBAL;
  new->xdir = 1;
  new->ydir = 1;

  NewState(new, &s_163);

  new->hitnorth = 1;
  new->ticcount = US_RndT() / 32;

  new->shootable = false;
  new->health = bosshealth = 200;
  word_389AA = -1;
  unknown = bosshealth / 20 - 1;
}


void T_DrMangle(objtype* ob)
{
  Sint16 shotorigin, xdelta;

  if (ob->health != bosshealth)
  {
    word_389AA = bosshealth;
    bosshealth = ob->health;
  }

  if (ob->obclass == inertobj)
  {
    ob->state = &s_168;
    ob->y += 32*PIXGLOBAL;
    ob->shootable = false;
    return;
  }

  if (ob->top > player->bottom || ob->bottom < player->top)
    return;

  if (US_RndT() > 230 && ob->shootable == true)
  {
    if (ob->xdir == 1)
    {
      shotorigin = ob->x + 112*PIXGLOBAL;
    }
    else
    {
      shotorigin = ob->x;
    }

    if (sub_22a7a(shotorigin, ob->y + 32*PIXGLOBAL, &s_255) == -1)
    {
      return;
    }

    new->xspeed = ob->xdir * 60;

    if (US_RndT() < 70)
    {
      new->yspeed = 0;
    }
    else
    {
      if (ob->temp1 & 1)
      {
        new->yspeed = 4;
      }
      else
      {
        new->yspeed = -4;
      }
    }

    SD_PlaySound(21);
  }

  if (ob->xdir == -1)
  {
    xdelta = ob->left - player->right;

    if (xdelta > 32*PIXGLOBAL)
      return;

    if (xdelta < -128*PIXGLOBAL)
    {
      ob->xdir = 1;
      return;
    }

    ob->yspeed = -24 - US_RndT() / 16;
    ob->xspeed = -32;

    SD_PlaySound(23);
    ob->shootable = true;
    ob->state = &s_167;
    return;
  }
  else
  {
    xdelta = player->left - ob->right;

    if (xdelta > 32*PIXGLOBAL)
      return;

    if (xdelta < -128*PIXGLOBAL)
    {
      ob->xdir = -1;
      return;
    }

    ob->yspeed = -24 - US_RndT() / 16;
    ob->xspeed = 32;

    SD_PlaySound(23);
    ob->shootable = true;
    ob->state = &s_167;
    return;
  }
}


void DrMangleDefeated(objtype* ob)
{
  gamestate.mapon = 11;
  ob->hitnorth = 1;
  ob->state = &s_170;
  ob->dmgflash = 0;
  playstate = ex_completed;
}


void R_DrMangleJumping(objtype* ob)
{
  if (ob->hitsouth)
  {
    ob->yspeed = 0;
  }

  if (ob->hitnorth)
  {
    ChangeState(ob, &s_165);
  }

  PLACESPRITE;
}
