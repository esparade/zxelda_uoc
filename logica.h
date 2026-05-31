// Fuerza el atributo de color amarillo en el sprite de la llave para hacerla visible.
void anima_llave(void) {
    if (!llave_en_mapa || mapa_actual != llave_mapa) return;
    item_llave[16] = 6;
    item_llave[17] = 6;
    item_llave[18] = 6;
    item_llave[19] = 6;
    render_tile(15, llave_pos % ancho_mapa, llave_pos / ancho_mapa);
}

// Tiles solidos (bloquean movimiento): arbol(1), matorral(2), bloque(3), pared(5),
// puerta_izq(6), puerta_der(7), puerta_arr(8), puerta_cerrada(12).
// Son pasables: suelo(0), baldosa(4), void(9), fuego(13) e items(14,15,16).
int es_solido(unsigned char tile) {
    return tile==1 || tile==2 || tile==3 || tile==5 || tile==6 || tile==7 || tile==8 || tile==12;
}

// Abre el pasillo superior de mapa3 si el heroe tiene la llave y esta en fila 1
// frente al hueco (cols 7-8). Consume la llave, sustituye PC(12) por VO(9) y activa sonido.
void check_puerta6(void) {
    if (mapa_actual != 3) return;
    if (puerta6_abierta) return;
    if (!tiene_llave) return;
    if (hy != 1) return;
    if (hx != 7 && hx != 8) return;
    puerta6_abierta = 1;
    tiene_llave = 0;
    mapa_trabajo[7] = 9;
    mapa_trabajo[8] = 9;
    render_tile(9, 7, 0);
    render_tile(9, 8, 0);
    render_hud_llave();
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

            if (anim > 1) {
                anim = 0;
            }
            break;

        case 1: //anim plyr rgh
            switch(anim) {
                case 0:
                    put_sprite_x16_mask_ink(plyr_rghA,hx*2+MAPA_OX,hy*2+MAPA_OY);
                    break;
                case 1:
                    put_sprite_x16_mask_ink(plyr_rghB,hx*2+MAPA_OX,hy*2+MAPA_OY);
                    break;
            }
            anim++;

            if (anim > 1) {
                anim = 0;
            }
            break;

        case 2: //anim plyr dwn
            switch(anim) {
                case 0:
                    put_sprite_x16_mask_ink(plyr_dwnA,hx*2+MAPA_OX,hy*2+MAPA_OY);
                    break;
                case 1:
                    put_sprite_x16_mask_ink(plyr_dwnB,hx*2+MAPA_OX,hy*2+MAPA_OY);
                    break;
            }
            anim++;

            if (anim > 1) {
                anim = 0;
            }
            break;

        case 3: //anim plyr lft
            switch(anim) {
                case 0:
                    put_sprite_x16_mask_ink(plyr_lftA,hx*2+MAPA_OX,hy*2+MAPA_OY);
                    break;
                case 1:
                    put_sprite_x16_mask_ink(plyr_lftB,hx*2+MAPA_OX,hy*2+MAPA_OY);
                    break;
            }
            anim++;

            if (anim > 1) {
                anim = 0;
            }
            break;
    }
}

// Recalcula el indice plano hmap = hy*ancho_mapa+hx. Llamar tras cada cambio de hx/hy.
void calculo_frame(void) {
    hmap = hy*ancho_mapa+hx;
}

// Gestiona los teletransportadores especiales (tile VO/9 en posicion fija).
// tienda(mapa1)→cueva(mapa5), mazmorra_mapa→mapa3, mapa3→mazmorra_mapa, cueva→mapa1.
// La mazmorra de destino es aleatoria cada partida (randomiza_tienda).
void check_warp(void) { //tienda a cueva (posicion aleatoria cada partida)
    if (mapa_actual == tienda_mapa && mapa_trabajo[hmap] == 9) {
        mapa_actual = 5;
        hx = 7;
        hy = 7;
        carga_datos_mapa();
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
    if (mapa_actual == mazmorra_mapa && mapa_trabajo[hmap] == 9) {
        mapa_actual = 3;
        hx = 7;
        hy = 7;
        carga_datos_mapa();
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
    if (mapa_actual == 3 && hy == alto_mapa-1 && mapa_trabajo[hmap] == 9) {
        mapa_actual = mazmorra_mapa;
        hx = mazmorra_pos % ancho_mapa;
        hy = mazmorra_pos / ancho_mapa + 1;
        carga_datos_mapa();
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
    if (mapa_actual == 5 && hy == alto_mapa-1 && (hx == 7 || hx == 8)) { //salida de cueva
        mapa_actual = 1;
        hx = tienda_pos % ancho_mapa;
        hy = tienda_pos / ancho_mapa + 1;
        carga_datos_mapa();
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
            if (hy == 0) return;
            put_sprite_8x16(swrd_up, hx*2+MAPA_OX, hy*2-2+MAPA_OY);
            break;
        case 1: // derecha
            if (hx == ancho_mapa-1) return;
            put_sprite_16x8(swrd_rgh, hx*2+2+MAPA_OX, hy*2+MAPA_OY);
            break;
        case 2: // abajo
            if (hy == alto_mapa-1) return;
            put_sprite_8x16(swrd_dwn, hx*2+MAPA_OX, hy*2+2+MAPA_OY);
            break;
        case 3: // izquierda
            if (hx == 0) return;
            put_sprite_16x8(swrd_lft, hx*2-2+MAPA_OX, hy*2+MAPA_OY);
            break;
    }
}

void sword_erase(void) {
    switch(vista) {
        case 0:
            if (hy > 0) render_tile(mapa_trabajo[(hy-1)*ancho_mapa+hx], hx, hy-1);
            break;
        case 1:
            if (hx < ancho_mapa-1) render_tile(mapa_trabajo[hy*ancho_mapa+hx+1], hx+1, hy);
            break;
        case 2:
            if (hy < alto_mapa-1) render_tile(mapa_trabajo[(hy+1)*ancho_mapa+hx], hx, hy+1);
            break;
        case 3:
            if (hx > 0) render_tile(mapa_trabajo[hy*ancho_mapa+hx-1], hx-1, hy);
            break;
    }
}

// Suelta un item en la posicion del enemigo eliminado.
// En mapa3 siempre suelta la llave (necesaria para abrir puerta6); en otro mapa, un corazon.
void drop_item(unsigned char ix, unsigned char iy) {
    unsigned char pos = iy * ancho_mapa + ix;
    if (mapa_actual == 3) {
        llave_mapa = mapa_actual;
        llave_pos  = pos;
        tile_bajo_llave = mapa_trabajo[pos];
        mapa_trabajo[pos] = 15;
        llave_en_mapa = 1;
    } else {
        corazon_mapa = mapa_actual;
        corazon_pos  = pos;
        tile_bajo_corazon = mapa_trabajo[pos];
        mapa_trabajo[pos] = 14;
        corazon_en_mapa = 1;
    }
}

void drop_power(unsigned char ix, unsigned char iy) {
    unsigned char pos = iy * ancho_mapa + ix;
    power_mapa = mapa_actual;
    power_pos  = pos;
    tile_bajo_power = mapa_trabajo[pos];
    mapa_trabajo[pos] = 16;
    power_en_mapa = 1;
}

// Al recoger el item_power: +1 fuerza (max 9) y duplica el dano de enemigos (aumenta dificultad).
// Reinicia la pantalla de juego para refrescar el estado sin perder pts ni enemy_dmg acumulado.
void check_power(void) {
    unsigned char saved_pts, new_dmg, saved_fuerza;
    if (!power_en_mapa) return;
    if (mapa_actual != power_mapa) return;
    if (hmap != power_pos) return;
    saved_pts = pts;
    saved_fuerza = fuerza;
    new_dmg = enemy_dmg * 2;
    cambiar_pantalla(PANTALLA_JUEGO);
    pts = saved_pts;
    enemy_dmg = new_dmg;
    fuerza = (saved_fuerza < 9) ? saved_fuerza + 1 : 9;
    render_hud_pts();
    render_hud_fuerza();
}

void erase_boss_tiles(unsigned char bx, unsigned char by) {
    unsigned char r, c;
    for (r = by-1; r <= by+1; r++)
        for (c = bx-1; c <= bx+1; c++)
            render_tile(mapa_trabajo[r*ancho_mapa+c], c, r);
}

// Comprueba si el tile delante del heroe contiene un enemigo y lo elimina con 1 golpe.
// El boss necesita boss_hp golpes; los demas enemigos mueren de 1 y sueltan item con prob 50%.
void check_sword_hit(void) {
    unsigned char tx, ty;
    switch(vista) {
        case 0: tx=hx;   ty=hy-1; break;
        case 1: tx=hx+1; ty=hy;   break;
        case 2: tx=hx;   ty=hy+1; break;
        case 3: tx=hx-1; ty=hy;   break;
    }
    if (heavy_active && heavy_x == tx && heavy_y == ty) {
        heavy_active = 0;
        pts += 3; render_hud_pts();
        if (rand_next() & 1) drop_item(heavy_x, heavy_y);
        render_tile(mapa_trabajo[heavy_y*ancho_mapa+heavy_x], heavy_x, heavy_y);
    }
    if (heavy2_active && heavy2_x == tx && heavy2_y == ty) {
        heavy2_active = 0;
        pts += 3; render_hud_pts();
        if (rand_next() & 1) drop_item(heavy2_x, heavy2_y);
        render_tile(mapa_trabajo[heavy2_y*ancho_mapa+heavy2_x], heavy2_x, heavy2_y);
    }
    if (octo1_active && octo1_x == tx && octo1_y == ty) {
        octo1_active = 0;
        pts += 1; render_hud_pts();
        if (rand_next() & 1) drop_item(octo1_x, octo1_y);
        render_tile(mapa_trabajo[octo1_y*ancho_mapa+octo1_x], octo1_x, octo1_y);
    }
    if (octo2_active && octo2_x == tx && octo2_y == ty) {
        octo2_active = 0;
        pts += 1; render_hud_pts();
        if (rand_next() & 1) drop_item(octo2_x, octo2_y);
        render_tile(mapa_trabajo[octo2_y*ancho_mapa+octo2_x], octo2_x, octo2_y);
    }
    if (boss_active && boss_y == ty && boss_x == tx) {
        boss_hp--;
        if (boss_hp == 0) {
            boss_active = 0;
            pts += 10; render_hud_pts();
            erase_boss_tiles(boss_x, boss_y);
            drop_power(boss_x, boss_y);
        }
    }
}

void check_corazon(void) {
    if (!corazon_en_mapa) return;
    if (mapa_actual != corazon_mapa) return;
    if (hmap != corazon_pos) return;
    corazon_en_mapa = 0;
    sonido_corazon();
    if (vidas < NUMERO_DE_VIDAS) {
        vidas++;
        render_hud_vidas();
    }
    mapa_trabajo[corazon_pos] = tile_bajo_corazon;
    render_tile(tile_bajo_corazon, corazon_pos % ancho_mapa, corazon_pos / ancho_mapa);
    render_hero(hx*2, hy*2);
}

void check_llave(void) {
    if (!llave_en_mapa) return;
    if (mapa_actual != llave_mapa) return;
    if (hmap != llave_pos) return;
    llave_en_mapa = 0;
    tiene_llave = 1;
    sonido_llave();
    mapa_trabajo[llave_pos] = tile_bajo_llave;
    render_tile(tile_bajo_llave, llave_pos % ancho_mapa, llave_pos / ancho_mapa);
    render_hud_llave();
    render_hero(hx*2, hy*2);
}

void update_attack(void) {
    if (attack_timer == 0) return;
    sword_render();
    attack_timer--;
    if (attack_timer == 0) sword_erase();
}

void render_npc(void) {
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

void animacion_heavy(void) {
    if (!heavy_active) return;
    put_sprite_x16(enmy_hvy, heavy_x*2+MAPA_OX, heavy_y*2+MAPA_OY);
}

void animacion_heavy2(void) {
    if (!heavy2_active) return;
    put_sprite_x16(enmy_hvy, heavy2_x*2+MAPA_OX, heavy2_y*2+MAPA_OY);
}

// El heavy persigue al heroe tile a tile (sin pathfinding), se mueve cada 16 frames.
// Si coincide con el heroe y inv_timer==0, inflige dano y activa invulnerabilidad.
void mueve_heavy(void) {
    unsigned char nx, ny;
    if (!heavy_active) return;
    heavy_mov++;
    if (heavy_mov < 16) return;
    heavy_mov = 0;
    render_tile(mapa_trabajo[heavy_y*ancho_mapa+heavy_x], heavy_x, heavy_y);
    nx = heavy_x; ny = heavy_y;
    if (heavy_x < hx) nx++;
    else if (heavy_x > hx) nx--;
    else if (heavy_y < hy) ny++;
    else if (heavy_y > hy) ny--;
    if (!es_solido(mapa_trabajo[ny*ancho_mapa+nx])) {
        heavy_x = nx; heavy_y = ny;
    }
    if (heavy_x == hx && heavy_y == hy && inv_timer == 0) {
        vidas = (vidas >= enemy_dmg) ? vidas - enemy_dmg : 0;
        sonido_danio();
        render_hud_vidas();
        inv_timer = 40;
        if (vidas == 0) cambiar_pantalla(PANTALLA_GAME_OVER);
    }
}

void mueve_heavy2(void) {
    unsigned char nx, ny;
    if (!heavy2_active) return;
    heavy2_mov++;
    if (heavy2_mov < 16) return;
    heavy2_mov = 0;
    render_tile(mapa_trabajo[heavy2_y*ancho_mapa+heavy2_x], heavy2_x, heavy2_y);
    nx = heavy2_x; ny = heavy2_y;
    if (heavy2_x < hx) nx++;
    else if (heavy2_x > hx) nx--;
    else if (heavy2_y < hy) ny++;
    else if (heavy2_y > hy) ny--;
    if (!es_solido(mapa_trabajo[ny*ancho_mapa+nx])) {
        heavy2_x = nx; heavy2_y = ny;
    }
    if (heavy2_x == hx && heavy2_y == hy && inv_timer == 0) {
        vidas = (vidas >= enemy_dmg) ? vidas - enemy_dmg : 0;
        sonido_danio();
        render_hud_vidas();
        inv_timer = 40;
        if (vidas == 0) cambiar_pantalla(PANTALLA_GAME_OVER);
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

// El octo camina en linea recta, cambia de direccion aleatoriamente al chocar o al agotar octo_steps.
// Dispara un proyectil en su direccion de movimiento cada vez que avanza un tile.
void mueve_octo1(void) {
    unsigned char nx, ny, blocked;
    if (!octo1_active) return;
    octo1_mov++;
    if (octo1_mov < 16) return;
    octo1_mov = 0;
    render_tile(mapa_trabajo[octo1_y*ancho_mapa+octo1_x], octo1_x, octo1_y);
    nx = octo1_x; ny = octo1_y;
    switch(octo1_dir) {
        case 0: if (ny > 0)             ny--; break;
        case 1: if (nx < ancho_mapa-1) nx++; break;
        case 2: if (ny < alto_mapa-1)  ny++; break;
        case 3: if (nx > 0)             nx--; break;
    }
    blocked = (nx == octo1_x && ny == octo1_y) || es_solido(mapa_trabajo[ny*ancho_mapa+nx]);
    if (!blocked) {
        octo1_x = nx; octo1_y = ny;
        octo1_steps--;
        if (!octo1_shot_active) {
            octo1_shot_active = 1;
            octo1_shot_x = octo1_x; octo1_shot_y = octo1_y;
            octo1_shot_dir = octo1_dir;
            octo1_shot_mov = 0;
        }
    }
    if (blocked) {
        octo1_dir = (rand_next() >> 6) & 3;
        octo1_steps = 2 + (rand_next() & 3);
    } else if (octo1_steps == 0) {
        octo1_dir = (rand_next() >> 6) & 3;
        octo1_steps = 2 + (rand_next() & 3);
    }
    if (octo1_x == hx && octo1_y == hy && inv_timer == 0) {
        vidas = (vidas >= enemy_dmg) ? vidas - enemy_dmg : 0;
        sonido_danio();
        render_hud_vidas();
        inv_timer = 40;
        if (vidas == 0) cambiar_pantalla(PANTALLA_GAME_OVER);
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

void mueve_octo2(void) {
    unsigned char nx, ny, blocked;
    if (!octo2_active) return;
    octo2_mov++;
    if (octo2_mov < 16) return;
    octo2_mov = 0;
    render_tile(mapa_trabajo[octo2_y*ancho_mapa+octo2_x], octo2_x, octo2_y);
    nx = octo2_x; ny = octo2_y;
    switch(octo2_dir) {
        case 0: if (ny > 0)             ny--; break;
        case 1: if (nx < ancho_mapa-1) nx++; break;
        case 2: if (ny < alto_mapa-1)  ny++; break;
        case 3: if (nx > 0)             nx--; break;
    }
    blocked = (nx == octo2_x && ny == octo2_y) || es_solido(mapa_trabajo[ny*ancho_mapa+nx]);
    if (!blocked) {
        octo2_x = nx; octo2_y = ny;
        octo2_steps--;
        if (!octo2_shot_active) {
            octo2_shot_active = 1;
            octo2_shot_x = octo2_x; octo2_shot_y = octo2_y;
            octo2_shot_dir = octo2_dir;
            octo2_shot_mov = 0;
        }
    }
    if (blocked) {
        octo2_dir = (rand_next() >> 6) & 3;
        octo2_steps = 2 + (rand_next() & 3);
    } else if (octo2_steps == 0) {
        octo2_dir = (rand_next() >> 6) & 3;
        octo2_steps = 2 + (rand_next() & 3);
    }
    if (octo2_x == hx && octo2_y == hy && inv_timer == 0) {
        vidas = (vidas >= enemy_dmg) ? vidas - enemy_dmg : 0;
        sonido_danio();
        render_hud_vidas();
        inv_timer = 40;
        if (vidas == 0) cambiar_pantalla(PANTALLA_GAME_OVER);
    }
}

void animacion_octo1_shot(void) {
    if (!octo1_shot_active) return;
    put_sprite_x8_noclr(enmy_octoShot, octo1_shot_x*2+MAPA_OX, octo1_shot_y*2+MAPA_OY);
}

void mueve_octo1_shot(void) {
    unsigned char nx, ny;
    if (!octo1_shot_active) return;
    octo1_shot_mov++;
    if (octo1_shot_mov < 6) return;
    octo1_shot_mov = 0;
    render_tile(mapa_trabajo[octo1_shot_y*ancho_mapa+octo1_shot_x], octo1_shot_x, octo1_shot_y);
    if (octo1_shot_dir == 0 && octo1_shot_y == 0)             { octo1_shot_active = 0; return; }
    if (octo1_shot_dir == 3 && octo1_shot_x == 0)             { octo1_shot_active = 0; return; }
    nx = octo1_shot_x; ny = octo1_shot_y;
    switch(octo1_shot_dir) {
        case 0: ny--; break;
        case 1: nx++; break;
        case 2: ny++; break;
        case 3: nx--; break;
    }
    if (nx >= ancho_mapa || ny >= alto_mapa || es_solido(mapa_trabajo[ny*ancho_mapa+nx])) {
        octo1_shot_active = 0;
        return;
    }
    octo1_shot_x = nx; octo1_shot_y = ny;
    if (octo1_shot_x == hx && octo1_shot_y == hy && inv_timer == 0) {
        octo1_shot_active = 0;
        render_tile(mapa_trabajo[octo1_shot_y*ancho_mapa+octo1_shot_x], octo1_shot_x, octo1_shot_y);
        render_hero(hx*2, hy*2);
        vidas = (vidas >= enemy_dmg) ? vidas - enemy_dmg : 0;
        sonido_danio();
        render_hud_vidas();
        inv_timer = 40;
        if (vidas == 0) cambiar_pantalla(PANTALLA_GAME_OVER);
    }
}

void animacion_octo2_shot(void) {
    if (!octo2_shot_active) return;
    put_sprite_x8_noclr(enmy_octoShot, octo2_shot_x*2+MAPA_OX, octo2_shot_y*2+MAPA_OY);
}

void mueve_octo2_shot(void) {
    unsigned char nx, ny;
    if (!octo2_shot_active) return;
    octo2_shot_mov++;
    if (octo2_shot_mov < 6) return;
    octo2_shot_mov = 0;
    render_tile(mapa_trabajo[octo2_shot_y*ancho_mapa+octo2_shot_x], octo2_shot_x, octo2_shot_y);
    if (octo2_shot_dir == 0 && octo2_shot_y == 0)        { octo2_shot_active = 0; return; }
    if (octo2_shot_dir == 3 && octo2_shot_x == 0)        { octo2_shot_active = 0; return; }
    nx = octo2_shot_x; ny = octo2_shot_y;
    switch(octo2_shot_dir) {
        case 0: ny--; break;
        case 1: nx++; break;
        case 2: ny++; break;
        case 3: nx--; break;
    }
    if (nx >= ancho_mapa || ny >= alto_mapa || es_solido(mapa_trabajo[ny*ancho_mapa+nx])) {
        octo2_shot_active = 0;
        return;
    }
    octo2_shot_x = nx; octo2_shot_y = ny;
    if (octo2_shot_x == hx && octo2_shot_y == hy && inv_timer == 0) {
        octo2_shot_active = 0;
        render_tile(mapa_trabajo[octo2_shot_y*ancho_mapa+octo2_shot_x], octo2_shot_x, octo2_shot_y);
        render_hero(hx*2, hy*2);
        vidas = (vidas >= enemy_dmg) ? vidas - enemy_dmg : 0;
        sonido_danio();
        render_hud_vidas();
        inv_timer = 40;
        if (vidas == 0) cambiar_pantalla(PANTALLA_GAME_OVER);
    }
}

void animacion_boss(void) {
    if (!boss_active || mapa_actual != 6) return;
    if (boss_form == 0) {
        put_sprite_x16(enmy_bossFire, (boss_x-1)*2+MAPA_OX, (boss_y-1)*2+MAPA_OY);
        put_sprite_x16(enmy_bossFire, (boss_x+1)*2+MAPA_OX, (boss_y-1)*2+MAPA_OY);
        put_sprite_x16(enmy_bossFire, (boss_x-1)*2+MAPA_OX, (boss_y+1)*2+MAPA_OY);
        put_sprite_x16(enmy_bossFire, (boss_x+1)*2+MAPA_OX, (boss_y+1)*2+MAPA_OY);
    } else {
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

void mueve_boss_shot(void) {
    unsigned char nx, ny;
    if (!boss_shot_active) return;
    boss_shot_mov++;
    if (boss_shot_mov < 6) return;
    boss_shot_mov = 0;
    render_tile(mapa_trabajo[boss_shot_y*ancho_mapa+boss_shot_x], boss_shot_x, boss_shot_y);
    if (boss_shot_dir == 0 && boss_shot_y == 0) { boss_shot_active = 0; return; }
    if (boss_shot_dir == 3 && boss_shot_x == 0) { boss_shot_active = 0; return; }
    nx = boss_shot_x; ny = boss_shot_y;
    switch(boss_shot_dir) {
        case 0: ny--; break;
        case 1: nx++; break;
        case 2: ny++; break;
        case 3: nx--; break;
    }
    if (nx >= ancho_mapa || ny >= alto_mapa || es_solido(mapa_trabajo[ny*ancho_mapa+nx])) {
        boss_shot_active = 0;
        return;
    }
    boss_shot_x = nx; boss_shot_y = ny;
    if (boss_shot_x == hx && boss_shot_y == hy && inv_timer == 0) {
        boss_shot_active = 0;
        render_tile(mapa_trabajo[boss_shot_y*ancho_mapa+boss_shot_x], boss_shot_x, boss_shot_y);
        render_hero(hx*2, hy*2);
        vidas = (vidas >= enemy_dmg) ? vidas - enemy_dmg : 0;
        sonido_danio();
        render_hud_vidas();
        inv_timer = 40;
        if (vidas == 0) cambiar_pantalla(PANTALLA_GAME_OVER);
    }
}

void check_boss_contact(void) {
    unsigned char dx, dy, hit;
    if (!boss_active || mapa_actual != 6 || inv_timer != 0) return;
    dx = (hx >= boss_x) ? hx - boss_x : boss_x - hx;
    dy = (hy >= boss_y) ? hy - boss_y : boss_y - hy;
    hit = 0;
    if (dx == 0 && dy == 0) hit = 1;
    else if (boss_form == 0 && dx == 1 && dy == 1) hit = 1;
    else if (boss_form == 1 && ((dx == 1 && dy == 0) || (dx == 0 && dy == 1))) hit = 1;
    if (hit) {
        vidas = (vidas >= enemy_dmg) ? vidas - enemy_dmg : 0;
        sonido_danio();
        render_hud_vidas();
        inv_timer = 40;
        if (vidas == 0) cambiar_pantalla(PANTALLA_GAME_OVER);
    }
}

// El boss alterna cada 20 frames entre dos patrones (boss_form XOR 1):
//   form 0: fuego en las 4 esquinas del tile del boss (patron diagonal).
//   form 1: fuego en los 4 laterales del tile del boss (patron en cruz).
// Se mueve hacia el heroe limitandose a los tiles interiores (x:3-12, y:2-6).
// Dispara un proyectil horizontal en form 0 y vertical en form 1.
void mueve_boss(void) {
    unsigned char ox, oy;
    if (!boss_active || mapa_actual != 6) return;
    boss_mov++;
    if (boss_mov < 20) return;
    boss_mov = 0;
    ox = boss_x; oy = boss_y;
    erase_boss_tiles(ox, oy);
    boss_form ^= 1;
    if (boss_x < hx && boss_x < 12) boss_x++;
    else if (boss_x > hx && boss_x > 3) boss_x--;
    if (boss_y < hy && boss_y < 6) boss_y++;
    else if (boss_y > hy && boss_y > 2) boss_y--;
    if (!boss_shot_active) {
        boss_shot_active = 1;
        boss_shot_x = boss_x;
        boss_shot_y = boss_y;
        if (boss_form == 0) {
            boss_shot_dir = (hx > boss_x) ? 1 : 3;
        } else {
            boss_shot_dir = (hy > boss_y) ? 2 : 0;
        }
        boss_shot_mov = 0;
    }
}
