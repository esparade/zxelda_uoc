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
unsigned char mapa_trabajo[160];
extern unsigned char mapa1[];
extern unsigned char mapa2[];
extern unsigned char mapa3[];

#asm
    ._mapa1
    defb 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
    defb 1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1
    defb 1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1
    defb 1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,1
    defb 1,0,0,0,0,0,1,1,1,1,0,1,0,1,0,1
    defb 1,0,0,0,0,0,1,0,0,1,0,1,0,1,0,1
    defb 1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1
    defb 1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1
    defb 1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0
    defb 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
    ._mapa2
    defb 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
    defb 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1
    defb 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1
    defb 1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1
    defb 1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1
    defb 1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1
    defb 1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,1
    defb 1,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1
    defb 0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1
    defb 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
#endasm

unsigned char Fx_anim;

// Carga en mapa_trabajo los tiles del mapa actual.
void carga_datos_mapa (void) {
    if (mapa_actual == 1) {
        for (x = 0; x <= 160; x++) {
            mapa_trabajo[x] = mapa1[x];
        }
    }
    if (mapa_actual == 2) {
        for (x = 0; x <= 160; x++) {
            mapa_trabajo[x] = mapa2[x];
        }
    }
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
    ancho_mapa = 16;
    alto_mapa = 10;
    mapa_actual = 1;
    carga_datos_mapa();
}
