extern unsigned char wrld_a1[];
extern unsigned char wrld_a2[];
extern unsigned char wrld_a3[];
extern unsigned char wrld_b2[];
extern unsigned char wrld_b3[];
extern unsigned char wrld_b4[];
extern unsigned char wrld_b5[];
extern unsigned char wrld_b6[];
extern unsigned char wrld_c2[];
extern unsigned char wrld_c4[];
extern unsigned char wrld_d1[];
extern unsigned char wrld_d2[];
extern unsigned char wrld_d3[];
extern unsigned char wrld_d4[];
extern unsigned char wrld_d6[];

extern unsigned char dngn_a1[];
extern unsigned char dngn_a2[];
extern unsigned char dngn_b1[];
extern unsigned char dngn_b2[];
extern unsigned char dngn_b3[];
extern unsigned char dngn_c3[];
extern unsigned char dngn_d2[];
extern unsigned char dngn_d3[];
extern unsigned char dngn_e1[];
extern unsigned char dngn_e2[];
extern unsigned char dngn_e3[];
extern unsigned char dngn_f2[];
extern unsigned char dngn_g2[];

#asm
    ; definiciones de tiles. mismos que los cases de render_tile() y es_solido().
    ; overworld
    defc SL =  0   ; suelo world
    defc AR =  1   ; arbol (solida)
    defc MA =  2   ; matorral (solida)
    ; dungeon
    defc RK =  3   ; bloque dungeon (solida)
    defc PS =  4   ; baldosa dungeon
    defc MU =  5   ; pared dungeon (solida)
    ; puertas
    defc PL =  6   ; puerta izquierda (solida hasta que se abre)
    defc PR =  7   ; puerta derecha (solida hasta que se abre)
    defc PA =  8   ; puerta arriba (solida hasta que se abre)
    ; especiales
    defc VO =  9   ; void/negro; en pos de tienda/mazmorra actua como warp
    defc O1 = 10   ; espada tienda (wrld_d6)
    defc O2 = 11   ; corazon tienda (wrld_d6)
    defc PC = 12   ; puerta cerrada (necesita llave, solida)
    defc FG = 13   ; fuego (transparente)
    defc TB = 17   ; tumba (solida)
    defc WT = 18   ; agua (solida)
    defc PB = 19   ; bloque empujable (solido, se desplaza una casilla al empujarlo)

; world
;   1 2 3 4 5 6
; d - \ - \   t
; c   |   |
; b   + s + - -
; a - + -
    ._wrld_d1 // ID19
    defb SL,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,SL
    defb SL,AR,AR,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,AR,SL
    defb SL,AR,AR,SL,MA,SL,MA,SL,MA,SL,MA,SL,SL,AR,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,MA,SL
    defb SL,AR,SL,SL,MA,SL,SL,SL,SL,SL,MA,SL,SL,SL,SL,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,MA,SL
    defb SL,AR,AR,SL,MA,SL,MA,SL,MA,SL,MA,SL,SL,AR,AR,SL
    defb SL,AR,AR,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,AR,SL
    defb SL,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,SL

    ._wrld_d2 // ID20
    defb SL,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,MA,SL,SL,SL,SL,SL,AR,SL
    defb SL,MA,SL,SL,SL,SL,SL,MA,SL,MA,SL,SL,SL,SL,AR,SL
    defb SL,SL,SL,SL,SL,SL,MA,SL,TB,SL,MA,SL,SL,SL,AR,SL
    defb SL,MA,SL,SL,SL,SL,SL,MA,SL,MA,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,MA,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,AR,AR,AR,AR,MA,SL,SL,MA,AR,AR,AR,AR,AR,SL

    ._wrld_d3 // ID21
    defb SL,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,SL
    defb SL,AR,AR,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,AR,SL
    defb SL,AR,AR,SL,MA,SL,MA,SL,MA,SL,MA,SL,SL,AR,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,MA,SL
    defb SL,AR,SL,SL,MA,SL,SL,SL,SL,SL,MA,SL,SL,SL,SL,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,MA,SL
    defb SL,AR,AR,SL,MA,SL,MA,SL,MA,SL,MA,SL,SL,AR,AR,SL
    defb SL,AR,AR,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,AR,SL
    defb SL,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,SL

    ._wrld_d4 // ID22
    defb SL,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,WT,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,MA,SL,SL,SL,SL,SL,WT,SL,TB,SL,AR,SL
    defb SL,MA,SL,SL,SL,SL,MA,SL,SL,SL,WT,SL,SL,SL,AR,SL
    defb SL,SL,SL,SL,MA,SL,SL,SL,SL,SL,WT,WT,WT,WT,AR,SL
    defb SL,MA,SL,SL,SL,SL,MA,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,MA,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,AR,AR,AR,AR,MA,SL,SL,MA,AR,AR,AR,AR,AR,SL

    ._wrld_d6 //tienda ID24
    defb SL,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,O1,SL,SL,SL,O2,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,AR,AR,AR,AR,AR,SL,SL,AR,AR,AR,AR,AR,AR,SL

    ._wrld_c2 // ID14
    defb SL,AR,AR,AR,AR,AR,MA,SL,SL,MA,AR,AR,AR,AR,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,MA,MA,MA,MA,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,MA,MA,MA,MA,MA,SL,AR,SL
    defb SL,AR,SL,MA,MA,MA,MA,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,MA,MA,MA,MA,MA,SL,AR,SL
    defb SL,AR,SL,MA,MA,MA,MA,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,AR,AR,AR,AR,MA,SL,SL,MA,AR,AR,AR,AR,AR,SL

    ._wrld_c4 // ID16
    defb SL,AR,AR,AR,AR,AR,MA,SL,SL,MA,AR,AR,AR,AR,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,MA,MA,SL,SL,MA,SL,SL,MA,SL,SL,MA,MA,AR,SL
    defb SL,AR,MA,MA,SL,SL,MA,SL,SL,MA,SL,SL,MA,MA,AR,SL
    defb SL,AR,MA,MA,SL,SL,MA,SL,SL,MA,SL,SL,MA,MA,AR,SL
    defb SL,AR,MA,MA,SL,SL,MA,SL,SL,MA,SL,SL,MA,MA,AR,SL
    defb SL,AR,MA,MA,SL,SL,MA,SL,SL,MA,SL,SL,MA,MA,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,AR,AR,AR,AR,MA,SL,SL,MA,AR,AR,AR,AR,AR,SL

    ._wrld_b2 // ID8
    defb SL,AR,AR,AR,AR,AR,MA,SL,SL,MA,AR,AR,AR,AR,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,MA,SL,MA,SL,MA,MA,SL,MA,SL,MA,SL,MA,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL
    defb SL,AR,SL,MA,SL,MA,SL,MA,MA,SL,MA,SL,MA,SL,MA,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,AR,AR,AR,AR,MA,SL,SL,MA,AR,AR,AR,AR,AR,SL

    ._wrld_b3 //world start - entrada tienda ID9
    defb SL,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,SL
    defb SL,AR,AR,VO,AR,AR,SL,SL,SL,AR,AR,AR,AR,AR,AR,SL
    defb SL,AR,AR,SL,SL,SL,SL,SL,SL,AR,AR,AR,AR,AR,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,AR,AR,AR,AR,AR,SL
    defb SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,AR,AR,SL
    defb SL,AR,AR,SL,SL,SL,SL,SL,SL,SL,SL,AR,AR,AR,AR,SL
    defb SL,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,SL

    ._wrld_b4 // ID10
    defb SL,AR,AR,AR,AR,AR,MA,SL,SL,MA,AR,AR,AR,AR,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,MA,MA,MA,MA,SL,SL,SL,SL,AR,SL
    defb SL,MA,SL,SL,SL,SL,MA,MA,MA,MA,SL,SL,SL,SL,MA,SL
    defb SL,SL,SL,SL,SL,SL,MA,MA,MA,MA,SL,SL,SL,SL,SL,SL
    defb SL,MA,SL,SL,SL,SL,MA,MA,MA,MA,SL,SL,SL,SL,MA,SL
    defb SL,AR,SL,SL,SL,SL,MA,MA,MA,MA,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,SL

    ._wrld_b5 // ID11
    defb SL,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,MA,SL,MA,MA,MA,MA,SL,MA,MA,MA,MA,SL,AR,SL
    defb SL,MA,SL,SL,MA,MA,MA,SL,SL,SL,MA,MA,MA,SL,MA,SL
    defb SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL
    defb SL,MA,SL,SL,MA,MA,MA,SL,SL,SL,MA,MA,MA,SL,MA,SL
    defb SL,AR,MA,SL,MA,MA,MA,MA,SL,MA,MA,MA,MA,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,SL

    ._wrld_b6 // ID12
    defb SL,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,SL
    defb SL,AR,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,AR,SL
    defb SL,AR,SL,SL,SL,TB,SL,TB,SL,TB,SL,TB,SL,SL,AR,SL
    defb SL,MA,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,SL,SL,SL,SL,TB,SL,SL,SL,SL,SL,TB,SL,SL,AR,SL
    defb SL,MA,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,TB,SL,TB,SL,TB,SL,TB,SL,SL,AR,SL
    defb SL,AR,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,AR,SL
    defb SL,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,SL

    ._wrld_a1 // ID1
    defb SL,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,SL
    defb SL,AR,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,AR,SL
    defb SL,AR,SL,SL,SL,TB,SL,TB,SL,TB,SL,TB,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,MA,SL
    defb SL,AR,SL,SL,SL,TB,SL,SL,SL,SL,SL,TB,SL,SL,SL,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,MA,SL
    defb SL,AR,SL,SL,SL,TB,SL,TB,SL,TB,SL,TB,SL,SL,AR,SL
    defb SL,AR,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,AR,SL
    defb SL,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,SL

    ._wrld_a2 // ID2
    defb SL,AR,AR,AR,AR,AR,MA,SL,SL,MA,AR,AR,AR,AR,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,MA,MA,SL,MA,SL,MA,MA,SL,SL,SL,AR,SL
    defb SL,MA,SL,SL,SL,SL,SL,MA,SL,SL,SL,SL,SL,SL,MA,SL
    defb SL,SL,SL,SL,MA,MA,MA,MA,MA,MA,MA,SL,SL,SL,SL,SL
    defb SL,MA,SL,SL,SL,SL,SL,MA,SL,SL,SL,SL,SL,SL,MA,SL
    defb SL,AR,SL,SL,MA,MA,SL,MA,SL,MA,MA,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,SL

    ._wrld_a3 // ID3
    defb SL,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,SL
    defb SL,AR,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,AR,SL
    defb SL,AR,SL,SL,SL,TB,SL,TB,SL,TB,SL,TB,SL,SL,AR,SL
    defb SL,MA,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,SL,SL,SL,SL,TB,SL,SL,SL,SL,SL,TB,SL,SL,AR,SL
    defb SL,MA,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,TB,SL,TB,SL,TB,SL,TB,SL,SL,AR,SL
    defb SL,AR,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,AR,SL
    defb SL,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,SL

; dungeon
;   1 2 3
; g   b
; f   |
; e +-+
; d | +
; c   |
; b +-+
; a +-s
    ._dngn_g2 //boss ID70
    defb VO,FG,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,FG,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,MU,PS,RK,PS,PS,PS,PS,PS,PS,PS,PS,RK,PS,MU,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,MU,PS,RK,PS,PS,PS,PS,PS,PS,PS,PS,RK,PS,MU,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,FG,MU,MU,MU,MU,RK,VO,VO,RK,MU,MU,MU,MU,FG,VO

    ._dngn_f2 // ID67
    defb VO,FG,MU,MU,MU,MU,RK,VO,VO,RK,MU,MU,MU,MU,FG,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,MU,PS,RK,PS,RK,PS,PS,PS,PS,PS,RK,PS,PS,MU,VO
    defb VO,MU,PS,PS,RK,PS,PS,RK,RK,PS,RK,RK,RK,PS,MU,VO
    defb VO,MU,PS,RK,PS,RK,PS,PS,PS,PS,PS,RK,PS,PS,MU,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,FG,MU,MU,MU,MU,RK,VO,VO,RK,MU,MU,MU,MU,FG,VO

    ._dngn_e1 // ID63
    defb VO,FG,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,FG,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,MU,PS,PS,PS,PS,RK,PS,PS,RK,PS,PS,PS,PS,RK,VO
    defb VO,MU,PS,PS,PS,PS,RK,PS,PS,RK,PS,PS,PS,PS,VO,VO
    defb VO,MU,PS,PS,PS,PS,RK,PS,PS,RK,PS,PS,PS,PS,RK,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,FG,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,FG,VO

    ._dngn_e2 // ID64
    defb VO,FG,MU,MU,MU,MU,RK,VO,VO,RK,MU,MU,MU,MU,FG,VO
    defb VO,MU,RK,RK,RK,RK,RK,PS,PS,RK,RK,RK,RK,RK,MU,VO
    defb VO,MU,RK,RK,RK,RK,RK,RK,PS,RK,RK,RK,RK,RK,MU,VO
    defb VO,RK,RK,RK,RK,RK,RK,RK,PS,RK,RK,RK,RK,RK,RK,VO
    defb VO,VO,PS,PS,PS,PS,PS,PS,PB,PS,PS,PS,PS,PS,VO,VO
    defb VO,RK,RK,RK,RK,RK,RK,RK,PS,RK,RK,RK,RK,RK,RK,VO
    defb VO,MU,RK,RK,RK,RK,RK,RK,PS,RK,RK,RK,RK,RK,MU,VO
    defb VO,MU,RK,RK,RK,RK,RK,PS,PS,RK,RK,RK,RK,RK,MU,VO
    defb VO,FG,MU,MU,MU,MU,RK,VO,VO,RK,MU,MU,MU,MU,FG,VO

    ._dngn_e3 // ID65
    defb VO,FG,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,FG,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,RK,PS,PS,RK,PS,PS,RK,RK,PS,PS,RK,PS,PS,MU,VO
    defb VO,VO,PS,RK,PS,PS,RK,RK,RK,RK,PS,PS,RK,PS,MU,VO
    defb VO,RK,PS,PS,RK,PS,PS,RK,RK,PS,PS,RK,PS,PS,MU,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,FG,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,FG,VO

    ._dngn_d2 // ID61
    defb VO,FG,MU,MU,MU,MU,RK,VO,VO,RK,MU,MU,MU,MU,FG,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,MU,PS,RK,RK,PS,PS,PS,PS,PS,PS,RK,RK,PS,MU,VO
    defb VO,MU,PS,RK,PS,PS,PS,PS,PS,PS,PS,PS,RK,PS,RK,VO
    defb VO,MU,PS,RK,PS,RK,RK,RK,RK,RK,RK,PS,RK,PS,VO,VO
    defb VO,MU,PS,RK,PS,PS,PS,PS,PS,PS,PS,PS,RK,PS,RK,VO
    defb VO,MU,PS,RK,RK,PS,PS,PS,PS,PS,PS,RK,RK,PS,MU,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,FG,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,FG,VO

    ._dngn_d3 // ID62
    defb VO,FG,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,FG,VO
    defb VO,MU,PS,PS,RK,PS,PS,PS,PS,PS,PS,PS,PS,RK,MU,VO
    defb VO,MU,PS,RK,PS,PS,PS,RK,PS,PS,PS,PS,RK,PS,MU,VO
    defb VO,RK,PS,PS,PS,PS,RK,PS,PS,PS,PS,RK,PS,PS,MU,VO
    defb VO,VO,PS,PS,PS,RK,PS,PS,PS,PS,RK,PS,PS,PS,MU,VO
    defb VO,RK,PS,PS,RK,PS,PS,PS,PS,RK,PS,PS,PS,PS,MU,VO
    defb VO,MU,PS,RK,PS,PS,PS,PS,RK,PS,PS,PS,RK,PS,MU,VO
    defb VO,MU,RK,PS,PS,PS,PS,PS,PS,PS,PS,RK,PS,PS,MU,VO
    defb VO,FG,MU,MU,MU,MU,RK,VO,VO,RK,MU,MU,MU,MU,FG,VO

    ._dngn_c3 //nsu ID59
    defb VO,FG,MU,MU,MU,MU,MU,VO,VO,MU,MU,MU,MU,MU,FG,VO
    defb VO,MU,RK,RK,RK,RK,RK,PS,PS,RK,RK,RK,RK,RK,MU,VO
    defb VO,MU,RK,PS,PS,PS,RK,PS,PS,PS,PS,RK,PS,PS,MU,VO
    defb VO,MU,RK,PS,RK,PS,RK,PS,RK,RK,PS,RK,PS,RK,MU,VO
    defb VO,MU,RK,PS,RK,PS,RK,PS,PS,RK,PS,RK,PS,RK,MU,VO
    defb VO,MU,RK,PS,RK,PS,RK,RK,PS,RK,PS,RK,PS,RK,MU,VO
    defb VO,MU,PS,PS,RK,PS,PS,PS,PS,RK,PS,RK,PS,RK,MU,VO
    defb VO,MU,RK,RK,RK,RK,RK,PS,PS,RK,PS,PS,PS,RK,MU,VO
    defb VO,FG,MU,MU,MU,MU,MU,VO,VO,MU,MU,MU,MU,MU,FG,VO

    ._dngn_b1 // ID53
    defb VO,FG,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,FG,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,MU,PS,RK,RK,PS,PS,PS,PS,PS,PS,RK,RK,PS,MU,VO
    defb VO,MU,PS,RK,RK,PS,PS,RK,PS,PS,PS,RK,RK,PS,RK,VO
    defb VO,MU,PS,PS,PS,PS,PS,RK,RK,PS,PS,PS,PS,PS,VO,VO
    defb VO,MU,PS,RK,RK,PS,PS,PS,RK,PS,PS,RK,RK,PS,RK,VO
    defb VO,MU,PS,RK,RK,PS,PS,PS,PS,PS,PS,RK,RK,PS,MU,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,FG,MU,MU,MU,MU,RK,VO,VO,RK,MU,MU,MU,MU,FG,VO

    ._dngn_b2 // ID54
    defb VO,FG,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,FG,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,MU,PS,RK,PS,RK,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,RK,PS,RK,PS,RK,PS,RK,RK,PS,PS,PS,PS,PS,RK,VO
    defb VO,VO,PS,RK,RK,RK,PS,RK,RK,PS,RK,RK,RK,PS,VO,VO
    defb VO,RK,PS,PS,PS,PS,PS,RK,RK,PS,RK,PS,PS,PS,RK,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,RK,RK,RK,PS,MU,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,FG,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,FG,VO

    ._dngn_b3 // ID55
    defb VO,FG,MU,MU,MU,MU,RK,VO,VO,RK,MU,MU,MU,MU,FG,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,MU,PS,PS,PS,RK,PS,RK,RK,PS,RK,PS,PS,PS,MU,VO
    defb VO,RK,PS,PS,RK,PS,PS,RK,RK,PS,PS,RK,PS,PS,MU,VO
    defb VO,VO,PS,RK,PS,PS,PS,RK,RK,PS,PS,PS,RK,PS,MU,VO
    defb VO,RK,PS,PS,RK,PS,PS,RK,RK,PS,PS,RK,PS,PS,MU,VO
    defb VO,MU,PS,PS,PS,RK,PS,RK,RK,PS,RK,PS,PS,PS,MU,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,FG,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,FG,VO

    ._dngn_a1 //ID50
    defb VO,FG,MU,MU,MU,MU,RK,VO,VO,RK,MU,MU,MU,MU,FG,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,RK,RK,RK,RK,RK,MU,VO
    defb VO,MU,PS,RK,RK,RK,RK,RK,RK,RK,RK,RK,RK,RK,MU,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,RK,RK,RK,VO
    defb VO,MU,RK,RK,RK,RK,RK,RK,RK,RK,RK,PS,RK,PS,VO,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,RK,PS,RK,VO
    defb VO,MU,PS,RK,RK,RK,RK,RK,RK,RK,RK,RK,RK,PS,MU,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,FG,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,FG,VO

    ._dngn_a2 //entrada - ID51
    defb VO,FG,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,FG,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,MU,PS,TB,PS,PS,TB,PS,PS,TB,PS,PS,TB,PS,MU,VO
    defb VO,RK,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,VO,PS,TB,PS,PS,TB,PS,PS,TB,PS,PS,TB,PS,MU,VO
    defb VO,RK,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,MU,PS,TB,PS,PS,TB,PS,PS,TB,PS,PS,TB,PS,MU,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,FG,MU,MU,MU,MU,RK,VO,VO,RK,MU,MU,MU,MU,FG,VO
#endasm
