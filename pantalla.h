//zxelda v0.1b
//07abr'26

void init_pantalla (void) {
    borde_actual = 6; port_out(254, borde_actual);
    cls(0);
}

void render_intro (void) {
    cls(0);
}

void render_game_over (void) {
    cls(0);
    //TODO: dibujar pantalla de game over
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

void put_hud_char(unsigned char *pix, unsigned char col, unsigned char row, unsigned char attr) {
    *((unsigned char *)(22528 + (unsigned int)row * 32 + col)) = attr;
    put_sprite_x8_noclr(pix, col, row);
}

// Dibuja el fondo del HUD: negro en mapa3 (mazmorra), amarillo en exteriores.
void render_hud_fondo(void) {
    unsigned char *borde = (mapa_actual == 3) ? sprite_negro : sprite_amaD;
    for (x=0; x<3; x++) {
        put_sprite_x16(borde, 0,  x*2);
        put_sprite_x16(borde, 30, x*2);
    }
}

void render_menu (void) {
    //put_partial1v_sprite_x16(menu8x8,0,0); //tile misterioso 1PLYR
}

// Redibuja el tile del mapa bajo el heroe (borra el sprite del heroe de su posicion actual).
void restaura_fondo_tile (void) {
    unsigned char tile=mapa_trabajo[hmap];
    render_tile(tile,hx,hy);
}

// Dibuja el tile con el ID dado en la celda (x,y) de la rejilla del mapa.
// IDs de tile: 0=suelo_mundo  1=arbol  2=matorral  3=bloque_dngn  4=baldosa  5=pared
//              6=puerta_izq   7=puerta_der  8=puerta_arr  9=void/negro
//              13=llave  14=corazon
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
        case 13:
            render_tile(tile_bajo_llave, x, y);
            put_sprite_x8_mask(item_llave, x*2+MAPA_OX, y*2+MAPA_OY);
        break;
        case 14:
            render_tile(tile_bajo_corazon, x, y);
            put_sprite_x8_mask(item_corazon, x*2+MAPA_OX, y*2+MAPA_OY);
        break;
    }
}

void render_hud_llave(void) {
    put_hud_char(F_LET('l'), 14, 2, 7);
    put_hud_char(F_LET('l'), 15, 2, 7);
    put_hud_char(F_LET('a'), 16, 2, 7);
    put_hud_char(F_LET('v'), 17, 2, 7);
    put_hud_char(F_LET('e'), 18, 2, 7);
    put_hud_char(F_LET('s'), 19, 2, 7);
    if (tiene_llave) {
        put_sprite_x8_mask_noclr(item_llave_trans, 20, 2);
    }
    put_hud_char(F_DIG(tiene_llave), 21, 2, 7);
}

void render_hud_vidas(void) {
    unsigned char n;
    put_hud_char(F_LET('v'), 2, 2, 7);
    put_hud_char(F_LET('i'), 3, 2, 7);
    put_hud_char(F_LET('d'), 4, 2, 7);
    put_hud_char(F_LET('a'), 5, 2, 7);
    for (n = 0; n < NUMERO_DE_VIDAS; n++) {
        if (n < vidas)
            put_hud_char(hud_corazon, 7 + n*2, 2, 2);
        else
            put_hud_char(hud_corazon_vacio, 7 + n*2, 2, 1);
    }
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
        case PANTALLA_INTRO:
            render_intro();
        break;
        case PANTALLA_MENU:
            render_menu();
        break;
        case PANTALLA_JUEGO:
            inicia_variables_juego();
            render_hud_fondo();
            render_hud_vidas();
            render_mapa();
            render_hud_llave();
            render_hero(hx*2, hy*2);
        break;
        case PANTALLA_GAME_OVER:
            render_game_over();
        break;
    }
}
