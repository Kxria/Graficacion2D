#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../global.h"
#include "../Estructuras/pila.h"
#include "../color/colores.h"
#include "figuras.h"
#include "draw.h"


// ---------------------- FUNCIONES ESPECÍFICAS ---------------------- //

void rellenar_figura(void *figura, uint32_t color) {
    Figuras *DUMMY = (Figuras*)figura;

    switch(DUMMY -> data.type) {
        case CIRC: {
            Circulo *circulo = (Circulo*)DUMMY;
            rellenar(&(circulo -> pos), color);
            break;
        }

        case CUADRO: {
            Cuadro *cuadrado = (Cuadro*)DUMMY;

            int x = cuadrado -> pos.unpack.x + (cuadrado -> w / 2);
            int y = cuadrado -> pos.unpack.y + (cuadrado -> h / 2);

            Vec2 puntoM = {{x, y}};
            puntoM.unpack.x = x;
            puntoM.unpack.y = y;

            rellenar(&puntoM, color);
            break;
        }

        case TRIAN: {
            Triangulo *triangulo = (Triangulo*)DUMMY;
            fill_triangulo(triangulo, color);
            break;
        }

        default:
            break;
    }
}
/*
void rellenar(Vec2 *pInicial, uint32_t fill_color) {
    Pila *pila = (Pila*)calloc(1, sizeof(Pila));

    int total_pixeles = estadosrender.w_height * estadosrender.w_width;
    char *verificado = (char*)calloc(total_pixeles, sizeof(char));

    Vec2 *pixel = malloc(sizeof(Vec2));
    pixel->unpack.x = pInicial->unpack.x;
    pixel->unpack.y = pInicial->unpack.y;

    push(pila, pixel);

    uint32_t colorObj = getColor(pixel);

    while(pila -> tope != NULL){
        pixel = (Vec2*)pop(pila);
        int x = pixel -> unpack.x;
        int y = pixel -> unpack.y;

        int idx = y * estadosrender.w_width + x;

        if(x >= 0 && x < estadosrender.w_width &&
           y >= 0 && y < estadosrender.w_height &&
           verificado[idx] == 0 &&
           getColor(pixel) == colorObj)
        {
            draw_pixel(x, y, fill_color);
            verificado[idx] = 1;

            Vec2 vecinos[4] = {{{1, 0}},
                               {{-1, 0}},
                               {{0, 1}},
                               {{0, -1}}};

            for(int i = 0; i < 4; i++){
                int newX = x + vecinos[i].unpack.x;
                int newY = y + vecinos[i].unpack.y;

                if(newX >= 0 && newX < estadosrender.w_width &&
                   newY >= 0 && newY < estadosrender.w_height)
                {
                    int pixelPos = newY * estadosrender.w_width + newX;
                    if(verificado[pixelPos] == 0){
                        Vec2 *objetivo = malloc(sizeof(Vec2));
                        objetivo->unpack.x = newX;
                        objetivo->unpack.y = newY;
                        push(pila, objetivo);
                    }
                }
            }
        }
        free(pixel);
    }

    free(verificado);
    freePila(pila);
    free(pila);
}

*/

void rellenar(Vec2 *start, uint32_t new_color) {
    // Obtiene las dimensiones del área de renderizado
    int width = estadosrender.w_width;
    int height = estadosrender.w_height;
    int pixel_count = width * height;

    // Crea un arreglo para marcar los píxeles ya visitados
    char *visited = calloc(pixel_count, sizeof(char));
    Pila *stack = calloc(1, sizeof(Pila));

    // se obtiene el color a reemplazar
    uint32_t target_color = getColor(start);

    // se crea el vector inicial y se aniade a la pila
    Vec2 *seed = malloc(sizeof(Vec2));
    *seed = *start;
    push(stack, seed);

    // mientras que la pila no este vacia...
    while (stack->tope != NULL) {
        // se Extrae el vector a trabajar
        Vec2 *current = (Vec2*)pop(stack);
        int cx = current->unpack.x;
        int cy = current->unpack.y;
        int pos = cy * width + cx;

        // se verifica si entra en el rango y si ya se visito
        if (cx < 0 || cx >= width || cy < 0 || cy >= height || visited[pos]) {
            free(current);
            continue;
        }

        // se compara el color actual con el color a reemplazar
        if (getColor(current) != target_color) {
            free(current);
            continue;
        }

        // se pinta el color y se aniade la coordenada al vector de visitados
        draw_pixel(cx, cy, new_color);
        visited[pos] = 1;

        // se declaran las posiciones vecinas (arriba, abajo, izq, der)
        static const int dx[4] = {1, -1, 0, 0};
        static const int dy[4] = {0, 0, 1, -1};

        // se recorren las posiciones vecinas
        for (int dir = 0; dir < 4; ++dir) {
            int nx = cx + dx[dir];
            int ny = cy + dy[dir];
            int npos = ny * width + nx;

            // si la pocision vecina esta dentro del rango y no ha sido visitada, creala y aniadela a la pila
            if (nx >= 0 && nx < width && ny >= 0 && ny < height && !visited[npos]) {
                Vec2 *neighbor = malloc(sizeof(Vec2));
                neighbor->unpack.x = nx;
                neighbor->unpack.y = ny;
                push(stack, neighbor);
            }
        }
        free(current); // se limpia el punto actual
    }

    // se libera la memoria usada
    free(visited);
    freePila(stack);
    free(stack);
}

// ---------------------- FUNCIONES AUXILIARES ---------------------- //

uint32_t getColor(Vec2 *pixel) {
    return estadosrender.color_buffer[(int)pixel->unpack.y * estadosrender.w_width + (int)pixel->unpack.x];
}

// ---------------------- FUNCIONES ORG ---------------------- //

void fill_triangulo(Triangulo *triangulo, uint32_t color) {
    float cy, cx;

    Vec2 y[3] = {triangulo -> p1, triangulo -> p2, triangulo -> p3};
    ordenar_y(y);

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

void fill_flat_bottom(Vec2 p2, Vec2 p3, Vec2 c, uint32_t color) {
    float mi = (p3.unpack.x - p2.unpack.x) / (p3.unpack.y - p2.unpack.y);
    float mf = (c.unpack.x - p2.unpack.x) / (c.unpack.y - p2.unpack.y);

    float xi = p2.unpack.x;
    float xf = p2.unpack.x;

    for (int y = (int)p2.unpack.y ; y <= (int)c.unpack.y ; y++) {
        draw_linea(xi, y, xf, y, color);
        xi += mi;
        xf += mf;
    }
}

void fill_flat_top(Vec2 p1, Vec2 p2 ,Vec2 c, uint32_t color) {
    float mi = (c.unpack.x - p1.unpack.x) / (c.unpack.y - p1.unpack.y);
    float mf = (c.unpack.x - p2.unpack.x) / (c.unpack.y - p2.unpack.y);

    float xi = c.unpack.x;
    float xf = c.unpack.x;

    for (int y = (int)c.unpack.y ; y >= (int)p1.unpack.y ; y--) {
        draw_linea(xi, y, xf, y, color);
        xi -= mi;
        xf -= mf;
    }
}

void ordenar_y(Vec2 *y) {
    Vec2 aux;

    for(int i = 0 ; i < 3 ; i++) {
        for(int j = i + 1 ; j < 3 ; j++) {
            if(y[i].unpack.y > y[j].unpack.y) {
                aux = y[i];
                y[i] = y[j];
                y[j] = aux;
            }
        }
    }
}