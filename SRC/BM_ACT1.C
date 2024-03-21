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

Sint16 TABLE6[] = { 0, 1, 0, -1, 1, 1, -1, -1, -1, 0, 1, 0, -1, 1, 1, -1 };


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

#if 1
statetype far s_167 = { /* 32730 */
  348, 350, think, false, ps_none, 0, 0, 0,
  T_Projectile, NULL, NULL, &s_167};
statetype far s_173 = { /* 327f0 */
  0, 0, slide, false, ps_none, 40, 0, 8,
  NULL, NULL, R_Draw, NULL};
statetype far s_176 = { /* 32850 */
  387, 387, stepthink, false, ps_none, 5, 0, 0,
  NULL, NULL, NULL, NULL};
statetype far s_186 = { /* 32990 */
  113, 113, step, false, ps_tofloor, 5, 64, 0,
  NULL, NULL, NULL, &s_187};
statetype far s_187 = { /* 329b0 */
  114, 114, step, false, ps_tofloor, 5, 64, 0,
  NULL, NULL, NULL, &s_186};
statetype far s_200 = { /* 32b50 */
  114, 114, stepthink, false, ps_tofloor, 7, 128, 0,
  NULL, NULL, NULL, NULL};
statetype far s_201 = { /* 32b70 */
  293, 293, stepthink, false, ps_tofloor, 50, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_225 = { /* 32e70 */
  253, 258, think, false, ps_none, 0, 0, 0,
  T_Projectile, NULL, NULL, &s_225};
#else

statetype far s_128 = { /* 32250 */
  369, 369, think, false, ps_none, 0, 0, 0,
  sub_2018a, NULL, R_Draw, NULL};

statetype far s_129 = { /* 32270 */
  406, 406, think, false, ps_none, 0, 0, 0,
  sub_2018a, NULL, R_Draw, NULL};

statetype far s_130 = { /* 32290 */
  352, 352, stepthink, false, ps_none, 1, 0, 0,
  sub_2041b, NULL, sub_20628, &s_130};

statetype far s_131 = { /* 322b0 */
  351, 351, stepthink, false, ps_none, 10, 0, 0,
  sub_2041b, NULL, sub_20628, &s_130};

statetype far s_132 = { /* 322d0 */
  351, 351, stepthink, false, ps_none, 1, 0, 0,
  sub_2041b, NULL, sub_2068c, &s_130};

statetype far s_133 = { /* 322f0 */
  355, 357, step, false, ps_tofloor, 10, 128, 0,
  sub_20739, NULL, R_Walk, &s_134};

statetype far s_134 = { /* 32310 */
  356, 358, step, false, ps_tofloor, 10, 128, 0,
  sub_20739, NULL, R_Walk, &s_133};

statetype far s_135 = { /* 32330 */
  356, 358, think, false, ps_none, 0, 0, 0,
  T_Projectile, sub_2080e, sub_2089a, &s_135};

statetype far s_136 = { /* 32350 */
  353, 354, stepthink, false, ps_none, 10, 8, 32,
  NULL, sub_2080e, sub_20838, &s_136};

statetype far s_137 = { /* 32370 */
  275, 277, step, false, ps_tofloor, 10, 128, 0,
  sub_20a42, NULL, R_Walk, &s_138};

statetype far s_138 = { /* 32390 */
  276, 278, step, false, ps_tofloor, 10, 128, 0,
  sub_20a42, NULL, R_Walk, &s_137};

statetype far s_139 = { /* 323b0 */
  275, 277, step, true, ps_tofloor, 5, 128, 0,
  sub_2097e, NULL, R_Walk, &s_140};

statetype far s_140 = { /* 323d0 */
  276, 278, step, true, ps_tofloor, 5, 128, 0,
  sub_2097e, NULL, R_Walk, &s_139};

statetype far s_141 = { /* 323f0 */
  279, 280, step, false, ps_none, 10, 0, 0,
  sub_20992, NULL, R_Draw, &s_142};

statetype far s_142 = { /* 32410 */
  279, 280, step, false, ps_none, 10, 65408, 0,
  NULL, NULL, R_Draw, &s_137};

statetype far s_143 = { /* 32430 */
  281, 283, stepthink, false, ps_none, 4, 0, 0,
  T_Projectile, NULL, sub_1fca6, &s_144};

statetype far s_144 = { /* 32450 */
  282, 284, stepthink, false, ps_none, 4, 0, 0,
  T_Projectile, NULL, sub_1fca6, &s_143};

statetype far s_145 = { /* 32470 */
  298, 301, step, false, ps_tofloor, 20, 128, 0,
  sub_20c43, NULL, R_Walk, &s_146};

statetype far s_146 = { /* 32490 */
  299, 302, step, false, ps_tofloor, 20, 128, 0,
  sub_20c43, NULL, R_Walk, &s_145};

statetype far s_147 = { /* 324b0 */
  300, 303, step, false, ps_tofloor, 10, 0, 0,
  sub_20b93, NULL, R_Walk, &s_145};

statetype far s_148 = { /* 324d0 */
  304, 304, stepthink, false, ps_none, 4, 0, 0,
  T_Projectile, NULL, sub_1fca6, &s_149};

statetype far s_149 = { /* 324f0 */
  305, 305, stepthink, false, ps_none, 4, 0, 0,
  T_Projectile, NULL, sub_1fca6, &s_148};

statetype far s_150 = { /* 32510 */
  223, 223, step, false, ps_tofloor, 40, 0, 0,
  NULL, NULL, R_Draw, &s_151};

statetype far s_151 = { /* 32530 */
  224, 224, step, false, ps_tofloor, 40, 0, 0,
  NULL, NULL, R_Draw, &s_150};

statetype far s_152 = { /* 32550 */
  225, 225, step, false, ps_tofloor, 40, 0, 0,
  NULL, NULL, R_Draw, &s_153};

statetype far s_153 = { /* 32570 */
  226, 226, step, false, ps_tofloor, 40, 0, 0,
  NULL, NULL, R_Draw, &s_152};

statetype far s_154 = { /* 32590 */
  227, 227, step, false, ps_tofloor, 40, 0, 0,
  NULL, NULL, R_Draw, &s_155};

statetype far s_155 = { /* 325b0 */
  228, 228, step, false, ps_tofloor, 40, 0, 0,
  NULL, NULL, R_Draw, &s_154};

statetype far s_156 = { /* 325d0 */
  337, 337, step, false, ps_none, 10, 0, 0,
  sub_20e1f, NULL, R_Draw, &s_156};

statetype far s_157 = { /* 325f0 */
  338, 338, step, false, ps_none, 10, 0, 0,
  sub_20e1f, NULL, R_Draw, &s_156};

statetype far s_158 = { /* 32610 */
  339, 339, step, false, ps_none, 200, 0, 0,
  sub_20e1f, NULL, R_Draw, &s_156};

statetype far s_159 = { /* 32630 */
  340, 340, step, false, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, &s_156};

statetype far s_160 = { /* 32650 */
  341, 341, step, false, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, &s_157};

statetype far s_161 = { /* 32670 */
  342, 342, step, false, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, &s_158};

statetype far s_162 = { /* 32690 */
  343, 343, step, false, ps_none, 3, 0, 0,
  sub_20f20, NULL, sub_2106d, &s_162};

statetype far s_163 = { /* 326b0 */
  344, 344, step, false, ps_tofloor, 20, 0, 0,
  sub_2117b, NULL, R_Draw, &s_164};

statetype far s_164 = { /* 326d0 */
  345, 345, step, false, ps_tofloor, 20, 0, 0,
  sub_2117b, NULL, R_Draw, &s_163};

statetype far s_165 = { /* 326f0 */
  347, 349, step, false, ps_tofloor, 10, 128, 0,
  sub_2117b, NULL, R_Walk, &s_166};

statetype far s_166 = { /* 32710 */
  348, 350, step, false, ps_tofloor, 10, 128, 0,
  sub_2117b, NULL, R_Walk, &s_165};

statetype far s_167 = { /* 32730 */
  348, 350, think, false, ps_none, 0, 0, 0,
  T_Projectile, NULL, sub_2134e, &s_167};

statetype far s_168 = { /* 32750 */
  346, 346, step, false, ps_tofloor, 200, 0, 0,
  NULL, NULL, R_Draw, &s_169};

statetype far s_169 = { /* 32770 */
  346, 346, step, false, ps_tofloor, 2, 0, 0,
  sub_21324, NULL, R_Draw, &s_169};

statetype far s_170 = { /* 32790 */
  346, 346, think, false, ps_tofloor, 0, 0, 0,
  NULL, NULL, R_Draw, &s_170};

statetype far s_171 = { /* 327b0 */
  0, 0, step, false, ps_none, 20, 0, 0,
  sub_21639, NULL, R_Draw, &s_172};

statetype far s_172 = { /* 327d0 */
  0, 0, step, false, ps_none, 20, 0, 0,
  sub_21639, NULL, R_Draw, &s_171};

statetype far s_173 = { /* 327f0 */
  0, 0, slide, false, ps_none, 40, 0, 8,
  sub_21654, NULL, R_Draw, NULL};

statetype far s_174 = { /* 32810 */
  387, 387, step, false, ps_none, 15, 0, 0,
  NULL, NULL, R_Draw, &s_175};

statetype far s_175 = { /* 32830 */
  388, 388, step, false, ps_none, 15, 0, 0,
  NULL, NULL, R_Draw, &s_174};

statetype far s_176 = { /* 32850 */
  387, 387, stepthink, false, ps_none, 5, 0, 0,
  sub_21704, NULL, sub_218a8, &s_177};

statetype far s_177 = { /* 32870 */
  388, 388, stepthink, false, ps_none, 5, 0, 0,
  sub_21704, NULL, sub_218a8, &s_176};

statetype far s_178 = { /* 32890 */
  389, 389, step, false, ps_none, 25, 0, 0,
  NULL, NULL, R_Draw, &s_179};

statetype far s_179 = { /* 328b0 */
  390, 390, step, false, ps_none, 25, 0, 0,
  NULL, NULL, R_Draw, &s_180};

statetype far s_180 = { /* 328d0 */
  65535, 65535, step, false, ps_none, 1, 0, 0,
  sub_219ab, NULL, R_Draw, &s_181};

statetype far s_181 = { /* 328f0 */
  390, 390, step, false, ps_none, 25, 0, 0,
  NULL, NULL, R_Draw, &s_182};

statetype far s_182 = { /* 32910 */
  389, 389, step, false, ps_none, 25, 0, 0,
  NULL, NULL, R_Draw, &s_176};

statetype far s_183 = { /* 32930 */
  229, 232, step, false, ps_tofloor, 10, 128, 0,
  sub_21b2c, NULL, R_Walk, &s_184};

statetype far s_184 = { /* 32950 */
  230, 233, step, false, ps_tofloor, 10, 128, 0,
  sub_21b2c, NULL, R_Walk, &s_183};

statetype far s_185 = { /* 32970 */
  231, 234, think, false, ps_none, 0, 0, 0,
  T_Projectile, NULL, sub_21d67, &s_183};

statetype far s_186 = { /* 32990 */
  113, 113, step, false, ps_tofloor, 5, 64, 0,
  sub_21ce4, sub_1e45c, sub_21e19, &s_187};

statetype far s_187 = { /* 329b0 */
  114, 114, step, false, ps_tofloor, 5, 64, 0,
  sub_21ce4, sub_1e45c, sub_21e19, &s_186};

statetype far s_188 = { /* 329d0 */
  294, 296, step, false, ps_tofloor, 10, 128, 0,
  sub_21bfb, NULL, R_Walk, &s_189};

statetype far s_189 = { /* 329f0 */
  295, 297, step, false, ps_tofloor, 10, 128, 0,
  sub_21bfb, NULL, R_Walk, &s_188};

statetype far s_190 = { /* 32a10 */
  294, 296, think, false, ps_none, 0, 0, 0,
  T_Projectile, NULL, sub_21dc0, &s_188};

statetype far s_191 = { /* 32a30 */
  267, 271, step, false, ps_tofloor, 10, 0, 0,
  sub_21f41, NULL, R_Draw, &s_191};

statetype far s_192 = { /* 32a50 */
  268, 272, stepthink, false, ps_none, 4, 0, 0,
  T_Projectile, NULL, R_Draw, &s_193};

statetype far s_193 = { /* 32a70 */
  269, 273, stepthink, false, ps_none, 4, 0, 0,
  T_Projectile, NULL, sub_21ffd, &s_194};

statetype far s_194 = { /* 32a90 */
  270, 274, stepthink, false, ps_none, 0, 0, 0,
  T_Projectile, NULL, sub_21ffd, &s_194};

statetype far s_195 = { /* 32ab0 */
  285, 289, step, false, ps_tofloor, 7, 128, 0,
  sub_220e0, NULL, sub_22148, &s_196};

statetype far s_196 = { /* 32ad0 */
  286, 290, step, false, ps_tofloor, 7, 128, 0,
  NULL, NULL, sub_22148, &s_197};

statetype far s_197 = { /* 32af0 */
  287, 291, step, false, ps_tofloor, 7, 128, 0,
  NULL, NULL, sub_22148, &s_198};

statetype far s_198 = { /* 32b10 */
  288, 292, step, false, ps_tofloor, 7, 128, 0,
  NULL, NULL, sub_22148, &s_195};

statetype far s_199 = { /* 32b30 */
  113, 113, stepthink, false, ps_tofloor, 7, 128, 0,
  NULL, NULL, sub_22148, &s_200};

statetype far s_200 = { /* 32b50 */
  114, 114, stepthink, false, ps_tofloor, 7, 128, 0,
  sub_22126, NULL, sub_22148, &s_199};

statetype far s_201 = { /* 32b70 */
  293, 293, stepthink, false, ps_tofloor, 50, 0, 0,
  NULL, NULL, R_Draw, &s_195};

statetype far s_202 = { /* 32b90 */
  288, 292, think, false, ps_none, 0, 0, 0,
  T_Projectile, NULL, sub_22213, NULL};

statetype far s_203 = { /* 32bb0 */
  323, 327, step, false, ps_tofloor, 7, 128, 0,
  sub_222f6, NULL, sub_22392, &s_204};

statetype far s_204 = { /* 32bd0 */
  324, 328, step, false, ps_tofloor, 7, 128, 0,
  NULL, NULL, sub_22392, &s_205};

statetype far s_205 = { /* 32bf0 */
  325, 329, step, false, ps_tofloor, 7, 128, 0,
  NULL, NULL, sub_22392, &s_206};

statetype far s_206 = { /* 32c10 */
  326, 330, step, false, ps_tofloor, 7, 128, 0,
  NULL, NULL, sub_22392, &s_203};

statetype far s_207 = { /* 32c30 */
  322, 321, stepthink, false, ps_tofloor, 25, 0, 0,
  sub_2233c, NULL, sub_22392, &s_207};

statetype far s_208 = { /* 32c50 */
  322, 321, stepthink, false, ps_tofloor, 75, 0, 0,
  sub_2235e, NULL, R_Draw, &s_208};

statetype far s_209 = { /* 32c70 */
  322, 321, think, false, ps_none, 0, 0, 0,
  T_Projectile, NULL, sub_2245d, NULL};

statetype far s_210 = { /* 32c90 */
  235, 236, step, true, ps_tofloor, 75, 0, 0,
  NULL, NULL, R_Draw, &s_211};

statetype far s_211 = { /* 32cb0 */
  237, 243, stepthink, false, ps_tofloor, 10, 64, 0,
  sub_22540, NULL, R_Walk, &s_212};

statetype far s_212 = { /* 32cd0 */
  238, 244, stepthink, false, ps_tofloor, 10, 64, 0,
  sub_22540, NULL, R_Walk, &s_213};

statetype far s_213 = { /* 32cf0 */
  239, 245, stepthink, false, ps_tofloor, 10, 64, 0,
  sub_22540, NULL, R_Walk, &s_214};

statetype far s_214 = { /* 32d10 */
  240, 246, stepthink, false, ps_tofloor, 10, 64, 0,
  sub_22540, NULL, R_Walk, &s_211};

statetype far s_215 = { /* 32d30 */
  241, 247, step, true, ps_tofloor, 15, 0, 0,
  NULL, NULL, R_Draw, &s_216};

statetype far s_216 = { /* 32d50 */
  242, 248, step, true, ps_tofloor, 10, 0, 0,
  NULL, NULL, R_Draw, &s_211};

statetype far s_217 = { /* 32d70 */
  249, 254, step, false, ps_toceiling, 10, 128, 0,
  sub_2268b, NULL, sub_213a2, &s_218};

statetype far s_218 = { /* 32d90 */
  250, 255, step, false, ps_toceiling, 10, 128, 0,
  sub_2268b, NULL, sub_213a2, &s_219};

statetype far s_219 = { /* 32db0 */
  251, 256, step, false, ps_toceiling, 10, 128, 0,
  sub_2268b, NULL, sub_213a2, &s_220};

statetype far s_220 = { /* 32dd0 */
  252, 257, step, false, ps_toceiling, 10, 128, 0,
  sub_2268b, NULL, sub_213a2, &s_217};

statetype far s_221 = { /* 32df0 */
  259, 263, step, false, ps_tofloor, 6, 128, 0,
  sub_2274a, NULL, R_Walk, &s_222};

statetype far s_222 = { /* 32e10 */
  260, 264, step, false, ps_tofloor, 6, 128, 0,
  sub_2274a, NULL, R_Walk, &s_223};

statetype far s_223 = { /* 32e30 */
  261, 265, step, false, ps_tofloor, 6, 128, 0,
  sub_2274a, NULL, R_Walk, &s_224};

statetype far s_224 = { /* 32e50 */
  262, 266, step, false, ps_tofloor, 6, 128, 0,
  sub_2274a, NULL, R_Walk, &s_221};

statetype far s_225 = { /* 32e70 */
  253, 258, think, false, ps_none, 0, 0, 0,
  T_Projectile, NULL, sub_227bc, &s_225};

statetype far s_226 = { /* 32e90 */
  316, 318, step, true, ps_tofloor, 25, 0, 0,
  NULL, NULL, R_Draw, &s_227};

statetype far s_227 = { /* 32eb0 */
  316, 318, stepthink, false, ps_tofloor, 10, 64, 0,
  sub_228aa, NULL, R_Walk, &s_228};

statetype far s_228 = { /* 32ed0 */
  317, 319, stepthink, false, ps_tofloor, 10, 64, 0,
  sub_228aa, NULL, R_Walk, &s_227};

statetype far s_229 = { /* 32ef0 */
  320, 320, step, true, ps_tofloor, 15, 0, 0,
  NULL, NULL, R_Draw, &s_226};

statetype far s_230 = { /* 32f10 */
  182, 182, step, false, ps_none, 15, 0, 0,
  NULL, NULL, R_Draw, &s_231};

statetype far s_231 = { /* 32f30 */
  183, 183, step, false, ps_none, 12, 0, 0,
  NULL, NULL, R_Draw, &s_232};

statetype far s_232 = { /* 32f50 */
  184, 184, step, false, ps_none, 5, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_233 = { /* 32f70 */
  399, 399, stepthink, false, ps_tofloor, 6, 0, 0,
  sub_2291e, NULL, R_Draw, &s_233};

statetype far s_234 = { /* 32f90 */
  399, 399, step, false, ps_tofloor, 10, 0, 0,
  sub_22b98, NULL, R_Draw, &s_234};

statetype far s_235 = { /* 32fb0 */
  399, 399, slide, false, ps_tofloor, 20, 8, 0,
  NULL, NULL, R_Walk, &s_236};

statetype far s_236 = { /* 32fd0 */
  400, 400, slide, false, ps_tofloor, 20, 8, 0,
  sub_22be7, NULL, R_Walk, &s_235};

statetype far s_237 = { /* 32ff0 */
  401, 401, step, false, ps_tofloor, 7, 0, 0,
  sub_22d16, NULL, R_Draw, &s_234};

statetype far s_238 = { /* 33010 */
  399, 399, step, false, ps_tofloor, 7, 0, 0,
  sub_22db0, NULL, R_Draw, &s_234};

statetype far s_239 = { /* 33030 */
  403, 403, stepthink, false, ps_none, 10, 0, 0,
  T_Projectile, NULL, sub_22f3f, &s_239};

statetype far s_240 = { /* 33050 */
  404, 404, stepthink, false, ps_none, 5, 8, 65504,
  NULL, NULL, sub_22fa5, &s_240};

statetype far s_241 = { /* 33070 */
  402, 402, stepthink, false, ps_none, 10, 0, 0,
  T_Projectile, NULL, sub_22e5c, &s_241};

statetype far s_242 = { /* 33090 */
  57, 57, step, false, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, &s_243};

statetype far s_243 = { /* 330b0 */
  58, 58, step, false, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_244 = { /* 330d0 */
  59, 59, step, true, ps_tofloor, 5, 0, 0,
  sub_22f1a, NULL, R_Draw, &s_245};

statetype far s_245 = { /* 330f0 */
  60, 60, step, true, ps_tofloor, 5, 0, 0,
  sub_22f1a, NULL, R_Draw, &s_246};

statetype far s_246 = { /* 33110 */
  61, 61, step, true, ps_tofloor, 5, 0, 0,
  sub_22f1a, NULL, R_Draw, &s_244};

statetype far s_247 = { /* 33130 */
  376, 378, step, false, ps_tofloor, 6, 0, 0,
  sub_230fe, NULL, R_Draw, &s_247};

statetype far s_248 = { /* 33150 */
  376, 378, step, true, ps_tofloor, 40, 0, 0,
  NULL, NULL, R_Draw, &s_249};

statetype far s_249 = { /* 33170 */
  376, 378, step, true, ps_tofloor, 4, 0, 0,
  NULL, NULL, R_Draw, &s_250};

statetype far s_250 = { /* 33190 */
  377, 379, step, false, ps_tofloor, 6, 0, 0,
  sub_23188, NULL, R_Draw, &s_249};

statetype far s_251 = { /* 331b0 */
  376, 378, stepthink, false, ps_tofloor, 6, 0, 0,
  sub_2291e, NULL, R_Draw, &s_251};

statetype far s_252 = { /* 331d0 */
  62, 62, stepthink, true, ps_none, 8, 0, 0,
  T_Velocity, sub_23223, sub_23254, &s_252};

statetype far s_253 = { /* 331f0 */
  57, 57, step, true, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, &s_254};

statetype far s_254 = { /* 33210 */
  58, 58, step, true, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_255 = { /* 33230 */
  57, 57, stepthink, true, ps_none, 8, 0, 0,
  T_Velocity, sub_23223, sub_23254, &s_256};

statetype far s_256 = { /* 33250 */
  58, 58, stepthink, true, ps_none, 8, 0, 0,
  T_Velocity, sub_23223, sub_23254, &s_255};

statetype far s_257 = { /* 33270 */
  386, 386, stepthink, false, ps_tofloor, 6, 0, 1,
  NULL, sub_233de, sub_2334c, &s_257};

statetype far s_258 = { /* 33290 */
  386, 386, stepthink, false, ps_none, 0, 0, 0,
  T_Projectile, sub_233de, sub_23395, &s_257};

statetype far s_259 = { /* 332b0 */
  398, 398, stepthink, false, ps_none, 1, 0, 0,
  sub_234b7, sub_2351f, R_Draw, &s_259};

statetype far s_260 = { /* 332d0 */
  398, 398, stepthink, false, ps_none, 0, 0, 0,
  T_Projectile, NULL, sub_234ed, &s_260};

statetype far s_261 = { /* 332f0 */
  397, 397, stepthink, false, ps_none, 6, 0, 0,
  sub_235c2, NULL, R_Draw, &s_261};

statetype far s_262 = { /* 33310 */
  397, 397, stepthink, false, ps_none, 5, 0, 8,
  sub_235e1, sub_2365a, sub_23600, &s_262};

statetype far s_263 = { /* 33330 */
  364, 364, stepthink, false, ps_none, 10, 0, 0,
  sub_2370e, NULL, sub_237bf, &s_264};

statetype far s_264 = { /* 33350 */
  366, 366, stepthink, false, ps_none, 10, 0, 0,
  sub_2370e, NULL, sub_237bf, &s_265};

statetype far s_265 = { /* 33370 */
  367, 367, stepthink, false, ps_none, 10, 0, 0,
  sub_2370e, NULL, sub_237bf, &s_266};

statetype far s_266 = { /* 33390 */
  368, 368, stepthink, false, ps_none, 10, 0, 0,
  sub_2370e, NULL, sub_237bf, &s_263};

statetype far s_267 = { /* 333b0 */
  365, 365, stepthink, false, ps_none, 15, 0, 0,
  sub_2370e, NULL, sub_237bf, &s_263};

statetype far s_268 = { /* 333d0 */
  306, 306, step, false, ps_none, 50, 0, 0,
  NULL, NULL, R_Draw, &s_269};

statetype far s_269 = { /* 333f0 */
  307, 307, step, false, ps_none, 50, 0, 0,
  NULL, NULL, R_Draw, &s_270};

statetype far s_270 = { /* 33410 */
  308, 308, step, false, ps_none, 1, 0, 0,
  sub_2390f, NULL, R_Draw, &s_268};

statetype far s_271 = { /* 33430 */
  309, 309, step, false, ps_none, 5, 0, 0,
  NULL, NULL, R_Draw, &s_272};

statetype far s_272 = { /* 33450 */
  310, 310, step, false, ps_none, 5, 0, 0,
  sub_23995, NULL, R_Draw, &s_271};

statetype far s_273 = { /* 33470 */
  311, 311, stepthink, false, ps_none, 0, 0, 0,
  T_Projectile, NULL, sub_239b3, &s_273};

statetype far s_274 = { /* 33490 */
  312, 312, step, false, ps_tofloor, 15, 0, 0,
  NULL, NULL, R_Draw, &s_275};

statetype far s_275 = { /* 334b0 */
  313, 313, step, false, ps_tofloor, 15, 0, 0,
  NULL, NULL, R_Draw, &s_276};

statetype far s_276 = { /* 334d0 */
  314, 314, step, false, ps_tofloor, 15, 0, 0,
  NULL, NULL, R_Draw, &s_277};

statetype far s_277 = { /* 334f0 */
  315, 315, step, false, ps_tofloor, 15, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_278 = { /* 33510 */
  370, 373, step, false, ps_tofloor, 6, 0, 0,
  sub_23aa2, NULL, R_Draw, &s_278};

statetype far s_279 = { /* 33530 */
  371, 374, step, true, ps_tofloor, 40, 0, 0,
  NULL, NULL, R_Draw, &s_280};

statetype far s_280 = { /* 33550 */
  371, 374, step, true, ps_tofloor, 4, 0, 0,
  NULL, NULL, R_Draw, &s_281};

statetype far s_281 = { /* 33570 */
  372, 375, step, false, ps_tofloor, 6, 0, 0,
  sub_23b07, NULL, R_Draw, &s_280};

statetype far s_282 = { /* 33590 */
  407, 407, slide, false, ps_none, 10, 24, 24,
  NULL, NULL, sub_23dc4, &s_283};

statetype far s_283 = { /* 335b0 */
  408, 408, slide, false, ps_none, 10, 24, 24,
  NULL, NULL, sub_23dc4, &s_284};

statetype far s_284 = { /* 335d0 */
  409, 409, slide, false, ps_none, 10, 24, 24,
  NULL, NULL, sub_23dc4, &s_285};

statetype far s_285 = { /* 335f0 */
  410, 410, slide, false, ps_none, 10, 24, 24,
  NULL, NULL, sub_23dc4, &s_282};

statetype far s_286 = { /* 33610 */
  221, 221, slide, false, ps_none, 10, 0, 0,
  NULL, sub_23d3f, sub_23dc4, &s_287};

statetype far s_287 = { /* 33630 */
  222, 222, slide, false, ps_none, 10, 0, 0,
  NULL, sub_23d3f, sub_23dc4, &s_286};

statetype far s_288 = { /* 33650 */
  331, 331, stepthink, false, ps_none, 35, 0, 0,
  sub_241cb, NULL, R_Draw, &s_288};

statetype far s_289 = { /* 33670 */
  332, 332, stepthink, false, ps_none, 35, 0, 0,
  sub_241cb, NULL, R_Draw, &s_289};

statetype far s_290 = { /* 33690 */
  334, 334, stepthink, false, ps_none, 10, 0, 0,
  sub_24048, NULL, R_Draw, &s_290};

statetype far s_291 = { /* 336b0 */
  333, 333, stepthink, false, ps_none, 10, 0, 0,
  sub_24067, NULL, R_Draw, &s_291};

statetype far s_292 = { /* 336d0 */
  334, 334, slide, false, ps_none, 10, 24, 24,
  sub_24086, NULL, sub_23f58, &s_292};

statetype far s_293 = { /* 336f0 */
  333, 333, slide, false, ps_none, 10, 24, 24,
  sub_240d4, NULL, sub_23f58, &s_293};

statetype far s_294 = { /* 33710 */
  335, 335, stepthink, false, ps_none, 20, 0, 0,
  T_Projectile, NULL, sub_23fba, &s_295};

statetype far s_295 = { /* 33730 */
  336, 336, stepthink, false, ps_none, 20, 0, 0,
  T_Projectile, NULL, sub_23fba, &s_294};

statetype far s_296 = { /* 33750 */
  335, 335, stepthink, false, ps_none, 20, 0, 0,
  T_Projectile, NULL, sub_24001, &s_297};

statetype far s_297 = { /* 33770 */
  336, 336, stepthink, false, ps_none, 20, 0, 0,
  T_Projectile, NULL, sub_24001, &s_296};

statetype far s_298 = { /* 33790 */
  0, 0, step, false, ps_none, 50, 0, 0,
  NULL, NULL, R_Draw, &s_299};

statetype far s_299 = { /* 337b0 */
  0, 0, step, false, ps_none, 1, 0, 0,
  sub_242b1, NULL, R_Draw, &s_298};

statetype far s_300 = { /* 337d0 */
  384, 384, stepthink, false, ps_none, 8, 0, 0,
  T_Velocity, NULL, sub_24372, &s_301};

statetype far s_301 = { /* 337f0 */
  385, 385, stepthink, false, ps_none, 8, 0, 0,
  T_Velocity, NULL, sub_24372, &s_300};

statetype far s_302 = { /* 33810 */
  57, 57, step, false, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, &s_303};

statetype far s_303 = { /* 33830 */
  58, 58, step, false, ps_none, 10, 0, 0,
  NULL, NULL, R_Draw, NULL};

statetype far s_304 = { /* 33850 */
  359, 359, step, false, ps_tofloor, 10, 0, 0,
  NULL, sub_24446, R_Draw, &s_304};

statetype far s_305 = { /* 33870 */
  360, 360, step, false, ps_tofloor, 10, 0, 0,
  NULL, NULL, R_Draw, &s_306};

statetype far s_306 = { /* 33890 */
  361, 361, step, false, ps_tofloor, 10, 0, 0,
  NULL, NULL, R_Draw, &s_307};

statetype far s_307 = { /* 338b0 */
  362, 362, step, false, ps_tofloor, 10, 0, 0,
  NULL, NULL, R_Draw, &s_308};

statetype far s_308 = { /* 338d0 */
  363, 363, step, false, ps_tofloor, 10, 0, 0,
  NULL, NULL, R_Draw, &s_305};

#endif

// PLACEHOLDER

void placeholder(void)
{
  "Goplat moved to a bad spot: ";
}

void sub_22A0D() {}

