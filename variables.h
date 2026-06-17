unsigned char modo_app=0; //0 menu, 1 juego
unsigned char x,y;        //render mapa

unsigned char hx;    // hero x (columna 1..ancho_mapa-2)
unsigned char hy;    // hero y (fila 0..alto_mapa-1; filas 0 y alto-1 son bordes de cambio de sala)
unsigned char hmap;  // indice plano = hy*ancho_mapa+hx, actualizado por calculo_frame()
int anim;            // frame de animacion del heroe (alterna 0/1)
unsigned char vista; // direccion que mira el heroe: 0=arr 1=der 2=abj 3=izq

unsigned char ancho_mapa;        // columnas y del mapa actual (16)
unsigned char alto_mapa;         // filas x del mapa actual (9)
unsigned char mapa_actual;       // id del mapa actual
unsigned char mapa_trabajo[144]; // copia del mapa ROM de referencia (version RAM modificable)

unsigned char Fx_anim;          // frame actual de la animacion espadazo
unsigned char attack_timer;     // frames restantes de animacion espadazo (4)
unsigned char inv_timer;        // frames invulnerabilidad heroe tras danyo (40)

unsigned char heavy_x;      // heavy1 pos x (tile)
unsigned char heavy_y;      // heavy2 pos y (tile)
unsigned char heavy_anim;   // frame animacion heavy1
unsigned char heavy_mov;    // contador movimiento heavy1
unsigned char heavy_active; // heavy1 activo en este mapa

unsigned char heavy2_x;     // heavy2 pos x (tile)
unsigned char heavy2_y;     // heavy2 pos y (tile)
unsigned char heavy2_mov;   // contador movimiento heavy2
unsigned char heavy2_active;// heavy2 activo en este mapa

unsigned char octo1_x;      // octo1 pos x (tile)
unsigned char octo1_y;      // octo1 pos y (tile)
unsigned char octo1_mov;    // contador movimiento octo1
unsigned char octo1_active; // octo1 activo en este mapa
unsigned char octo1_dir;    // direccion actual: 0=up 1=right 2=down 3=left
unsigned char octo1_steps;  // pasos restantes antes de cambiar direccion

unsigned char octo2_x;      // octo2 pos x (tile)
unsigned char octo2_y;      // octo2 pos y (tile)
unsigned char octo2_mov;    // contador movimiento octo2
unsigned char octo2_active; // octo2 activo en este mapa
unsigned char octo2_dir;    // direccion actual: 0=up 1=right 2=down 3=left
unsigned char octo2_steps;  // pasos restantes antes de cambiar direccion

unsigned char octo1_shot_active;  // disparo del octo1
unsigned char octo1_shot_x;       // disparo del octo1 posx
unsigned char octo1_shot_y;       // disparo del octo1 posy
unsigned char octo1_shot_dir;     // direccion actual: 0=up 1=right 2=down 3=left
unsigned char octo1_shot_mov;     // velocidad delay del disparo octo1

unsigned char octo2_shot_active;  // disparo del octo2
unsigned char octo2_shot_x;       // disparo del octo2 posx
unsigned char octo2_shot_y;       // disparo del octo2 posy
unsigned char octo2_shot_dir;     // direccion actual: 0=up 1=right 2=down 3=left
unsigned char octo2_shot_mov;     // velocidad delay del disparo octo1

unsigned char boss_active;     // jefe final activo en dngn_g2 (ID70)
unsigned char boss_x;          // tile x del boss
unsigned char boss_y;          // tile y del boss
unsigned char boss_hp;         // vida del boss (8 golpes)
unsigned char boss_mov;        // contador movimiento boss
unsigned char boss_form;       // alterna disparo: 0=horizontal 1=vertical

unsigned char boss_shot_active;// disparo del octo2
unsigned char boss_shot_x;     // disparo del boss posx
unsigned char boss_shot_y;     // disparo del boss posy
unsigned char boss_shot_dir;   // direccion actual: 0=up 1=right 2=down 3=left
unsigned char boss_shot_mov;   // velocidad delay del disparo boss

unsigned char npc_active; // npc estatico activo en este mapa
unsigned char npc_x;      // npc pos x (tile)
unsigned char npc_y;      // npc pos y (tile)

unsigned char borde_actual = 6; // color de borde actual (bits 0-2 de puerto 254)

unsigned char puerta_abierta;  // 1 si la puerta del dungeon se abrio (persistente)

unsigned char spike_active;
// estado independiente por spike: permite reaccionar en horizontal Y vertical
unsigned char spike1_x, spike1_y, spike1_hx, spike1_hy, spike1_state, spike1_mov, spike1_dir;
unsigned char spike2_x, spike2_y, spike2_hx, spike2_hy, spike2_state, spike2_mov, spike2_dir;
unsigned char spike3_x, spike3_y, spike3_hx, spike3_hy, spike3_state, spike3_mov, spike3_dir;
unsigned char spike4_x, spike4_y, spike4_hx, spike4_hy, spike4_state, spike4_mov, spike4_dir;

unsigned char llave_en_mapa;    // 1 si la llave esta en el suelo
unsigned char llave_mapa;       // en que mapa cayo la llave
unsigned char llave_pos;        // indice en mapa_trabajo donde esta la llave
unsigned char tiene_llave;      // 1 si el heroe la recogio
unsigned char tile_bajo_llave;  // tile original donde cayo la llave

unsigned char corazon_en_mapa;  // 1 si el corazon esta en el suelo
unsigned char corazon_mapa;     // en que mapa cayo el corazon
unsigned char corazon_pos;      // indice en mapa_trabajo donde esta el corazon
unsigned char tile_bajo_corazon;// tile original donde cayo el corazon

unsigned char power_en_mapa;    // 1 si el item_power esta en el suelo
unsigned char power_mapa;       // en que mapa cayo
unsigned char power_pos;        // indice en mapa_trabajo
unsigned char tile_bajo_power;  // tile original donde cayo

// teclas redefinibles: port 16-bit + mascara de bit
unsigned int  key_arr_port; unsigned char key_arr_mask; // arriba
unsigned int  key_abj_port; unsigned char key_abj_mask; // abajo
unsigned int  key_izq_port; unsigned char key_izq_mask; // izquierda
unsigned int  key_der_port; unsigned char key_der_mask; // derecha
unsigned int  key_atk_port; unsigned char key_atk_mask; // ataque
unsigned int  key_men_port; unsigned char key_men_mask; // menu/reinicio

unsigned char redef_paso;   // 0=inactivo 1-6=capturando accion
unsigned char redef_espera; // 1=esperar a que se suelten teclas

void inicia_teclas(void) {
    key_arr_port = 64510; key_arr_mask = 1; // Q
    key_abj_port = 65022; key_abj_mask = 1; // A
    key_izq_port = 57342; key_izq_mask = 2; // O
    key_der_port = 57342; key_der_mask = 1; // P
    key_atk_port = 32766; key_atk_mask = 1; // SPACE
    key_men_port = 61438;  key_men_mask = 1; // 0
    redef_paso   = 0;
    redef_espera = 0;
}

unsigned char pts;
unsigned char vidas;
unsigned char fuerza;
unsigned char rand_seed; // semilla del generador; se inicializa con el registro R del Z80 (aleatorio al arrancar)
unsigned char enemy_dmg;
unsigned char game_over_timer;
unsigned char jgh_color;
unsigned char jgh_timer;
unsigned char tienda_mapa; // mapa de la tienda 1 (siempre 1)
unsigned char tienda_pos;  // posicion fija de la tienda 1
unsigned char mazmorra_mapa; // mapa de la tienda 2 (2 o 5, aleatorio)
unsigned char mazmorra_pos;  // posicion de la tienda 2 (centro del mapa)


void init_rand(void) {
    #asm
    ld a, r
    ld (_rand_seed), a
    #endasm
}

// generador aleatorio: seed = seed*65+13
unsigned char rand_next(void) {
    rand_seed = rand_seed * 65 + 13;
    return rand_seed;
}

// Elige aleatoriamente uno de los 5 mapas de mundo como ubicacion de la mazmorra
void randomize_mazmorra(void) {
    unsigned char r;
    tienda_mapa = 9; // wrld_b3 (mapa inicio)
    tienda_pos = 19; // (4,2) en wrld_b3
    r = rand_next() % 5;
    if      (r == 0) mazmorra_mapa = 1;  // wrld_a1
    else if (r == 1) mazmorra_mapa = 3;  // wrld_a3
    else if (r == 2) mazmorra_mapa = 12; // wrld_b6
    else if (r == 3) mazmorra_mapa = 19; // wrld_d1
    else             mazmorra_mapa = 21; // wrld_d3
    mazmorra_pos = 71; // (7,4) centro del mapa 16x9
}

//border color. 0_black, 1_blue, 2_red, 3_magenta, 4_green, 5_teal, 6_yellow, 7_white
// Carga en mapa_trabajo los tiles del mapa actual, activa los enemigos correspondientes y fija el color de borde
void carga_datos_mapa (void) {
    // reset de todos los enemigos (se reactivaran segun el mapa)
    heavy_active = 0;
    heavy_anim = 0;
    heavy_mov = 0;
    heavy2_active = 0;
    heavy2_mov = 0;
    octo1_active = 0;
    octo1_mov = 0;
    octo1_dir = 1;
    octo1_steps = 3;
    octo2_active = 0;
    octo2_mov = 0;
    octo2_dir = 1;
    octo2_steps = 3;
    octo1_shot_active = 0;
    octo2_shot_active = 0;
    npc_active = 0;
    spike_active = 0;
    spike1_state=0; spike2_state=0; spike3_state=0; spike4_state=0;
    // heavy: spawnea solo en mazmorra incluyendo boss
    if (mapa_actual == 59 || mapa_actual == 67 || mapa_actual == 70 || mapa_actual == 50 || mapa_actual == 51 || mapa_actual == 53 || mapa_actual == 54 || mapa_actual == 55 || mapa_actual == 61 || mapa_actual == 62 || mapa_actual == 63 || mapa_actual == 65) {
        heavy_active = 1; heavy_x = 10; heavy_y = 4;
        heavy2_active = 1; heavy2_x = 4; heavy2_y = 4;
    }
    // octo: spawnea en mapas de mundo exterior (tienda, cueva y mazmorra no)
    if (mapa_actual != 9 && mapa_actual != 24 && mapa_actual != 59 && mapa_actual != 67 && mapa_actual != 70 && mapa_actual != 51 && mapa_actual != 50 && mapa_actual != 53 && mapa_actual != 54 && mapa_actual != 55 && mapa_actual != 61 && mapa_actual != 62 && mapa_actual != 63 && mapa_actual != 64 && mapa_actual != 65) {
        octo1_active = 1; octo1_x = 9; octo1_y = 1;
        octo1_dir = (rand_next() >> 6) & 3;
        octo1_steps = 2 + (rand_next() & 3);
        octo2_active = 1; octo2_x = 6; octo2_y = 7;
        octo2_dir = (rand_next() >> 6) & 3;
        octo2_steps = 2 + (rand_next() & 3);
    }
    if (mapa_actual == 9) { // wrld_b3: mapa inicio, entada tienda
        borde_actual = 6; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = wrld_b3[x];
        }
        mapa_trabajo[tienda_pos] = 9;
    }
    if (mapa_actual == 10) { // wrld_b4
        borde_actual = 6; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = wrld_b4[x];
        }
    }
    if (mapa_actual == 59) { // dngn_c3
        borde_actual = 0; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = dngn_c3[x];
        }
        if (!puerta_abierta) {
            mapa_trabajo[7] = 12;
            mapa_trabajo[8] = 12;
        }
    }
    if (mapa_actual == 8) { // wrld_b2
        borde_actual = 6; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = wrld_b2[x];
        }
    }
    if (mapa_actual == 24) { // wrld_d6: shop room
        npc_active = 1; npc_x = 7; npc_y = 2;
        borde_actual = 0; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = wrld_d6[x];
        }
    }
    if (mapa_actual == 70) { // dngn_g2: sala del boss
        boss_active = 1;
        boss_x = 7;
        boss_y = 4;
        boss_hp = 8; // vida boss
        boss_mov = 0;
        boss_form = 0;
        boss_shot_active = 0;
        borde_actual = 0; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = dngn_g2[x];
        }
    }
    if (mapa_actual == 11) { // wrld_b5
        borde_actual = 6; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = wrld_b5[x];
        }
    }
    if (mapa_actual == 12) { // wrld_b6
        borde_actual = 6; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = wrld_b6[x];
        }
        if (mazmorra_mapa == 12) { // posible ubicacion de la entrada a la mazmorra dependiendo del resultado rnd
            mapa_trabajo[mazmorra_pos] = 9;
            mapa_trabajo[mazmorra_pos - 1] = 6;
            mapa_trabajo[mazmorra_pos + 1] = 7;
            mapa_trabajo[mazmorra_pos - ancho_mapa] = 8;
        }
    }
    if (mapa_actual == 1) { // wrld_a1
        borde_actual = 6; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = wrld_a1[x];
        }
        if (mazmorra_mapa == 1) { // posible ubicacion de la entrada a la mazmorra dependiendo del resultado rnd
            mapa_trabajo[mazmorra_pos] = 9;
            mapa_trabajo[mazmorra_pos - 1] = 6;
            mapa_trabajo[mazmorra_pos + 1] = 7;
            mapa_trabajo[mazmorra_pos - ancho_mapa] = 8;
        }
    }
    if (mapa_actual == 2) { // wrld_a2
        borde_actual = 6; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = wrld_a2[x];
        }
    }
    if (mapa_actual == 3) { // wrld_a3
        borde_actual = 6; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = wrld_a3[x];
        }
        if (mazmorra_mapa == 3) { // posible ubicacion de la entrada a la mazmorra dependiendo del resultado rnd
            mapa_trabajo[mazmorra_pos] = 9;
            mapa_trabajo[mazmorra_pos - 1] = 6;
            mapa_trabajo[mazmorra_pos + 1] = 7;
            mapa_trabajo[mazmorra_pos - ancho_mapa] = 8;
        }
    }
    if (mapa_actual == 19) { // wrld_d1
        borde_actual = 6; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = wrld_d1[x];
        }
        if (mazmorra_mapa == 19) { // posible ubicacion de la entrada a la mazmorra dependiendo del resultado rnd
            mapa_trabajo[mazmorra_pos] = 9;
            mapa_trabajo[mazmorra_pos - 1] = 6;
            mapa_trabajo[mazmorra_pos + 1] = 7;
            mapa_trabajo[mazmorra_pos - ancho_mapa] = 8;
        }
    }
    if (mapa_actual == 20) { // wrld_d2
        borde_actual = 6; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = wrld_d2[x];
        }
    }
    if (mapa_actual == 21) { // wrld_d3
        borde_actual = 6; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = wrld_d3[x];
        }
        if (mazmorra_mapa == 21) { // posible ubicacion de la entrada a la mazmorra dependiendo del resultado rnd
            mapa_trabajo[mazmorra_pos] = 9;
            mapa_trabajo[mazmorra_pos - 1] = 6;
            mapa_trabajo[mazmorra_pos + 1] = 7;
            mapa_trabajo[mazmorra_pos - ancho_mapa] = 8;
        }
    }
    if (mapa_actual == 22) { // wrld_d4
        borde_actual = 6; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = wrld_d4[x];
        }
    }
    if (mapa_actual == 14) { // wrld_c2
        borde_actual = 6; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = wrld_c2[x];
        }
    }
    if (mapa_actual == 16) { // wrld_c4
        borde_actual = 6; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = wrld_c4[x];
        }
    }
    if (mapa_actual == 51) {
        borde_actual = 0; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = dngn_a2[x];
        }
    }
    if (mapa_actual == 50) {
        borde_actual = 0; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = dngn_a1[x];
        }
    }
    if (mapa_actual == 53) {
        borde_actual = 0; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = dngn_b1[x];
        }
        spike_active=1;
        spike1_x=2;  spike1_y=1;  spike1_hx=2;  spike1_hy=1;  spike1_state=0; spike1_mov=0; spike1_dir=0;
        spike2_x=13; spike2_y=1;  spike2_hx=13; spike2_hy=1;  spike2_state=0; spike2_mov=0; spike2_dir=0;
        spike3_x=2;  spike3_y=7;  spike3_hx=2;  spike3_hy=7;  spike3_state=0; spike3_mov=0; spike3_dir=0;
        spike4_x=13; spike4_y=7;  spike4_hx=13; spike4_hy=7;  spike4_state=0; spike4_mov=0; spike4_dir=0;
    }
    if (mapa_actual == 54) {
        borde_actual = 0; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = dngn_b2[x];
        }
    }
    if (mapa_actual == 55) {
        borde_actual = 0; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = dngn_b3[x];
        }
        spike_active=1;
        spike1_x=2;  spike1_y=1;  spike1_hx=2;  spike1_hy=1;  spike1_state=0; spike1_mov=0; spike1_dir=0;
        spike2_x=13; spike2_y=1;  spike2_hx=13; spike2_hy=1;  spike2_state=0; spike2_mov=0; spike2_dir=0;
        spike3_x=2;  spike3_y=7;  spike3_hx=2;  spike3_hy=7;  spike3_state=0; spike3_mov=0; spike3_dir=0;
        spike4_x=13; spike4_y=7;  spike4_hx=13; spike4_hy=7;  spike4_state=0; spike4_mov=0; spike4_dir=0;
    }
    if (mapa_actual == 61) { // dngn_d2
        borde_actual = 0; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = dngn_d2[x];
        }
    }
    if (mapa_actual == 62) { // dngn_d3
        borde_actual = 0; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = dngn_d3[x];
        }
    }

    if (mapa_actual == 63) { // dngn_e1
        borde_actual = 0; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = dngn_e1[x];
        }
    }
    if (mapa_actual == 64) { // dngn_e2
        borde_actual = 0; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = dngn_e2[x];
        }
    }
    if (mapa_actual == 65) { // dngn_e3
        borde_actual = 0; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = dngn_e3[x];
        }
    }
    if (mapa_actual == 67) { // dngn_f2: antesala del boss
        borde_actual = 0; port_out(254, borde_actual);
        for (x = 0; x < ancho_mapa * alto_mapa; x++) {
            mapa_trabajo[x] = dngn_f2[x];
        }
    }
}

// Devuelve el ID del mapa conectado en la direccion dada, o 0 si no existe conexion.
// Los IDs de los mapas se asignan manualmente aqui y deben coincidir con los bloques de carga_datos_mapa.
// wrld_b3: derecha→wrld_b4, izquierda→wrld_b2
// wrld_b4: izquierda→wrld_b3, derecha→wrld_b5
// wrld_b5: izquierda→wrld_b4, derecha→wrld_b6
// wrld_b6: izquierda→wrld_b5
// wrld_b2: derecha→wrld_b3, abajo→wrld_a2, arriba→wrld_c2
// wrld_a1: derecha→wrld_a2
// wrld_a2: izquierda→wrld_a1, derecha→wrld_a3, arriba→wrld_b2
// wrld_a3: izquierda→wrld_a2
// wrld_d1: derecha→wrld_d2
// wrld_d2: izquierda→wrld_d1, abajo→wrld_c2
// wrld_c2: arriba→wrld_d2, abajo→wrld_b2
// wrld_d3: derecha→wrld_d4
// wrld_d4: izquierda→wrld_d3, abajo→wrld_c4
// wrld_c4: arriba→wrld_d4, abajo→wrld_b4
// wrld_d2: izquierda→wrld_d1
// wrld_d3: derecha→wrld_d4
// wrld_d4: izquierda→wrld_d3
// dngn_b1: abajo→dngn_a1, derecha→dngn_b2
// dngn_b2: izquierda→dngn_b1, derecha→dngn_b3
// dngn_b3: izquierda→dngn_b2, arriba→dngn_c3
// dngn_a1: derecha→dngn_a2, arriba→dngn_b1
// dngn_a2: izquierda→dngn_a1
// dngn_e1(63): derecha→dngn_e2

// dngn_e2(64): izquierda→dngn_e1, derecha→dngn_e3, abajo→dngn_d2, arriba→dngn_f2
// dngn_e3(65): izquierda→dngn_e2
// dngn_d2: arriba→dngn_e2, derecha→dngn_d3
// dngn_d3: izquierda→dngn_d2, abajo→dngn_c3
// dngn_c3: arriba→dngn_d3, abajo→dngn_b3
// dngn_f2: abajo→dngn_e2, arriba→dngn_g2
// dngn_g2: abajo→dngn_f2
unsigned char get_mapa_conexion(unsigned char mapa, unsigned char dir) {
    switch(mapa) {
        case 9: // wrld_b3 (start)
            if (dir == DIR_DER) return 10;
            if (dir == DIR_IZQ) return 8;
        break;
        case 10: // wrld_b4
            if (dir == DIR_IZQ) return 9;
            if (dir == DIR_DER) return 11;
            if (dir == DIR_ARR) return 16;
        break;
        case 11: // wrld_b5
            if (dir == DIR_IZQ) return 10;
            if (dir == DIR_DER) return 12;
        break;
        case 12: // wrld_b6
            if (dir == DIR_IZQ) return 11;
        break;
        case 1: // wrld_a1
            if (dir == DIR_DER) return 2;
        break;
        case 2: // wrld_a2
            if (dir == DIR_IZQ) return 1;
            if (dir == DIR_DER) return 3;
            if (dir == DIR_ARR) return 8;
        break;
        case 3: // wrld_a3
            if (dir == DIR_IZQ) return 2;
        break;
        case 19: // wrld_d1
            if (dir == DIR_DER) return 20;
        break;
        case 20: // wrld_d2
            if (dir == DIR_IZQ) return 19;
            if (dir == DIR_ABA) return 14;
        break;
        case 14: // wrld_c2
            if (dir == DIR_ARR) return 20;
            if (dir == DIR_ABA) return 8;
        break;
        case 21: // wrld_d3
            if (dir == DIR_DER) return 22;
        break;
        case 22: // wrld_d4
            if (dir == DIR_IZQ) return 21;
            if (dir == DIR_ABA) return 16;
        break;
        case 16: // wrld_c4
            if (dir == DIR_ARR) return 22;
            if (dir == DIR_ABA) return 10;
        break;
        case 8: // wrld_b2
            if (dir == DIR_DER) return 9;
            if (dir == DIR_ABA) return 2;
            if (dir == DIR_ARR) return 14;
        break;
        case 59: // dngn_c3
            if (dir == DIR_ARR) return 62;
            if (dir == DIR_ABA) return 55;
        break;
        case 61: // dngn_d2
            if (dir == DIR_DER) return 62;
            if (dir == DIR_ARR) return 64;
        break;
        case 63: // dngn_e1
            if (dir == DIR_DER) return 64;
        break;

        case 64: // dngn_e2
            if (dir == DIR_IZQ) return 63;
            if (dir == DIR_DER) return 65;
            if (dir == DIR_ABA) return 61;
            if (dir == DIR_ARR) return 67;
        break;
        case 65: // dngn_e3
            if (dir == DIR_IZQ) return 64;
        break;
        case 62: // dngn_d3
            if (dir == DIR_IZQ) return 61;
            if (dir == DIR_ABA) return 59;
        break;
        case 67: // dngn_f2
            if (dir == DIR_ABA) return 64;
            if (dir == DIR_ARR) return 70;
        break;
        case 70: // dngn_g2 (boss)
            if (dir == DIR_ABA) return 67;
        break;
        case 53: // dngn_b1
            if (dir == DIR_ABA) return 50;
            if (dir == DIR_DER) return 54;
        break;
        case 54: // dngn_b2
            if (dir == DIR_IZQ) return 53;
            if (dir == DIR_DER) return 55;
        break;
        case 55: // dngn_b3
            if (dir == DIR_IZQ) return 54;
            if (dir == DIR_ARR) return 59;
        break;
        case 50:
            if (dir == DIR_DER) return 51;
            if (dir == DIR_ARR) return 53;
        break;
        case 51:
            if (dir == DIR_IZQ) return 50;
        break;
    }
    return 0;
}

// Inicializa todas las variables de juego al estado inicial y carga el primer mapa (wrld_b3, ID1).
void inicia_variables_juego(void) {
    //heroe
    hx = 7;    //hero pos x start
    hy = 4;    //hero pos y start
    hmap = 0;  //posicion del heroe dentro del array del mapa: (hy * ancho_mapa + hx), si + ancho_mapa = tile justo encima de hero, - justo debajo
    anim = 0;  //animacion stop
    vista = 2; //sprite hero mirando abajo

    //stats
    pts = 0;
    vidas = NUMERO_DE_VIDAS;
    fuerza = 1;
    enemy_dmg = 1;

    //items
    llave_en_mapa = 0;
    llave_mapa = 0;
    llave_pos = 0;
    tiene_llave = 0;
    corazon_en_mapa = 0;
    corazon_mapa = 0;
    corazon_pos = 0;
    power_en_mapa = 0;
    power_mapa = 0;
    power_pos = 0;

    //ataque
    attack_timer = 0;
    inv_timer = 0;

    //enemigos heavy
    heavy_x = 7;
    heavy_y = 7;
    heavy_anim = 0;
    heavy_mov = 0;
    heavy_active = 1;
    heavy2_x = 0;
    heavy2_y = 0;
    heavy2_mov = 0;
    heavy2_active = 0;

    //enemigo octo1
    octo1_x = 0;
    octo1_y = 0;
    octo1_mov = 0;
    octo1_active = 0;
    octo1_dir = 1;
    octo1_steps = 3;

    //enemigo octo2
    octo2_x = 0;
    octo2_y = 0;
    octo2_mov = 0;
    octo2_active = 0;
    octo2_dir = 1;
    octo2_steps = 3;

    //disparos octos
    octo1_shot_active = 0;
    octo1_shot_x = 0;
    octo1_shot_y = 0;
    octo1_shot_dir = 0;
    octo1_shot_mov = 0;
    octo2_shot_active = 0;
    octo2_shot_x = 0;
    octo2_shot_y = 0;
    octo2_shot_dir = 0;
    octo2_shot_mov = 0;

    //boss
    boss_active = 0;
    boss_x = 7;
    boss_y = 4;
    boss_hp = 8;
    boss_mov = 0;
    boss_form = 0;
    boss_shot_active = 0;

    //npc
    npc_active = 0;
    npc_x = 0;
    npc_y = 0;

    //spikes
    spike_active=0;
    spike1_x=0; spike1_y=0; spike1_hx=0; spike1_hy=0; spike1_state=0; spike1_mov=0; spike1_dir=0;
    spike2_x=0; spike2_y=0; spike2_hx=0; spike2_hy=0; spike2_state=0; spike2_mov=0; spike2_dir=0;
    spike3_x=0; spike3_y=0; spike3_hx=0; spike3_hy=0; spike3_state=0; spike3_mov=0; spike3_dir=0;
    spike4_x=0; spike4_y=0; spike4_hx=0; spike4_hy=0; spike4_state=0; spike4_mov=0; spike4_dir=0;

    //puertas
    puerta_abierta = 0;

    //mapa actual
    ancho_mapa = 16;
    alto_mapa = 9;
    mapa_actual = 9; // wrld_b3 (inicio)
    init_rand();
    randomize_mazmorra();
    carga_datos_mapa();
}
