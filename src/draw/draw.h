#pragma once

#include "../math/vectores.h"
#include "linea.h"
#include "figuras.h"

#include <stdint.h>

void draw_pixel(int x, int y, uint32_t color);
void draw_trian(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void draw_cuadrado(int x0, int y0, int largo, int altura, uint32_t color);
void draw_circuloTrig(int radio , int x0, int y0, int numvertices, uint32_t color);
void draw_circuloPM(int radio , int x0, int y0, uint32_t color);
void draw_linea(int x0, int y0, int x1, int y1, uint32_t color);

// Curvas
void draw_linea_lerp(Vec2 p1, Vec2 p2, uint32_t color);
void draw_curva(Vec2 p1, Vec2 p2, Vec2 p3, uint32_t color);

// test
int puedeRellenar(int x, int y, uint32_t colorRelleno, uint32_t colorBorde);
void rellenar_generico(int x, int y, uint32_t colorRelleno, uint32_t colorBorde);
void fill_circulo(Circulo *c, uint32_t color);
void fill_cuadrado(Cuadro *c, uint32_t color);

// Relleno triangulo
void fill_triangulo(Triangulo *triangulo, uint32_t color);