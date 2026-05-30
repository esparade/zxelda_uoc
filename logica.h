void anima_llave(void) {
    unsigned char ink;
    if (!llave_en_mapa || mapa_actual != llave_mapa) return;
    llave_anim++;
    if (llave_anim >= 28) llave_anim = 0;
    if (llave_anim & 1) return;                  // actua cada frame
    ink = (llave_anim >> 2);                     // ink de la llave
    item_llave[16] = 48 | ink;                   // paper amarillo (48) + nueva tinta
    item_llave[17] = 48 | ink;
    item_llave[18] = 48 | ink;
    item_llave[19] = 48 | ink;
    render_tile(15, llave_pos % ancho_mapa, llave_pos / ancho_mapa);
}

// Tiles solidos (bloquean movimiento): arbol(1), bloque(3), pared(5),
// puerta_izq(6), puerta_der(7), puerta_arr(8), puerta_cerrada(12).
// Son pasables: suelo(0), matorral(2), baldosa(4), void(9), fuego(13) e items(14,15).
int es_solido(unsigned char tile) {
    return tile==1 || tile==3 || tile==5 || tile==6 || tile==7 || tile==8 || tile==12;
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
// entrada(mapa1)→cueva(mapa5), entrada2_mapa→mapa3, mapa3→entrada2_mapa, cueva→mapa1.
// La posicion de la segunda entrada es aleatoria cada partida (randomiza_entrada).
void check_warp(void) { //entrada a cueva (posicion aleatoria cada partida)
    if (mapa_actual == entrada_mapa && mapa_trabajo[hmap] == 9) {
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
    if (mapa_actual == entrada2_mapa && mapa_trabajo[hmap] == 9) {
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
        mapa_actual = entrada2_mapa;
        hx = entrada2_pos % ancho_mapa;
        hy = entrada2_pos / ancho_mapa + 1;
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
        hx = entrada_pos % ancho_mapa;
        hy = entrada_pos / ancho_mapa + 1;
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
    if (eactive && ex == tx && ey == ty) {
        eactive = 0;
        if (rand_next() & 1) drop_item(ex, ey);
        render_tile(mapa_trabajo[ey*ancho_mapa+ex], ex, ey);
    }
    if (e2active && e2x == tx && e2y == ty) {
        e2active = 0;
        if (rand_next() & 1) drop_item(e2x, e2y);
        render_tile(mapa_trabajo[e2y*ancho_mapa+e2x], e2x, e2y);
    }
    if (boss_active && boss_y == ty && boss_x == tx) {
        boss_hp--;
        if (boss_hp == 0) {
            boss_active = 0;
            erase_boss_tiles(boss_x, boss_y);
            drop_item(boss_x, boss_y);
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
    mapa_trabajo[llave_pos] = 0;
    render_tile(0, llave_pos % ancho_mapa, llave_pos / ancho_mapa);
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

void animacion_enemigo(void) {
    if (!eactive) return;
    put_sprite_x16(enmy_hvy, ex*2+MAPA_OX, ey*2+MAPA_OY);
}

// El enemigo persigue al heroe tile a tile (sin pathfinding), se mueve cada 16 frames.
// Si coincide con el heroe y inv_timer==0, inflige dano y activa invulnerabilidad.
void mueve_enemigo(void) {
    if (!eactive) return;
    emov++;
    if (emov < 16) return;
    emov = 0;
    render_tile(mapa_trabajo[ey*ancho_mapa+ex], ex, ey);
    if (ex < hx) ex++;
    else if (ex > hx) ex--;
    else if (ey < hy) ey++;
    else if (ey > hy) ey--;
    if (ex == hx && ey == hy && inv_timer == 0) {
        vidas--;
        sonido_danio();
        render_hud_vidas();
        inv_timer = 40;
        if (vidas == 0) cambiar_pantalla(PANTALLA_GAME_OVER);
    }
}

void animacion_enemigo2(void) {
    if (!e2active) return;
    if (eanim == 0)
        put_sprite_x16(enmy_octoD_a, e2x*2+MAPA_OX, e2y*2+MAPA_OY);
    else
        put_sprite_x16(enmy_octoD_b, e2x*2+MAPA_OX, e2y*2+MAPA_OY);
    eanim ^= 1;
}

void mueve_enemigo2(void) {
    unsigned char ny;
    if (!e2active) return;
    e2mov++;
    if (e2mov < 16) return;
    e2mov = 0;
    render_tile(mapa_trabajo[e2y*ancho_mapa+e2x], e2x, e2y);
    if (rand_next() & 1) {
        ny = e2y + 1;
        if (ny < alto_mapa && !es_solido(mapa_trabajo[ny*ancho_mapa+e2x]))
            e2y = ny;
        else {
            ny = e2y - 1;
            if (ny < alto_mapa && !es_solido(mapa_trabajo[ny*ancho_mapa+e2x]))
                e2y = ny;
        }
    } else {
        ny = e2y - 1;
        if (ny < alto_mapa && !es_solido(mapa_trabajo[ny*ancho_mapa+e2x]))
            e2y = ny;
        else {
            ny = e2y + 1;
            if (ny < alto_mapa && !es_solido(mapa_trabajo[ny*ancho_mapa+e2x]))
                e2y = ny;
        }
    }
    if (e2x == hx && e2y == hy && inv_timer == 0) {
        vidas--;
        sonido_danio();
        render_hud_vidas();
        inv_timer = 40;
        if (vidas == 0) cambiar_pantalla(PANTALLA_GAME_OVER);
    }
}

void animacion_boss(void) {
    if (!boss_active || mapa_actual != 6) return;
    if (boss_form == 0) {
        // X: diagonales
        put_sprite_x16(enmy_bossFire, (boss_x-1)*2+MAPA_OX, (boss_y-1)*2+MAPA_OY);
        put_sprite_x16(enmy_bossFire, (boss_x+1)*2+MAPA_OX, (boss_y-1)*2+MAPA_OY);
        put_sprite_x16(enmy_bossFire, (boss_x-1)*2+MAPA_OX, (boss_y+1)*2+MAPA_OY);
        put_sprite_x16(enmy_bossFire, (boss_x+1)*2+MAPA_OX, (boss_y+1)*2+MAPA_OY);
    } else {
        // +: cardinales
        put_sprite_x16(enmy_bossFire,  boss_x*2   +MAPA_OX, (boss_y-1)*2+MAPA_OY);
        put_sprite_x16(enmy_bossFire, (boss_x-1)*2+MAPA_OX,  boss_y*2   +MAPA_OY);
        put_sprite_x16(enmy_bossFire, (boss_x+1)*2+MAPA_OX,  boss_y*2   +MAPA_OY);
        put_sprite_x16(enmy_bossFire,  boss_x*2   +MAPA_OX, (boss_y+1)*2+MAPA_OY);
    }
    put_sprite_x16(enmy_boss, boss_x*2+MAPA_OX, boss_y*2+MAPA_OY);
}

// El boss alterna cada 20 frames entre dos patrones (boss_form XOR 1):
//   form 0: fuego en las 4 esquinas del tile del boss (patron diagonal).
//   form 1: fuego en los 4 laterales del tile del boss (patron en cruz).
// Se mueve hacia el heroe limitandose a los tiles interiores (x:3-12, y:2-6).
// El contacto con el heroe o sus fuegos inflige dano directamente (sin proyectil).
void mueve_boss(void) {
    unsigned char ox, oy, dx, dy, hit;
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
    if (inv_timer == 0) {
        dx = (hx >= boss_x) ? hx - boss_x : boss_x - hx;
        dy = (hy >= boss_y) ? hy - boss_y : boss_y - hy;
        hit = 0;
        if (dx == 0 && dy == 0) hit = 1;
        else if (boss_form == 0 && dx == 1 && dy == 1) hit = 1;
        else if (boss_form == 1 && ((dx == 1 && dy == 0) || (dx == 0 && dy == 1))) hit = 1;
        if (hit) {
            vidas--;
            sonido_danio();
            render_hud_vidas();
            inv_timer = 40;
            if (vidas == 0) cambiar_pantalla(PANTALLA_GAME_OVER);
        }
    }
}
