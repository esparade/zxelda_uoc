//zxelda v0.1a
//16mar'26

unsigned char modo_app=0; //0 menu, 1 juego
unsigned char x,y; //render mapa

unsigned char hx; //hero x (columna 0..ancho_mapa-1)
unsigned char hy; //hero y (fila 0..alto_mapa-1; filas 0 y alto-1 son bordes de cambio de sala)
unsigned char hmap; // indice plano = hy*ancho_mapa+hx, actualizado por calculo_frame()
int anim;          // frame de animacion del heroe (alterna 0/1)
unsigned char vista; // orientacion del heroe: 0=der 1=izq

unsigned char ancho_mapa;
unsigned char alto_mapa;
unsigned char mapa_actual;
unsigned char mapa_trabajo[140];
extern unsigned char mapa1[];
extern unsigned char mapa2[];
extern unsigned char mapa3[];

#asm
    ._mapa1
    defb 1,1,1,1,1,1,0,0,1,1,1,1,1,1
    defb 1,1,9,1,1,0,0,0,1,1,1,1,1,1
    defb 1,1,0,0,0,0,0,0,1,1,1,1,1,1
    defb 1,0,0,0,0,0,0,0,0,1,1,1,1,1
    defb 1,0,0,0,0,0,0,0,0,0,0,0,0,1
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 1,1,0,0,0,0,0,0,0,0,0,1,1,1
    defb 1,1,0,0,0,0,0,0,0,0,1,1,1,1
    defb 1,1,1,1,1,1,1,1,1,1,1,1,1,1
    ._mapa2
    defb 0,0,0,0,2,0,0,0,0,2,0,2,0,2
    defb 1,1,0,0,0,0,0,0,0,0,0,0,0,0
    defb 1,1,0,0,2,0,0,0,0,2,0,2,0,2
    defb 1,1,0,0,0,0,0,0,0,0,0,0,0,0
    defb 1,1,0,0,0,0,0,0,0,2,0,2,0,2
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 1,1,0,0,2,0,0,0,0,2,0,2,0,2
    defb 1,1,0,0,0,0,0,0,0,0,0,0,0,0
    defb 1,1,2,2,2,2,2,2,2,2,2,2,2,2
    ._mapa3
    defb 5,5,5,5,5,5,3,3,5,5,5,5,5,5
    defb 5,9,9,9,9,9,4,4,9,9,9,9,9,5
    defb 5,9,4,4,4,9,3,4,4,4,9,4,9,5
    defb 5,9,4,9,4,9,4,9,9,4,9,4,9,5
    defb 5,4,4,9,4,9,4,4,9,4,9,4,4,5
    defb 5,9,4,9,4,9,9,4,9,4,9,4,9,5
    defb 5,9,4,9,4,4,4,3,9,4,9,4,9,5
    defb 5,9,9,9,9,9,4,4,9,4,4,4,9,5
    defb 5,5,5,5,5,5,9,9,5,5,5,5,5,5
#endasm

unsigned char Fx_anim;

// Carga en mapa_trabajo los tiles del mapa actual y fija el color de borde.
void carga_datos_mapa (void) {
    if (mapa_actual == 1) {
        port_out (254,6); //border color. 0_black, 1_blue, 2_red, 3_magenta, 4_green, 5_teal, 6_yellow, 7_white
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = mapa1[x];
        }
    }
    if (mapa_actual == 2) {
        port_out (254,1); //border color. 0_black, 1_blue, 2_red, 3_magenta, 4_green, 5_teal, 6_yellow, 7_white
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = mapa2[x];
        }
    }
    if (mapa_actual == 3) {
        port_out (254,0); //border color. 0_black, 1_blue, 2_red, 3_magenta, 4_green, 5_teal, 6_yellow, 7_white
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = mapa3[x];
        }
    }
}

// devuelve el mapa conectado en la direccion dada, 0 si no hay conexion
// mapa1: derecha→mapa2
// mapa2: izquierda→mapa1, arriba→mapa3
// mapa3: abajo→mapa2
unsigned char get_mapa_conexion(unsigned char mapa, unsigned char dir) {
    switch(mapa) {
        case 1:
            if (dir == DIR_DER) return 2;
        break;
        case 2:
            if (dir == DIR_IZQ) return 1;
            if (dir == DIR_ARR) return 3;
        break;
        case 3:
            if (dir == DIR_ABA) return 2;
        break;
    }
    return 0;
}

// Inicializa todas las variables de juego al estado inicial y carga el primer mapa (mapa1, ID1).
void inicia_variables_juego(void) {
    //heroe
    hx = 7;
    hy = 2;
    hmap = 0;
    anim = 0;
    vista = 0;

    //mapa actual
    ancho_mapa = 14;
    alto_mapa = 9;
    mapa_actual = 1;
    carga_datos_mapa();
}
