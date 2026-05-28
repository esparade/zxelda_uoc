// sonidoszx.h

extern unsigned char borde_actual;

void sonido_andar (void) {
	port_out (254, borde_actual | 16);
	port_out (254, borde_actual | 16);
	port_out(254, borde_actual);
	port_out (254, borde_actual | 16);
	port_out (254, borde_actual | 16);
	port_out(254, borde_actual);
}

void sonido_golpe (void) {
	unsigned char i, j;
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 16; j++) port_out(254, borde_actual | 16);
		for (j = 0; j < 16; j++) port_out(254, borde_actual);
	}
}

void sonido_corazon (void) {
	unsigned char i;
	for (i = 0; i < 35; i++) {
		port_out(254, borde_actual | 16);
		port_out(254, borde_actual | 16);
		port_out(254, borde_actual | 16);
		port_out(254, borde_actual | 16);
		port_out(254, borde_actual);
		port_out(254, borde_actual);
		port_out(254, borde_actual);
		port_out(254, borde_actual);
	}
	for (i = 0; i < 40; i++) {
		port_out(254, borde_actual | 16);
		port_out(254, borde_actual | 16);
		port_out(254, borde_actual | 16);
		port_out(254, borde_actual);
		port_out(254, borde_actual);
		port_out(254, borde_actual);
	}
}

void sonido_danio (void) {
	unsigned char i;
	for (i = 0; i < 12; i++) {
		port_out(254, borde_actual | 16);
		port_out(254, borde_actual);
	}
	for (i = 0; i < 24; i++) {
		port_out(254, borde_actual | 16);
		port_out(254, borde_actual | 16);
		port_out(254, borde_actual);
		port_out(254, borde_actual);
	}
}

void sonido_secreto (void) {
    unsigned char i;
    for (i = 0; i < 20; i++) {
        port_out(254, borde_actual | 16);
        port_out(254, borde_actual | 16);
        port_out(254, borde_actual | 16);
        port_out(254, borde_actual | 16);
        port_out(254, borde_actual | 16);
        port_out(254, borde_actual | 16);
        port_out(254, borde_actual | 16);
        port_out(254, borde_actual | 16);
        port_out(254, borde_actual);
        port_out(254, borde_actual);
        port_out(254, borde_actual);
        port_out(254, borde_actual);
        port_out(254, borde_actual);
        port_out(254, borde_actual);
        port_out(254, borde_actual);
        port_out(254, borde_actual);
    }
    for (i = 0; i < 28; i++) {
        port_out(254, borde_actual | 16);
        port_out(254, borde_actual | 16);
        port_out(254, borde_actual | 16);
        port_out(254, borde_actual | 16);
        port_out(254, borde_actual);
        port_out(254, borde_actual);
        port_out(254, borde_actual);
        port_out(254, borde_actual);
    }
    for (i = 0; i < 36; i++) {
        port_out(254, borde_actual | 16);
        port_out(254, borde_actual | 16);
        port_out(254, borde_actual);
        port_out(254, borde_actual);
    }
    for (i = 0; i < 50; i++) {
        port_out(254, borde_actual | 16);
        port_out(254, borde_actual);
    }
}

void sonido_llave (void) {
	unsigned char i;
	for (i = 0; i < 20; i++) {
		port_out(254, borde_actual | 16);
		port_out(254, borde_actual | 16);
		port_out(254, borde_actual | 16);
		port_out(254, borde_actual);
		port_out(254, borde_actual);
		port_out(254, borde_actual);
	}
	for (i = 0; i < 28; i++) {
		port_out(254, borde_actual | 16);
		port_out(254, borde_actual | 16);
		port_out(254, borde_actual);
	}
	for (i = 0; i < 36; i++) {
		port_out(254, borde_actual | 16);
		port_out(254, borde_actual);
	}
}
