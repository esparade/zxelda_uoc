void put_hud_char(unsigned char *pix, unsigned char col, unsigned char row, unsigned char attr) {
    *((unsigned char *)(22528 + (unsigned int)row * 32 + col)) = attr;
    put_sprite_x8_noclr(pix, col, row);
}

void init_pantalla (void) {
    borde_actual = 6; port_out(254, borde_actual);
    cls(0);
}

void render_game_over (void) {
    cls(0);
    put_hud_char(F_LET('h'), 11, 11, 7);
    put_hud_char(F_LET('a'), 12, 11, 7);
    put_hud_char(F_LET('s'), 13, 11, 7);
    put_hud_char(F_LET('m'), 15, 11, 7);
    put_hud_char(F_LET('u'), 16, 11, 7);
    put_hud_char(F_LET('e'), 17, 11, 7);
    put_hud_char(F_LET('r'), 18, 11, 7);
    put_hud_char(F_LET('t'), 19, 11, 7);
    put_hud_char(F_LET('o'), 20, 11, 7);
}

// Dibuja todos los tiles del mapa actual recorriendo mapa_trabajo fila a fila.
void render_mapa (void) {
    int contador=0;
    for (y=0;y<alto_mapa;y++) {
        for (x=0;x<ancho_mapa;x++) {
            render_tile (mapa_trabajo[contador],x,y);
            contador++;
        }
    }
}

// Dibuja el fondo del HUD: negro en mazmorras (mapas 3 y 6), amarillo en exteriores.
void render_hud_fondo(void) {
    unsigned char *borde;
    if (mapa_actual == 3 || mapa_actual == 6) {
        borde = sprite_negro;
        for (y = 0; y < 6; y++)
            for (x = 0; x < 32; x++)
                *((unsigned char *)(22528 + (unsigned int)y * 32 + x)) = 0;
    } else {
        borde = sprite_amaD;
    }
    for (x=0; x<3; x++) {
        put_sprite_x16(borde, 0,  x*2);
        put_sprite_x16(borde, 30, x*2);
    }
}

void render_menu (void) {
    put_hud_char(F_LET('z'), 13, 7, 7);
    put_hud_char(F_LET('x'), 14, 7, 7);
    put_hud_char(F_LET('e'), 15, 7, 7);
    put_hud_char(F_LET('l'), 16, 7, 7);
    put_hud_char(F_LET('d'), 17, 7, 7);
    put_hud_char(F_LET('a'), 18, 7, 7);

    put_hud_char(F_DIG(1),   10, 15, 2);
    put_hud_char(F_LET('t'), 12, 15, 2);
    put_hud_char(F_LET('e'), 13, 15, 2);
    put_hud_char(F_LET('c'), 14, 15, 2);
    put_hud_char(F_LET('l'), 15, 15, 2);
    put_hud_char(F_LET('a'), 16, 15, 2);
    put_hud_char(F_LET('d'), 17, 15, 2);
    put_hud_char(F_LET('o'), 18, 15, 2);
    
    put_hud_char(F_DIG(2),   10, 16, 3);
    put_hud_char(F_LET('k'), 12, 16, 3);
    put_hud_char(F_LET('e'), 13, 16, 3);
    put_hud_char(F_LET('m'), 14, 16, 3);
    put_hud_char(F_LET('p'), 15, 16, 3);
    put_hud_char(F_LET('s'), 16, 16, 3);
    put_hud_char(F_LET('t'), 17, 16, 3);
    put_hud_char(F_LET('o'), 18, 16, 3);
    put_hud_char(F_LET('n'), 19, 16, 3);
    
    put_hud_char(F_DIG(3),   10, 17, 7);
    put_hud_char(F_LET('r'), 12, 17, 7);
    put_hud_char(F_LET('e'), 13, 17, 7);
    put_hud_char(F_LET('d'), 14, 17, 7);
    put_hud_char(F_LET('e'), 15, 17, 7);
    put_hud_char(F_LET('f'), 16, 17, 7);
    put_hud_char(F_LET('i'), 17, 17, 7);
    put_hud_char(F_LET('n'), 18, 17, 7);
    put_hud_char(F_LET('i'), 19, 17, 7);
    put_hud_char(F_LET('r'), 20, 17, 7);

    put_hud_char(F_LET('u'),  4, 21, 69);
    put_hud_char(F_LET('o'),  5, 21, 69);
    put_hud_char(F_LET('c'),  6, 21, 69);

    put_hud_char(F_DIG(2),    8, 21, 7);
    put_hud_char(F_DIG(0),    9, 21, 7);
    put_hud_char(F_DIG(2),   10, 21, 7);
    put_hud_char(F_DIG(6),   11, 21, 7);

    put_hud_char(F_LET('n'), 13, 21, 7);
    put_hud_char(F_LET('o'), 14, 21, 7);
    put_hud_char(F_LET('t'), 15, 21, 7);

    put_hud_char(F_LET('l'), 17, 21, 7);
    put_hud_char(F_LET('i'), 18, 21, 7);
    put_hud_char(F_LET('c'), 19, 21, 7);
    put_hud_char(F_LET('e'), 20, 21, 7);
    put_hud_char(F_LET('n'), 21, 21, 7);
    put_hud_char(F_LET('s'), 22, 21, 7);
    put_hud_char(F_LET('e'), 23, 21, 7);
    put_hud_char(F_LET('d'), 24, 21, 7);

    put_hud_char(F_LET('b'), 26, 21, 7);
    put_hud_char(F_LET('y'), 27, 21, 7);

    put_hud_char(F_LET('n'),  4, 22, 66);
    put_hud_char(F_LET('i'),  5, 22, 66);
    put_hud_char(F_LET('n'),  6, 22, 66);
    put_hud_char(F_LET('t'),  7, 22, 66);
    put_hud_char(F_LET('e'),  8, 22, 66);
    put_hud_char(F_LET('n'),  9, 22, 66);
    put_hud_char(F_LET('d'), 10, 22, 66);
    put_hud_char(F_LET('o'), 11, 22, 66);

    put_hud_char(F_LET('v'), 14, 22, 7);
    put_hud_char(F_LET('e'), 15, 22, 7);
    put_hud_char(F_LET('r'), 16, 22, 7);
    put_hud_char(F_LET('s'), 17, 22, 7);
    put_hud_char(F_LET('i'), 18, 22, 7);
    put_hud_char(F_LET('o'), 19, 22, 7);
    put_hud_char(F_LET('n'), 20, 22, 7);

    put_hud_char(F_LET('b'), 22, 22, 7);
    put_hud_char(F_LET('y'), 23, 22, 7);

    put_hud_char(F_LET('j'), 25, 22, 7);
    put_hud_char(F_LET('g'), 26, 22, 7);
    put_hud_char(F_LET('h'), 27, 22, 7);
}

void render_redefine_paso(void) {
    cls(0);
    put_hud_char(F_LET('r'), 12,  4, 7);
    put_hud_char(F_LET('e'), 13,  4, 7);
    put_hud_char(F_LET('d'), 14,  4, 7);
    put_hud_char(F_LET('e'), 15,  4, 7);
    put_hud_char(F_LET('f'), 16,  4, 7);
    put_hud_char(F_LET('i'), 17,  4, 7);
    put_hud_char(F_LET('n'), 18,  4, 7);
    put_hud_char(F_LET('e'), 19,  4, 7);

    put_hud_char(F_LET('p'), 8,  11, 7);
    put_hud_char(F_LET('u'), 9,  11, 7);
    put_hud_char(F_LET('l'), 10, 11, 7);
    put_hud_char(F_LET('s'), 11, 11, 7);
    put_hud_char(F_LET('a'), 12, 11, 7);
    put_hud_char(F_LET('t'), 14, 11, 7);
    put_hud_char(F_LET('e'), 15, 11, 7);
    put_hud_char(F_LET('c'), 16, 11, 7);
    put_hud_char(F_LET('l'), 17, 11, 7);
    put_hud_char(F_LET('a'), 18, 11, 7);
    put_hud_char(F_LET('p'), 20, 11, 7);
    put_hud_char(F_LET('a'), 21, 11, 7);
    put_hud_char(F_LET('r'), 22, 11, 7);
    put_hud_char(F_LET('a'), 23, 11, 7);

    switch(redef_paso) {
        case 1:
            put_hud_char(F_LET('a'), 13, 12, 7);
            put_hud_char(F_LET('r'), 14, 12, 7);
            put_hud_char(F_LET('r'), 15, 12, 7);
            put_hud_char(F_LET('i'), 16, 12, 7);
            put_hud_char(F_LET('b'), 17, 12, 7);
            put_hud_char(F_LET('a'), 18, 12, 7);
        break;
        case 2:
            put_hud_char(F_LET('a'), 13, 12, 7);
            put_hud_char(F_LET('b'), 14, 12, 7);
            put_hud_char(F_LET('a'), 15, 12, 7);
            put_hud_char(F_LET('j'), 16, 12, 7);
            put_hud_char(F_LET('o'), 17, 12, 7);
        break;
        case 3:
            put_hud_char(F_LET('i'), 11, 12, 7);
            put_hud_char(F_LET('z'), 12, 12, 7);
            put_hud_char(F_LET('q'), 13, 12, 7);
            put_hud_char(F_LET('u'), 14, 12, 7);
            put_hud_char(F_LET('i'), 15, 12, 7);
            put_hud_char(F_LET('e'), 16, 12, 7);
            put_hud_char(F_LET('r'), 17, 12, 7);
            put_hud_char(F_LET('d'), 18, 12, 7);
            put_hud_char(F_LET('a'), 19, 12, 7);
        break;
        case 4:
            put_hud_char(F_LET('d'), 12, 12, 7);
            put_hud_char(F_LET('e'), 13, 12, 7);
            put_hud_char(F_LET('r'), 14, 12, 7);
            put_hud_char(F_LET('e'), 15, 12, 7);
            put_hud_char(F_LET('c'), 16, 12, 7);
            put_hud_char(F_LET('h'), 17, 12, 7);
            put_hud_char(F_LET('a'), 18, 12, 7);
        break;
        case 5:
            put_hud_char(F_LET('a'), 13, 12, 7);
            put_hud_char(F_LET('t'), 14, 12, 7);
            put_hud_char(F_LET('a'), 15, 12, 7);
            put_hud_char(F_LET('q'), 16, 12, 7);
            put_hud_char(F_LET('u'), 17, 12, 7);
            put_hud_char(F_LET('e'), 18, 12, 7);
        break;
        case 6:
            put_hud_char(F_LET('r'), 11, 12, 7);
            put_hud_char(F_LET('e'), 12, 12, 7);
            put_hud_char(F_LET('i'), 13, 12, 7);
            put_hud_char(F_LET('n'), 14, 12, 7);
            put_hud_char(F_LET('i'), 15, 12, 7);
            put_hud_char(F_LET('c'), 16, 12, 7);
            put_hud_char(F_LET('i'), 17, 12, 7);
            put_hud_char(F_LET('a'), 18, 12, 7);
            put_hud_char(F_LET('r'), 19, 12, 7);
        break;
    }
}

// Redibuja el tile del mapa bajo el heroe (borra el sprite del heroe de su posicion actual).
void restaura_fondo_tile (void) {
    unsigned char tile=mapa_trabajo[hmap];
    render_tile(tile,hx,hy);
}

// Dibuja el tile con el ID dado en la celda (x,y) de la rejilla del mapa.
// IDs de tile: 0=suelo_mundo  1=arbol  2=matorral  3=bloque_dngn  4=baldosa  5=pared
//              6=puerta_izq   7=puerta_der  8=puerta_arr  9=void/negro
//              10/11=objetos_cueva  12=bloque_cerrado  13=fuego  14=corazon  15=llave  16=power
int render_tile(int grafico, int x, int y) {
    switch (grafico) {
        case 0:
            put_sprite_x16 (sprite_amaD, x*2+MAPA_OX, y*2+MAPA_OY);
        break;
        case 1:
            put_sprite_x16 (wrld_frst, x*2+MAPA_OX, y*2+MAPA_OY);
        break;
        case 2:
            put_sprite_x16 (wrld_bush, x*2+MAPA_OX, y*2+MAPA_OY);
        break;
        case 3:
            put_sprite_x16 (dngn_blck, x*2+MAPA_OX, y*2+MAPA_OY);
        break;
        case 4:
            put_sprite_x16 (dngn_tile, x*2+MAPA_OX, y*2+MAPA_OY);
        break;
        case 5:
            put_sprite_x16 (dngn_wall,x*2+MAPA_OX, y*2+MAPA_OY);
        break;
        case 6:
            put_sprite_x16 (wrld_door_left, x*2+MAPA_OX, y*2+MAPA_OY);
        break;
        case 7:
            put_sprite_x16 (wrld_door_right, x*2+MAPA_OX, y*2+MAPA_OY);
        break;
        case 8:
            put_sprite_16x8 (wrld_door_up, x*2+MAPA_OX, y*2+1+MAPA_OY);
        break;
        case 9:
            put_sprite_x16 (sprite_negro, x*2+MAPA_OX, y*2+MAPA_OY);
        break;
        case 10:
            put_sprite_x16 (itm_bigSwrd, x*2+MAPA_OX, y*2+MAPA_OY);
        break;
        case 11:
            put_sprite_x16 (itm_bigHrth, x*2+MAPA_OX, y*2+MAPA_OY);
        break;
        case 12:
            put_sprite_x16 (dngn_blck, x*2+MAPA_OX, y*2+MAPA_OY);
        break;
        case 13:
            put_sprite_x16 (dngn_fire, x*2+MAPA_OX, y*2+MAPA_OY);
        break;
        case 15:
            render_tile(tile_bajo_llave, x, y);
            put_sprite_x8_mask(item_llave, x*2+MAPA_OX, y*2+MAPA_OY);
        break;
        case 16:
            render_tile(tile_bajo_power, x, y);
            put_hud_char(item_power, x*2+MAPA_OX, y*2+MAPA_OY, item_power[8]);
        break;
        case 14:
            render_tile(tile_bajo_corazon, x, y);
            put_sprite_x8_mask(item_corazon, x*2+MAPA_OX, y*2+MAPA_OY);
        break;
    }
}

void render_hud_pts(void) {
    put_hud_char(item_points, 14, 1, item_points[8]);
    put_hud_char(F_LET('p'), 16, 1, 7);
    put_hud_char(F_LET('t'), 17, 1, 7);
    put_hud_char(F_LET('s'), 18, 1, 7);
    put_hud_char(F_DIG(pts / 10), 23, 1, 7);
    put_hud_char(F_DIG(pts % 10), 24, 1, 7);
}

void render_hud_vidas(void) {
    put_hud_char(hud_corazon, 14, 2, 2);
    put_hud_char(F_LET('v'), 16, 2, 7);
    put_hud_char(F_LET('i'), 17, 2, 7);
    put_hud_char(F_LET('d'), 18, 2, 7);
    put_hud_char(F_LET('a'), 19, 2, 7);
    put_hud_char(F_DIG(vidas), 23, 2, 7);
}

void render_hud_fuerza(void) {
    put_hud_char(item_power, 14, 3, item_power[8]);
    put_hud_char(F_LET('f'), 16, 3, 7);
    put_hud_char(F_LET('u'), 17, 3, 7);
    put_hud_char(F_LET('e'), 18, 3, 7);
    put_hud_char(F_LET('r'), 19, 3, 7);
    put_hud_char(F_LET('z'), 20, 3, 7);
    put_hud_char(F_LET('a'), 21, 3, 7);
    put_hud_char(F_DIG(fuerza), 23, 3, 7);
}

void render_hud_llave(void) {
    put_sprite_x8_mask(item_llave, 14, 4);
    put_hud_char(F_LET('l'), 16, 4, 7);
    put_hud_char(F_LET('l'), 17, 4, 7);
    put_hud_char(F_LET('a'), 18, 4, 7);
    put_hud_char(F_LET('v'), 19, 4, 7);
    put_hud_char(F_LET('e'), 20, 4, 7);
    put_hud_char(F_LET('s'), 21, 4, 7);
    put_hud_char(F_DIG(tiene_llave), 23, 4, 7);
}

int render_hero(int x, int y) {
    int rx = x + MAPA_OX;
    int ry = y + MAPA_OY;
    switch (vista) {
        case 0: //up
            switch (anim) {
                case 0:
                    put_sprite_x16_mask_ink (plyr_upA,rx,ry);
                    break;
                case 1:
                    put_sprite_x16_mask_ink (plyr_upB,rx,ry);
                    break;
                }
            anim++;

            if (anim > 1) {
                anim = 0;
            }
            break;

        case 1: //der
            switch (anim) {
                case 0:
                    put_sprite_x16_mask_ink (plyr_rghA,rx,ry);
                    break;
                case 1:
                    put_sprite_x16_mask_ink (plyr_rghB,rx,ry);
                    break;
                }
            anim++;

            if (anim > 1) {
                anim = 0;
            }
            break;

        case 2: //abaj
            switch (anim) {
                case 0:
                    put_sprite_x16_mask_ink (plyr_dwnA,rx,ry);
                    break;
                case 1:
                    put_sprite_x16_mask_ink (plyr_dwnB,rx,ry);
                    break;
                }
            anim++;

            if (anim > 1) {
                anim = 0;
            }
            break;

        case 3: //izq
            switch (anim) {
                case 0:
                    put_sprite_x16_mask_ink (plyr_lftA,rx,ry);
                    break;
                case 1:
                    put_sprite_x16_mask_ink (plyr_lftB,rx,ry);
                    break;
                }
            anim++;

            if (anim > 1) {
                anim = 0;
            }
            break;
    }
}

// Cambia el estado de la aplicacion, limpia pantalla e inicializa el modo nuevo.
// En PANTALLA_JUEGO llama a inicia_variables_juego(), que resetea todo el estado de partida.
void cambiar_pantalla (unsigned char nueva) {
    modo_app = nueva;
    cls(0);
    switch (modo_app) {
case PANTALLA_MENU:
            jgh_color = 0;
            jgh_timer = 0;
            borde_actual = 0; port_out(254, 0);
            render_menu();
        break;
        case PANTALLA_JUEGO:
            inicia_variables_juego();
            render_hud_fondo();
            render_hud_pts();
            render_hud_vidas();
            render_hud_fuerza();
            render_hud_llave();
            render_mapa();
            render_hero(hx*2, hy*2);
        break;
        case PANTALLA_GAME_OVER:
            game_over_timer = 50;
            render_game_over();
        break;
    }
}
