#include "barracarregamento.h"
#include "st7789/st7789.h"
#include <stdio.h>

void DrawLoadingBar(uint16_t atual, uint16_t total)
{
	uint8_t progress = (atual * 100) / total;
    uint16_t x = 45;
    uint16_t y = 75;

    uint16_t largura = 150;
    uint16_t altura = 14;

    // fundo
    ST7789_DrawFilledRectangle(
        x,
        y,
        largura,
        altura,
        BLACK
    );

    // borda
    ST7789_DrawRectangle(
        x,
        y,
        x + largura - 1,
        y + altura - 1,
        WHITE
    );

    // preenchimento
    uint16_t preenchido =
        ((largura - 4) * progress) / 100;

    ST7789_DrawFilledRectangle(
        x + 2,
        y + 2,
        preenchido,
        altura - 4,
        GREEN
    );

    // texto
    char texto[10];

    sprintf(texto, "%d%%", progress);

    ST7789_WriteString(
        200,
        80,
        texto,
        Font_7x10,
        WHITE,
        BLACK
    );
}
