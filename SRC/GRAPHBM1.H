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

#ifndef __GFX_H__
#define __GFX_H__

//#include "VERSION.H"

//////////////////////////////////////
//
// Graphics .H file for .BM1
// not IGRAB-ed :)
//
//////////////////////////////////////

//
// Lump creation macros
//

#define START_LUMP(actualname, dummyname) actualname, dummyname=actualname-1,
#define END_LUMP(actualname, dummyname) dummyname, actualname=dummyname-1,

//
// Amount of each data item
//

#define NUMCHUNKS    NUMGRCHUNKS
#define NUMFONT      2
#define NUMFONTM     0
#define NUMPICS      50
#define NUMPICM      1
#define NUMSPRITES   355
#define NUMTILE8     144
#define NUMTILE8M    36
#define NUMTILE16    1512
#define NUMTILE16M   2682
#define NUMTILE32    0
#define NUMTILE32M   0
#define NUMEXTERNS   14

//
// File offsets for data items
//
#define STRUCTPIC    0
#define STRUCTPICM   1
#define STRUCTSPRITE 2

#define STARTFONT    3
#define STARTFONTM   (STARTFONT+NUMFONT)
#define STARTPICS    (STARTFONTM+NUMFONTM)
#define STARTPICM    (STARTPICS+NUMPICS)
#define STARTSPRITES (STARTPICM+NUMPICM)
#define STARTTILE8   (STARTSPRITES+NUMSPRITES)
#define STARTTILE8M  (STARTTILE8+1)
#define STARTTILE16  (STARTTILE8M+1)
#define STARTTILE16M (STARTTILE16+NUMTILE16)
#define STARTTILE32  (STARTTILE16M+NUMTILE16M)
#define STARTTILE32M (STARTTILE32+NUMTILE32)
#define STARTEXTERNS (STARTTILE32M+NUMTILE32M)

typedef enum {
  LASTFONT=STARTPICS-1,

  //
  // PICS
  //

  START_LUMP(CONTROLS_LUMP_START, __CONTROLSSTART)
  CP_MAINMENUPIC,              // 5
  CP_NEWGAMEMENUPIC,           // 6
  CP_LOADMENUPIC,              // 7
  CP_SAVEMENUPIC,              // 8
  CP_CONFIGMENUPIC,            // 9
  CP_SOUNDMENUPIC,             // 10
  CP_MUSICMENUPIC,             // 11
  CP_KEYBOARDMENUPIC,          // 12
  CP_KEYMOVEMENTPIC,           // 13
  CP_KEYBUTTONPIC,             // 14
  CP_JOYSTICKMENUPIC,          // 15
  CP_OPTIONSMENUPIC,           // 16
  CP_QUITPIC,                  // 17
  CP_JOYSTICKPIC,              // 18
  CP_MENUSCREENPIC,            // 19
  END_LUMP(CONTROLS_LUMP_END, __CONTROLSEND)

  TITLESHAREWAREPIC,           // 20
  H_HELPPIC,                   // 21
  H_HANDPIC,                   // 22
  H_FLASHARROW1PIC,            // 23
  H_FLASHARROW2PIC,            // 24
  H_TOPWINDOWPIC,              // 25
  H_LEFTWINDOWPIC,             // 26
  H_RIGHTWINDOWPIC,            // 27
  H_BOTTOMINFOPIC,             // 28
  H_ESCPIC,                    // 29
  H_LARROWPIC,                 // 30
  H_RARROWPIC,                 // 31
  H_ENTERPIC,                  // 32
  ENDOFTEXTPIC,                // 33
  H_VISAPIC,                   // 34
  H_MCPIC,                     // 35
  HOSTAGE1PIC,                 // 36
  HOSTAGE2PIC,                 // 37
  HOSTAGE3PIC,                 // 38
  SNAKETALKPIC,                // 39
  H_ITEMSPIC,                  // 40
  STORY1PIC,                   // 41
  STORY2PIC,                   // 42
  STORY3PIC,                   // 43
  STORY4PIC,                   // 44
  STORY5PIC,                   // 45
  STORY6PIC,                   // 46
  STORY7PIC,                   // 47
  STORY8PIC,                   // 48
  STORY9PIC,                   // 49
  CREDITSPIC,                  // 50
  PREVIEWPIC,                  // 51
  TITLEPIC,                    // 52
  NOTSHAREWAREPIC,             // 53
  TECHHELPPIC,                 // 54

  CP_MENUMASKPICM,             // 55

  //
  // SPRITES
  //

  HANDCURSORSPR,               // 56

  START_LUMP(PLAYER_LUMP_START, __PLAYERSTART)
  SHOT_EXPLODE1_SPR,           // 57
  SHOT_EXPLODE2_SPR,           // 58
  SMALL_FIRE1_SPR,             // 59
  SMALL_FIRE2_SPR,             // 60
  SMALL_FIRE3_SPR,             // 61
  LASER_BLAST_BLUE_SPR,        // 62
  LASER_BLAST_RED_SPR,         // 63
  SUPER_BLAST_R_SPR,           // 64
  SUPER_BLAST_L_SPR,           // 65
  PLAYER_STANDING_R_SPR,       // 66
  PLAYER_WALKING1_R_SPR,       // 67
  PLAYER_WALKING2_R_SPR,       // 68
  PLAYER_WALKING3_R_SPR,       // 69
  PLAYER_WALKING4_R_SPR,       // 70
  PLAYER_STANDING_L_SPR,       // 71
  PLAYER_WALKING1_L_SPR,       // 72
  PLAYER_WALKING2_L_SPR,       // 73
  PLAYER_WALKING3_L_SPR,       // 74
  PLAYER_WALKING4_L_SPR,       // 75
  PLAYER_SHIELDED1_R_SPR,      // 76
  PLAYER_SHIELDED2_R_SPR,      // 77
  PLAYER_SHIELDED1_L_SPR,      // 78
  PLAYER_SHIELDED2_L_SPR,      // 79
  PLAYER_INTERACTING_SPR,      // 80
  PLAYER_CLIMBING1_SPR,        // 81
  PLAYER_CLIMBING2_SPR,        // 82
  PLAYER_DYING1_SPR,           // 83
  PLAYER_DYING2_SPR,           // 84
  PLAYER_THROW1_R_SPR,         // 85
  PLAYER_THROW2_R_SPR,         // 86
  PLAYER_THROW1_L_SPR,         // 87
  PLAYER_THROW2_L_SPR,         // 88
  PLAYER_IN_AIR_THROW1_R_SPR,  // 89
  PLAYER_IN_AIR_THROW2_R_SPR,  // 90
  PLAYER_IN_AIR_THROW1_L_SPR,  // 91
  PLAYER_IN_AIR_THROW2_L_SPR,  // 92
  PLAYER_SHOOT1_R_SPR,         // 93
  PLAYER_SHOOT2_R_SPR,         // 94
  PLAYER_SHOOT1_L_SPR,         // 95
  PLAYER_SHOOT2_L_SPR,         // 96
  PLAYER_CROUCH_R_SPR,         // 97
  PLAYER_CROUCH_SHOOT_R_SPR,   // 98
  PLAYER_CROUCH_L_SPR,         // 99
  PLAYER_CROUCH_SHOOT_L_SPR,   // 100
  PLAYER_IN_AIR_R_SPR,         // 101
  PLAYER_IN_AIR_SHOOT_R_SPR,   // 102
  PLAYER_IN_AIR_L_SPR,         // 103
  PLAYER_IN_AIR_SHOOT_L_SPR,   // 104
  GRENADE_GREEN1_SPR,          // 105
  GRENADE_GREEN2_SPR,          // 106
  GRENADE_GREEN3_SPR,          // 107
  GRENADE_GREEN4_SPR,          // 108
  GRENADE_RED1_SPR,            // 109
  GRENADE_RED2_SPR,            // 110
  GRENADE_RED3_SPR,            // 111
  GRENADE_RED4_SPR,            // 112
  RUNNING_FIRE1_SPR,           // 113
  RUNNING_FIRE2_SPR,           // 114
  GRENADE_EXPLOSION1_SPR,      // 115
  GRENADE_EXPLOSION2_SPR,      // 116
  GRENADE_EXPLOSION3_SPR,      // 117
  GRENADE_EXPLOSION4_SPR,      // 118
  GRENADE_EXPLOSION5_SPR,      // 119
  GRENADE_EXPLOSION6_SPR,      // 120
  FIREBALL1_SPR,               // 121
  FIREBALL2_SPR,               // 122
  FIREBALL3_SPR,               // 123
  FIREBALL4_SPR,               // 124
  FIREBALL5_SPR,               // 125
  FIREBALL6_SPR,               // 126
  FIREBALL7_SPR,               // 127
  FIREBALL8_SPR,               // 128
  BULLET_IMPACT1_SPR,          // 129
  BULLET_IMPACT2_SPR,          // 130
  BULLET_IMPACT3_SPR,          // 131
  GIBS1_SPR,                   // 132
  GIBS2_SPR,                   // 133
  GIBS_BONE1_SPR,              // 134
  GIBS_BONE2_SPR,              // 135
  GIBS_EYEBALL1_SPR,           // 136
  GIBS_EYEBALL2_SPR,           // 137
  GIBS_FLESH1_SPR,             // 138
  GIBS_FLESH2_SPR,             // 139
  PICKUP_GRENADE1_SPR,         // 140
  PICKUP_GRENADE2_SPR,         // 141
  PICKUP_GRENADE_RED1_SPR,     // 142
  PICKUP_GRENADE_RED2_SPR,     // 143
  PICKUP_GUN1_SPR,             // 144
  PICKUP_GUN2_SPR,             // 145
  METAL_DEBRIS1_SPR,           // 146
  METAL_DEBRIS2_SPR,           // 147
  METAL_DEBRIS3_SPR,           // 148
  METAL_DEBRIS4_SPR,           // 149
  METAL_DEBRIS5_SPR,           // 150
  METAL_DEBRIS6_SPR,           // 151
  METAL_DEBRIS7_SPR,           // 152
  METAL_DEBRIS8_SPR,           // 153
  PICKUP_KEYCARD1_SPR,         // 154
  PICKUP_KEYCARD2_SPR,         // 155
  PICKUP_KEY1_SPR,             // 156
  PICKUP_KEY2_SPR,             // 157
  BONUS_CHEMICALS1_1_SPR,      // 158
  BONUS_CHEMICALS1_2_SPR,      // 159
  BONUS_CHEMICALS2_1_SPR,      // 160
  BONUS_CHEMICALS2_2_SPR,      // 161
  BONUS_DEVICE1_SPR,           // 162
  BONUS_DEVICE2_SPR,           // 163
  BONUS_BOOK1_SPR,             // 164
  BONUS_BOOK2_SPR,             // 165
  PICKUP_LIFEGEM1_SPR,         // 166
  PICKUP_LIFEGEM2_SPR,         // 167
  PICKUP_HEALTH1_SPR,          // 168
  PICKUP_HEALTH2_SPR,          // 169
  PICKUP_NUKE1_SPR,            // 170
  PICKUP_NUKE2_SPR,            // 171
  PICKUP_RADPILL1_SPR,         // 172
  PICKUP_RADPILL2_SPR,         // 173
  PICKUP_INVINCIBILITY1_SPR,   // 174
  PICKUP_INVINCIBILITY2_SPR,   // 175
  BONUS_GEM1_1_SPR,            // 176
  BONUS_GEM1_2_SPR,            // 177
  BONUS_GEM2_1_SPR,            // 178
  BONUS_GEM2_2_SPR,            // 179
  PICKUP_SECRETLEVELGEM1_SPR,  // 180
  PICKUP_SECRETLEVELGEM2_SPR,  // 181
  BIG_EXPLOSION1_SPR,          // 182
  BIG_EXPLOSION2_SPR,          // 183
  BIG_EXPLOSION3_SPR,          // 184
  PICKUP_SHARD_BLUE1_SPR,      // 185
  PICKUP_SHARD_BLUE2_SPR,      // 186
  PICKUP_SHARD_GREEN1_SPR,     // 187
  PICKUP_SHARD_GREEN2_SPR,     // 188
  PICKUP_SHARD_RED1_SPR,       // 189
  PICKUP_SHARD_RED2_SPR,       // 190
  PICKUP_SHARD_CYAN1_SPR,      // 191
  PICKUP_SHARD_CYAN2_SPR,      // 192
  PICKUP_EXTRALIFE1_SPR,       // 193
  PICKUP_EXTRALIFE2_SPR,       // 194
  BONUS_TAPE1_SPR,             // 195
  BONUS_TAPE2_SPR,             // 196
  BONUS_CALCULATOR1_SPR,       // 197
  BONUS_CALCULATOR2_SPR,       // 198
  ONE_UP_SPR,                  // 199
  POINTS_100_SPR,              // 200
  POINTS_200_SPR,              // 201
  POINTS_500_SPR,              // 202
  POINTS_800_SPR,              // 203
  POINTS_1000_SPR,             // 204
  POINTS_1500_SPR,             // 205
  POINTS_2000_SPR,             // 206
  POINTS_5000_SPR,             // 207
  POINTS_50000_SPR,            // 208
  PICKUP_SPECIALKEY1_SPR,      // 209
  PICKUP_SPECIALKEY2_SPR,      // 210
  PICKUP_EXITKEY1_SPR,         // 211
  PICKUP_EXITKEY2_SPR,         // 212
  PICKUP_TRIANGLE1_SPR,        // 213
  PICKUP_TRIANGLE2_SPR,        // 214
  PICKUP_AMMO_PLASMA1_SPR,     // 215
  PICKUP_AMMO_PLASMA2_SPR,     // 216
  PICKUP_AMMO_SUPER1_SPR,      // 217
  PICKUP_AMMO_SUPER2_SPR,      // 218
  PICKUP_LANDMINES1_SPR,       // 219
  PICKUP_LANDMINES2_SPR,       // 220
  LANDMINE1_SPR,               // 221
  LANDMINE2_SPR,               // 222
  END_LUMP(PLAYER_LUMP_END, __PLAYEREND)

  START_LUMP(HOSTAGE_LUMP_START, __HOSTAGESTART)
  HOSTAGE1_1_SPR,              // 223
  HOSTAGE1_2_SPR,              // 224
  HOSTAGE2_1_SPR,              // 225
  HOSTAGE2_2_SPR,              // 226
  HOSTAGE3_1_SPR,              // 227
  HOSTAGE3_2_SPR,              // 228
  END_LUMP(HOSTAGE_LUMP_END, __HOSTAGEEND)

  START_LUMP(SLUG_LUMP_START, __SLUGSTART)
  SLUG_WALK1_L_SPR,            // 229
  SLUG_WALK2_L_SPR,            // 230
  SLUG_ATTACK_L_SPR,           // 231
  SLUG_WALK1_R_SPR,            // 232
  SLUG_WALK2_R_SPR,            // 233
  SLUG_ATTACK_R_SPR,           // 234
  END_LUMP(SLUG_LUMP_END, __SLUGEND)

  START_LUMP(UNUSED1_LUMP_START, __UNUSED1START)
  END_LUMP(UNUSED1_LUMP_END, __UNUSED1END)

  START_LUMP(BRAWLER_LUMP_START, __BRAWLERSTART)
  BRAWLER_STAND_L_SPR,         // 235
  BRAWLER_STAND_R_SPR,         // 236
  BRAWLER_WALK1_L_SPR,         // 237
  BRAWLER_WALK2_L_SPR,         // 238
  BRAWLER_WALK3_L_SPR,         // 239
  BRAWLER_WALK4_L_SPR,         // 240
  BRAWLER_ATTACK1_L_SPR,       // 241
  BRAWLER_ATTACK2_L_LPR,       // 242
  BRAWLER_WALK1_R_SPR,         // 243
  BRAWLER_WALK2_R_SPR,         // 244
  BRAWLER_WALK3_R_SPR,         // 245
  BRAWLER_WALK4_R_SPR,         // 246
  BRAWLER_ATTACK1_R_SPR,       // 247
  BRAWLER_ATTACK2_R_LPR,       // 248
  END_LUMP(BRAWLER_LUMP_END, __BRAWLEREND)

  START_LUMP(CEILWALKER_LUMP_START, __CEILWALKERSTART)
  CEILWALKER_WALK_CEIL1_L,     // 249
  CEILWALKER_WALK_CEIL2_L,     // 250
  CEILWALKER_WALK_CEIL3_L,     // 251
  CEILWALKER_WALK_CEIL4_L,     // 252
  CEILWALKER_FALL_L,           // 253
  CEILWALKER_WALK_CEIL1_R,     // 254
  CEILWALKER_WALK_CEIL2_R,     // 255
  CEILWALKER_WALK_CEIL3_R,     // 256
  CEILWALKER_WALK_CEIL4_R,     // 257
  CEILWALKER_FALL_R,           // 258
  CEILWALKER_WALK1_L,          // 259
  CEILWALKER_WALK2_L,          // 260
  CEILWALKER_WALK3_L,          // 261
  CEILWALKER_WALK4_L,          // 262
  CEILWALKER_WALK1_R,          // 263
  CEILWALKER_WALK2_R,          // 264
  CEILWALKER_WALK3_R,          // 265
  CEILWALKER_WALK4_R,          // 266
  END_LUMP(CEILWALKER_LUMP_END, __CEILWALKEREND)

  START_LUMP(BOMB_LUMP_START, __BOMBSTART)
  BOMB_WAIT_L_SPR,             // 267
  BOMB_JUMP1_L_SPR,            // 268
  BOMB_JUMP2_L_SPR,            // 269
  BOMB_JUMP3_L_SPR,            // 270
  BOMB_WAIT_R_SPR,             // 271
  BOMB_JUMP1_R_SPR,            // 272
  BOMB_JUMP2_R_SPR,            // 273
  BOMB_JUMP3_R_SPR,            // 274
  END_LUMP(BOMB_LUMP_END, __BOMBEND)

  START_LUMP(SPITSNAKE_LUMP_START, __SPITSNAKESTART)
  SPITSNAKE_WALK1_L_SPR,       // 275
  SPITSNAKE_WALK2_L_SPR,       // 276
  SPITSNAKE_WALK1_R_SPR,       // 277
  SPITSNAKE_WALK2_R_SPR,       // 278
  SPITSNAKE_ATTACK_L_SPR,      // 279
  SPITSNAKE_ATTACK_R_SPR,      // 280
  SPITSNAKE_SPIT1_L_SPR,       // 281
  SPITSNAKE_SPIT2_L_SPR,       // 282
  SPITSNAKE_SPIT1_R_SPR,       // 283
  SPITSNAKE_SPIT2_R_SPR,       // 284
  END_LUMP(SPITSNAKE_LUMP_END, __SPITSNAKEEND)

  START_LUMP(FIREIMP_LUMP_START, __FIREIMPSTART)
  FIREIMP_WALK1_L_SPR,         // 285
  FIREIMP_WALK2_L_SPR,         // 286
  FIREIMP_WALK3_L_SPR,         // 287
  FIREIMP_WALK4_L_SPR,         // 288
  FIREIMP_WALK1_R_SPR,         // 289
  FIREIMP_WALK2_R_SPR,         // 290
  FIREIMP_WALK3_R_SPR,         // 291
  FIREIMP_WALK4_R_SPR,         // 292
  FIREIMP_STAND_SPR,           // 293
  END_LUMP(FIREIMP_LUMP_END, __FIREIMPEND)

  START_LUMP(GHOSTSLUG_LUMP_START, __GHOSTSLUGSTART)
  GHOSTSLUG1_L_SPR,            // 294
  GHOSTSLUG2_L_SPR,            // 295
  GHOSTSLUG1_R_SPR,            // 296
  GHOSTSLUG2_R_SPR,            // 297
  END_LUMP(GHOSTSLUG_LUMP_END, __GHOSTSLUGEND)

  START_LUMP(SEWERMUTANT_LUMP_START, __SEWERMUTANTSTART)
  SEWERMUTANT_WALK1_L_SPR,     // 298
  SEWERMUTANT_WALK2_L_SPR,     // 299
  SEWERMUTANT_ATTACK_L_SPR,    // 300
  SEWERMUTANT_WALK1_R_SPR,     // 301
  SEWERMUTANT_WALK2_R_SPR,     // 302
  SEWERMUTANT_ATTACK_R_SPR,    // 303
  SEWERMUTANT_SPIT1_SPR,       // 304
  SEWERMUTANT_SPIT2_SPR,       // 305
  END_LUMP(SEWERMUTANT_LUMP_END, __SEWERMUTANTEND)

  START_LUMP(SLIME_DROPPER_LUMP_START, __SLIME_DROPPERSTART)
  SLIME_DROPPER1_SPR,          // 306
  SLIME_DROPPER2_SPR,          // 307
  SLIME_DROPPER3_SPR,          // 308
  SLIME_DROP1_SPR,             // 309
  SLIME_DROP2_SPR,             // 310
  SLIME_DROP3_SPR,             // 311
  SLIME_DROP_SPLAT1_SPR,       // 312
  SLIME_DROP_SPLAT2_SPR,       // 313
  SLIME_DROP_SPLAT3_SPR,       // 314
  SLIME_DROP_SPLAT4_SPR,       // 315
  END_LUMP(SLIME_DROPPER_LUMP_END, __SLIME_DROPPEREND)

  START_LUMP(CRAWLSLIME_LUMP_START, __CRAWLSLIMESTART)
  CRAWLSLIME1_L_SPR,           // 316
  CRAWLSLIME2_L_SPR,           // 317
  CRAWLSLIME1_R_SPR,           // 318
  CRAWLSLIME2_R_SPR,           // 319
  CRAWLSLIME_STEPON_SPR,       // 320
  END_LUMP(CRAWLSLIME_LUMP_END, __CRAWLSLIMEEND)

  START_LUMP(HEDGEHOG_LUMP_START, __HEDGEHOGSTART)
  HEDGEHOG_STAND_R_SPR,        // 321
  HEDGEHOG_STAND_L_SPR,        // 322
  HEDGEHOG_ROLL1_L_SPR,        // 323
  HEDGEHOG_ROLL2_L_SPR,        // 324
  HEDGEHOG_ROLL3_L_SPR,        // 325
  HEDGEHOG_ROLL4_L_SPR,        // 326
  HEDGEHOG_ROLL1_R_SPR,        // 327
  HEDGEHOG_ROLL2_R_SPR,        // 328
  HEDGEHOG_ROLL3_R_SPR,        // 329
  HEDGEHOG_ROLL4_R_SPR,        // 330
  END_LUMP(HEDGEHOG_LUMP_END, __HEDGEHOGEND)

  START_LUMP(UNUSED2_LUMP_START, __UNUSED2START)
  END_LUMP(UNUSED2_LUMP_END, __UNUSED2END)

  START_LUMP(SKULLMAN_LUMP_START, __SKULLMANSTART)
  SKULLMAN1_SPR,               // 331
  SKULLMAN2_SPR,               // 332
  SKULLMAN_HAND_L_SPR,         // 333
  SKULLMAN_HAND_R_SPR,         // 334
  SKULLMAN_HAND_ATTACK1_SPR,   // 335
  SKULLMAN_HAND_ATTACK2_SPR,   // 336
  END_LUMP(SKULLMAN_LUMP_END, __SKULLMANEND)

  START_LUMP(MANGLE_LUMP_START, __MANGLESTART)
  MANGLE_HOLOGRAM1_SPR,        // 337
  MANGLE_HOLOGRAM2_SPR,        // 338
  MANGLE_HOLOGRAM3_SPR,        // 339
  MANGLE_HOLOGRAM_FADE1_SPR,   // 340
  MANGLE_HOLOGRAM_FADE2_SPR,   // 341
  MANGLE_HOLOGRAM_FADE3_SPR,   // 342
  MANGLE_HOLOGRAM_ATTACK_SPR,  // 343
  MANGLE_TYPING1_SPR,          // 344
  MANGLE_TYPING2_SPR,          // 345
  MANGLE_DEFEATED_SPR,         // 346
  MANGLE_MONSTER1_L_SPR,       // 347
  MANGLE_MONSTER2_L_SPR,       // 348
  MANGLE_MONSTER1_R_SPR,       // 349
  MANGLE_MONSTER2_R_SPR,       // 350
  END_LUMP(MANGLE_LUMP_END, __MANGLEEND)

  START_LUMP(HELICOPTER_LUMP_START, __HELICOPTERSTART)
  HELICOPTER1_SPR,             // 351
  HELICOPTER2_SPR,             // 352
  PARACHUTEBOT_FALLING_L_SPR,  // 353
  PARACHUTEBOT_FALLING_R_SPR,  // 354
  PARACHUTEBOT_WALK1_L_SPR,    // 355
  PARACHUTEBOT_WALK2_L_SPR,    // 356
  PARACHUTEBOT_WALK1_R_SPR,    // 357
  PARACHUTEBOT_WALK2_R_SPR,    // 358
  END_LUMP(HELICOPTER_LUMP_END, __HELICOPTEREND)

  START_LUMP(RESPAWN_BEACON_LUMP_START, __RESPAWN_BEACONSTART)
  RESPAWN_BEACON_INACTIVE_SPR, // 359
  RESPAWN_BEACON_ACTIVE1_SPR,  // 360
  RESPAWN_BEACON_ACTIVE2_SPR,  // 361
  RESPAWN_BEACON_ACTIVE3_SPR,  // 362
  RESPAWN_BEACON_ACTIVE4_SPR,  // 363
  END_LUMP(RESPAWN_BEACON_LUMP_END, __RESPAWN_BEACONEND)

  START_LUMP(BOUNCEBOT_LUMP_START, __BOUNCEBOTSTART)
  BOUNCEBOT1_SPR,              // 364
  BOUNCEBOT2_SPR,              // 365
  BOUNCEBOT3_SPR,              // 366
  BOUNCEBOT4_SPR,              // 367
  BOUNCEBOT5_SPR,              // 368
  END_LUMP(BOUNCEBOT_LUMP_END, __BOUNCEBOTEND)

  START_LUMP(PLATFORM_LUMP_START, __PLATFORMSTART)
  PLATFORMSPR,                 // 369
  END_LUMP(PLATFORM_LUMP_END, __PLATFORMEND)

  START_LUMP(UNUSED3_LUMP_START, __UNUSED3START)
  END_LUMP(UNUSED3_LUMP_END, __UNUSED3END)

  START_LUMP(TURRET_LUMP_START, __TURRETSTART)
  TURRET_IDLE_L_SPR,           // 370
  TURRET_READY_L_SPR,          // 371
  TURRET_SHOOT_L_SPR,          // 372
  TURRET_IDLE_R_SPR,           // 373
  TURRET_READY_R_SPR,          // 374
  TURRET_SHOOT_R_SPR,          // 375
  END_LUMP(TURRET_LUMP_END, __TURRETEND)

  START_LUMP(LASERGUNNER_LUMP_START, __LASERGUNNERSTART)
  LASERGUNNER_IDLE_L_SPR,      // 376
  LASERGUNNER_SHOOT_L_SPR,     // 377
  LASERGUNNER_IDLE_R_SPR,      // 378
  LASERGUNNER_SHOOT_R_SPR,     // 379
  END_LUMP(LASERGUNNER_LUMP_END, __LASERGUNNEREND)

  START_LUMP(FORCEFIELD_BOT_LUMP_START, __FORCEFIELD_BOTSTART)
  FORCEFIELD_BOT1_SPR,         // 380
  FORCEFIELD_BOT2_SPR,         // 381
  FORCEFIELD_BOT3_SPR,         // 382
  FORCEFIELD_BOT4_SPR,         // 383
  END_LUMP(FORCEFIELD_BOT_LUMP_END, __FORCEFIELD_BOTEND)

  START_LUMP(SPARKSHOT_LUMP_START, __SPARKSHOTSTART)
  SPARKSHOT1_SPR,              // 384
  SPARKSHOT2_SPR,              // 385
  END_LUMP(SPARKSHOT_LUMP_END, __SPARKSHOTEND)

  START_LUMP(PUSHBLOCK_LUMP_START, __PUSHBLOCKSTART)
  PUSHBLOCKSPR,                // 386
  END_LUMP(PUSHBLOCK_LUMP_END, __PUSHBLOCKEND)

  START_LUMP(ROBOPAL_LUMP_START, __ROBOPALSTART)
  ROBOPAL1_SPR,                // 387
  ROBOPAL2_SPR,                // 388
  ROBOPAL_TELEPORT1_SPR,       // 389
  ROBOPAL_TELEPORT2_SPR,       // 390
  ROBOPAL_SHOT1_R_SPR,         // 391
  ROBOPAL_SHOT2_R_SPR,         // 392
  ROBOPAL_SHOT1_L_SPR,         // 393
  ROBOPAL_SHOT2_L_SPR,         // 394
  ROCKET_IMPACT1_SPR,          // 395
  ROCKET_IMPACT2_SPR,          // 396
  END_LUMP(ROBOPAL_LUMP_END, __ROBOPALEND)

  START_LUMP(CRUSHERBLOCK_LUMP_START, __CRUSHERBLOCKSTART)
  CRUSHERBLOCKSPR,             // 397
  END_LUMP(CRUSHERBLOCK_LUMP_END, __CRUSHERBLOCKEND)

  START_LUMP(FALLINGBLOCK_LUMP_START, __FALLINGBLOCKSTART)
  FALLINGBLOCKSPR,             // 398
  END_LUMP(FALLINGBLOCK_LUMP_END, __FALLINGBLOCKEND)

  START_LUMP(TANKBOT_LUMP_START, __TANKBOTSTART)
  TANKBOT1_SPR,                // 399
  TANKBOT2_SPR,                // 400
  TANKBOT_SHOOT_SPR,           // 401
  TANKBOT_BIG_SHOT_SPR,        // 402
  TANKBOT_SHOT_FLYING_SPR,     // 403
  TANKBOT_SHOT_LANDING_SPR,    // 404
  END_LUMP(TANKBOT_LUMP_END, __TANKBOTEND)

  SCOREBOXSPR,                 // 405

  START_LUMP(INTRO_LUMP_START, __INTROSTART)
  APOGEELOGOSPR,               // 406
  ASTEROID1_SPR,               // 407
  ASTEROID2_SPR,               // 408
  ASTEROID3_SPR,               // 409
  ASTEROID4_SPR,               // 410
  END_LUMP(INTRO_LUMP_END, __INTROEND)

  //
  // TILES (these don't need names)
  //

  LASTTILE=STARTEXTERNS-1,

  //
  // EXTERNS
  //

  //texts
  T_1,                         // 4607
  T_2,                         // 4608
  T_3,                         // 4609
  T_4,                         // 4610
  T_5,                         // 4611
  T_6,                         // 4612
  T_7,                         // 4613

  //demos
  DEMO0,                       // 4614
  DEMO1,                       // 4615
  DEMO2,                       // 4616
  DEMO3,                       // 4617
  DEMO4,                       // 4618

  ORDERSCREEN,                 // 4619
  OUTOFMEM,                    // 4620

  NUMGRCHUNKS
} graphicnums;

#undef START_LUMP
#undef END_LUMP

#endif //__GFX_H__

