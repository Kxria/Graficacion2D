#include "draw.h"
#include "linea.h"

void draw_cuadrado(int x0, int y0, int largo, int altura, uint32_t color){
    int x1 = x0 + largo;
    int y1 = y0 + altura;

    draw_linea(x0, y0, x1, y0, color);
    draw_linea(x1, y0, x1, y1, color);
    draw_linea(x1, y1, x0, y1, color);
    draw_linea(x0, y1, x0, y0, color);
}