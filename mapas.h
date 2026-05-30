extern unsigned char mapa1[];
extern unsigned char mapa2[];
extern unsigned char mapa3[];
extern unsigned char mapa4[];
extern unsigned char mapa5[];
extern unsigned char mapa6[];

#asm
    ; tiles overworld
    defc SL =  0   ; suelo
    defc AR =  1   ; arbol
    defc MA =  2   ; matorral
    ; tiles dungeon
    defc RK =  3   ; block (infranqueable)
    defc PS =  4   ; baldosa
    defc MU =  5   ; wall
    ; puertas
    defc PL =  6   ; puerta izquierda
    defc PR =  7   ; puerta derecha
    defc PA =  8   ; puerta arriba
    ; especiales
    defc VO =  9   ; void / entrada cueva
    defc O1 = 10   ; objeto mapa5
    defc O2 = 11   ; objeto mapa5
    defc PC = 12   ; puerta cerrada (bloqueada con llave)
    defc FG = 13   ; fuego (decorativo)

    ._mapa1 //start point
    defb SL,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,SL
    defb SL,AR,AR,SL,AR,AR,SL,SL,SL,AR,AR,AR,AR,AR,AR,SL
    defb SL,AR,AR,SL,SL,SL,SL,SL,SL,AR,AR,AR,AR,AR,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,AR,AR,AR,AR,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL
    defb SL,AR,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,AR,AR,SL
    defb SL,AR,AR,SL,SL,SL,SL,SL,SL,SL,SL,AR,AR,AR,AR,SL
    defb SL,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,SL

    ._mapa2 //arboleda
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
    defb VO,FG,MU,MU,MU,MU,MU,VO,VO,MU,MU,MU,MU,MU,FG,VO
    defb VO,MU,RK,RK,RK,RK,RK,PS,PS,RK,RK,RK,RK,RK,MU,VO
    defb VO,MU,RK,PS,PS,PS,RK,PS,PS,PS,PS,RK,PS,RK,MU,VO
    defb VO,MU,RK,PS,RK,PS,RK,PS,RK,RK,PS,RK,PS,RK,MU,VO
    defb VO,MU,PS,PS,RK,PS,RK,PS,PS,RK,PS,RK,PS,PS,MU,VO
    defb VO,MU,RK,PS,RK,PS,RK,RK,PS,RK,PS,RK,PS,RK,MU,VO
    defb VO,MU,RK,PS,RK,PS,PS,PS,PS,RK,PS,RK,PS,RK,MU,VO
    defb VO,MU,RK,RK,RK,RK,RK,PS,PS,RK,PS,PS,PS,RK,MU,VO
    defb VO,FG,MU,MU,MU,MU,MU,VO,VO,MU,MU,MU,MU,MU,FG,VO

    ._mapa6 //dngn_002
    defb VO,FG,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,MU,FG,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,RK,PS,PS,PS,PS,MU,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,MU,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,PS,MU,VO
    defb VO,FG,MU,MU,MU,MU,MU,VO,VO,MU,MU,MU,MU,MU,FG,VO

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

    ._mapa5 //shop
    defb SL,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,O1,SL,SL,SL,O2,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,SL,AR,SL
    defb SL,AR,AR,AR,AR,AR,AR,SL,SL,AR,AR,AR,AR,AR,AR,SL
#endasm
