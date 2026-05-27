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

unsigned char Fx_anim;
unsigned char attack_timer;

unsigned char ex;      // enemigo pos x (tile)
unsigned char ey;      // enemigo pos y (tile)
unsigned char eanim;   // frame animacion enemigo
unsigned char emov;    // contador movimiento enemigo
unsigned char eactive; // enemigo activo en este mapa

unsigned char e2x;     // enemigo2 pos x (tile)
unsigned char e2y;     // enemigo2 pos y (tile)
unsigned char e2mov;   // contador movimiento enemigo2
unsigned char e2active;// enemigo2 activo en este mapa

unsigned char borde_actual = 6; // color de borde vigente (bits 0-2 de puerto 254)

unsigned char llave_en_mapa;    // 1 si la llave esta en el suelo
unsigned char llave_mapa;       // en que mapa cayo la llave
unsigned char llave_pos;        // indice en mapa_trabajo donde esta la llave
unsigned char tiene_llave;      // 1 si el heroe la recogio
unsigned char tile_bajo_llave;  // tile original donde cayo la llave

unsigned char corazon_en_mapa;  // 1 si el corazon esta en el suelo
unsigned char corazon_mapa;     // en que mapa cayo el corazon
unsigned char corazon_pos;      // indice en mapa_trabajo donde esta el corazon
unsigned char tile_bajo_corazon;// tile original donde cayo el corazon

unsigned char vidas;
unsigned char rand_seed; // semilla del generador; se inicializa con el registro R del Z80 (aleatorio en arranque)
unsigned char llave_anim;
unsigned char entrada_mapa; // mapa de la entrada 1 (siempre 1)
unsigned char entrada_pos;  // posicion fija de la entrada 1
unsigned char entrada2_mapa; // mapa de la entrada 2 (2 o 5, aleatorio)
unsigned char entrada2_pos;  // posicion aleatoria de la entrada 2

// posiciones validas en mapa1: (3,1) (6,1) (8,1) (3,3) (9,3) (4,5) (11,5) (3,6)
const unsigned char cand1[8] = {19, 22, 24, 51, 57, 84, 91, 99};
// posiciones validas en mapa2: (3,1) (7,1) (3,3) (7,3) (4,5) (9,5) (3,7) (6,7)
const unsigned char cand2[8] = {19, 23, 51, 55, 84, 89, 115, 118};
// posiciones validas en mapa4: (4,3) (7,3) (10,3) (4,4) (7,4) (10,4) (5,5) (9,5)
const unsigned char cand4[8] = {52, 55, 58, 68, 71, 74, 85, 89};

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
    // entrada 1: siempre en mapa 1, posicion fija
    entrada_mapa = 1;
    entrada_pos = 19; // (3,1) en mapa1
    // entrada 2: aleatoria entre mapa 2 y mapa 4
    r = rand_next();
    entrada2_mapa = (r & 128) ? 4 : 2;
    r = rand_next() & 7;
    entrada2_pos = (entrada2_mapa == 2) ? cand2[r] : cand4[r];
}

// Carga en mapa_trabajo los tiles del mapa actual, activa los enemigos correspondientes y fija el color de borde.
void carga_datos_mapa (void) {
    // reset de todos los enemigos (se reactivaran segun el mapa)
    eactive = 0;
    eanim = 0;
    emov = 0;
    e2active = 0;
    e2mov = 0;
    if (mapa_actual == 1) {
        eactive = 1;
        borde_actual = 6; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = mapa1[x];
        }
        mapa_trabajo[entrada_pos] = 9;
    }
    if (mapa_actual == 2) {
        e2active = 1; e2x = 8; e2y = 4;
        borde_actual = 6; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = mapa2[x];
        }
        if (entrada2_mapa == 2) {
            mapa_trabajo[entrada2_pos] = 9;
            mapa_trabajo[entrada2_pos - 1] = 6;
            mapa_trabajo[entrada2_pos + 1] = 7;
            mapa_trabajo[entrada2_pos - ancho_mapa] = 8;
        }
    }
    if (mapa_actual == 3) {
        eactive = 1; ex = 10; ey = 4;
        borde_actual = 0; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = mapa3[x];
        }
    }
    if (mapa_actual == 4) {
        borde_actual = 6; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = mapa4[x];
        }
        if (entrada2_mapa == 4) {
            mapa_trabajo[entrada2_pos] = 9;
            mapa_trabajo[entrada2_pos - 1] = 6;
            mapa_trabajo[entrada2_pos + 1] = 7;
            mapa_trabajo[entrada2_pos - ancho_mapa] = 8;
        }
    }
    if (mapa_actual == 5) {
        borde_actual = 0; port_out(254, borde_actual);
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

    //vidas
    vidas = NUMERO_DE_VIDAS;

    //items
    llave_en_mapa = 0;
    llave_mapa = 0;
    llave_pos = 0;
    tiene_llave = 0;
    corazon_en_mapa = 0;
    corazon_mapa = 0;
    corazon_pos = 0;

    //ataque
    attack_timer = 0;

    //enemigo
    ex = 7;
    ey = 7;
    eanim = 0;
    emov = 0;
    eactive = 1;

    //enemigo2
    e2x = 0;
    e2y = 0;
    e2mov = 0;
    e2active = 0;

    //mapa actual
    ancho_mapa = 16;
    alto_mapa = 9;
    mapa_actual = 1;
    init_rand();
    randomiza_entrada();
    carga_datos_mapa();
}
