int x8,y8;

// devuelve 1 si ninguna tecla esta pulsada (todas las filas del teclado en 0x1F).
unsigned char all_keys_up(void) {
    if ((port_in(65278) & 0x1F) != 0x1F) return 0;
    if ((port_in(65022) & 0x1F) != 0x1F) return 0;
    if ((port_in(64510) & 0x1F) != 0x1F) return 0;
    if ((port_in(63486) & 0x1F) != 0x1F) return 0;
    if ((port_in(61438) & 0x1F) != 0x1F) return 0;
    if ((port_in(57342) & 0x1F) != 0x1F) return 0;
    if ((port_in(49150) & 0x1F) != 0x1F) return 0;
    if ((port_in(32766) & 0x1F) != 0x1F) return 0;
    return 1;
}

// lee la fila del teclado en 'port'; si hay tecla pulsada guarda el puerto en *op y la mascara de bit en *ob, y devuelve 1
unsigned char check_row_key(unsigned int port, unsigned int *op, unsigned char *ob) {
    unsigned char v = port_in(port) & 0x1F;
    if (v == 0x1F) return 0;
    if (!(v &  1)) { *op = port; *ob =  1; return 1; }
    if (!(v &  2)) { *op = port; *ob =  2; return 1; }
    if (!(v &  4)) { *op = port; *ob =  4; return 1; }
    if (!(v &  8)) { *op = port; *ob =  8; return 1; }
    if (!(v & 16)) { *op = port; *ob = 16; return 1; }
    return 0;
}

// recorre las 8 filas del teclado; devuelve 1 si detecta alguna tecla pulsada y guarda *op y *ob con su identificador
unsigned char scan_any_key(unsigned int *op, unsigned char *ob) {
    if (check_row_key(65278, op, ob)) return 1;
    if (check_row_key(65022, op, ob)) return 1;
    if (check_row_key(64510, op, ob)) return 1;
    if (check_row_key(63486, op, ob)) return 1;
    if (check_row_key(61438, op, ob)) return 1;
    if (check_row_key(57342, op, ob)) return 1;
    if (check_row_key(49150, op, ob)) return 1;
    if (check_row_key(32766, op, ob)) return 1;
    return 0;
}

// cambia al mapa contiguo en la direccion dada y coloca al heroe en el borde de entrada opuesta
// columnas 0 y 15 son invisibles (VO), por eso los limites son col 1/14 y fila 0/8
void cambiar_mapa(unsigned char dir) {
    unsigned char destino = get_mapa_conexion(mapa_actual, dir);
    if (destino == 0) return; // sin conexion en esa direccion
    mapa_actual = destino;
    carga_datos_mapa();
    switch(dir) {
        // coloca al heroe en el borde opuesto al que salio
        case DIR_DER: hx = 1;             break; // salio derecha -> entra izquierda
        case DIR_IZQ: hx = ancho_mapa-2;  break; // salio izquierda -> entra derecha
        case DIR_ABA: hy = 0;             break; // salio abajo -> entra arriba
        case DIR_ARR: hy = alto_mapa-1;   break; // salio arriba -> entra abajo
    }
    calculo_frame();
    cls(0); // redibuja el resto de la pantalla
    render_hud_fondo();
    render_hud_pts();
    render_hud_vidas();
    render_hud_fuerza();
    render_hud_llave();
    render_mapa();
    render_hero(hx*2, hy*2);
}

void control_teclas_juego (void) {
    if ((port_in(key_arr_port) & key_arr_mask) == 0) { //arriba
        if (hy == 0) { // fila 0: borde superior, cambia de sala
            cambiar_mapa(DIR_ARR);
            return;
        }

        if (vista != 0) { // primera pulsacion: orienta el sprite arriba antes de mover (necesita 1 frame)
            vista = 0;
            restaura_fondo_tile();
            render_hero(hx*2,hy*2);
            wait_int();
            wait_int();
            wait_int(); // espera 3 interrupciones
            return;
        }

        if (es_solido(mapa_trabajo[hmap-ancho_mapa])) { //cancelar movimiento tile solido
            return;
        }

        x8=hx*2;               // columna pixel del heroe (1 tile = 2 chars)
        y8=(hy*2)-1;           // fila pixel: medio char por encima del tile actual (posicion intermedia)
        restaura_fondo_tile();
        render_hero(x8,y8);    // dibuja heroe en posicion intermedia (paso 1 de 2)
        y8=y8-1;               // avanza otro medio char hacia arriba (posicion final del frame)
        wait_int();
        wait_int();            // espera 2 interrupciones para suavizar el movimiento
        render_tile(mapa_trabajo[hmap],hx,hy);              // borra tile origen
        render_tile(mapa_trabajo[hmap-ancho_mapa],hx,hy-1); // borra tile destino
        render_hero(x8,y8);   // dibuja heroe en posicion final del frame
        hy--;
        calculo_frame();      // recalcula hmap
        wait_int();
        return;
    }

    if ((port_in(key_der_port) & key_der_mask) == 0) { // derecha
        if (hx==ancho_mapa-2) { // compruba si necesita cambio de mapa. col 14: borde derecho (col 15 invisible)
            cambiar_mapa(DIR_DER);
            return;
        }

        if (vista !=1) { // primera pulsacion: orienta el sprite derecha antes de mover (necesita 1 frame)
            vista = 1;
            restaura_fondo_tile();
            render_hero(hx*2,hy*2);
            wait_int();
            wait_int();
            wait_int(); // espera 3 interrupciones
            return;
        }

        if (es_solido(mapa_trabajo[hmap+1])) { //cancelar movimiento tile solido
            return;
        }

        x8=(hx*2)+1; // medio char en la columna del tile actual (posicion intermedia)(1 tile = 2 chars)
        y8=hy*2;     // fila pixel del heroe
        restaura_fondo_tile();
        render_hero(x8,y8); // dibuja heroe en posicion intermedia (paso 1 de 2)
        x8=x8+1;            // avanza otro medio char hacia derecha (posicion final del frame)
        wait_int();
        wait_int();         // espera 2 interrupciones para suavizar el movimiento
        render_tile(mapa_trabajo[hmap],hx,hy);      // borra tile origen
        render_tile(mapa_trabajo[hmap+1],hx+1,hy);  // borra tile destino
        render_hero(x8,y8);      // dibuja heroe en posicion final del frame
        hx++;
        calculo_frame();   // recalcula hmap
        wait_int();
        return;
    }

    if ((port_in(key_abj_port) & key_abj_mask) == 0) { // abajo
        if (hy == alto_mapa-1) { // comprueba si necesita cambio de mapa fila 8: borde inferior, cambia mapa
            cambiar_mapa(DIR_ABA);
            return;
        }

        if (vista != 2) { // primera pulsacion: orienta el sprite abajo antes de mover (necesita 1 frame)
            vista = 2;
            restaura_fondo_tile();
            render_hero(hx*2,hy*2);
            wait_int();
            wait_int();
            wait_int(); // espera 3 interrupciones
            return;
        }

        if (es_solido(mapa_trabajo[hmap+ancho_mapa])) { //cancelar movimiento tile solido
            return;
        }
        x8=hx*2;          // medio char en la columna del tile actual
        y8=(hy*2)+1;      // fila pixel del heroe (posicion intermedia)(1 tile = 2 chars)
        restaura_fondo_tile();
        render_hero(x8,y8); // dibuja heroe en posicion intermedia (paso 1 de 2)
        y8=y8+1;            // avanza otro medio char hacia abajo (posicion final del frame)
        wait_int();
        wait_int();         // espera 2 interrupciones para suavizar el movimiento
        render_tile(mapa_trabajo[hmap],hx,hy);      // borra tile origen
        render_tile(mapa_trabajo[hmap+ancho_mapa],hx,hy+1);  // borra tile destino
        render_hero(x8,y8);      // dibuja heroe en posicion final del frame
        hy++;
        calculo_frame();   // recalcula hmap
        wait_int();
        return;
    }

    if ((port_in(key_izq_port) & key_izq_mask) == 0) { //izquierda
        if (hx == 1) { // col 1: borde izquierdo (col 0 invisible)
            cambiar_mapa(DIR_IZQ);
            return;
        }

        if (vista != 3) { // primera pulsacion: orienta el sprite izquierda antes de mover (necesita 1 frame)
            vista = 3;
            restaura_fondo_tile();
            render_hero(hx*2,hy*2);
            wait_int();
            wait_int();
            wait_int(); // espera 3 interrupciones
            return;
        }

        if (es_solido(mapa_trabajo[hmap - 1])) { //cancelar movimiento tile solido
            return;
        }
        x8=(hx*2)-1; // medio char en la columna del tile actual (posicion intermedia)
        y8=hy*2;     // fila pixel del heroe (1 tile = 2 chars)
        restaura_fondo_tile();
        render_hero(x8,y8); // dibuja heroe en posicion intermedia (paso 1 de 2)
        x8=x8-1;            // avanza otro medio char hacia izquierda (posicion final del frame)
        wait_int();
        wait_int();         // espera 2 interrupciones para suavizar el movimiento
        render_tile(mapa_trabajo[hmap],hx,hy);      // borra tile origen
        render_tile(mapa_trabajo[hmap-1],hx-1,hy);  // borra tile destino
        render_hero(x8,y8);      // dibuja heroe en posicion final del frame
        hx--;
        calculo_frame();    // recalcula hmap
        wait_int();
        return;
    }

    if ((port_in(key_atk_port) & key_atk_mask)==0) { //espadazo
        if (attack_timer == 0) {
            attack_timer = 4; // la espada permanece visible 4 frames
            sonido_golpe();
            check_sword_hit();
        }
    }

    if ((port_in(key_men_port) & key_men_mask)==0) { //menu/reinicio
        cambiar_pantalla(PANTALLA_MENU);
    }

    if ((port_in(61438) & 16)==0) { //DEV: tecla 6 -> warp directo a entrada dungeon dngn_a2 (pruebas debug)
        mapa_actual = 51;
        hx = 7; hy = 4;
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
    }
}

// captura secuencialmente las 6 teclas de juego (arr/abj/izq/der/atk/menu).
void control_teclas_redefine(void) {
    unsigned int p;
    unsigned char b;

    if (redef_espera) { // evita que la misma tecla se registre varias veces seguidas
        if (all_keys_up()) redef_espera = 0;
        return;
    }

    if (!scan_any_key(&p, &b)) return;

    switch(redef_paso) {
        case 1: key_arr_port=p; key_arr_mask=b; break;
        case 2: key_abj_port=p; key_abj_mask=b; break;
        case 3: key_izq_port=p; key_izq_mask=b; break;
        case 4: key_der_port=p; key_der_mask=b; break;
        case 5: key_atk_port=p; key_atk_mask=b; break;
        case 6: key_men_port=p; key_men_mask=b; break;
    }
    redef_paso++;
    redef_espera = 1;

    if (redef_paso > 6) { //si todas redefinidas vuelve solo al menu
        redef_paso = 0;
        cambiar_pantalla(PANTALLA_MENU);
        return;
    }
    render_redefine_paso();
}

void control_teclas_menu(void) {
    if (redef_paso > 0) {
        control_teclas_redefine();
        return;
    }
    if ((port_in(63486)&1)==0) { //tecla 1 -> jugar (teclado)
        cambiar_pantalla(PANTALLA_JUEGO);
    }
    if ((port_in(63486)&2)==0) { //tecla 2 -> jugar (kempston) (sin uso)
        cambiar_pantalla(PANTALLA_JUEGO);
    }
    if ((port_in(63486)&4)==0) { //tecla 3 -> redefinir
        redef_paso   = 1;
        redef_espera = 1;
        render_redefine_paso();
    }
}

void control_teclas_game_over(void) {
    if ((port_in(63486)&1)==0) { //tecla 1 volver al menu antes de tiempo
        cambiar_pantalla(PANTALLA_MENU);
    }
}

void teclado(void) {
    switch(modo_app) {
        case PANTALLA_MENU:
            control_teclas_menu();
        break;
        case PANTALLA_JUEGO:
            control_teclas_juego();
        break;
        case PANTALLA_GAME_OVER:
            control_teclas_game_over();
        break;
    }
}
