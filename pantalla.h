//zxelda v0.1a
//16mar'26

void init_pantalla (void) {
    port_out (254,6); //border color. 0_black, 1_blue, 2_red, 3_magenta, 4_green, 5_teal, 6_yellow, 7_white
    cls(0);
}

void render_intro (void) {
    cls(0);
    //TODO: dibujar pantalla de intro
}

void render_game_over (void) {
    cls(0);
    //TODO: dibujar pantalla de game over
}

// Dibuja todos los tiles del mapa actual recorriendo mapa_trabajo fila a fila.
void render_mapa (void) {
    int contador=0;

    //put_partial2v_sprite_x16(menu8x8,0,23); //tile de la firma -- aqui hay que poner los tiles del status

    for (y=0;y<alto_mapa;y++) {
        for (x=0;x<ancho_mapa;x++) {
            render_tile (mapa_trabajo[contador],x,y);
            contador++;
        }
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
//              9=void/negro
int render_tile(int grafico, int x, int y) {
    switch (grafico) {
        case 9:
            put_sprite_x16 (sprite_negro, x*2+MAPA_OX, y*2+MAPA_OY);
        break;
        case 0:
            put_sprite_x16 (sprite_amaD, x*2+MAPA_OX, y*2+MAPA_OY);
        break;
        case 1:
            put_sprite_x16 (worldA_forest, x*2+MAPA_OX, y*2+MAPA_OY);
        break;
        case 2:
            put_sprite_x16 (worldA_bush, x*2+MAPA_OX, y*2+MAPA_OY);
        break;
        case 3:
            put_sprite_x16 (worldB_block, x*2+MAPA_OX, y*2+MAPA_OY);
        break;
        case 4:
            put_sprite_x16 (worldB_tile, x*2+MAPA_OX, y*2+MAPA_OY);
        break;
        case 5:
            put_sprite_x16 (worldB_wall, x*2+MAPA_OX, y*2+MAPA_OY);
        break;
    }
}

int render_hero(int x, int y) {
    int rx = x + MAPA_OX;
    int ry = y + MAPA_OY;
    switch (vista) {
        case 0:
            switch (anim) {
                case 0:
                    put_sprite_x16 (sprite_linkDownA,rx,ry);
                    break;
                case 1:
                    put_sprite_x16 (sprite_linkDownB,rx,ry);
                    break;
                }
            anim++;

            if (anim >= 2) {
                anim = 0;
            }
            break;

        case 1:
            switch (anim) {
                case 0:
                    put_sprite_x16 (sprite_linkUpA,rx,ry);
                    break;
                case 1:
                    put_sprite_x16 (sprite_linkUpB,rx,ry);
                    break;
                }
            anim--;

            if (anim <= -1) {
                anim = 1;
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
            render_mapa();
        break;
        case PANTALLA_GAME_OVER:
            render_game_over();
        break;
    }
}
