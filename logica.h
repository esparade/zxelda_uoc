//zxelda v0.1a
//16mar'26

void animacion_hero(void) {
    switch(vista) {
        case 0:
            switch(anim) {
                case 0:
                    put_sprite_x16(anim1,hx*2,hy*2);
                    break;
                case 1:
                    put_sprite_x16(anim2,hx*2,hy*2);
                    break;
            }
            anim++;

            if (anim >= 2) {
                anim = 0;
            }
            break;

        case 1:
            switch(anim) {
                case 0:
                    put_sprite_x16(anim1b,hx*2,hy*2);
                    break;
                case 1:
                    put_sprite_x16(anim2b,hx*2,hy*2);
                    break;
            }
            anim--;

            if (anim <= -1) {
                anim = 1;
            }
            break;
    }
}

// Recalcula el indice plano hmap = hy*ancho_mapa+hx. Llamar tras cada cambio de hx/hy.
void calculo_frame(void) {
    hmap = hy*ancho_mapa+hx;
}

