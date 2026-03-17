//zxelda v0.1a
//16mar'26

int x8,y8;

void control_teclas_juego (void) {
    if ((port_in(64510)&1) == 0 && hy > 0) { //tecla Q
        if (mapa_trabajo[hmap-ancho_mapa] == 1) {
            return;
        }
        //restaura_fondo_tile();
        //hy--;
        //calculo_frame();
        x8=hx*2;
        y8=(hy*2)-1;
        restaura_fondo_tile();
        render_hero(x8,y8);
        y8=y8-1;
        wait_int();
        wait_int();
        render_tile(mapa_trabajo[hmap],hx,hy);
        render_hero(x8,y8);
        hy--;
        calculo_frame();
        wait_int();
        return;
    }

    if ((port_in(65022)&1) == 0 && hy < alto_mapa - 1) { //tecla A
        if (mapa_trabajo[hmap+ancho_mapa] == 1) {
            return;
        }
        //restaura_fondo_tile();
        //hy++;
        //calculo_frame();
        x8=hx*2;
        y8=(hy*2)+1;
        restaura_fondo_tile();
        render_hero(x8,y8);
        y8=y8+1;
        wait_int();
        wait_int();
        render_tile(mapa_trabajo[hmap],hx,hy);
        render_hero(x8,y8);
        hy++;
        calculo_frame();
        wait_int();
        return;
    }

    if ((port_in(57342)&2) == 0) { //tecla O
        if (hx == 0) { //cambio mapa izq
            mapa_actual--;
            carga_datos_mapa();
            hx=ancho_mapa-1;
            render_mapa();
            return;
        }

        if (vista != 1) { // primer pulso: orienta el sprite antes de mover (consume 1 frame)
            vista = 1;
            render_hero(hx*2,hy*2);
            wait_int();
            wait_int();
            wait_int();
            return;
        }

        if (mapa_trabajo[hmap - 1] == 1) {
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
        render_hero(x8,y8);
        hx--;
        calculo_frame();
        wait_int();
        return;
    }

    if ((port_in(57342)&1) == 0) { //tecla P
        if (hx==ancho_mapa-1) { //cambio mapa der
            mapa_actual++;
            carga_datos_mapa();
            hx=0;
            render_mapa();
            return;
        }

        if (vista !=0) { // primer pulso: orienta el sprite antes de mover (consume 1 frame)
            vista = 0;
            render_hero(hx*2,hy*2);
            wait_int();
            wait_int();
            wait_int();
            return;
        }

        if (mapa_trabajo[hmap+1]==1) {
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
        render_hero(x8,y8);
        hx++;
        calculo_frame();
        wait_int();
        return;
    }

    if ((port_in(61438)&1)==0) { //tecla 0 -> menu
        modo_app=0;
        cls(0);
        render_menu();
    }
}

void control_teclas_menu(void) {
    if ((port_in(63486)&1)==0) { //tecla 1 -> jugar
        modo_app=1;
        cls(0);
        inicia_variables_juego();
        render_mapa();
    }
}

void teclado(void) {
    switch(modo_app) {
        case 0:
            control_teclas_menu();
        break;

        case 1:
            control_teclas_juego();
        break;
    }
}
