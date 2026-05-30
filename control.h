int x8,y8;

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

// Cambia al mapa adyacente en la direccion dada y coloca al heroe en el borde de entrada opuesto.
// Columnas 0 y 15 son relleno invisible (VO), por eso los limites son col 1/14 y fila 0/8.
void cambiar_mapa(unsigned char dir) {
    unsigned char destino = get_mapa_conexion(mapa_actual, dir);
    if (destino == 0) return; // sin conexion en esa direccion
    if (destino == 6) mapa_anterior = mapa_actual; // guarda origen solo al entrar en mapa6
    mapa_actual = destino;
    carga_datos_mapa();
    switch(dir) {
        // coloca al heroe en el borde opuesto al que salio
        case DIR_DER: hx = 1;             break; // salio por derecha -> entra por izquierda
        case DIR_IZQ: hx = ancho_mapa-2;  break; // salio por izquierda -> entra por derecha
        case DIR_ABA: hy = 0;             break; // salio por abajo -> entra por arriba
        case DIR_ARR: hy = alto_mapa-1;   break; // salio por arriba -> entra por abajo
    }
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

void control_teclas_juego (void) {
    if ((port_in(key_arr_port) & key_arr_mask) == 0) { //arriba
        if (hy == 0) { // fila 0: borde superior, cambia de sala
            cambiar_mapa(DIR_ARR);
            return;
        }

        if (vista != 0) { // primer pulso: orienta el sprite antes de mover (consume 1 frame)
            vista = 0;
            restaura_fondo_tile();
            render_hero(hx*2,hy*2);
            wait_int();
            wait_int();
            wait_int();
            return;
        }

        if (es_solido(mapa_trabajo[hmap-ancho_mapa])) {
            return;
        }
        x8=hx*2;
        y8=(hy*2)-1;
        restaura_fondo_tile();
        render_hero(x8,y8);
        y8=y8-1;
        wait_int();
        wait_int();
        render_tile(mapa_trabajo[hmap],hx,hy);
        render_tile(mapa_trabajo[hmap-ancho_mapa],hx,hy-1);
        render_hero(x8,y8);
        hy--;
        calculo_frame();
        wait_int();
        return;
    }

    if ((port_in(key_der_port) & key_der_mask) == 0) { //derecha
        if (hx==ancho_mapa-2) { // col 14: borde derecho (col 15 es relleno invisible)
            cambiar_mapa(DIR_DER);
            return;
        }

        if (vista !=1) { //animacion plyr der
            vista = 1;
            restaura_fondo_tile();
            render_hero(hx*2,hy*2);
            wait_int();
            wait_int();
            wait_int();
            return;
        }

        if (es_solido(mapa_trabajo[hmap+1])) {
            return;
        }
        x8=(hx*2)+1;
        y8=hy*2;
        restaura_fondo_tile();
        render_hero(x8,y8);
        x8=x8+1;
        wait_int();
        wait_int();
        render_tile(mapa_trabajo[hmap],hx,hy);
        render_tile(mapa_trabajo[hmap+1],hx+1,hy);
        render_hero(x8,y8);
        hx++;
        calculo_frame();
        wait_int();
        return;
    }

    if ((port_in(key_abj_port) & key_abj_mask) == 0) { //abajo
        if (hy == alto_mapa-1) { // fila 8: borde inferior, cambia de sala
            cambiar_mapa(DIR_ABA);
            return;
        }

        if (vista != 2) { //anim plyr mov izq
            vista = 2;
            restaura_fondo_tile();
            render_hero(hx*2,hy*2);
            wait_int();
            wait_int();
            wait_int();
            return;
        }

        if (es_solido(mapa_trabajo[hmap+ancho_mapa])) {
            return;
        }
        x8=hx*2;
        y8=(hy*2)+1;
        restaura_fondo_tile();
        render_hero(x8,y8);
        y8=y8+1;
        wait_int();
        wait_int();
        render_tile(mapa_trabajo[hmap],hx,hy);
        render_tile(mapa_trabajo[hmap+ancho_mapa],hx,hy+1);
        render_hero(x8,y8);
        hy++;
        calculo_frame();
        wait_int();
        return;
    }

    if ((port_in(key_izq_port) & key_izq_mask) == 0) { //izquierda
        if (hx == 1) { // col 1: borde izquierdo (col 0 es relleno invisible)
            cambiar_mapa(DIR_IZQ);
            return;
        }

        if (vista != 3) { //anim plyr mov izq
            vista = 3;
            restaura_fondo_tile();
            render_hero(hx*2,hy*2);
            wait_int();
            wait_int();
            wait_int();
            return;
        }

        if (es_solido(mapa_trabajo[hmap - 1])) {
            return;
        }

        //restaura_fondo_tile();
        //hx--;
        //calculo_frame();
        x8=(hx*2)-1;
        y8=hy*2;
        restaura_fondo_tile();
        render_hero(x8,y8);
        x8=x8-1;
        wait_int();
        wait_int();
        render_tile(mapa_trabajo[hmap],hx,hy);
        render_tile(mapa_trabajo[hmap-1],hx-1,hy);
        render_hero(x8,y8);
        hx--;
        calculo_frame();
        wait_int();
        return;
    }

    if ((port_in(key_atk_port) & key_atk_mask)==0) { //ataque
        if (attack_timer == 0) {
            attack_timer = 4; // la espada permanece visible 4 frames
            sonido_golpe();
            check_sword_hit();
        }
    }

    if ((port_in(61438)&1)==0) { //tecla 0 -> menu
        cambiar_pantalla(PANTALLA_MENU);
    }
}

void control_teclas_intro(void) {
    if ((port_in(63486)&1)==0) { //tecla 1 -> menu
        cambiar_pantalla(PANTALLA_MENU);
    }
}

// Captura una tecla por cada accion (arr/abj/izq/der/atk) y la almacena como port+mascara.
// Avanza redef_paso hasta 5; al terminar vuelve al menu.
void control_teclas_redefine(void) {
    unsigned int p;
    unsigned char b;

    if (redef_espera) {
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
    }
    redef_paso++;
    redef_espera = 1;

    if (redef_paso > 5) {
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
    if ((port_in(63486)&2)==0) { //tecla 2 -> jugar (kempston)
        cambiar_pantalla(PANTALLA_JUEGO);
    }
    if ((port_in(63486)&4)==0) { //tecla 3 -> redefinir
        redef_paso   = 1;
        redef_espera = 1;
        render_redefine_paso();
    }
}

void control_teclas_game_over(void) {
    if ((port_in(63486)&1)==0) { //tecla 1 -> menu
        cambiar_pantalla(PANTALLA_MENU);
    }
}

void teclado(void) {
    switch(modo_app) {
        case PANTALLA_INTRO:
            control_teclas_intro();
        break;
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
