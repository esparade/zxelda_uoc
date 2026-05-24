//zxelda v0.1b
//07abr'26

extern unsigned char sprite_negro [];
extern unsigned char sprite_amaD [];

extern unsigned char wrld_frst [];
extern unsigned char wrld_bush [];
extern unsigned char wrld_door_up [];
extern unsigned char wrld_door_left [];
extern unsigned char wrld_door_right [];

extern unsigned char dngn_tile [];
extern unsigned char dngn_blck [];
extern unsigned char dngn_wall [];


extern unsigned char plyr_upA [];
extern unsigned char plyr_upB [];
extern unsigned char plyr_rghA [];
extern unsigned char plyr_rghB [];
extern unsigned char plyr_dwnA [];
extern unsigned char plyr_dwnB [];
extern unsigned char plyr_lftA [];
extern unsigned char plyr_lftB [];
extern unsigned char swrd_up [];
extern unsigned char swrd_rgh [];
extern unsigned char swrd_dwn [];
extern unsigned char swrd_lft [];


extern unsigned char enmy_octoD_a [];
extern unsigned char enmy_octoD_b [];

extern unsigned char item_llave [];
extern unsigned char item_llave_trans [];

extern unsigned char hud_corazon_ama [];
extern unsigned char hud_corazon_neg [];
extern unsigned char hud_corazon_vacio_ama [];
extern unsigned char hud_corazon_vacio_neg [];

extern unsigned char hud_lV_ama [];
extern unsigned char hud_lI_ama [];
extern unsigned char hud_lD_ama [];
extern unsigned char hud_lA_ama [];
extern unsigned char hud_lV_neg [];
extern unsigned char hud_lI_neg [];
extern unsigned char hud_lD_neg [];
extern unsigned char hud_lA_neg [];

#asm
    ._wrld_frst
	DEFB	224,192,241,240,241,242,113,250
	DEFB	115,250,243,254,243,224,243,220
	DEFB	227,222,227,222, 65,220, 64,156
	DEFB	159, 28,158, 28,191, 24, 44,  0
	DEFB	  4,  4,  4,  4

    ._wrld_bush
	DEFB	 10, 64, 47,168, 55,212,127,234
	DEFB	125,213,255,250,223,244,127,106
	DEFB	247,228,255,160,223,208,126, 32
	DEFB	 26,  0,  5,192, 14,170, 21, 85
	DEFB	  52,  52,  52,  52

	._wrld_door_up
	DEFB	199,227,252, 63,135,225,192,  3
	DEFB	222,123,204, 51,128,  1,170,171
	DEFB	 56, 56

    ._wrld_door_left
	DEFB	126, 63, 24, 96, 62, 79, 69, 79
	DEFB	131, 76,185, 76,169, 79,129, 76
	DEFB	 81, 63,138, 76,146, 76,177, 63
	DEFB	129, 76,153,127,145, 76, 81,127
	DEFB	 56, 56, 56, 56

    ._wrld_door_right
	DEFB	252,126,  6, 24,242,124,242,132
	DEFB	 50,179, 50,153,242,137, 50,161
	DEFB	252,157, 50,129, 50,145,252,137
	DEFB	 50,153,254, 65, 50,162,254,177
	DEFB	 56, 56, 56, 56

    ._dngn_tile
	DEFB	  0,  0, 96,  1, 64,  1,  0,  1
	DEFB	  0,  1,  0,  1,  0,  1,  0,  1
	DEFB	  0,  1,  0,  1,  0,  1,  0,  1
	DEFB	  0,  1,  0,  1,  0,  0,127,252
	DEFB	 56, 56, 56, 56

    ._dngn_blck
	DEFB	 85, 85,170,171, 85, 87,170,175
	DEFB	 95,255,168, 31, 88, 31,168, 31
	DEFB	 88, 31,168, 31, 88, 31,175,239
	DEFB	 95,247,191,251,127,253,255,254
	DEFB	 56, 56, 56, 56

	._dngn_wall
	DEFB	170,170,  0,  1,  0,  0,  0,  1
	DEFB	  0,  0,  0,  1,  0,  0,  0,  1
	DEFB	170,170,  1,  0,  0,  0,  1,  0
	DEFB	  0,  0,  1,  0,  0,  0,  1,  0
	DEFB	  7,  7,  7,  7


    ._plyr_upA
	DEFB	  7,224, 15,240, 47,244, 47,244
	DEFB	 63,252, 63,252, 23,232, 25,144
	DEFB	 28, 60, 55,238,127,254,119,238
	DEFB	124, 62, 63,254, 14, 96,  0,112
	DEFB	 60, 60, 60, 60

    ._plyr_upB
	DEFB	  7,224, 15,240, 47,244, 47,244
	DEFB	 63,252, 63,252, 23,232,  9,152
	DEFB	 60, 56,119,236,127,254,119,238
	DEFB	124, 62,127,252,  6,112, 14,  0
	DEFB	 60, 60, 60, 60

    ._plyr_dwnA
	DEFB	  7,224, 15,240, 40, 20, 47,244
	DEFB	 56, 28, 34, 68, 16,  8,  9,144
	DEFB	124, 56,223,244,138,106,219, 22
	DEFB	218,122,251,252,  6,112, 14,  0
	DEFB	 60, 60, 60, 60
	
	._plyr_dwnB
	DEFB	  7,224, 15,240, 40, 20, 47,244
	DEFB	 56, 28, 34, 68, 16,  8,  9,144
	DEFB	 60, 48,111,248, 68,124,109, 12
	DEFB	108,124,125,240,  0,112,  0,112
	DEFB	 60, 60, 60, 60

    ._plyr_lftA
	DEFB	  3,224, 29,248, 32,222, 31, 31
	DEFB	177, 57,197, 72,160,144,161,224
	DEFB	223,216,194, 60,190, 60,139, 60
	DEFB	136,200, 15, 60,  1,224,  3,224
	DEFB	 60, 60, 60, 60

    ._plyr_lftB
	DEFB	  0,  0,  3,224, 29,248, 32,222
	DEFB	 31, 30,177, 58,197, 72,160,144
	DEFB	161,240,246, 56,207,232,190,  4
	DEFB	150,  4,178, 14,127,242, 28, 28
	DEFB	 60, 60, 60, 60

    ._plyr_rghA
	DEFB	  7,192, 31,184,123,  4,248,248
	DEFB	156,141, 18,163,  9,  5,  7,133
	DEFB	 27,251, 60, 67, 60,125, 60,209
	DEFB	 19, 17, 60,240,  7,128,  7,192
	DEFB	 60, 60, 60, 60

    ._plyr_rghB
	DEFB	  0,  0,  7,192, 31,184,123,  4
	DEFB	120,248, 92,141, 18,163,  9,  5
	DEFB	 15,133, 28,111, 23,243, 32,125
	DEFB	 32,105,112, 77, 79,254, 56, 56
	DEFB	 60, 60, 60, 60

    ._swrd_up
	DEFB	 24, 60, 60, 60, 60, 60, 60,126
	DEFB	  0,  0,  0,  0,  0,  0,  0,  0
	DEFB	 60, 60

    ._swrd_rgh
	DEFB	  0,  0,128,  0,254,  0,255,  0
	DEFB	255,  0,254,  0,128,  0,  0,  0
	DEFB	 60, 60

    ._swrd_dwn
	DEFB	126, 60, 60, 60, 60, 60, 60, 24
	DEFB	  0,  0,  0,  0,  0,  0,  0,  0
	DEFB	 60, 60

    ._swrd_lft
	DEFB	  0,  0,  0,  1,  0,127,  0,255
	DEFB	  0,255,  0,127,  0,  1,  0,  0
	DEFB	 60, 60



    ._enmy_octoD_a
	DEFB	  6, 96,219,219,127,254, 61,188
	DEFB	255,255,115,206, 36, 36,102,102
	DEFB	246,111, 18, 72, 28, 56, 51,204
	DEFB	  7,224, 15,240,  0,  0,  0,  0
	DEFB	 58, 58, 58, 58

    ._enmy_octoD_b
	DEFB	  6, 96, 27,216,255,255,125,190
	DEFB	 63,252,243,207,100, 38, 38,100
	DEFB	118,110, 82, 74, 28, 56, 27,216
	DEFB	  3,192,  3,192,  3,192, 15,240
	DEFB	 58, 58, 58, 58


    ._item_llave
	; formato: mascara,pixel x8 filas + 1 byte attr
	; mascara = ~pixel (1=transparente, 0=opaco)
	DEFB	241, 14,236, 19,238, 17,246,  9
	DEFB	233, 22,223, 32,175, 80, 95,160
	DEFB	 52, 52, 52, 52

	._item_llave_trans
	; formato: mascara,pixel x8 filas, sin byte attr
	DEFB	241, 14,236, 19,238, 17,246,  9
	DEFB	233, 22,223, 32,175, 80, 95,160


    ; --- letras VIDA, papel amarillo (attr=48: tinta negra) ---
    ._hud_lV_ama
	DEFB 195,195,102,102, 60, 24,  0,  0
	DEFB  48
    ._hud_lI_ama
	DEFB  60, 24, 24, 24, 24, 60,  0,  0
	DEFB  48
    ._hud_lD_ama
	DEFB 240,204,198,198,204,240,  0,  0
	DEFB  48
    ._hud_lA_ama
	DEFB  56,108,198,254,198,198,  0,  0
	DEFB  48

    ; --- letras VIDA, papel negro (attr=7: tinta blanca) ---
    ._hud_lV_neg
	DEFB 195,195,102,102, 60, 24,  0,  0
	DEFB   7
    ._hud_lI_neg
	DEFB  60, 24, 24, 24, 24, 60,  0,  0
	DEFB   7
    ._hud_lD_neg
	DEFB 240,204,198,198,204,240,  0,  0
	DEFB   7
    ._hud_lA_neg
	DEFB  56,108,198,254,198,198,  0,  0
	DEFB   7

    ._hud_corazon_ama
	; corazon lleno: papel amarillo (48) + tinta roja (2) = 50
	DEFB 108,254,254,254,124, 56, 16,  0
	DEFB  50

    ._hud_corazon_neg
	; corazon lleno: papel negro (0) + tinta roja (2) = 2
	DEFB 108,254,254,254,124, 56, 16,  0
	DEFB   2

    ._hud_corazon_vacio_ama
	; corazon vacio: papel amarillo (48) + tinta negra (0) = 48
	DEFB 108,130,130, 68, 40, 16,  0,  0
	DEFB  48

    ._hud_corazon_vacio_neg
	; corazon vacio: papel negro (0) + tinta azul (1) = 1
	DEFB 108,130,130, 68, 40, 16,  0,  0
	DEFB   1

    ._sprite_negro
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 0,0,0,0
    ._sprite_azulB
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 9,9,9,9
    ._sprite_rojoB
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 80,80,80,80
    ._sprite_magB
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 88,88,88,88
    ._sprite_verB
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 96,96,96,96
    ._sprite_tealB
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 104,104,104,104
    ._sprite_amaB
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 112,112,112,112
    ._sprite_blaB
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 120,120,120,120
    ._sprite_azulD
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 8,8,8,8
    ._sprite_rojoD
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 16,16,16,16
    ._sprite_magD
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 24,24,24,24
    ._sprite_verD
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 32,32,32,32
    ._sprite_tealD
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 40,40,40,40
    ._sprite_amaD
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 48,48,48,48
    ._sprite_blaD
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 56,56,56,56
#endasm
