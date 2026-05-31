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
case PANTALLA_MENU:
                if (++jgh_timer < 2) break;
                jgh_timer = 0;
                {
                    static unsigned char color_seq[] = {5, 4, 3, 2, 1, 0};
                    unsigned char attr;
                    if (++jgh_color >= 6) jgh_color = 0;
                    attr = color_seq[jgh_color];
                    *((unsigned char *)(22528 + (unsigned int)22 * 32 + 25)) = attr;
                    *((unsigned char *)(22528 + (unsigned int)22 * 32 + 26)) = attr;
                    *((unsigned char *)(22528 + (unsigned int)22 * 32 + 27)) = attr;
                    *((unsigned char *)(22528 + (unsigned int)7 * 32 + 13)) = attr;
                    *((unsigned char *)(22528 + (unsigned int)7 * 32 + 14)) = attr;
                    *((unsigned char *)(22528 + (unsigned int)7 * 32 + 15)) = attr;
                    *((unsigned char *)(22528 + (unsigned int)7 * 32 + 16)) = attr;
                    *((unsigned char *)(22528 + (unsigned int)7 * 32 + 17)) = attr;
                    *((unsigned char *)(22528 + (unsigned int)7 * 32 + 18)) = attr;
                }
            break;

            case PANTALLA_JUEGO:
                calculo_frame();
                check_warp();
                check_puerta6();
                check_llave();
                check_corazon();
                check_power();
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
                if (game_over_timer > 0) game_over_timer--;
                else cambiar_pantalla(PANTALLA_MENU);
            break;
        }
        teclado();

        wait_int();
        wait_int();
        wait_int();
    }
}
