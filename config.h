#define NUMERO_DE_VIDAS 3

// pantallas / screens
#define PANTALLA_MENU     0
#define PANTALLA_JUEGO    1
// #define PANTALLA_INVENTARIO 2
#define PANTALLA_GAME_OVER 3

// offset de render del mapa en pantalla (chars)
// centrado en x, alineado abajo en y
// pantalla ZX: 32x24 chars, tile: 2x2 chars, mapa: 14x9 tiles
#define MAPA_OX 0   // 16*2 = 32 = ancho pantalla ZX
#define MAPA_OY 6   // 24 - 9*2

// direcciones de cambio de mapa
#define DIR_ARR 0
#define DIR_DER 1
#define DIR_ABA 2
#define DIR_IZQ 3