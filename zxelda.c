//zxelda v0.1a
//16mar'26

#include <stdio.h>

#include <lib\motorzx.h>
#include <lib\sonidoszx.h>

#include <config.h>
#include <variables.h>
#include <graficos.h>
#include <pantalla.h>
#include <logica.h>
#include <control.h>

#pragma output STACKPTR = 65000

void main (void) {
    init_pantalla();

    switch(modo_app) {
        case 0:
            render_menu();
        break;
        case 1:
            render_mapa();
        break;
    }

    while(!zx_break()) { //hasta pulsar break
        switch(modo_app) {
            case 0: //render_menu();
            break;

            case 1:
                calculo_frame();
                animacion_hero();
            break;
    }
        teclado();

        wait_int();
        wait_int();
        wait_int();
    }
}
