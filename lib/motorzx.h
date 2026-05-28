// motorzx.h

// - COLORES -
// - TINTA -
// NEGRO	0	00000000
// AZUL		1	00000001
// ROJO		2	00000010
// MAGENTA	3	00000011
// VERDE	4	00000100
// TEAL		5	00000101
// AMARILLO	6	00000110
// BLANCO	7	00000111
//
// - PAPEL -
// NEGRO	0	00000000
// AZUL		8	00001000
// ROJO		16	00010000
// MAGENTA	24	00011000
// VERDE	32	00100000
// TEAL		40	00101000
// AMARILLO	48	00110000
// BLANCO	56	00111000

// Borra la pantalla a un color
void cls (int color) {
    #asm
        ld hl,2
		add hl,sp
		ld a, (hl)

		ld hl, 22528
		ld de, 22529
		ld bc, 767
		ld (hl), a
		ldir
		ld hl, 16384
		ld de, 16385
		ld bc, 6143
		ld (hl),l
		ldir
	#endasm
}

// Escribe en un puerto
void port_out (int port, int value) {
    #asm
    ld hl,2
	add hl,sp
	ld a, (hl)
	inc hl
	inc hl
	ld c, (hl)
	inc hl
	ld b, (hl)
	out (c),a
	#endasm
}

// Lee un puerto
int __FASTCALL__ port_in (int port) {
    #asm
        ld      b, h
        ld      c, l
        ld      h, 0
        in      l, (c)
	#endasm
}

// Espera interrupcion (sincroniza con el refresco de pantalla)
void wait_int (void) {
    #asm
        halt
    #endasm
}

// Sprite 8x8 sin escribir atributo
// Formato: 8 bytes de pixeles
void put_sprite_x8_noclr (unsigned char *posicion, unsigned int x, unsigned int y) {
	#asm
		ld hl,2
		add hl,sp
		ld d, (hl)
		inc hl
		inc hl
		ld e, (hl)
		inc hl
		inc hl
		ld a, (hl)
		inc hl
		ld h, (hl)
		ld l, a
		ld a, d
		and 7
		rrca
		rrca
		rrca
		and 224
		or e
		ld e, a
		ld a, d
		and 24
		or 64
		ld d, a
		ld b, 8
		ld c, 255
	.draw9nc
		ldi
		dec de
		inc d
		djnz draw9nc
		ret
	#endasm
}

// Sprite 8x8 con mascara y atributo
// Formato: mask0,pix0, mask1,pix1, ..., mask7,pix7, attr
void put_sprite_x8_mask (unsigned char *posicion, unsigned int x, unsigned int y) {
	#asm
		ld hl,2
		add hl,sp
		ld d, (hl)
		inc hl
		inc hl
		ld e, (hl)
		inc hl
		inc hl
		ld a, (hl)
		inc hl
		ld h, (hl)
		ld l, a
		ld a, d
		and 7
		rrca
		rrca
		rrca
		and 224
		or e
		ld e, a
		ld a, d
		and 24
		or 64
		ld d, a
		push de
		ld b, 8
	.draw9m
		ld a, (de)
		and (hl)
		inc hl
		or (hl)
		ld (de), a
		inc hl
		inc d
		djnz draw9m
		pop de
		ld a,d
		rra
		rra
		rra
		and 3
		or 88
		ld d,a
		ldi
		ret
	#endasm
}

// Sprite 16x16 a color
void put_sprite_x16 (unsigned char *posicion, unsigned int x, unsigned int y) {
	#asm
		ld hl,2
		add hl,sp
		ld d, (hl)
		inc hl
		inc hl
		ld e, (hl)
		inc hl
		inc hl
		ld a, (hl)
        inc hl
        ld h, (hl)
        ld l, a
		ld a, d
		and 7
		rrca
	    rrca
	    rrca
		and 224
		or e
		ld e, a
		ld a, d
		and 24
		or 64
		ld d, a
		push de
		push de
		ld b, 8
		ld c,255
		call draw
		pop de
		ld a,e
		add a,32
		ld e,a
		jr nc, salto
		ld a,d
		add a,8
		ld d,a
		.salto
		ld b, 8
		ld c,255
		call draw
		pop de
		ld a,d
	    rra
	    rra
	    rra
        and 3
        or 88
        ld d,a
        push de
        ldi
        ldi
        pop de
        ld a,e
		add a,32
        ld e,a
		ld a,d
		adc a,0
		ld d,a
        ldi
		ldi
		ret

		.draw
		ldi
		ldi
		dec de
		dec de
		inc d
		djnz draw
		ret
	#endasm
}

// Sprite 16x16 con mascara e ink (conserva papel del tile, aplica tinta del sprite)
void put_sprite_x16_mask_ink (unsigned char *posicion, unsigned int x, unsigned int y) {
	#asm
		ld hl,2
		add hl,sp
		ld d, (hl)
		inc hl
		inc hl
		ld e, (hl)
		inc hl
		inc hl
		ld a, (hl)
		inc hl
		ld h, (hl)
		ld l, a
		ld a, d
		and 7
		rrca
		rrca
		rrca
		and 224
		or e
		ld e, a
		ld a, d
		and 24
		or 64
		ld d, a
		push de
		push de
		ld b, 8
		call drawmxi
		pop de
		ld a, e
		add a, 32
		ld e, a
		jr nc, saltomxi
		ld a, d
		add a, 8
		ld d, a
		.saltomxi
		ld b, 8
		call drawmxi
		pop de
		ld a, d
		rra
		rra
		rra
		and 3
		or 88
		ld d, a
		push de
		ld a, (hl)
		and 7
		ld c, a
		ld a, (de)
		and 248
		or c
		ld (de), a
		inc hl
		inc de
		ld a, (hl)
		and 7
		ld c, a
		ld a, (de)
		and 248
		or c
		ld (de), a
		inc hl
		inc de
		pop de
		ld a, e
		add a, 32
		ld e, a
		ld a, d
		adc a, 0
		ld d, a
		ld a, (hl)
		and 7
		ld c, a
		ld a, (de)
		and 248
		or c
		ld (de), a
		inc hl
		inc de
		ld a, (hl)
		and 7
		ld c, a
		ld a, (de)
		and 248
		or c
		ld (de), a
		ret

		.drawmxi
		ld a, (de)
		ld c, a
		ld a, (hl)
		cpl
		and c
		or (hl)
		ld (de), a
		inc hl
		inc de
		ld a, (de)
		ld c, a
		ld a, (hl)
		cpl
		and c
		or (hl)
		ld (de), a
		inc hl
		dec de
		inc d
		djnz drawmxi
		ret
	#endasm
}

// Sprite 8x16 a color
void put_sprite_8x16 (unsigned char *posicion, unsigned int x, unsigned int y) {
	#asm
		ld hl,2
		add hl,sp
		ld d, (hl)
		inc hl
		inc hl
		ld e, (hl)
		inc hl
		inc hl
		ld a, (hl)
        inc hl
        ld h, (hl)
        ld l, a
		ld a, d
		and 7
		rrca
        rrca
        rrca
		and 224
		or e
		ld e, a
		ld a, d
		and 24
		or 64
		ld d, a
		push de
		push de
		ld b, 8
		ld c,255
		call draw7
		pop de
		ld a,e
		add a,32
		ld e,a
		jr nc, salto13
		ld a,d
		add a,8
		ld d,a
		.salto13
		ld b, 8
		call draw7
		pop de
		ld a,d
        rra
        rra
        rra
        and 3
        or 88
        ld d,a
		push de
		ldi
		pop de
		ld a,e
		add a,32
		ld e,a
		ldi
		ret

		.draw7
		ldi
		dec de
		inc d
		djnz draw7
		ret
	#endasm
}

// Sprite 16x8 a color
void put_sprite_16x8 (unsigned char *posicion, unsigned int x, unsigned int y) {
	#asm
		ld hl,2
		add hl,sp
		ld d, (hl)
		inc hl
		inc hl
		ld e, (hl)
		inc hl
		inc hl
		ld a, (hl)
        inc hl
        ld h, (hl)
        ld l, a
		ld a, d
		and 7
		rrca
        rrca
        rrca
		and 224
		or e
		ld e, a
		ld a, d
		and 24
		or 64
		ld d, a
		push de
		ld b, 8
		ld c,255
		.draw8
		ldi
		ldi
		dec de
		dec de
		inc d
		djnz draw8
		pop de
		ld a,d
        rra
        rra
        rra
        and 3
        or 88
        ld d,a
		ldi
		ldi
		ret
	#endasm
}
