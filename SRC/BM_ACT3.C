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

void sub_2291e();
void sub_22b98();
void sub_22be7();
void sub_22d16();
void sub_22db0();
void sub_22e5c();
void sub_22f1a();
void sub_22f3f();
void sub_22fa5();
void sub_230fe();
void sub_23188();
void sub_23223();
void sub_23254();
void sub_2334c();
void sub_23395();
void sub_233de();
void sub_234b7();
void sub_234ed();
void sub_2351f();
void sub_235c2();
void sub_235e1();
void sub_23600();
void sub_2365a();
void sub_2370e();
void sub_237bf();
void sub_2390f();
void sub_23995();
void sub_239b3();
void sub_23aa2();
void sub_23b07();
void sub_23d3f();
void sub_23dc4();
void sub_23f58();
void sub_23fba();
void sub_24001();
void sub_24048();
void sub_24067();
void sub_24086();
void sub_240d4();
void sub_241cb();
void sub_242b1();
void sub_24372();
void sub_24446();

statetype far s_230 = { /* 32f10 */
  BIG_EXPLOSION1_SPR, BIG_EXPLOSION1_SPR,
  step, false, ps_none, 15, 0, 0,
  NULL, NULL, R_Draw, &s_231};

statetype far s_231 = { /* 32f30 */
  BIG_EXPLOSION2_SPR, BIG_EXPLOSION2_SPR,
  step, false, ps_none, 12, 0, 0,
  NULL, NULL, R_Draw, &s_232};

statetype far s_232 = { /* 32f50 */
  BIG_EXPLOSION3_SPR, BIG_EXPLOSION3_SPR,
  step, false, ps_none, 5, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_233 = { /* 32f70 */
  TANKBOT1_SPR, TANKBOT1_SPR,
  stepthink, false, ps_tofloor, 6, 0, 0,
  sub_2291e, NULL, R_Draw, &s_233};

statetype far s_234 = { /* 32f90 */
  TANKBOT1_SPR, TANKBOT1_SPR,
  step, false, ps_tofloor, 10, 0, 0,
  sub_22b98, NULL, R_Draw, &s_234};

statetype far s_235 = { /* 32fb0 */
  TANKBOT1_SPR, TANKBOT1_SPR,
  slide, false, ps_tofloor, 20, 8, 0,
  NULL, NULL, R_Walk, &s_236};

statetype far s_236 = { /* 32fd0 */
  TANKBOT2_SPR, TANKBOT2_SPR,
  slide, false, ps_tofloor, 20, 8, 0,
  sub_22be7, NULL, R_Walk, &s_235};

statetype far s_237 = { /* 32ff0 */
  TANKBOT_SHOOT_SPR, TANKBOT_SHOOT_SPR,
  step, false, ps_tofloor, 7, 0, 0,
  sub_22d16, NULL, R_Draw, &s_234};

statetype far s_238 = { /* 33010 */
  TANKBOT1_SPR, TANKBOT1_SPR,
  step, false, ps_tofloor, 7, 0, 0,
  sub_22db0, NULL, R_Draw, &s_234};

statetype far s_239 = { /* 33030 */
  TANKBOT_SHOT_FLYING_SPR, TANKBOT_SHOT_FLYING_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  T_Projectile, NULL, sub_22f3f, &s_239};

statetype far s_240 = { /* 33050 */
  TANKBOT_SHOT_LANDING_SPR, TANKBOT_SHOT_LANDING_SPR,
  stepthink, false, ps_none, 5, 8, 65504,
  NULL, NULL, sub_22fa5, &s_240};

statetype far s_241 = { /* 33070 */
  TANKBOT_BIG_SHOT_SPR, TANKBOT_BIG_SHOT_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  T_Projectile, NULL, sub_22e5c, &s_241};

statetype far s_242 = { /* 33090 */
  SHOT_EXPLODE1_SPR, SHOT_EXPLODE1_SPR,
  step, false, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, &s_243};

statetype far s_243 = { /* 330b0 */
  SHOT_EXPLODE2_SPR, SHOT_EXPLODE2_SPR,
  step, false, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_244 = { /* 330d0 */
  SMALL_FIRE1_SPR, SMALL_FIRE1_SPR,
  step, true, ps_tofloor, 5, 0, 0,
  sub_22f1a, NULL, R_Draw, &s_245};

statetype far s_245 = { /* 330f0 */
  SMALL_FIRE2_SPR, SMALL_FIRE2_SPR,
  step, true, ps_tofloor, 5, 0, 0,
  sub_22f1a, NULL, R_Draw, &s_246};

statetype far s_246 = { /* 33110 */
  SMALL_FIRE3_SPR, SMALL_FIRE3_SPR,
  step, true, ps_tofloor, 5, 0, 0,
  sub_22f1a, NULL, R_Draw, &s_244};

statetype far s_247 = { /* 33130 */
  LASERGUNNER_IDLE_L_SPR, LASERGUNNER_IDLE_R_SPR,
  step, false, ps_tofloor, 6, 0, 0,
  sub_230fe, NULL, R_Draw, &s_247};

statetype far s_248 = { /* 33150 */
  LASERGUNNER_IDLE_L_SPR, LASERGUNNER_IDLE_R_SPR,
  step, true, ps_tofloor, 40, 0, 0,
  NULL, NULL, R_Draw, &s_249};

statetype far s_249 = { /* 33170 */
  LASERGUNNER_IDLE_L_SPR, LASERGUNNER_IDLE_R_SPR,
  step, true, ps_tofloor, 4, 0, 0,
  NULL, NULL, R_Draw, &s_250};

statetype far s_250 = { /* 33190 */
  LASERGUNNER_SHOOT_L_SPR, LASERGUNNER_SHOOT_R_SPR,
  step, false, ps_tofloor, 6, 0, 0,
  sub_23188, NULL, R_Draw, &s_249};

statetype far s_251 = { /* 331b0 */
  LASERGUNNER_IDLE_L_SPR, LASERGUNNER_IDLE_R_SPR,
  stepthink, false, ps_tofloor, 6, 0, 0,
  sub_2291e, NULL, R_Draw, &s_251};

statetype far s_252 = { /* 331d0 */
  LASER_BLAST_BLUE_SPR, LASER_BLAST_BLUE_SPR,
  stepthink, true, ps_none, 8, 0, 0,
  T_Velocity, sub_23223, sub_23254, &s_252};

statetype far s_253 = { /* 331f0 */
  SHOT_EXPLODE1_SPR, SHOT_EXPLODE1_SPR,
  step, true, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, &s_254};

statetype far s_254 = { /* 33210 */
  SHOT_EXPLODE2_SPR, SHOT_EXPLODE2_SPR,
  step, true, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_255 = { /* 33230 */
  SHOT_EXPLODE1_SPR, SHOT_EXPLODE1_SPR,
  stepthink, true, ps_none, 8, 0, 0,
  T_Velocity, sub_23223, sub_23254, &s_256};

statetype far s_256 = { /* 33250 */
  SHOT_EXPLODE2_SPR, SHOT_EXPLODE2_SPR,
  stepthink, true, ps_none, 8, 0, 0,
  T_Velocity, sub_23223, sub_23254, &s_255};

statetype far s_257 = { /* 33270 */
  PUSHBLOCKSPR, PUSHBLOCKSPR,
  stepthink, false, ps_tofloor, 6, 0, 1,
  NULL, sub_233de, sub_2334c, &s_257};

statetype far s_258 = { /* 33290 */
  PUSHBLOCKSPR, PUSHBLOCKSPR,
  stepthink, false, ps_none, 0, 0, 0,
  T_Projectile, sub_233de, sub_23395, &s_257};

statetype far s_259 = { /* 332b0 */
  FALLINGBLOCKSPR, FALLINGBLOCKSPR,
  stepthink, false, ps_none, 1, 0, 0,
  sub_234b7, sub_2351f, R_Draw, &s_259};

statetype far s_260 = { /* 332d0 */
  FALLINGBLOCKSPR, FALLINGBLOCKSPR,
  stepthink, false, ps_none, 0, 0, 0,
  T_Projectile, NULL, sub_234ed, &s_260};

statetype far s_261 = { /* 332f0 */
  CRUSHERBLOCKSPR, CRUSHERBLOCKSPR,
  stepthink, false, ps_none, 6, 0, 0,
  sub_235c2, NULL, R_Draw, &s_261};

statetype far s_262 = { /* 33310 */
  CRUSHERBLOCKSPR, CRUSHERBLOCKSPR,
  stepthink, false, ps_none, 5, 0, 8,
  sub_235e1, sub_2365a, sub_23600, &s_262};

statetype far s_263 = { /* 33330 */
  BOUNCEBOT1_SPR, BOUNCEBOT1_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  sub_2370e, NULL, sub_237bf, &s_264};

statetype far s_264 = { /* 33350 */
  BOUNCEBOT3_SPR, BOUNCEBOT3_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  sub_2370e, NULL, sub_237bf, &s_265};

statetype far s_265 = { /* 33370 */
  BOUNCEBOT4_SPR, BOUNCEBOT4_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  sub_2370e, NULL, sub_237bf, &s_266};

statetype far s_266 = { /* 33390 */
  BOUNCEBOT5_SPR, BOUNCEBOT5_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  sub_2370e, NULL, sub_237bf, &s_263};

statetype far s_267 = { /* 333b0 */
  BOUNCEBOT2_SPR, BOUNCEBOT2_SPR,
  stepthink, false, ps_none, 15, 0, 0,
  sub_2370e, NULL, sub_237bf, &s_263};

statetype far s_268 = { /* 333d0 */
  SLIME_DROPPER1_SPR, SLIME_DROPPER1_SPR,
  step, false, ps_none, 50, 0, 0,
  NULL, NULL, R_Draw, &s_269};

statetype far s_269 = { /* 333f0 */
  SLIME_DROPPER2_SPR, SLIME_DROPPER2_SPR,
  step, false, ps_none, 50, 0, 0,
  NULL, NULL, R_Draw, &s_270};

statetype far s_270 = { /* 33410 */
  SLIME_DROPPER3_SPR, SLIME_DROPPER3_SPR,
  step, false, ps_none, 1, 0, 0,
  sub_2390f, NULL, R_Draw, &s_268};

statetype far s_271 = { /* 33430 */
  SLIME_DROP1_SPR, SLIME_DROP1_SPR,
  step, false, ps_none, 5, 0, 0,
  NULL, NULL, R_Draw, &s_272};

statetype far s_272 = { /* 33450 */
  SLIME_DROP2_SPR, SLIME_DROP2_SPR,
  step, false, ps_none, 5, 0, 0,
  sub_23995, NULL, R_Draw, &s_271};

statetype far s_273 = { /* 33470 */
  SLIME_DROP3_SPR, SLIME_DROP3_SPR,
  stepthink, false, ps_none, 0, 0, 0,
  T_Projectile, NULL, sub_239b3, &s_273};

statetype far s_274 = { /* 33490 */
  SLIME_DROP_SPLAT1_SPR, SLIME_DROP_SPLAT1_SPR,
  step, false, ps_tofloor, 15, 0, 0,
  NULL, NULL, R_Draw, &s_275};

statetype far s_275 = { /* 334b0 */
  SLIME_DROP_SPLAT2_SPR, SLIME_DROP_SPLAT2_SPR,
  step, false, ps_tofloor, 15, 0, 0,
  NULL, NULL, R_Draw, &s_276};

statetype far s_276 = { /* 334d0 */
  SLIME_DROP_SPLAT3_SPR, SLIME_DROP_SPLAT3_SPR,
  step, false, ps_tofloor, 15, 0, 0,
  NULL, NULL, R_Draw, &s_277};

statetype far s_277 = { /* 334f0 */
  SLIME_DROP_SPLAT4_SPR, SLIME_DROP_SPLAT4_SPR,
  step, false, ps_tofloor, 15, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_278 = { /* 33510 */
  TURRET_IDLE_L_SPR, TURRET_IDLE_R_SPR,
  step, false, ps_tofloor, 6, 0, 0,
  sub_23aa2, NULL, R_Draw, &s_278};

statetype far s_279 = { /* 33530 */
  TURRET_READY_L_SPR, TURRET_READY_R_SPR,
  step, true, ps_tofloor, 40, 0, 0,
  NULL, NULL, R_Draw, &s_280};

statetype far s_280 = { /* 33550 */
  TURRET_READY_L_SPR, TURRET_READY_R_SPR,
  step, true, ps_tofloor, 4, 0, 0,
  NULL, NULL, R_Draw, &s_281};

statetype far s_281 = { /* 33570 */
  TURRET_SHOOT_L_SPR, TURRET_SHOOT_R_SPR,
  step, false, ps_tofloor, 6, 0, 0,
  sub_23b07, NULL, R_Draw, &s_280};

statetype far s_282 = { /* 33590 */
  ASTEROID1_SPR, ASTEROID1_SPR,
  slide, false, ps_none, 10, 24, 24,
  NULL, NULL, sub_23dc4, &s_283};

statetype far s_283 = { /* 335b0 */
  ASTEROID2_SPR, ASTEROID2_SPR,
  slide, false, ps_none, 10, 24, 24,
  NULL, NULL, sub_23dc4, &s_284};

statetype far s_284 = { /* 335d0 */
  ASTEROID3_SPR, ASTEROID3_SPR,
  slide, false, ps_none, 10, 24, 24,
  NULL, NULL, sub_23dc4, &s_285};

statetype far s_285 = { /* 335f0 */
  ASTEROID4_SPR, ASTEROID4_SPR,
  slide, false, ps_none, 10, 24, 24,
  NULL, NULL, sub_23dc4, &s_282};

statetype far s_286 = { /* 33610 */
  LANDMINE1_SPR, LANDMINE1_SPR,
  slide, false, ps_none, 10, 0, 0,
  NULL, sub_23d3f, sub_23dc4, &s_287};

statetype far s_287 = { /* 33630 */
  LANDMINE2_SPR, LANDMINE2_SPR,
  slide, false, ps_none, 10, 0, 0,
  NULL, sub_23d3f, sub_23dc4, &s_286};

statetype far s_288 = { /* 33650 */
  SKULLMAN1_SPR, SKULLMAN1_SPR,
  stepthink, false, ps_none, 35, 0, 0,
  sub_241cb, NULL, R_Draw, &s_288};

statetype far s_289 = { /* 33670 */
  SKULLMAN2_SPR, SKULLMAN2_SPR,
  stepthink, false, ps_none, 35, 0, 0,
  sub_241cb, NULL, R_Draw, &s_289};

statetype far s_290 = { /* 33690 */
  SKULLMAN_HAND_R_SPR, SKULLMAN_HAND_R_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  sub_24048, NULL, R_Draw, &s_290};

statetype far s_291 = { /* 336b0 */
  SKULLMAN_HAND_L_SPR, SKULLMAN_HAND_L_SPR,
  stepthink, false, ps_none, 10, 0, 0,
  sub_24067, NULL, R_Draw, &s_291};

statetype far s_292 = { /* 336d0 */
  SKULLMAN_HAND_R_SPR, SKULLMAN_HAND_R_SPR,
  slide, false, ps_none, 10, 24, 24,
  sub_24086, NULL, sub_23f58, &s_292};

statetype far s_293 = { /* 336f0 */
  SKULLMAN_HAND_L_SPR, SKULLMAN_HAND_L_SPR,
  slide, false, ps_none, 10, 24, 24,
  sub_240d4, NULL, sub_23f58, &s_293};

statetype far s_294 = { /* 33710 */
  SKULLMAN_HAND_ATTACK1_SPR, SKULLMAN_HAND_ATTACK1_SPR,
  stepthink, false, ps_none, 20, 0, 0,
  T_Projectile, NULL, sub_23fba, &s_295};

statetype far s_295 = { /* 33730 */
  SKULLMAN_HAND_ATTACK2_SPR, SKULLMAN_HAND_ATTACK2_SPR,
  stepthink, false, ps_none, 20, 0, 0,
  T_Projectile, NULL, sub_23fba, &s_294};

statetype far s_296 = { /* 33750 */
  SKULLMAN_HAND_ATTACK1_SPR, SKULLMAN_HAND_ATTACK1_SPR,
  stepthink, false, ps_none, 20, 0, 0,
  T_Projectile, NULL, sub_24001, &s_297};

statetype far s_297 = { /* 33770 */
  SKULLMAN_HAND_ATTACK2_SPR, SKULLMAN_HAND_ATTACK2_SPR,
  stepthink, false, ps_none, 20, 0, 0,
  T_Projectile, NULL, sub_24001, &s_296};

statetype far s_298 = { /* 33790 */
  0, 0, step, false, ps_none, 50, 0, 0,
  NULL, NULL, R_Draw, &s_299};

statetype far s_299 = { /* 337b0 */
  0, 0, step, false, ps_none, 1, 0, 0,
  sub_242b1, NULL, R_Draw, &s_298};

statetype far s_300 = { /* 337d0 */
  SPARKSHOT1_SPR, SPARKSHOT1_SPR,
  stepthink, false, ps_none, 8, 0, 0,
  T_Velocity, NULL, sub_24372, &s_301};

statetype far s_301 = { /* 337f0 */
  SPARKSHOT2_SPR, SPARKSHOT2_SPR,
  stepthink, false, ps_none, 8, 0, 0,
  T_Velocity, NULL, sub_24372, &s_300};

statetype far s_302 = { /* 33810 */
  SHOT_EXPLODE1_SPR, SHOT_EXPLODE1_SPR,
  step, false, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, &s_303};

statetype far s_303 = { /* 33830 */
  SHOT_EXPLODE2_SPR, SHOT_EXPLODE2_SPR,
  step, false, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_304 = { /* 33850 */
  RESPAWN_BEACON_INACTIVE_SPR, RESPAWN_BEACON_INACTIVE_SPR,
  step, false, ps_tofloor, 10, 0, 0,
  NULL, sub_24446, R_Draw, &s_304};

statetype far s_305 = { /* 33870 */
  RESPAWN_BEACON_ACTIVE1_SPR, RESPAWN_BEACON_ACTIVE1_SPR,
  step, false, ps_tofloor, 10, 0, 0,
  NULL, NULL, R_Draw, &s_306};

statetype far s_306 = { /* 33890 */
  RESPAWN_BEACON_ACTIVE2_SPR, RESPAWN_BEACON_ACTIVE2_SPR,
  step, false, ps_tofloor, 10, 0, 0,
  NULL, NULL, R_Draw, &s_307};

statetype far s_307 = { /* 338b0 */
  RESPAWN_BEACON_ACTIVE3_SPR, RESPAWN_BEACON_ACTIVE3_SPR,
  step, false, ps_tofloor, 10, 0, 0,
  NULL, NULL, R_Draw, &s_308};

statetype far s_308 = { /* 338d0 */
  RESPAWN_BEACON_ACTIVE4_SPR, RESPAWN_BEACON_ACTIVE4_SPR,
  step, false, ps_tofloor, 10, 0, 0,
  NULL, NULL, R_Draw, &s_305};


void sub_2291e()
{
}


void SpawnBigExplosion(Sint16 x, Sint16 y)
{
}


void SpawnTankBot(Sint16 x, Sint16 y)
{
}


void sub_22a7a()
{
}


void sub_22b98()
{
}


void sub_22be7()
{
}


void sub_22d16()
{
}


void sub_22db0()
{
}


void sub_22e5c()
{
}


void sub_22f1a()
{
}


void sub_22f3f()
{
}


void sub_22fa5()
{
}


void SpawnLaserGunner(Sint16 x, Sint16 y)
{
}


void sub_230fe()
{
}


void sub_23188()
{
}


void sub_23223()
{
}


void sub_23254()
{
}


void SpawnPushBlock(Sint16 x, Sint16 y)
{
}


void sub_2334c()
{
}


void sub_23395()
{
}


void sub_233de()
{
}


void SpawnFallingBlock(Sint16 x, Sint16 y)
{
}


void sub_234b7()
{
}


void sub_234ed()
{
}


void sub_2351f()
{
}


void SpawnCrusher(Sint16 x, Sint16 y)
{
}


void sub_235c2()
{
}


void sub_235e1()
{
}


void sub_23600()
{
}


void sub_2365a()
{
}


void SpawnBounceBot(Sint16 x, Sint16 y)
{
}


void sub_2370e()
{
}


void sub_237bf()
{
}


void SpawnSlimeDropper(Sint16 x, Sint16 y)
{
}


void sub_2390f()
{
}


void sub_23995()
{
}


void sub_239b3()
{
}


void SpawnLaserTurret(Sint16 x, Sint16 y)
{
}


void sub_23aa2()
{
}


void sub_23b07()
{
}


void SpawnAsteroid(Sint16 x, Sint16 y)
{
}


void SpawnLandMine(Sint16 x, Sint16 y)
{
}


void sub_23d3f()
{
}


void sub_23dc4()
{
}


void SpawnSkullmanHand(Sint16 x, Sint16 y, Sint16 t)
{
}


void sub_23f58()
{
}


void sub_23fba()
{
}


void sub_24001()
{
}


void sub_24048()
{
}


void sub_24067()
{
}


void sub_24086()
{
}


void sub_240d4()
{
}


void SpawnSkullman(Sint16 x, Sint16 y)
{
}


void sub_241cb()
{
}


void SpawnSparkShooter(Sint16 x, Sint16 y)
{
}


void sub_242b1()
{
}


void sub_24372()
{
}


void SpawnRespawnBeacon(Sint16 x, Sint16 y)
{
}


void sub_24446()
{
  "Continue from beacons when you get killed.\n";
}
