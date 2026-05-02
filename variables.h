//zxelda v0.1b
//07abr'26

unsigned char modo_app=0; //0 menu, 1 juego
unsigned char x,y; //render mapa

unsigned char hx; //hero x (columna 1..ancho_mapa-2)
unsigned char hy; //hero y (fila 0..alto_mapa-1; filas 0 y alto-1 son bordes de cambio de sala)
unsigned char hmap; // indice plano = hy*ancho_mapa+hx, actualizado por calculo_frame()
int anim;          // frame de animacion del heroe (alterna 0/1)
unsigned char vista; // direccion que mira el heroe: 0=arr 1=der 2=abj 3=izq

unsigned char ancho_mapa;
unsigned char alto_mapa;
unsigned char mapa_actual;
unsigned char mapa_trabajo[144];
extern unsigned char mapa1[];
extern unsigned char mapa2[];
extern unsigned char mapa3[];
extern unsigned char mapa4[];
extern unsigned char mapa5[];

#asm
    ._mapa1 //start 000
    defb 0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0
    defb 0,1,1,0,1,1,0,0,0,1,1,1,1,1,1,0
    defb 0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,0
    defb 0,1,0,0,0,0,0,0,0,0,1,1,1,1,1,0
    defb 0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0
    defb 0,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0
    defb 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0
    ._mapa2 //start_lft 001
    defb 0,1,1,0,0,2,0,0,0,0,2,0,2,0,2,0
    defb 0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 0,1,1,0,0,2,0,0,0,0,2,0,2,0,2,0
    defb 0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 0,1,1,0,0,0,0,0,0,0,2,0,2,0,2,0
    defb 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 0,1,1,0,0,2,0,0,0,0,2,0,2,0,2,0
    defb 0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 0,1,1,2,2,2,2,2,2,2,2,2,2,2,2,0
    ._mapa3 //dngn_001
    defb 9,5,5,5,5,5,5,3,3,5,5,5,5,5,5,9
    defb 9,5,9,9,9,9,9,4,4,9,9,9,9,9,5,9
    defb 9,5,9,4,4,4,9,3,4,4,4,9,4,9,5,9
    defb 9,5,9,4,9,4,9,4,9,9,4,9,4,9,5,9
    defb 9,5,4,4,9,4,9,4,4,9,4,9,4,4,5,9
    defb 9,5,9,4,9,4,9,9,4,9,4,9,4,9,5,9
    defb 9,5,9,4,9,4,4,4,3,9,4,9,4,9,5,9
    defb 9,5,9,9,9,9,9,4,4,9,4,4,4,9,5,9
    defb 9,5,5,5,5,5,5,9,9,5,5,5,5,5,5,9
    ._mapa4 //start -1 dungeon enter
    defb 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0
    defb 0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0
    defb 0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0
    defb 0,1,0,0,0,0,0,8,0,0,0,0,0,0,1,0
    defb 0,1,0,0,0,0,6,9,7,0,0,0,0,0,1,0
    defb 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    defb 0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0
    defb 0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0
    defb 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0
    ._mapa5 //from_start_room_door
    defb 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0
    defb 0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0
    defb 0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0
    defb 0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0
    defb 0,1,0,11,0,0,0,10,0,0,0,0,11,0,1,0
    defb 0,1,0,0,0,0,0,12,0,0,0,0,0,0,1,0
    defb 0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0
    defb 0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0
    defb 0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0
#endasm

unsigned char Fx_anim;
unsigned char attack_timer;

unsigned char ex;      // enemigo pos x (tile)
unsigned char ey;      // enemigo pos y (tile)
unsigned char eanim;   // frame animacion enemigo
unsigned char emov;    // contador movimiento enemigo
unsigned char eactive; // enemigo activo en este mapa

unsigned char llave_en_mapa; // 1 si la llave esta en el suelo
unsigned char llave_mapa;   // en que mapa cayo la llave
unsigned char llave_pos;    // indice en mapa_trabajo donde esta la llave
unsigned char tiene_llave;  // 1 si el heroe la recogio

unsigned char rand_seed; // semilla del generador; se inicializa con el registro R del Z80 (aleatorio en arranque)
unsigned char entrada_mapa; // mapa donde aparece la entrada (1 o 2)
unsigned char entrada_pos;  // indice en mapa_trabajo (y*16+x)

// posiciones validas en mapa1: (3,1) (6,1) (8,1) (3,3) (9,3) (4,5) (11,5) (3,6)
const unsigned char cand1[8] = {19, 22, 24, 51, 57, 84, 91, 99};
// posiciones validas en mapa2: (3,1) (7,1) (3,3) (7,3) (4,5) (9,5) (3,7) (6,7)
const unsigned char cand2[8] = {19, 23, 51, 55, 84, 89, 115, 118};

void init_rand(void) {
    #asm
    ld a, r
    ld (_rand_seed), a
    #endasm
}

// Generador congruencial lineal: seed = seed*167+13. Rapido y determinista; semilla del registro R del Z80.
unsigned char rand_next(void) {
    rand_seed = rand_seed * 167 + 13;
    return rand_seed;
}

void randomiza_entrada(void) {
    unsigned char r;
    r = rand_next();
    entrada_mapa = (r & 1) ? 2 : 1;
    r = rand_next() & 7;
    entrada_pos = (entrada_mapa == 1) ? cand1[r] : cand2[r];
}

// Carga en mapa_trabajo los tiles del mapa actual y fija el color de borde.
// Activa el enemigo solo en mapa1; en el resto permanece inactivo.
void carga_datos_mapa (void) {
    eactive = (mapa_actual == 1) ? 1 : 0;
    if (mapa_actual == 1) {
        port_out (254,6);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = mapa1[x];
        }
        if (entrada_mapa == 1) mapa_trabajo[entrada_pos] = 9;
    }
    if (mapa_actual == 2) {
        port_out (254,6);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = mapa2[x];
        }
        if (entrada_mapa == 2) mapa_trabajo[entrada_pos] = 9;
    }
    if (mapa_actual == 3) {
        port_out (254,0);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = mapa3[x];
        }
    }
    if (mapa_actual == 4) {
        port_out (254,6);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = mapa4[x];
        }
    }
    if (mapa_actual == 5) {
        port_out (254,0);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = mapa5[x];
        }
    }
}

// devuelve el mapa conectado en la direccion dada, 0 si no hay conexion
// mapa1: derecha→mapa2, izquierda→mapa4
// mapa2: izquierda→mapa1
// mapa4: derecha→mapa1
unsigned char get_mapa_conexion(unsigned char mapa, unsigned char dir) {
    switch(mapa) {
        case 1:
            if (dir == DIR_DER) return 2;
            if (dir == DIR_IZQ) return 4;
        break;
        case 2:
            if (dir == DIR_IZQ) return 1;
        break;
        case 4:
            if (dir == DIR_DER) return 1;
        break;
    }
    return 0;
}

// Inicializa todas las variables de juego al estado inicial y carga el primer mapa (mapa1, ID1).
void inicia_variables_juego(void) {
    //heroe
    hx = 7; //hero pos x start
    hy = 2; //hero pos y start
    hmap = 0;
    anim = 0;
    vista = 0;

    //items
    llave_en_mapa = 0;
    llave_mapa = 0;
    llave_pos = 0;
    tiene_llave = 0;

    //ataque
    attack_timer = 0;

    //enemigo
    ex = 7;
    ey = 7;
    eanim = 0;
    emov = 0;
    eactive = 1;

    //mapa actual
    ancho_mapa = 16;
    alto_mapa = 9;
    mapa_actual = 1;
    init_rand();
    randomiza_entrada();
    carga_datos_mapa();
}
