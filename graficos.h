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
extern unsigned char dngn_fire [];

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

extern unsigned char npc_shopper [];

extern unsigned char enmy_octoUp [];
extern unsigned char enmy_octoRight [];
extern unsigned char enmy_octoDown [];
extern unsigned char enmy_octoLeft [];
extern unsigned char enmy_octoShot [];

extern unsigned char enmy_hvy [];

extern unsigned char enmy_boss [];
extern unsigned char enmy_bossFire [];

extern unsigned char item_llave [];
extern unsigned char item_llave_trans [];
extern unsigned char item_corazon [];
extern unsigned char item_power [];
extern unsigned char item_points [];

extern unsigned char itm_bigHrth [];
extern unsigned char itm_bigSwrd [];

extern unsigned char hud_corazon [];
extern unsigned char hud_corazon_vacio [];

extern unsigned char fuente [];
#define F_DIG(n) (&fuente[(n) * 8])
#define F_LET(c) (&fuente[(10 + (c) - 'a') * 8])

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
	DEFB	 60, 63, 66, 96,129, 79,133, 79
	DEFB	141, 76,153, 76, 66, 79, 60,204
	DEFB	126,255, 24,204,126, 76,133,127
	DEFB	131, 76,129,127,129, 76,129,127
	DEFB	 56, 56, 56, 56

    ._wrld_door_right
	DEFB	252, 60,  6, 66,242,129,242,161
	DEFB	 50,177, 50,153,242, 66, 51, 60
	DEFB	255,126, 51, 24, 50,126,254,161
	DEFB	 50,193,254,129, 50,129,254,129
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

	._dngn_fire
	DEFB	  0, 64,  4,132, 16,164, 36,194
	DEFB	 15,104, 45,218, 91, 86,122,189
	DEFB	114,173,160, 87,233,  9,229, 70
	DEFB	115,230,115,204, 60, 28,  7,240
	DEFB	 2, 2, 2, 2

	._dngn_wall
	DEFB	170,170,  0,  1,  0,  0,  0,  1
	DEFB	  0,  0,  0,  1,  0,  0,  0,  1
	DEFB	170,170,  1,  0,  0,  0,  1,  0
	DEFB	  0,  0,  1,  0,  0,  0,  1,  0
	DEFB	  7,  7,  7,  7

	._dngn_tomb
	DEFB	  3,192,  7,224, 14,112, 30,120
	DEFB	 24, 24, 24, 24, 30,120, 30,120
	DEFB	 30,120, 30,120, 31,248, 31,248
	DEFB	124,174, 98,106, 75,166,127,254
	DEFB	 57, 57, 57, 57

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

	._enmy_octoUp
	DEFB	  0,  0, 15,240,  7,224, 51,204
	DEFB	 28, 56, 18, 72,246,111,102,102
	DEFB	 36, 36,115,206,255,255, 61,188
	DEFB	127,254,219,219,  6, 96,  0,  0
	DEFB	 58, 58, 58, 58

	._enmy_octoRight
	DEFB	 36, 64, 54,192, 31,200, 62,120
	DEFB	 60, 18, 93,214,118,238, 62, 14
	DEFB	 62, 14,118,238, 93,214, 60, 18
	DEFB	 62,120, 31,200, 54,192, 36, 64
	DEFB	 58, 58, 58, 58

    ._enmy_octoDown
	DEFB	  6, 96,219,219,127,254, 61,188
	DEFB	255,255,115,206, 36, 36,102,102
	DEFB	246,111, 18, 72, 28, 56, 51,204
	DEFB	  7,224, 15,240,  0,  0,  0,  0
	DEFB	 58, 58, 58, 58

	._enmy_octoLeft
	DEFB	  2, 36,  3,108, 19,248, 30,124
	DEFB	 72, 60,107,186,119,110,112,124
	DEFB	112,124,119,110,107,186, 72, 60
	DEFB	 30,124, 19,248,  3,108,  2, 36
	DEFB	 58, 58, 58, 58

	._enmy_octoShot
	DEFB	 94,178,127,223,219,227,126,116
	DEFB	 58

	._enmy_hvy
	DEFB	 27,218, 23,235, 12, 51, 13,179
	DEFB	 13,179, 12, 50,255,250,129,110
	DEFB	165,246,129,246,129, 62,165,130
	DEFB	129, 62,255,242, 28, 56, 60, 60
	DEFB	 58, 58, 58, 58

	._enmy_boss
	DEFB	  7,224, 30,120, 38,100, 47,244
	DEFB	 63,252, 62,124, 78,114, 95,250
	DEFB	127,254,126,126,158,121,191,253
	DEFB	252, 63,251,223,118,110, 44, 52
	DEFB	 57, 57, 57, 57

	._enmy_bossFire
	DEFB	  3,192,  7,224, 15,240, 24, 24
	DEFB	 51,204, 54,108,116, 46,117,174
	DEFB	117,174,116, 46, 54,108, 51,204
	DEFB	 24, 24, 15,240,  7,224,  3,192
	DEFB	 61, 61, 61, 61

	._npc_shopper
	DEFB	 15,240, 31,248, 24, 24, 10, 80
	DEFB	  4, 32,  4, 32, 63,252,102,102
	DEFB	119,238,118,110, 75,210, 81,138
	DEFB	 47,244, 12, 48, 60, 60, 24, 24
	DEFB	 53, 53, 53, 53

	._itm_bigHrth
	DEFB	  0,  0, 24, 24, 60, 60,126,126
	DEFB	255,255,255,255,255,255,255,255
	DEFB	127,254, 63,252, 31,248, 15,240
	DEFB	  7,224,  3,192,  1,128,  0,  0
	DEFB	 51, 51, 51, 51

	._itm_bigSwrd
	DEFB	  0,128,  0,128,  1,128,  1,128
	DEFB	  1,128,  1,128,  1,128,  1,128
	DEFB	  1,128,  1,128,  1,128, 15,240
	DEFB	  9,144,  3,192,  1,128,  3,192
	DEFB	 51, 51, 51, 51

	;fuente[0..9]=dig, [10..35]=a-z, [36]=coma [37]=punto [38]=comill [39]=excla [40]=interr
    ._fuente
    DEFB	 56,108,198,198,198,108, 56,  0 //0
    DEFB	 56,112,240, 48, 48, 48,252,  0 //1
    DEFB	124,198,230, 12, 56, 98,252,  0 //2
    DEFB	254,140, 24, 60,  6,134,124,  0 //3
    DEFB	 12, 28, 60,108,254, 12, 30,  0 //4
    DEFB	252,192,252,198,  6,198,124,  0 //5
    DEFB	 28, 48, 96,252,198,198,124,  0 //6
    DEFB	254,134, 12, 24, 24, 24, 24,  0 //7
    DEFB	124,198,198,124,198,198,124,  0 //8
    DEFB	124,198,198,126,  6, 12,120,  0 //9
    DEFB	 56,110,198,198,254,198,198,  0 //A
    DEFB	220,230,198,252,198,198,252,  0
	DEFB	 60,102,192,192,192,102, 60,  0
    DEFB	248,204,198,198,198,204,248,  0
    DEFB	126,230,192,252,192,230,126,  0 //E
    DEFB	254,102, 96,120, 96, 96,240,  0
    DEFB	124,198,192,222,198,206,122,  0
    DEFB	198,198,198,254,230,198,198,  0
    DEFB	252, 48, 48, 48, 48, 48,252,  0 //I
    DEFB	254, 12,  6,  6,198,108, 56,  0
    DEFB	198,204,216,248,220,206,198,  0
    DEFB	224,192,192,192,192,194,254,  0
    DEFB	236,254,214,214,214,198,204,  0
    DEFB	236,126,102,102,102,100,228,  0
    DEFB	124,198,198,198,198,198,124,  0 //O
    DEFB	220,246,198,198,252,192,192,  0
    DEFB	124,198,198,198,214,222,124,  0
    DEFB	220,230,198,198,252,204,198,  0
    DEFB	124,198,192,124,  6,198,124,  0
    DEFB	254,178, 48, 48, 48, 48, 48,  0
    DEFB	230,102,102,198,198,198,124,  0 //U
    DEFB	230,102,198,198,198,108, 56,  0
    DEFB	236,102,198,214,214,254,108,  0
    DEFB	238,198,108, 56,108,198,238,  0
    DEFB	230,102, 54, 30, 14,198,124,  0
    DEFB	254,134, 12, 56, 96,194,254,  0 //Z
    DEFB	  0,  0,  0,  0, 48, 48, 96,  0 //coma
    DEFB	  0,  0,  0,  0,  0, 96, 96,  0 //punto
    DEFB	108,108, 36, 72,  0,  0,  0,  0 //comill
    DEFB	 48,120,120,120, 48,  0, 48,  0 //excla
    DEFB	124,198,230, 12, 24,  0, 24,  0 //interr

    ._item_power
	DEFB	 24, 36,126,165,165,126, 36, 24
	DEFB	 4

	._item_points
	DEFB	 60,126,231,219,219,231,126, 60
	DEFB	  3

    ._item_llave
	; formato: mascara,pixel x8 filas + 1 byte attr
	; mascara = ~pixel (1=transparente, 0=opaco)
	DEFB	241, 14,236, 19,238, 17,246,  9
	DEFB	233, 22,223, 32,175, 80, 95,160
	DEFB	  6, 6, 6, 6

	._item_llave_trans
	; formato: mascara,pixel x8 filas, sin byte attr
	DEFB	241, 14,236, 19,238, 17,246,  9
	DEFB	233, 22,223, 32,175, 80, 95,160

	._item_corazon
	; formato: mascara,pixel x8 filas + 1 byte attr
	DEFB	147,108,  1,254,  1,254,  1,254
	DEFB	131,124,199, 56,239, 16,255,  0
	DEFB	 50, 50, 50, 50

    ._hud_corazon
	DEFB 108,254,254,254,124, 56, 16,  0

    ._hud_corazon_vacio
	DEFB 108,130,130, 68, 40, 16,  0,  0

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
