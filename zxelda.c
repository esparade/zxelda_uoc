#include <stdio.h>

#include <lib\motorzx.h>
#include <lib\sonidoszx.h>

#include <config.h>
#include <mapas.h>
#include <variables.h>
#include <graficos.h>
#include <pantalla.h>
#include <logica.h>
#include <control.h>

#pragma output STACKPTR = 65000

void main (void) {
    inicia_teclas();
    init_pantalla();
    cambiar_pantalla(PANTALLA_MENU);

    while(!zx_break()) { //infinte loop
        switch(modo_app) {
            case PANTALLA_INTRO:
            break;

            case PANTALLA_MENU:
            break;

            case PANTALLA_JUEGO:
                calculo_frame();
                check_warp();
                check_puerta6();
                check_llave();
                check_corazon();
                anima_llave();
                if (inv_timer > 0) inv_timer--;
                mueve_heavy();
                animacion_heavy();
                mueve_heavy2();
                animacion_heavy2();
                mueve_octo1();
                animacion_octo1();
                mueve_octo2();
                animacion_octo2();
                mueve_octo1_shot();
                animacion_octo1_shot();
                mueve_octo2_shot();
                animacion_octo2_shot();
                check_boss_contact();
                mueve_boss();
                animacion_boss();
                mueve_boss_shot();
                animacion_boss_shot();
                render_npc();
                update_attack();
            break;

            case PANTALLA_GAME_OVER:
            break;
        }
        teclado();

        wait_int();
        wait_int();
        wait_int();
    }
}
