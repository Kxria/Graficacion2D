#include "render.h"
#include "draw/draw.h"
#include "draw/linea.h"
#include "math/lerp.h"
#include "math/vectores.h"
#include "draw/figuras.h"
#include "memoria/memoria.h"
#include "color/colores.h"

#include <math.h>
#include <stdio.h>

Vec2 *punto_seleccionado = NULL;

Vec2* pivote_mas_cerca(Vec2 mp, Figuras *figs, float umbral) {
    
    int a = 0;
    int b = array_size(figs) - 1;
    
    float low;
    float high;
    float centro;

    for(int i = 0 ; i < array_size(figs) ; i++) {
        int r = (a + b) / 2;

        low = distanciav2(mp, figs[a].cuadro.pos);
        high = distanciav2(mp, figs[b].cuadro.pos);
        centro = distanciav2(mp, figs[r].cuadro.pos);

        if(fabs(low) <= umbral) {
            return &figs[a].cuadro.pos;
        } else if (fabs(high) <= umbral) {
            return &figs[b].cuadro.pos;
        } else if (fabs(centro) <= umbral) {
            return &figs[r].cuadro.pos;
        }

        if(r < b) {
            b = r;
        } else if (r > a) {
            a = r;
        }
    }

    return NULL;
}

void update() {
    for(int i = 0 ; i < array_size(estadosrender.figuras_buffer) ; i++) {
        draw_figura(&estadosrender.figuras_buffer[i]);
    }
}


void render_input(void) {
    if(estadosrender.evento.type == SDL_EVENT_QUIT){
        estadosrender.run = 0;
    }

    if(estadosrender.evento.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        printf("(%.3f, %.3f)\n", estadosrender.evento.motion.x, estadosrender.evento.motion.y);

        Vec2 *pivote = pivote_mas_cerca((Vec2){{estadosrender.evento.motion.x,
                                               estadosrender.evento.motion.y}},
                                               estadosrender.figuras_buffer,
                                               10.f);

        if(!punto_seleccionado) {
            punto_seleccionado = pivote_mas_cerca((Vec2){{estadosrender.evento.motion.x,
                                                          estadosrender.evento.motion.y}},
                                                          estadosrender.figuras_buffer,
                                                          10.f);
        }

        if(punto_seleccionado) {
            printf("Punto cercano (%.3f, %.3f)\n", pivote -> unpack.x, pivote -> unpack.y);
        }
    } else if (estadosrender.evento.type == SDL_EVENT_MOUSE_BUTTON_UP) {
        // Modificar la figura
        if(punto_seleccionado) {
            punto_seleccionado->unpack.x = estadosrender.evento.motion.x;
            punto_seleccionado->unpack.y = estadosrender.evento.motion.y;
            punto_seleccionado = NULL;
        }
    }
}

void clear_color_buffer(){
    for(int y = 0; y < estadosrender.w_height; ++y){
        for(int x = 0; x < estadosrender.w_width; ++x){
            draw_pixel(x, y, estadosrender.clear_color.hex);
        }
    }
}

void copy_buffer_to_texture(){
    SDL_UpdateTexture(estadosrender.texture, 
                      NULL, 
                      estadosrender.color_buffer, 
                      (int)(estadosrender.w_width * sizeof(int)));

    SDL_RenderTexture(estadosrender.renderer, 
                      estadosrender.texture, 
                      NULL, 
                      NULL);
}

void _Init(){
    Vec2 pc1 = {{400.f, 360.f}};
    Vec2 pc2 = {{600.f, 100.f}};
    Vec2 pc3 = {{800.f, 360.f}};
    
    Linea linea = {
        .p1 = (Vec2){{800, 100}},
        .p2 = (Vec2){{600, 250}},
        .offset_mem1 = {0},
        .color = (Color){0xAB00ABFF},
        .type = LINEA
    };

    Curva curva = {
        .p1 = pc1,
        .p2 = pc2,
        .p3 = pc3,
        .color = (Color){0xFFFF00FF},
        .type = CURVA
    };

    Circulo circ = {
        .pos = {{estadosrender.w_width/2.f, estadosrender.w_height/2.f}},
        .r = 20.f,
        .vert = 32,
        .offset_mem1 = {0},
        .color = (Color){0x00FFFFFF},
        .type = CIRC
    };

    Cuadro cuadro = {
        .pos = {.unpack = {.x = 140, .y = 140}},
        .h = 200,
        .w = 200,
        .offset_mem1 = {0},
        .color = (Color){0x140140FF},
        .type = CUADRO
    };

    Triangulo triangulo = {
        .p1 = {.unpack = {.x = 400, .y = 360}},
        .p2 = {.unpack = {.x = 600, .y = 100}},
        .p3 = {.unpack = {.x = 800, .y = 360}},
        .color = (Color){0xFFFFFFFF},
        .type = TRIAN
    };


    Figuras test = {.linea = linea};
    Figuras test2 = {.curva = curva};
    Figuras test3 = {.circulo = circ};
    Figuras test4 = {.cuadro = cuadro};
    Figuras test5 = {.triangulo = triangulo};

    pushto_array(estadosrender.figuras_buffer, test);
    pushto_array(estadosrender.figuras_buffer, test2);
    pushto_array(estadosrender.figuras_buffer, test3);
    pushto_array(estadosrender.figuras_buffer, test4);
    pushto_array(estadosrender.figuras_buffer, test5);
}

void render_frame() {
    SDL_RenderPresent(estadosrender.renderer);
}