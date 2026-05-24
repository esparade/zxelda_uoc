//zxelda v0.1b
//07abr'26

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
    render_tile(13, llave_pos % ancho_mapa, llave_pos / ancho_mapa);
}

// Tiles solidos (bloquean movimiento): arbol(1), bloque(3), pared(5),
// puerta_izq(6), puerta_der(7), puerta_arr(8).
// Son pasables: suelo(0), matorral(2), baldosa(4), void(9), llave(13).
int es_solido(unsigned char tile) {
    return tile==1 || tile==3 || tile==5 || tile==6 || tile==7 || tile==8;
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
        hx = 6;
        hy = 7;
        carga_datos_mapa();
        calculo_frame();
        render_hud_fondo();
        render_hud_vidas();
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
        render_hud_fondo();
        render_hud_vidas();
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
        render_hud_fondo();
        render_hud_vidas();
        render_hud_llave();
        render_mapa();
        render_hero(hx*2, hy*2);
        return;
    }
    if (mapa_actual == 5 && hy == alto_mapa-1 && (hx == 7 || hx == 8)) { //salida de cueva
        mapa_actual = 1;
        hx = 2;
        hy = 2;
        carga_datos_mapa();
        calculo_frame();
        render_hud_fondo();
        render_hud_vidas();
        render_hud_llave();
        render_mapa();
        render_hero(hx*2, hy*2);
        return;
    }
}

void sword_render(void) { //logica del ataque a espada
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

// Comprueba si el tile delante del heroe contiene un enemigo y lo elimina con 1 golpe,
// soltando la llave en ese tile con probabilidad 50%.
void check_sword_hit(void) {
    unsigned char tx, ty;
    if (!eactive) return;
    switch(vista) {
        case 0: tx=hx;   ty=hy-1; break;
        case 1: tx=hx+1; ty=hy;   break;
        case 2: tx=hx;   ty=hy+1; break;
        case 3: tx=hx-1; ty=hy;   break;
    }
    if (ex == tx && ey == ty) {
        eactive = 0;
        if (rand_next() & 1) { // 50% drop chance
            llave_mapa = mapa_actual;
            llave_pos  = ey * ancho_mapa + ex;
            tile_bajo_llave = mapa_trabajo[llave_pos];
            mapa_trabajo[llave_pos] = 13;
            llave_en_mapa = 1;
        }
        render_tile(mapa_trabajo[ey*ancho_mapa+ex], ex, ey);
    }
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

void animacion_enemigo(void) {
    if (!eactive) return;
    if (eanim == 0)
        put_sprite_x16(enmy_octoD_a, ex*2+MAPA_OX, ey*2+MAPA_OY);
    else
        put_sprite_x16(enmy_octoD_b, ex*2+MAPA_OX, ey*2+MAPA_OY);
    eanim ^= 1;
}

// El enemigo persigue al heroe tile a tile (sin pathfinding), se mueve cada 16 frames.
// Si coincide con el heroe, provoca game over directamente (sin sistema de dano ni invulnerabilidad).
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
    if (ex == hx && ey == hy) {
        cambiar_pantalla(PANTALLA_GAME_OVER);
    }
}
