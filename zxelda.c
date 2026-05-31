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

#pragma output STACKPTR = 65000  // pila al final de RAM, por encima de los datos de sprites/mapas

void main (void) {
    inicia_teclas();
    init_pantalla();
    cambiar_pantalla(PANTALLA_MENU);

    while(!zx_break()) { // gameloop infinito; solo sale pulsando BREAK
        switch(modo_app) {
            case PANTALLA_MENU:
                if (++jgh_timer < 2) break; // 1 cambio de color cada 2 frames
                jgh_timer = 0;
                {
                    // anima ciclo de colores en la pantalla del titulo
                    static unsigned char color_seq[] = {5, 4, 3, 2, 1, 0};
                    unsigned char attr;
                    if (++jgh_color >= 6) jgh_color = 0;
                    attr = color_seq[jgh_color];
                    *((unsigned char *)(22528 + (unsigned int)7 * 32 + 13)) = attr; // z
                    *((unsigned char *)(22528 + (unsigned int)7 * 32 + 14)) = attr; // x
                    *((unsigned char *)(22528 + (unsigned int)7 * 32 + 15)) = attr; // e
                    *((unsigned char *)(22528 + (unsigned int)7 * 32 + 16)) = attr; // l
                    *((unsigned char *)(22528 + (unsigned int)7 * 32 + 17)) = attr; // d
                    *((unsigned char *)(22528 + (unsigned int)7 * 32 + 18)) = attr; // a
                    *((unsigned char *)(22528 + (unsigned int)22 * 32 + 25)) = attr; // j
                    *((unsigned char *)(22528 + (unsigned int)22 * 32 + 26)) = attr; // g
                    *((unsigned char *)(22528 + (unsigned int)22 * 32 + 27)) = attr; // h
                }
            break;

            case PANTALLA_JUEGO:
                calculo_frame();
                check_warp();
                check_puerta();
                check_llave();
                check_corazon();
                check_power();
                anima_llave();
                if (inv_timer > 0) inv_timer--; // invul heroe tras recibir daño (40 frames, 0,8seg a 50hz)
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
                if (game_over_timer > 0) game_over_timer--; // mensaje de game over expira tras un tiempo (3segs) y vuelve solo al menu
                else cambiar_pantalla(PANTALLA_MENU);
            break;
        }
        teclado();

        wait_int(); // 3 interrupciones a 50Hz = ~60ms por frame (~16fps)
        wait_int();
        wait_int();
    }
}
