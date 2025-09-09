#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../math/Estructuras/pila.h"
#include "../math/Estructuras/nodo.h"
#include "figuras.h"
#include "draw.h"
#include "../color/colores.h"

/*
extern uint32_t *pixel_buffer;

// Estructura auxiliar para coordenadas
typedef struct {
    int x;
    int y;
} Pixel;

// ---------------------- RELLENO GENÉRICO ---------------------- //

uint32_t get_pixel(int x, int y) {
    if (x < 0 || y < 0 || x >= 1080 || y >= 720) return 0; // fuera de rango
    return pixel_buffer[y * 1080 + x];
}

int puedeRellenar(int x, int y, uint32_t colorRelleno, uint32_t colorBorde) {
    uint32_t actual = get_pixel(x, y);   // función que ya tienes para leer el color en (x,y)
    return (actual != colorRelleno && actual != colorBorde);
}

void rellenar_generico(int x, int y, uint32_t colorRelleno, uint32_t colorBorde) {
    Pila pila;
    inicializarPila(&pila);

    Pixel *inicio = malloc(sizeof(Pixel));
    inicio->x = x;
    inicio->y = y;
    push(&pila, inicio);

    while (!pilaVacia(&pila)){
        Pixel *p = (Pixel*)pop(&pila);
        
        if (!p) {
            continue;
        }

        if (puedeRellenar(p->x, p->y, colorRelleno, colorBorde)){
            draw_pixel(p->x, p->y, colorRelleno);

            int dx[4] = {1, -1, 0, 0};
            int dy[4] = {0, 0, 1, -1};

            for (int i = 0 ; i < 4 ; i++){
                Pixel *vecino = calloc(1, sizeof(Pixel));
                vecino->x = p->x + dx[i];
                vecino->y = p->y + dy[i];
                push(&pila, vecino);
            }
        }
    }

    freePila(&pila);
}

// ---------------------- FUNCIONES ESPECÍFICAS ---------------------- //
void fill_circulo(Circulo *c, uint32_t color) {
    int cx = (int)c->pos.unpack.x;
    int cy = (int)c->pos.unpack.y;
    rellenar_generico(cx, cy, 0xFFFFFFFF, c->color.hex); 
}

void fill_cuadrado(Cuadro *c, uint32_t color) {
    int cx = c->pos.unpack.x/ 2;
    int cy = c->pos.unpack.y / 2;
    rellenar_generico(cx, cy, 0xFFFFFFFF, c->color.hex);
}

// ---------------------- FUNCIONES ORG ---------------------- //

*/

void fill_flat_bottom(Vec2 p1,Vec2 p2, Vec2 p3, uint32_t color);
void fill_flat_top(Vec2 p1,Vec2 p2, Vec2 p3, uint32_t color);
void ordenar_y(Vec2 *y);

void fill_triangulo(Triangulo *triangulo, uint32_t color){
    // Ordenar
    float cy, cx;

    Vec2 y[3] = {triangulo -> p1, triangulo -> p2, triangulo -> p3};
    ordenar_y(y);

    // Pintar
    if (y[1].unpack.y == y[2].unpack.y) {
        fill_flat_bottom(y[0], y[1], y[2], color);
    } else if (y[0].unpack.y == y[1].unpack.y) {
        fill_flat_top(y[0], y[1], y[2], color);
    } else {
        cy = y[1].unpack.y;
        cx = (y[1].unpack.y - y[0].unpack.y) * (y[2].unpack.x - y[0].unpack.x) / (y[2].unpack.y - y[0].unpack.y) + y[0].unpack.x;

        Vec2 v = {{cx, cy}};
        fill_flat_bottom(y[0], y[1], v, color);
        fill_flat_top(v, y[1], y[2], color);
    }

}

void ordenar_y(Vec2 *y){
    Vec2 aux;

    for(int i = 0; i < 3; i++){
        for(int j = i + 1; j < 3; j++){
            if(y[i].unpack.y > y[j].unpack.y){
                aux = y[i];
                y[i] = y[j];
                y[j] = aux;
            }
        }
    }
}

void fill_flat_bottom(Vec2 p2, Vec2 p3, Vec2 c, uint32_t color){
    float mi = (p3.unpack.x - p2.unpack.x) / (p3.unpack.y - p2.unpack.y);
    float mf = (c.unpack.x - p2.unpack.x) / (c.unpack.y - p2.unpack.y);

    float xi = p2.unpack.x;
    float xf = p2.unpack.x;

    for (int y = (int)p2.unpack.y; y <= (int)c.unpack.y; y++) {
        draw_linea(xi, y, xf, y, color);
        xi += mi;
        xf += mf;
    }
}

void fill_flat_top(Vec2 p1, Vec2 p2 ,Vec2 c, uint32_t color){
    float mi = (c.unpack.x - p1.unpack.x) / (c.unpack.y - p1.unpack.y);
    float mf = (c.unpack.x - p2.unpack.x) / (c.unpack.y - p2.unpack.y);

    float xi = c.unpack.x;
    float xf = c.unpack.x;

    for (int y = (int)c.unpack.y; y >= (int)p1.unpack.y; y--) {
        draw_linea(xi, y, xf, y, color);
        xi -= mi;
        xf -= mf;
    }
}