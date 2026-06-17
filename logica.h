// fuerza el atributo de color amarillo en el sprite de la llave para hacerla visible.
void anima_llave(void) {
    if (!llave_en_mapa || mapa_actual != llave_mapa) return;
    item_llave[16] = 6;
    item_llave[17] = 6;
    item_llave[18] = 6;
    item_llave[19] = 6;
    render_tile(15, llave_pos % ancho_mapa, llave_pos / ancho_mapa);
}

// solidosolidos: arbol(1), matorral(2), bloque(3), pared(5),
// puerta_izq(6), puerta_der(7), puerta_arr(8), puerta_cerrada(12), tumba(17), agua(18), bloque_empujable(19).
// transparentes: suelo(0), baldosa(4), void(9), fuego(13) e items(14,15,16).
int es_solido(unsigned char tile) {
    return tile==1 || tile==2 || tile==3 || tile==5 || tile==6 || tile==7 || tile==8 || tile==12 || tile==17 || tile==18 || tile==19;
}

// Intenta empujar el bloque empujable en (bx,by) hacia (dest_x,dest_y).
// Devuelve 1 si el empuje tuvo exito (destino libre), 0 si esta bloqueado.
// Al empujar, restaura baldosa(4) en la posicion original del bloque.
unsigned char intenta_empujar_bloque(unsigned char bx, unsigned char by, unsigned char dest_x, unsigned char dest_y) {
    if (dest_x < 1 || dest_x > ancho_mapa-2) return 0;
    if (dest_y >= alto_mapa) return 0;
    if (es_solido(mapa_trabajo[dest_y*ancho_mapa+dest_x])) return 0;
    mapa_trabajo[by*ancho_mapa+bx] = 4;
    mapa_trabajo[dest_y*ancho_mapa+dest_x] = 3;
    render_tile(4, bx, by);
    render_tile(3, dest_x, dest_y);
    return 1;
}

// abre acceso superior de dngn_c3 si tienes llave y estas en fila 1
// frente al hueco (cols 7-8). gasta la llave, sustituye PC(12) por VO(9) y emite sonido
void check_puerta(void) {
    if (mapa_actual != 59) return; //comprueba mapa
    if (puerta_abierta) return; //comprueba puerta ya abierta
    if (!tiene_llave) return; //comprueba num llaves
    if (hy != 1) return; //comprueba pos y
    if (hx != 7 && hx != 8) return; //comprueba pos x
    puerta_abierta = 1;
    tiene_llave = 0;
    mapa_trabajo[7] = 9;  // cambia tile puertas
    mapa_trabajo[8] = 9;  // cambia tile puertas
    render_tile(9, 7, 0); // cambia tile puertas
    render_tile(9, 8, 0); // cambia tile puertas
    render_hud_llave();   // num llaves inventario a 0
    borde_actual = 0; port_out(254, 0);
    sonido_secreto();
}

void animacion_hero(void) {
    switch(vista) {
        case 0: // anim plyr up
            switch(anim) {
                case 0: //frame 0
                    put_sprite_x16_mask_ink(plyr_upA,hx*2+MAPA_OX,hy*2+MAPA_OY);
                    break;
                case 1: //frame 1
                    put_sprite_x16_mask_ink(plyr_upB,hx*2+MAPA_OX,hy*2+MAPA_OY);
                    break;
            }
            anim++;

            if (anim > 1) { // loop animacion
                anim = 0;
            }
            break;

        case 1: // anim plyr rgh
            switch(anim) {
                case 0:
                    put_sprite_x16_mask_ink(plyr_rghA,hx*2+MAPA_OX,hy*2+MAPA_OY);
                    break;
                case 1:
                    put_sprite_x16_mask_ink(plyr_rghB,hx*2+MAPA_OX,hy*2+MAPA_OY);
                    break;
            }
            anim++;

            if (anim > 1) { // loop animacion
                anim = 0;
            }
            break;

        case 2: // anim plyr dwn
            switch(anim) {
                case 0:
                    put_sprite_x16_mask_ink(plyr_dwnA,hx*2+MAPA_OX,hy*2+MAPA_OY);
                    break;
                case 1:
                    put_sprite_x16_mask_ink(plyr_dwnB,hx*2+MAPA_OX,hy*2+MAPA_OY);
                    break;
            }
            anim++;

            if (anim > 1) { // loop animacion
                anim = 0;
            }
            break;

        case 3: // anim plyr lft
            switch(anim) {
                case 0:
                    put_sprite_x16_mask_ink(plyr_lftA,hx*2+MAPA_OX,hy*2+MAPA_OY);
                    break;
                case 1:
                    put_sprite_x16_mask_ink(plyr_lftB,hx*2+MAPA_OX,hy*2+MAPA_OY);
                    break;
            }
            anim++;

            if (anim > 1) { // loop animacion
                anim = 0;
            }
            break;
    }
}

// recalcula el indice del hero en el array del mapa hmap = hy*ancho_mapa+hx. recalcular tras cada cambio de hx o hy.
void calculo_frame(void) {
    hmap = hy*ancho_mapa+hx;
}

// gestion de los teletransportes entre mapas (tile VO/9 en posicion fija).
// tienda(mapa1)→shop(mapa5), mazmorra_mapa→dngn_a2(51), dngn_a2→mazmorra_mapa, shop→mapa1.
// la mazmorra es aleatoria cada partida (randomize_mazmorra).
void check_warp(void) {
    if (mapa_actual == tienda_mapa && mapa_trabajo[hmap] == 9) { // entrada a la tienda: mundo -> shop (mapa 24)
        mapa_actual = 24; // wrld_b3
        hx = 7;
        hy = 7;
        carga_datos_mapa(); // redibujado tras cambio de pantalla
        calculo_frame();
        cls(0);
        render_hud_fondo();
        render_hud_pts();
        render_hud_vidas();
        render_hud_fuerza();
        render_hud_llave();
        render_mapa();
        render_hero(hx*2, hy*2);
        return;
    }
    if (mapa_actual == mazmorra_mapa && mapa_trabajo[hmap] == 9) { // entrada a la mazmorra: mundo (aleatorio) -> dngn_a2 (mapa 51)
        mapa_actual = 51; // dngs_a2
        hx = 7;
        hy = 7;
        carga_datos_mapa(); // redibujado tras cambio de pantalla
        calculo_frame();
        cls(0);
        render_hud_fondo();
        render_hud_pts();
        render_hud_vidas();
        render_hud_fuerza();
        render_hud_llave();
        render_mapa();
        render_hero(hx*2, hy*2);
        return;
    }
    if (mapa_actual == 51 && hy == alto_mapa-1 && mapa_trabajo[hmap] == 9) { // salida de la mazmorra: dngn_a2 (mapa 51) -> mundo (aleatorio) (mazmorra_mapa)
        mapa_actual = mazmorra_mapa;
        hx = mazmorra_pos % ancho_mapa;
        hy = mazmorra_pos / ancho_mapa + 1;
        carga_datos_mapa(); // redibujado tras cambio de pantalla
        calculo_frame();
        cls(0);
        render_hud_fondo();
        render_hud_pts();
        render_hud_vidas();
        render_hud_fuerza();
        render_hud_llave();
        render_mapa();
        render_hero(hx*2, hy*2);
        return;
    }
    if (mapa_actual == 24 && hy == alto_mapa-1 && (hx == 7 || hx == 8)) { // salida de la tienda: shop (mapa 24) -> wrld_b3 (mapa 9)
        mapa_actual = 9; // wrld_b3
        hx = tienda_pos % ancho_mapa;
        hy = tienda_pos / ancho_mapa + 1;
        carga_datos_mapa(); // redibujado tras cambio de pantalla
        calculo_frame();
        cls(0);
        render_hud_fondo();
        render_hud_pts();
        render_hud_vidas();
        render_hud_fuerza();
        render_hud_llave();
        render_mapa();
        render_hero(hx*2, hy*2);
        return;
    }
}

void sword_render(void) { //ataque con espada
    switch(vista) {
        case 0: // arriba
            if (hy == 0) return; // en borde, no dibujar
            put_sprite_8x16(swrd_up, hx*2+MAPA_OX, hy*2-2+MAPA_OY);
            break;
        case 1: // derecha
            if (hx == ancho_mapa-1) return; // en borde, no dibujar
            put_sprite_16x8(swrd_rgh, hx*2+2+MAPA_OX, hy*2+MAPA_OY);
            break;
        case 2: // abajo
            if (hy == alto_mapa-1) return; // en borde, no dibujar
            put_sprite_8x16(swrd_dwn, hx*2+MAPA_OX, hy*2+2+MAPA_OY);
            break;
        case 3: // izquierda
            if (hx == 0) return; // en borde, no dibujar
            put_sprite_16x8(swrd_lft, hx*2-2+MAPA_OX, hy*2+MAPA_OY);
            break;
    }
}

void sword_erase(void) { //ataque fin, borrar espada
    switch(vista) {
        case 0: // arriba
            if (hy > 0) render_tile(mapa_trabajo[(hy-1)*ancho_mapa+hx], hx, hy-1);
            break;
        case 1: // derecha
            if (hx < ancho_mapa-1) render_tile(mapa_trabajo[hy*ancho_mapa+hx+1], hx+1, hy);
            break;
        case 2: // abajo
            if (hy < alto_mapa-1) render_tile(mapa_trabajo[(hy+1)*ancho_mapa+hx], hx, hy+1);
            break;
        case 3: // izquierda
            if (hx > 0) render_tile(mapa_trabajo[hy*ancho_mapa+hx-1], hx-1, hy);
            break;
    }
}

// suelta un item en la posicion del enemigo eliminado
// en dngn_c3 siempre suelta la llave, resto un corazon
void drop_item(unsigned char ix, unsigned char iy) {
    unsigned char pos = iy * ancho_mapa + ix;    // index de la posicion del drop
    if (mapa_actual == 59) {                     // llave solo cae en dngn_c3
        llave_mapa = mapa_actual;                // registra el mapa donde esta la llave
        llave_pos  = pos;                        // registra la posicion de la llave
        tile_bajo_llave = mapa_trabajo[pos];     // guarda el tile original para restaurarlo al recoger
        mapa_trabajo[pos] = 15;                  // coloca tile llave (15) en el mapa
        llave_en_mapa = 1;                       // activa flag de llave visible
    } else {                                     // en resto de mapas
        corazon_mapa = mapa_actual;              // registra el mapa donde esta el corazon
        corazon_pos  = pos;                      // registra la posicion del corazon
        tile_bajo_corazon = mapa_trabajo[pos];   // guarda el tile original para restaurarlo al recoger
        mapa_trabajo[pos] = 14;                  // coloca tile corazon (14) en el mapa
        corazon_en_mapa = 1;                     // activa flag de corazon visible
    }
}

// drop del item del boss que finaliza la run
void drop_power(unsigned char ix, unsigned char iy) {
    unsigned char pos = iy * ancho_mapa + ix;    // index de la posicion del drop
    power_mapa = mapa_actual;                    // registra el mapa donde esta el power
    power_pos  = pos;                            // registra la posicion del power
    tile_bajo_power = mapa_trabajo[pos];         // guarda el tile original para restaurarlo al recoger
    mapa_trabajo[pos] = 16;                      // coloca tile power (16) en el mapa
    power_en_mapa = 1;                           // activa flag de power visible
}

// al recoger el item_power: +1 fuerza (max 9) y multiplica * 2 danyo enemigos
// reinicia el juego para refrescar el estado sin perder pts ni enemy_dmg
void check_power(void) {
    unsigned char saved_pts, new_dmg, saved_fuerza;
    if (!power_en_mapa) return;                                          // solo si el power esta en el mapa
    if (mapa_actual != power_mapa) return;                               // solo si estamos en el mapa correcto
    if (hmap != power_pos) return;                                       // solo si el heroe esta sobre el power
    saved_pts = pts;                                                     // salva pts antes del reinicio de pantalla
    saved_fuerza = fuerza;                                               // salva fuerza antes del reinicio de pantalla
    new_dmg = enemy_dmg * 2;                                             // nuevo danyo (x2) antes del reinicio
    cambiar_pantalla(PANTALLA_JUEGO);                                    // reinicia la pantalla de juego
    pts = saved_pts;                                                     // restaura pts tras el reinicio
    enemy_dmg = new_dmg;                                                 // aplica nuevo danyo de enemigos
    fuerza = (saved_fuerza < 9) ? saved_fuerza + 1 : 9;                  // incrementa fuerza con tope en 9
    render_hud_pts();
    render_hud_fuerza();
}

// restaura los 9 tiles (3x3) que ocupa el boss en (bx,by) redibujando desde mapa_trabajo
// se llama antes de mover al boss para borrar su sprite de la pantalla
void erase_boss_tiles(unsigned char bx, unsigned char by) {
    unsigned char r, c;
    for (r = by-1; r <= by+1; r++)        // recorre las 3 filas del area del boss
        for (c = bx-1; c <= bx+1; c++)    // recorre las 3 columnas del area del boss
            render_tile(mapa_trabajo[r*ancho_mapa+c], c, r); // redibuja tiles originales de map
}

// hitbox del ataque del heroe
// el boss necesita boss_hp golpes, sueltan item prob. 1/2 veces
void check_sword_hit(void) {
    unsigned char tx, ty;
    switch(vista) {                                                          // tile objetivo segun direccion del heroe
        case 0: tx=hx;   ty=hy-1; break;                                     // arriba
        case 1: tx=hx+1; ty=hy;   break;                                     // derecha
        case 2: tx=hx;   ty=hy+1; break;                                     // abajo
        case 3: tx=hx-1; ty=hy;   break;                                     // izquierda
    }
    if (heavy_active && heavy_x == tx && heavy_y == ty) {                    // comprobacion heavy1
        heavy_active = 0;                                                    // elimina heavy1
        pts += 3; render_hud_pts();                                          // suma 3 pts
        if (rand_next() & 1) drop_item(heavy_x, heavy_y);                    // drop item con prob. 1/2
        render_tile(mapa_trabajo[heavy_y*ancho_mapa+heavy_x], heavy_x, heavy_y); // restaura tile
    }
    if (heavy2_active && heavy2_x == tx && heavy2_y == ty) {                 // comprobacion heavy2
        heavy2_active = 0;                                                   // elimina heavy2
        pts += 3; render_hud_pts();                                          // suma 3 pts
        if (rand_next() & 1) drop_item(heavy2_x, heavy2_y);                  // drop item con prob. 1/2
        render_tile(mapa_trabajo[heavy2_y*ancho_mapa+heavy2_x], heavy2_x, heavy2_y); // restaura tile
    }
    if (octo1_active && octo1_x == tx && octo1_y == ty) {                    // comprobacion octo1
        octo1_active = 0;                                                    // elimina octo1
        pts += 1; render_hud_pts();                                          // suma 1 pt
        if (rand_next() & 1) drop_item(octo1_x, octo1_y);                    // drop item con prob. 1/2
        render_tile(mapa_trabajo[octo1_y*ancho_mapa+octo1_x], octo1_x, octo1_y); // restaura tile
    }
    if (octo2_active && octo2_x == tx && octo2_y == ty) {                    // comprobacion octo2
        octo2_active = 0;                                                    // elimina octo2
        pts += 1; render_hud_pts();                                          // suma 1 pt
        if (rand_next() & 1) drop_item(octo2_x, octo2_y);                    // drop item con prob. 1/2
        render_tile(mapa_trabajo[octo2_y*ancho_mapa+octo2_x], octo2_x, octo2_y); // restaura tile
    }
    if (boss_active && boss_y == ty && boss_x == tx) {                       // comprobacion boss
        boss_hp--;                                                           // resta un punto de vida al boss
        if (boss_hp == 0) {                                                  // boss derrotado
            boss_active = 0;
            pts += 10; render_hud_pts();                                     // suma 10 pts
            erase_boss_tiles(boss_x, boss_y);                                // limpia los tiles del boss
            drop_power(boss_x, boss_y);                                      // suelta el item final
        }
    }
}

void check_corazon(void) { // comprobacion recoger vida
    if (!corazon_en_mapa) return;                                                                    // solo si el corazon esta en el mapa
    if (mapa_actual != corazon_mapa) return;                                                         // solo si estamos en el mapa correcto
    if (hmap != corazon_pos) return;                                                                 // solo si el heroe esta sobre el corazon
    corazon_en_mapa = 0;                                                                             // desactiva flag: corazon recogido
    sonido_corazon();
    if (vidas < NUMERO_DE_VIDAS) {                                                                   // solo suma vida si no esta al maximo
        vidas++;
        render_hud_vidas();
    }
    mapa_trabajo[corazon_pos] = tile_bajo_corazon;                                                   // restaura el tile original del array
    render_tile(tile_bajo_corazon, corazon_pos % ancho_mapa, corazon_pos / ancho_mapa);              // redibuja tile fondo
    render_hero(hx*2, hy*2);                                                                         // redibuja heroe encima
}

void check_llave(void) { // comprobacion recoger llave
    if (!llave_en_mapa) return;                                                                      // solo si la llave esta en el mapa
    if (mapa_actual != llave_mapa) return;                                                           // solo si estamos en el mapa correcto
    if (hmap != llave_pos) return;                                                                   // solo si el heroe esta sobre la llave
    llave_en_mapa = 0;                                                                               // desactiva flag: llave recogida
    tiene_llave = 1;                                                                                 // tenemos la llave
    sonido_llave();
    mapa_trabajo[llave_pos] = tile_bajo_llave;                                                       // restaura el tile original del array
    render_tile(tile_bajo_llave, llave_pos % ancho_mapa, llave_pos / ancho_mapa);                    // redibuja el tile fondo
    render_hud_llave();                                                                              // actualiza el icono de llave en el hud
    render_hero(hx*2, hy*2);                                                                         // redibuja heroe encima
}

void update_attack(void) { // tiempo en el que la hitbox del espadazo esta activo
    if (attack_timer == 0) return;
    sword_render();
    attack_timer--;
    if (attack_timer == 0) sword_erase();
}

void render_npc(void) { // dibuja el mapa de la tienda
    unsigned char col;
    if (!npc_active) return;
    put_sprite_x16(npc_shopper, npc_x*2+MAPA_OX, npc_y*2+MAPA_OY+1);
    col = 9;
    put_hud_char(F_LET('c'), col++, 9, 48);
    put_hud_char(F_LET('o'), col++, 9, 48);
    put_hud_char(F_LET('m'), col++, 9, 48);
    put_hud_char(F_LET('p'), col++, 9, 48);
    put_hud_char(F_LET('r'), col++, 9, 48);
    put_hud_char(F_LET('a'), col++, 9, 48);
    put_hud_char(F_LET('t'), col++, 9, 48);
    put_hud_char(F_LET('e'), col++, 9, 48);
    col++,
    put_hud_char(F_LET('a'), col++, 9, 48);
    put_hud_char(F_LET('l'), col++, 9, 48);
    put_hud_char(F_LET('g'), col++, 9, 48);
    put_hud_char(F_LET('o'), col++, 9, 48);
    col = 13;
    put_hud_char(F_LET('p'), col++, 10, 48);
    put_hud_char(F_LET('r'), col++, 10, 48);
    put_hud_char(F_LET('i'), col++, 10, 48);
    put_hud_char(F_LET('m'), col++, 10, 48);
    put_hud_char(F_LET('o'), col++, 10, 48);
    // precio 100 sword
    put_hud_char(F_DIG(1), 10, 16, 48);
    put_hud_char(F_DIG(0), 11, 16, 48);
    put_hud_char(F_DIG(0), 12, 16, 48);
    // precio 100 hearth
    put_hud_char(F_DIG(1), 18, 16, 48);
    put_hud_char(F_DIG(0), 19, 16, 48);
    put_hud_char(F_DIG(0), 20, 16, 48);
}

void animacion_spike(void) {
    if (!spike_active) return;
    put_sprite_x16(enmy_spk, spike1_x*2+MAPA_OX, spike1_y*2+MAPA_OY);
    put_sprite_x16(enmy_spk, spike2_x*2+MAPA_OX, spike2_y*2+MAPA_OY);
    put_sprite_x16(enmy_spk, spike3_x*2+MAPA_OX, spike3_y*2+MAPA_OY);
    put_sprite_x16(enmy_spk, spike4_x*2+MAPA_OX, spike4_y*2+MAPA_OY);
}

void spike_dmg(unsigned char sx, unsigned char sy) {
    if (sx == hx && sy == hy && inv_timer == 0) {
        vidas = (vidas >= enemy_dmg) ? vidas - enemy_dmg : 0;
        sonido_danio(); render_hud_vidas();
        inv_timer = 40;
        if (vidas == 0) cambiar_pantalla(PANTALLA_GAME_OVER);
    }
}

// mueve un spike individual un paso en su direccion (state=1) o de vuelta (state=2).
// dir: 0=arr 1=der 2=abj 3=izq
void mueve_un_spike(unsigned char *sx, unsigned char *sy,
                    unsigned char hx2, unsigned char hy2,
                    unsigned char *state, unsigned char *mov, unsigned char dir) {
    if (*state == 1) {
        (*mov)++;
        if (*mov >= 3) {
            *mov = 0;
            render_tile(mapa_trabajo[(*sy)*ancho_mapa+(*sx)], *sx, *sy);
            switch(dir) {
                case 0: if (*sy > 0)           (*sy)--; break;
                case 1: if (*sx < ancho_mapa-1)(*sx)++; break;
                case 2: if (*sy < alto_mapa-1) (*sy)++; break;
                case 3: if (*sx > 0)           (*sx)--; break;
            }
            spike_dmg(*sx, *sy);
        }
    } else if (*state == 2) {
        (*mov)++;
        if (*mov >= 16) {
            *mov = 0;
            render_tile(mapa_trabajo[(*sy)*ancho_mapa+(*sx)], *sx, *sy);
            if      (*sx > hx2) (*sx)--;
            else if (*sx < hx2) (*sx)++;
            if      (*sy > hy2) (*sy)--;
            else if (*sy < hy2) (*sy)++;
            spike_dmg(*sx, *sy);
            if (*sx == hx2 && *sy == hy2) *state = 0;
        }
    }
}

// 4 spikes en las 4 esquinas con estado independiente, cada spike puede pertenecer
// a un par horizontal (misma fila) o vertical (misma columna) segun donde este hero
// al acercarte a una pared, el par de esa pared se lanza hacia el centro,
// choca con sonido metalico y vuelve despacio a las esquinas.
void mueve_spike(void) {
    if (!spike_active) return;

    // cuando hero entra en la fila o columna de la pared
    if (hy == spike1_hy && spike1_state == 0 && spike2_state == 0) { // par horizontal sup
        spike1_state=1; spike1_dir=1; spike1_mov=0;
        spike2_state=1; spike2_dir=3; spike2_mov=0;
    }
    if (hy == spike3_hy && spike3_state == 0 && spike4_state == 0) { // par horizontal inf
        spike3_state=1; spike3_dir=1; spike3_mov=0;
        spike4_state=1; spike4_dir=3; spike4_mov=0;
    }
    if (hx == spike1_hx && spike1_state == 0 && spike3_state == 0) { // par vertical izq
        spike1_state=1; spike1_dir=2; spike1_mov=0;
        spike3_state=1; spike3_dir=0; spike3_mov=0;
    }
    if (hx == spike2_hx && spike2_state == 0 && spike4_state == 0) { // par vertical der
        spike2_state=1; spike2_dir=2; spike2_mov=0;
        spike4_state=1; spike4_dir=0; spike4_mov=0;
    }

    // movimiento de cada spike
    mueve_un_spike(&spike1_x,&spike1_y,spike1_hx,spike1_hy,&spike1_state,&spike1_mov,spike1_dir); // spike 1 top left
    mueve_un_spike(&spike2_x,&spike2_y,spike2_hx,spike2_hy,&spike2_state,&spike2_mov,spike2_dir); // spike 2 top right
    mueve_un_spike(&spike3_x,&spike3_y,spike3_hx,spike3_hy,&spike3_state,&spike3_mov,spike3_dir); // spike 3 down left
    mueve_un_spike(&spike4_x,&spike4_y,spike4_hx,spike4_hy,&spike4_state,&spike4_mov,spike4_dir); // spike 4 down right

    // colision - cuando el par se encuentra en el centro, cambian estado a retorno y suenan
    if (spike1_state==1 && spike2_state==1 &&                             // par horizontal sup
        spike1_y==spike2_y && spike2_x<=spike1_x+1) {
        spike1_state=2; spike1_mov=0; spike2_state=2; spike2_mov=0;
        sonido_choque_spike();
    }
    if (spike3_state==1 && spike4_state==1 &&                             // par horizontal inf
        spike3_y==spike4_y && spike4_x<=spike3_x+1) {
        spike3_state=2; spike3_mov=0; spike4_state=2; spike4_mov=0;
        sonido_choque_spike();
    }
    if (spike1_state==1 && spike3_state==1 &&                             // par vertical izq
        spike1_x==spike3_x && spike3_y<=spike1_y+1) {
        spike1_state=2; spike1_mov=0; spike3_state=2; spike3_mov=0;
        sonido_choque_spike();
    }
    if (spike2_state==1 && spike4_state==1 &&                             // par vertical der
        spike2_x==spike4_x && spike4_y<=spike2_y+1) {
        spike2_state=2; spike2_mov=0; spike4_state=2; spike4_mov=0;
        sonido_choque_spike();
    }
}

void animacion_heavy(void) {
    if (!heavy_active) return;
    put_sprite_x16(enmy_hvy, heavy_x*2+MAPA_OX, heavy_y*2+MAPA_OY);
}

void animacion_heavy2(void) {
    if (!heavy2_active) return;
    put_sprite_x16(enmy_hvy, heavy2_x*2+MAPA_OX, heavy2_y*2+MAPA_OY);
}

// el heavy persigue al heroe de tile en tile (sin pathfinding), se mueve cada 16 frames
// si coincide con el heroe y inv_timer==0, inflige dano y activa invulnerabilidad heroe
void mueve_heavy(void) {
    unsigned char nx, ny;
    if (!heavy_active) return;                                      // solo si esta vivo
    heavy_mov++;
    if (heavy_mov < 16) return;                                     // un paso cada 16 frames
    heavy_mov = 0;
    render_tile(mapa_trabajo[heavy_y*ancho_mapa+heavy_x], heavy_x, heavy_y); // borra el sprite de su posicion actual
    nx = heavy_x; ny = heavy_y;
    if (heavy_x < hx) nx++;                                         // heroe a la derecha -> avanza derecha
    else if (heavy_x > hx) nx--;                                    // heroe a la izquierda -> avanza izquierda
    else if (heavy_y < hy) ny++;                                    // heroe abajo -> avanza abajo
    else if (heavy_y > hy) ny--;                                    // heroe arriba -> avanza arriba
    if (!es_solido(mapa_trabajo[ny*ancho_mapa+nx])) {
        heavy_x = nx; heavy_y = ny;                                 // solo mueve si no es tile solido
    }
    if (heavy_x == hx && heavy_y == hy && inv_timer == 0) {         // colision con el heroe sin invulnerabilidad
        vidas = (vidas >= enemy_dmg) ? vidas - enemy_dmg : 0;       // resta vida sin bajar de 0
        sonido_danio();
        render_hud_vidas();
        inv_timer = 40;                                              // activa 40 frames de invulnerabilidad
        if (vidas == 0) cambiar_pantalla(PANTALLA_GAME_OVER);        // comprueba game over
    }
}

// el heavy2 persigue al heroe de tile en tile (sin pathfinding), se mueve cada 16 frames
// si coincide con el heroe y inv_timer==0, inflige dano y activa invulnerabilidad heroe
void mueve_heavy2(void) {
    unsigned char nx, ny;
    if (!heavy2_active) return;                                      // solo si esta vivo
    heavy2_mov++;
    if (heavy2_mov < 16) return;                                     // un paso cada 16 frames
    heavy2_mov = 0;
    render_tile(mapa_trabajo[heavy2_y*ancho_mapa+heavy2_x], heavy2_x, heavy2_y); // borra el sprite de su posicion actual
    nx = heavy2_x; ny = heavy2_y;
    if (heavy2_x < hx) nx++;                                         // heroe a la derecha -> avanza derecha
    else if (heavy2_x > hx) nx--;                                    // heroe a la izquierda -> avanza izquierda
    else if (heavy2_y < hy) ny++;                                    // heroe abajo -> avanza abajo
    else if (heavy2_y > hy) ny--;                                    // heroe arriba -> avanza arriba
    if (!es_solido(mapa_trabajo[ny*ancho_mapa+nx])) {
        heavy2_x = nx; heavy2_y = ny;                                 // solo mueve si no es tile solido
    }
    if (heavy2_x == hx && heavy2_y == hy && inv_timer == 0) {         // colision con el heroe sin invulnerabilidad
        vidas = (vidas >= enemy_dmg) ? vidas - enemy_dmg : 0;         // resta vida sin bajar de 0
        sonido_danio();
        render_hud_vidas();
        inv_timer = 40;                                               // activa 40 frames de invulnerabilidad
        if (vidas == 0) cambiar_pantalla(PANTALLA_GAME_OVER);         // comprueba game over
    }
}

void animacion_octo1(void) {
    if (!octo1_active) return;
    switch(octo1_dir) {
        case 0: put_sprite_x16(enmy_octoUp,    octo1_x*2+MAPA_OX, octo1_y*2+MAPA_OY); break;
        case 1: put_sprite_x16(enmy_octoRight, octo1_x*2+MAPA_OX, octo1_y*2+MAPA_OY); break;
        case 2: put_sprite_x16(enmy_octoDown,  octo1_x*2+MAPA_OX, octo1_y*2+MAPA_OY); break;
        case 3: put_sprite_x16(enmy_octoLeft,  octo1_x*2+MAPA_OX, octo1_y*2+MAPA_OY); break;
    }
}

// el octo1 camina en linea recta, cambia de direccion aleatoriamente al chocar o octo_steps == 0.
// dispara en su direccion de movimiento cada vez que avanza un tile
void mueve_octo1(void) {
    unsigned char nx, ny, blocked;
    if (!octo1_active) return;                                           // solo si esta vivo
    octo1_mov++;
    if (octo1_mov < 16) return;                                          // un paso cada 16 frames
    octo1_mov = 0;
    render_tile(mapa_trabajo[octo1_y*ancho_mapa+octo1_x], octo1_x, octo1_y); // borra sprite de posicion actual
    nx = octo1_x; ny = octo1_y;
    switch(octo1_dir) {                                                  // calcula posicion destino segun direccion
        case 0: if (ny > 0)            ny--; break;                      // arriba
        case 1: if (nx < ancho_mapa-1) nx++; break;                      // derecha
        case 2: if (ny < alto_mapa-1)  ny++; break;                      // abajo
        case 3: if (nx > 0)            nx--; break;                      // izquierda
    }
    blocked = (nx == octo1_x && ny == octo1_y) || es_solido(mapa_trabajo[ny*ancho_mapa+nx]); // borde o tile solido
    if (!blocked) {
        octo1_x = nx; octo1_y = ny;                                      // mueve octo
        octo1_steps--;
        if (!octo1_shot_active) {                                        // lanza proyectil si no hay uno en vuelo
            octo1_shot_active = 1;
            octo1_shot_x = octo1_x; octo1_shot_y = octo1_y;              // proyectil sale en la posicion actual
            octo1_shot_dir = octo1_dir;                                  // misma direccion del octo
            octo1_shot_mov = 0;
        }
    }
    if (blocked) {                                                       // solido: nueva dir y pasos aleatorios
        octo1_dir = (rand_next() >> 6) & 3;
        octo1_steps = 2 + (rand_next() & 3);
    } else if (octo1_steps == 0) {                                       // no mas pasos para avanzar: nueva dir y pasos aleatorios
        octo1_dir = (rand_next() >> 6) & 3;
        octo1_steps = 2 + (rand_next() & 3);
    }
    if (octo1_x == hx && octo1_y == hy && inv_timer == 0) {             // colision con el heroe sin invulnerabilidad
        vidas = (vidas >= enemy_dmg) ? vidas - enemy_dmg : 0;           // resta vida sin bajar de 0
        sonido_danio();
        render_hud_vidas();
        inv_timer = 40;                                                  // activa 40 frames de invulnerabilidad
        if (vidas == 0) cambiar_pantalla(PANTALLA_GAME_OVER);            // comprueba gameover
    }
}

void animacion_octo2(void) {
    if (!octo2_active) return;
    switch(octo2_dir) {
        case 0: put_sprite_x16(enmy_octoUp,    octo2_x*2+MAPA_OX, octo2_y*2+MAPA_OY); break;
        case 1: put_sprite_x16(enmy_octoRight, octo2_x*2+MAPA_OX, octo2_y*2+MAPA_OY); break;
        case 2: put_sprite_x16(enmy_octoDown,  octo2_x*2+MAPA_OX, octo2_y*2+MAPA_OY); break;
        case 3: put_sprite_x16(enmy_octoLeft,  octo2_x*2+MAPA_OX, octo2_y*2+MAPA_OY); break;
    }
}

// el octo2 camina en linea recta, cambia de direccion aleatoriamente al chocar o octo_steps == 0.
// dispara en su direccion de movimiento cada vez que avanza un tile
void mueve_octo2(void) {
    unsigned char nx, ny, blocked;
    if (!octo2_active) return;                         // solo si esta vivo
    octo2_mov++;
    if (octo2_mov < 16) return;                        // un paso cada 16 frames
    octo2_mov = 0;
    render_tile(mapa_trabajo[octo2_y*ancho_mapa+octo2_x], octo2_x, octo2_y);  // borra sprite de posicion actual
    nx = octo2_x; ny = octo2_y;
    switch(octo2_dir) {                                // calcula posicion destino segun direccion
        case 0: if (ny > 0)             ny--; break;   // arriba
        case 1: if (nx < ancho_mapa-1) nx++; break;    // derecha
        case 2: if (ny < alto_mapa-1)  ny++; break;    // abajo
        case 3: if (nx > 0)             nx--; break;   // izquierda
    }
    blocked = (nx == octo2_x && ny == octo2_y) || es_solido(mapa_trabajo[ny*ancho_mapa+nx]); // borde o tile solido
    if (!blocked) {
        octo2_x = nx; octo2_y = ny;   // mueve octo
        octo2_steps--;
        if (!octo2_shot_active) {     // lanza proyectil si no hay uno en vuelo
            octo2_shot_active = 1;
            octo2_shot_x = octo2_x; octo2_shot_y = octo2_y;    // proyectil sale en la posicion actual
            octo2_shot_dir = octo2_dir;                        // misma direccion del octo
            octo2_shot_mov = 0;
        }
    }
    if (blocked) {                                             // solido: nueva dir y pasos aleatorios
        octo2_dir = (rand_next() >> 6) & 3;
        octo2_steps = 2 + (rand_next() & 3);
    } else if (octo2_steps == 0) {                             // no mas pasos para avanzar: nueva dir y pasos aleatorios
        octo2_dir = (rand_next() >> 6) & 3;
        octo2_steps = 2 + (rand_next() & 3);
    }
    if (octo2_x == hx && octo2_y == hy && inv_timer == 0) {              // colision con el heroe sin invulnerabilidad
        vidas = (vidas >= enemy_dmg) ? vidas - enemy_dmg : 0;            // resta vida sin bajar de 0
        sonido_danio();
        render_hud_vidas();
        inv_timer = 40;                                                  // activa 40 frames de invulnerabilidad
        if (vidas == 0) cambiar_pantalla(PANTALLA_GAME_OVER);            // comprueba gameover
    }
}

void animacion_octo1_shot(void) {
    if (!octo1_shot_active) return;
    put_sprite_x8_noclr(enmy_octoShot, octo1_shot_x*2+MAPA_OX, octo1_shot_y*2+MAPA_OY);
}

// el disparo del octo1 viaja en linea recta, avanza por la pantalla hasta que choca con algo o llega al borde
void mueve_octo1_shot(void) {
    unsigned char nx, ny;
    if (!octo1_shot_active) return;                                                               // solo si el disparo esta activo
    octo1_shot_mov++;
    if (octo1_shot_mov < 6) return;                                                               // un paso cada 6 frames
    octo1_shot_mov = 0;
    render_tile(mapa_trabajo[octo1_shot_y*ancho_mapa+octo1_shot_x], octo1_shot_x, octo1_shot_y);  // borra sprite de posicion actual

    if (octo1_shot_dir == 0 && octo1_shot_y == 0)             { octo1_shot_active = 0; return; }  // borde superior: borra el disparo
    if (octo1_shot_dir == 3 && octo1_shot_x == 0)             { octo1_shot_active = 0; return; }  // borde izquierdo: borra el disparo

    nx = octo1_shot_x; ny = octo1_shot_y;                                                         // copia posicion actual como base del calculo

    switch(octo1_shot_dir) {                                                                      // calcula posicion siguiente segun direccion
        case 0: ny--; break;                                                                      // arriba
        case 1: nx++; break;                                                                      // derecha
        case 2: ny++; break;                                                                      // abajo
        case 3: nx--; break;                                                                      // izquierda
    }
    if (nx >= ancho_mapa || ny >= alto_mapa || es_solido(mapa_trabajo[ny*ancho_mapa+nx])) {       // disparo octo llega final del mapa o choca contra algo solido
        octo1_shot_active = 0;
        return;
    }

    octo1_shot_x = nx; octo1_shot_y = ny;                                                         // actualiza posicion del disparo

    if (octo1_shot_x == hx && octo1_shot_y == hy && inv_timer == 0) {                             // golpea hero
        octo1_shot_active = 0;
        render_tile(mapa_trabajo[octo1_shot_y*ancho_mapa+octo1_shot_x], octo1_shot_x, octo1_shot_y); // restaura tile bajo el disparo
        render_hero(hx*2, hy*2);
        vidas = (vidas >= enemy_dmg) ? vidas - enemy_dmg : 0;                                     // resta vida sin bajar de 0
        sonido_danio();
        render_hud_vidas();
        inv_timer = 40;                                                                           // activa 40 frames de invulnerabilidad
        if (vidas == 0) cambiar_pantalla(PANTALLA_GAME_OVER);                                     // comprueba gameover
    }
}

void animacion_octo2_shot(void) {
    if (!octo2_shot_active) return;
    put_sprite_x8_noclr(enmy_octoShot, octo2_shot_x*2+MAPA_OX, octo2_shot_y*2+MAPA_OY);
}

// el disparo del octo2 viaja en linea recta, avanza por la pantalla hasta que choca con algo o llega al borde
void mueve_octo2_shot(void) {
    unsigned char nx, ny;
    if (!octo2_shot_active) return;                                                                // solo si el disparo esta activo
    octo2_shot_mov++;
    if (octo2_shot_mov < 6) return;                                                                // un paso cada 6 frames
    octo2_shot_mov = 0;
    render_tile(mapa_trabajo[octo2_shot_y*ancho_mapa+octo2_shot_x], octo2_shot_x, octo2_shot_y);   // borra sprite de posicion actual
    if (octo2_shot_dir == 0 && octo2_shot_y == 0)        { octo2_shot_active = 0; return; }        // borde superior: borra el disparo
    if (octo2_shot_dir == 3 && octo2_shot_x == 0)        { octo2_shot_active = 0; return; }        // borde izquierdo: borra el disparo
    
    nx = octo2_shot_x; ny = octo2_shot_y;                                                          // copia posicion actual como base del calculo
    
    switch(octo2_shot_dir) {                                                                       // calcula posicion siguiente segun direccion
        case 0: ny--; break;                                                                       // arriba
        case 1: nx++; break;                                                                       // derecha
        case 2: ny++; break;                                                                       // abajo
        case 3: nx--; break;                                                                       // izquierda
    }
    if (nx >= ancho_mapa || ny >= alto_mapa || es_solido(mapa_trabajo[ny*ancho_mapa+nx])) {        // disparo octo llega final del mapa o choca contra algo solido
        octo2_shot_active = 0;
        return;
    }
    
    octo2_shot_x = nx; octo2_shot_y = ny;                                                          // actualiza posicion del disparo

    if (octo2_shot_x == hx && octo2_shot_y == hy && inv_timer == 0) {                              // golpea hero
        octo2_shot_active = 0;
        render_tile(mapa_trabajo[octo2_shot_y*ancho_mapa+octo2_shot_x], octo2_shot_x, octo2_shot_y);  // restaura tile bajo el disparo
        render_hero(hx*2, hy*2);
        vidas = (vidas >= enemy_dmg) ? vidas - enemy_dmg : 0;                                      // resta vida sin bajar de 0
        sonido_danio();
        render_hud_vidas();
        inv_timer = 40;                                                                            // activa 40 frames de invulnerabilidad
        if (vidas == 0) cambiar_pantalla(PANTALLA_GAME_OVER);                                      // comprueba gameover
    }
}

void animacion_boss(void) { // movimiento de los fuegos que rodean al boss
    if (!boss_active || mapa_actual != 70) return;
    if (boss_form == 0) {                                        // fuegos forma x
        put_sprite_x16(enmy_bossFire, (boss_x-1)*2+MAPA_OX, (boss_y-1)*2+MAPA_OY);
        put_sprite_x16(enmy_bossFire, (boss_x+1)*2+MAPA_OX, (boss_y-1)*2+MAPA_OY);
        put_sprite_x16(enmy_bossFire, (boss_x-1)*2+MAPA_OX, (boss_y+1)*2+MAPA_OY);
        put_sprite_x16(enmy_bossFire, (boss_x+1)*2+MAPA_OX, (boss_y+1)*2+MAPA_OY);
    } else {                                                     // fuegos forma +
        put_sprite_x16(enmy_bossFire,  boss_x*2   +MAPA_OX, (boss_y-1)*2+MAPA_OY);
        put_sprite_x16(enmy_bossFire, (boss_x-1)*2+MAPA_OX,  boss_y*2   +MAPA_OY);
        put_sprite_x16(enmy_bossFire, (boss_x+1)*2+MAPA_OX,  boss_y*2   +MAPA_OY);
        put_sprite_x16(enmy_bossFire,  boss_x*2   +MAPA_OX, (boss_y+1)*2+MAPA_OY);
    }
    put_sprite_x16(enmy_boss, boss_x*2+MAPA_OX, boss_y*2+MAPA_OY);
}

void animacion_boss_shot(void) {
    if (!boss_shot_active) return;
    put_sprite_x16(enmy_bossFire, boss_shot_x*2+MAPA_OX, boss_shot_y*2+MAPA_OY);
}

void mueve_boss_shot(void) { // basicamente misma rutina de movimiento que los disparos octos
    unsigned char nx, ny;
    if (!boss_shot_active) return;                                                                 // solo si el disparo esta activo
    boss_shot_mov++;
    if (boss_shot_mov < 6) return;                                                                 // un paso cada 6 frames
    boss_shot_mov = 0;
    render_tile(mapa_trabajo[boss_shot_y*ancho_mapa+boss_shot_x], boss_shot_x, boss_shot_y);       // borra sprite de posicion actual
    if (boss_shot_dir == 0 && boss_shot_y == 0) { boss_shot_active = 0; return; }                  // borde superior borra el disparo
    if (boss_shot_dir == 3 && boss_shot_x == 0) { boss_shot_active = 0; return; }                  // borde izquierdo borra el disparo
    
    nx = boss_shot_x; ny = boss_shot_y;                                                            // posicion actual como punto de partida
    
    switch(boss_shot_dir) {                                                                        // calcula posicion siguiente segun direccion
        case 0: ny--; break;                                                                       // arriba
        case 1: nx++; break;                                                                       // derecha
        case 2: ny++; break;                                                                       // abajo
        case 3: nx--; break;                                                                       // izquierda
    }
    if (nx >= ancho_mapa || ny >= alto_mapa || es_solido(mapa_trabajo[ny*ancho_mapa+nx])) {        // disparo boss llega final del mapa o choca contra algo solido
        boss_shot_active = 0;
        return;
    }
    boss_shot_x = nx; boss_shot_y = ny;                                                            // actualiza posicion del disparo
    if (boss_shot_x == hx && boss_shot_y == hy && inv_timer == 0) {                                // colision disparo con hero
        boss_shot_active = 0;
        render_tile(mapa_trabajo[boss_shot_y*ancho_mapa+boss_shot_x], boss_shot_x, boss_shot_y);   // restaura tile bajo el disparo
        render_hero(hx*2, hy*2);
        vidas = (vidas >= enemy_dmg) ? vidas - enemy_dmg : 0;                                      // resta vida sin bajar de 0
        sonido_danio();
        render_hud_vidas();
        inv_timer = 40;                                                                            // activa 40 frames de invulnerabilidad
        if (vidas == 0) cambiar_pantalla(PANTALLA_GAME_OVER);                                      // comprueba gameover
    }
}

void check_boss_contact(void) {
    unsigned char dx, dy, hit;
    if (!boss_active || mapa_actual != 70 || inv_timer != 0) return;  // sin invulnerabilidad activa
    dx = (hx >= boss_x) ? hx - boss_x : boss_x - hx;                  // distancia horizontal absoluta heroe-boss
    dy = (hy >= boss_y) ? hy - boss_y : boss_y - hy;                  // distancia vertical absoluta heroe-boss
    hit = 0;
    if (dx == 0 && dy == 0) hit = 1;                                  // colision
    else if (boss_form == 0 && dx == 1 && dy == 1) hit = 1;           // form 0: hit en diagonal
    else if (boss_form == 1 && ((dx == 1 && dy == 0) || (dx == 0 && dy == 1))) hit = 1; // form 1: hit cruz
    if (hit) {
        vidas = (vidas >= enemy_dmg) ? vidas - enemy_dmg : 0;         // resta vida sin bajar de 0
        sonido_danio();
        render_hud_vidas();                                           // update vidas hud
        inv_timer = 40;                                               // hit invul (40f)
        if (vidas == 0) cambiar_pantalla(PANTALLA_GAME_OVER);         // check gameover
    }
}

// boss alterna cada 20 frames entre dos patrones (boss_form XOR 1):
//   form 0: fuego en diagonales
//   form 1: fuego en cruz
// se mueve hacia el heroe en un rango del mapa (x:3-12, y:2-6).
// dispara horizontal en form 0 y vertical en form 1
void mueve_boss(void) {
    unsigned char ox, oy;                                    // posicion anterior del boss (para borrar tiles)
    if (!boss_active || mapa_actual != 70) return;           // solo actua en dngn_g2
    boss_mov++;
    if (boss_mov < 20) return;                               // un paso cada 20 frames
    boss_mov = 0;
    ox = boss_x; oy = boss_y;                                // guarda posicion antes de mover
    erase_boss_tiles(ox, oy);                                // restaura los tiles que ocupaba
    boss_form ^= 1;                                          // alterna forma de disparo: 0=horizontal 1=vertical
    if (boss_x < hx && boss_x < 12) boss_x++;                // persigue al heroe en X (limite derecho: col 12)
    else if (boss_x > hx && boss_x > 3)  boss_x--;           // persigue al heroe en X (limite izquierdo: col 3)
    if (boss_y < hy && boss_y < 6)  boss_y++;                // persigue al heroe en Y (limite inferior: fila 6)
    else if (boss_y > hy && boss_y > 2)  boss_y--;           // persigue al heroe en Y (limite superior: fila 2)
    if (!boss_shot_active) {                                 // lanza proyectil si no hay uno
        boss_shot_active = 1;
        boss_shot_x = boss_x;                                // el proyectil origina en la posicion actual del boss
        boss_shot_y = boss_y;
        if (boss_form == 0) {
            boss_shot_dir = (hx > boss_x) ? 1 : 3;           // forma 0: dispara izq(3) o der(1) segun donde este el heroe
        } else {
            boss_shot_dir = (hy > boss_y) ? 2 : 0;           // forma 1: dispara abj(2) o arr(0) segun donde este el heroe
        }
        boss_shot_mov = 0;                                   // reinicia contador de velocidad del proyectil
    }
}
