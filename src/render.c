#include "render.h"
#include "draw/draw.h"
#include "draw/linea.h"
#include "math/lerp.h"
#include "math/vectores.h"
#include "math/matrix.h"
#include "draw/figuras.h"
#include "memoria/memoria.h"
#include "color/colores.h"
// #include "HUD/boton.h"

#include <math.h>
#include <stdio.h>

Vec2 *punto_seleccionado = NULL;

void transformar(void) {
    int tam = array_size(estadosrender.figuras_buffer);
    
    // por cada figura
    for(int i = 0 ; i < tam ; ++i) {
        Figuras *fig = &estadosrender.figuras_buffer[i];
        
        if(fig -> data.type != TRIAN) continue;
        Triangulo *trian = (Triangulo*)fig;
        
        // por cada vertice
        for(int v = 0 ; v < 3 ; ++v) {
            // crear matriz transformacion (eye)
            Mat4 mat_trans = mat4_eye();
            // escalar la matriz transformacion
            mat4_push_escala(&mat_trans, (Vec3){{2.f, 2.f, 2.f}});
            
            // trasladar la matriz transformacion
            mat4_push_traslado(&mat_trans, (Vec3){{0.01f, 0.f, 0.f}});

            // rotar la matriz transformacion
            mat4_push_rotar(&mat_trans, (Vec3){{0.f, 0.f, 0.f}});
            
            // producto punto entre matriz transformacion y vertice
            Vec4 vertice = {{trian -> p[v].unpack.x , trian -> p[v].unpack.y, 1.f, 1.f}};
            Vec4 vf = mat4_dot_vec4(&mat_trans, &vertice);
            
            // reemplazar vertice
            trian->p[v].unpack.x = vf.unpack.x;
            trian->p[v].unpack.y = vf.unpack.y;
        }
    }
}

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
    transformar();    
    // for(int i = 0 ; i < array_size(estadosrender.botones_buffer) ; i++) {
    //     draw_boton(&estadosrender.botones_buffer[i]);
    //     capturar_boton(&estadosrender.botones_buffer[i]);
    // }
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
        if(punto_seleccionado) {
            punto_seleccionado->unpack.x = estadosrender.evento.motion.x;
            punto_seleccionado->unpack.y = estadosrender.evento.motion.y;
            punto_seleccionado = NULL;
        }
    }
}

void clear_color_buffer() {
    for(int y = 0; y < estadosrender.w_height; ++y){
        for(int x = 0; x < estadosrender.w_width; ++x){
            draw_pixel(x, y, estadosrender.clear_color.hex);
        }
    }
}

void copy_buffer_to_texture() {
    SDL_UpdateTexture(estadosrender.texture, 
                      NULL, 
                      estadosrender.color_buffer, 
                      (int)(estadosrender.w_width * sizeof(int)));

    SDL_RenderTexture(estadosrender.renderer, 
                      estadosrender.texture, 
                      NULL, 
                      NULL);
}

void _Init() {
    // int boton_alto = 50;
    // int boton_largo = boton_alto + (boton_alto / 2);

    // Cuadro boton_cuadrado_fig = {
    //     .pos = {.unpack = {.x = 50 + (boton_largo / 3.f), .y = 10 + (boton_alto / 5.f)}},
    //     .w = (boton_alto / 5.f) * 3,
    //     .h = (boton_alto / 5.f) * 3,
    //     .offset_mem1 = {0},
    //     .color = (Color){0x140140FF},
    //     .type = CUADRO
    // };

    // Circulo boton_circulo_fig = {
    //     .pos = {.unpack = {.x = 150 + (boton_largo / 2.f), .y = 10 + (boton_alto / 2.f)}},
    //     .r = (boton_alto / 10.f) * 3,
    //     .offset_mem1 = {0},
    //     .color = (Color){0x140140FF},
    //     .type = CIRC
    // };
    
    // Triangulo boton_triangulo_fig = {
        // .p1 = {.unpack = {.x = 250 + (boton_largo / 3.f), .y = 10 + (boton_alto / 3.f) * 2}},
        // .p2 = {.unpack = {.x = 250 + (boton_largo / 2.f), .y = 10 + (boton_alto / 3.f)}},
        // .p3 = {.unpack = {.x = 250 + (boton_largo / 3.f) * 2, .y = 10 + (boton_alto / 3.f) * 2}},

    //     .p = {{{100, 100}},
    //           {{200, 150}},
    //           {{100, 300}}},
    //     .color = (Color){0x140140FF},
    //     .type = TRIAN
    // };
    
    // --- Iconos para los nuevos botones de color ---
    // Cuadro icono_borde = {
    //     .pos = {.unpack = {.x = 350 + 15, .y = 10 + 10}},
    //     .w = boton_alto - 20, .h = boton_alto - 20,
    //     .color = (Color){0x00FF00FF}, .type = CUADRO
    // };

    // Cuadro icono_relleno = {
    //     .pos = {.unpack = {.x = 450 + 15, .y = 10 + 10}},
    //     .w = boton_alto - 20, .h = boton_alto - 20,
    //     .color = (Color){0xFF0000FF}, .type = CUADRO
    // };
    // ---------------------------------------------

    // Figuras tipo_cuadro = {.cuadro = boton_cuadrado_fig};
    // Figuras tipo_circ = {.circulo = boton_circulo_fig};
    // Figuras tipo_trian = {.triangulo = boton_triangulo_fig};
    
    // Boton boton1 = {
    //     .pos = {.unpack = {.x = 50, .y = 10}},
    //     .largo = boton_largo, .alto = boton_alto,
    //     .fig = tipo_cuadro,
    //     .tipo = BOTON_TIPO_FIGURA // Asignar tipo
    // };

    // Boton boton2 = {
    //     .pos = {.unpack = {.x = 150, .y = 10}},
    //     .largo = boton_largo, .alto = boton_alto,
    //     .fig = tipo_circ,
    //     .tipo = BOTON_TIPO_FIGURA // Asignar tipo
    // };
    
    // Boton boton3 = {
    //     .pos = {.unpack = {.x = 250, .y = 10}},
    //     .largo = boton_largo, .alto = boton_alto,
    //     .fig = tipo_trian,
    //     .tipo = BOTON_TIPO_FIGURA // Asignar tipo
    // };

    // // --- Definicion de los nuevos botones ---
    // Boton boton_borde = {
    //     .pos = {.unpack = {.x = 350, .y = 10}},
    //     .largo = boton_largo, .alto = boton_alto,
    //     .fig.cuadro = icono_borde,
    //     .tipo = BOTON_TIPO_COLOR_BORDE
    // };

    // Boton boton_relleno = {
    //     .pos = {.unpack = {.x = 450, .y = 10}},
    //     .largo = boton_largo, .alto = boton_alto,
    //     .fig.cuadro = icono_relleno,
    //     .tipo = BOTON_TIPO_COLOR_RELLENO
    // };
    // -------------------------------------

    // pushto_array(estadosrender.botones_buffer, boton1);
    // pushto_array(estadosrender.botones_buffer, boton2);
    // pushto_array(estadosrender.botones_buffer, boton3);
    // // --- Añadir nuevos botones al buffer ---
    // pushto_array(estadosrender.botones_buffer, boton_borde);
    // pushto_array(estadosrender.botones_buffer, boton_relleno);
    // --------------------------------------
}

void render_frame() {
    for(int i = 0 ; i < array_size(estadosrender.figuras_buffer) ; i++) {
        draw_figura(&estadosrender.figuras_buffer[i]);
    }

    SDL_RenderPresent(estadosrender.renderer);
}