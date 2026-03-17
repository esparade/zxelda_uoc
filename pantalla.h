//zxelda v0.1a
//16mar'26

void init_pantalla (void) {
    port_out (254,2); //border 2
    cls(0);
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
    put_partial2v_sprite_x16(menu8x8,0,23);
}

void render_menu (void) {
    put_partial1v_sprite_x16(menu8x8,0,0);
}

// Redibuja el tile del mapa bajo el heroe (borra el sprite del heroe de su posicion actual).
void restaura_fondo_tile (void) {
    unsigned char tile=mapa_trabajo[hmap];
    render_tile(tile,hx,hy);
}

// Dibuja el tile con el ID dado en la celda (x,y) de la rejilla del mapa.
// IDs de tile: 0=negro  1=esfera
int render_tile(int grafico, int x, int y) {
    switch (grafico) {
        case 0:
            put_sprite_x16 (sprite_negro,x*2,y*2);
        break;
        case 1:
            put_sprite_x16 (sprite_esfera,x*2,y*2);
        break;
    }
}

int render_hero(int x, int y) {
    switch (vista) {
        case 0:
            switch (anim) {
                case 0:
                    put_sprite_x16 (anim1,x,y);
                    break;
                case 1:
                    put_sprite_x16 (anim2,x,y);
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
                    put_sprite_x16 (anim1b,x,y);
                    break;
                case 1:
                    put_sprite_x16 (anim2b,x,y);
                    break;
                }
            anim--;

            if (anim <= -1) {
                anim = 1;
            }
            break;
    }
}
