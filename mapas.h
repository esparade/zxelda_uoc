//zxelda v0.1b
//07abr'26

extern unsigned char mapa1[];
extern unsigned char mapa2[];
extern unsigned char mapa3[];
extern unsigned char mapa4[];
extern unsigned char mapa5[];

#asm
    ; tiles overworld
    defc SL =  0   ; suelo
    defc AR =  1   ; arbol
    defc MA =  2   ; matorral
    ; tiles dungeon
    defc RK =  3   ; roca (solido)
    defc PS =  4   ; piso
    defc MU =  5   ; muro
    ; puertas
    defc PL =  6   ; puerta izquierda
    defc PR =  7   ; puerta derecha
    defc PA =  8   ; puerta arriba
    ; especiales
    defc VO =  9   ; void / entrada cueva
    defc O1 = 10   ; objeto mapa5
    defc O2 = 11   ; objeto mapa5
    defc O3 = 12   ; objeto mapa5

    ._mapa1 //start 000
    defb SL,AR,AR,AR,AR,AR,AR,SL,SL,AR,AR,AR,AR,AR,AR,SL
    defb SL,AR,AR,SL,AR,AR,SL,SL,SL,AR,AR,AR,AR,AR,AR,SL
    defb SL,AR,AR,SL,SL,SL,SL,SL,SL,AR,AR,AR,AR,AR,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,AR,AR,AR,AR,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL
    defb SL,AR,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,AR,AR,SL
    defb SL,AR,AR,SL,SL,SL,SL,SL,SL,SL,SL,AR,AR,AR,AR,SL
    defb SL,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,SL

    ._mapa2 //start_rgh 001
    defb SL,AR,AR,SL,SL,MA,SL,SL,SL,SL,MA,SL,MA,SL,MA,SL
    defb SL,AR,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL
    defb SL,AR,AR,SL,SL,MA,SL,SL,SL,SL,MA,SL,MA,SL,MA,SL
    defb SL,AR,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL
    defb SL,AR,AR,SL,SL,SL,SL,SL,SL,SL,MA,SL,MA,SL,MA,SL
    defb SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL
    defb SL,AR,AR,SL,SL,MA,SL,SL,SL,SL,MA,SL,MA,SL,MA,SL
    defb SL,AR,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL
    defb SL,AR,AR,MA,MA,MA,MA,MA,MA,MA,MA,MA,MA,MA,MA,SL

    ._mapa3 //dngn_001
    defb VO,MU,MU,MU,MU,MU,MU,RK,RK,MU,MU,MU,MU,MU,MU,VO
    defb VO,MU,VO,VO,VO,VO,VO,PS,PS,VO,VO,VO,VO,VO,MU,VO
    defb VO,MU,VO,PS,PS,PS,VO,RK,PS,PS,PS,VO,PS,VO,MU,VO
    defb VO,MU,VO,PS,VO,PS,VO,PS,VO,VO,PS,VO,PS,VO,MU,VO
    defb VO,MU,PS,PS,VO,PS,VO,PS,PS,VO,PS,VO,PS,PS,MU,VO
    defb VO,MU,VO,PS,VO,PS,VO,VO,PS,VO,PS,VO,PS,VO,MU,VO
    defb VO,MU,VO,PS,VO,PS,PS,PS,RK,VO,PS,VO,PS,VO,MU,VO
    defb VO,MU,VO,VO,VO,VO,VO,PS,PS,VO,PS,PS,PS,VO,MU,VO
    defb VO,MU,MU,MU,MU,MU,MU,VO,VO,MU,MU,MU,MU,MU,MU,VO

    ._mapa4 //start -1 dungeon enter
    defb SL,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,SL
    defb SL,AR,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,AR,SL
    defb SL,AR,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL
    defb SL,AR,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,AR,SL
    defb SL,AR,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,AR,SL
    defb SL,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,SL

    ._mapa5 //from_start_room_door
    defb SL,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,O2,SL,SL,SL,O1,SL,SL,SL,SL,O2,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,O3,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,AR,AR,AR,AR,AR,SL,SL,AR,AR,AR,AR,AR,AR,SL
#endasm
