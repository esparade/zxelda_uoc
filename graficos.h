//zxelda v0.1a
//16mar'26

extern unsigned char test8x8 [];
extern unsigned char menu8x8 [];
extern unsigned char sprite_negro [];
extern unsigned char sprite_esfera [];
extern unsigned char anim1 [];
extern unsigned char anim2 [];
extern unsigned char anim1b [];
extern unsigned char anim2b [];

#asm
    ._test8x8
    defb 55,129,153,165,165,153,129,255
    defb 2

    ._menu8x8
    defb 0,0,38,69,101,69,37,69
    defb 38,66,36,66,116,114,0,0
    defb 0,0,117,101,87,85,85,85,85
    defb 85,85,85,85,117,87,0,0
    defb 7,7,7,7

    ._sprite_negro
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 0,0,0,0

    ._sprite_esfera //muros
    defb 224,192,241,240,241,242,113,250
    defb 115,250,243,254,243,224,243,220
    defb 227,222,227,222, 65,220, 64,156
    defb 159, 28,158, 28,191, 24, 44,  0
    defb 4,4,4,4


    ._anim1
    defb 7,224, 15,240, 40, 20, 47,244
    defb 56, 28, 34, 68, 16,  8,  9,152
    defb 60, 56,111,236, 68,214,110, 42
    defb 108,246,127,252,  6,112, 14,  0
    defb 60, 60, 60, 60

    ._anim2
    defb 7,224, 15,240, 40, 20, 47,244
    defb 56, 28, 34, 68, 16,  8,  9,144
    defb 60, 32,119,248, 98,120,119, 28
    defb 118,116,127,236, 14, 96,  0,112
    defb 60, 60, 60, 60

    ._anim1b
    defb 7,224, 15,240, 47,244, 47,244
    defb 63,252, 63,252, 23,232, 25,144
    defb 28, 60, 55,238,127,254,119,238
    defb 124, 62, 63,254, 14, 96,  0,112
    defb 60, 60, 60, 60

    ._anim2b
    defb 7,224, 15,240, 47,244, 47,244
    defb 63,252, 63,252, 23,232,  9,152
    defb 60, 56,119,236,127,254,119,238
    defb 124, 62,127,252,  6,112, 14,  0
    defb 60, 60, 60, 60
#endasm
