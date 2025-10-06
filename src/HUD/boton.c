// // #include "boton.h"
// // #include "../global.h"
// // #include "../draw/draw.h"
// // #include "../memoria/memoria.h"

// // #include <stdlib.h>
// // #include <stdio.h>

// // void draw_boton(Boton *boton) {
// //     draw_cuadrado(boton->pos.unpack.x, boton->pos.unpack.y, boton->largo, boton->alto, 0x00000000);
// //     draw_figura(&(boton->fig));
// // }

// // // Función que maneja la interacción del usuario con un botón en la interfaz
// // void capturar_boton(Boton *boton) {
    
// //     // Verifica si el cursor está dentro del área del botón y si se ha hecho clic
// //     if(estadosrender.evento.motion.x >= boton->pos.unpack.x && estadosrender.evento.motion.x <= (boton->pos.unpack.x + boton->largo) &&
// //        estadosrender.evento.motion.y >= boton->pos.unpack.y && estadosrender.evento.motion.y <= (boton->pos.unpack.y + boton->alto) &&
// //        estadosrender.evento.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {

// //         // Evalúa el tipo de botón para ejecutar la acción correspondiente
// //         switch (boton->tipo) {

// //             // Si el botón es del tipo que crea figuras
// //             case BOTON_TIPO_FIGURA:

// //                 // Determina qué figura debe crearse según el tipo especificado
// //                 switch (boton->fig.data.type) {

// //                     case CUADRO:
// //                         printf("Boton CUADRO\n"); 
// //                         Figuras *cuadro = boton_cuadrado(); // Crea un nuevo cuadro
// //                         pushto_array(estadosrender.figuras_buffer, *cuadro); // Lo agrega al buffer de figuras
// //                         break;

// //                     case CIRC:
// //                         printf("Boton CIRC\n");
// //                         Figuras *circulo = boton_circulo(); // Crea un nuevo círculo
// //                         pushto_array(estadosrender.figuras_buffer, *circulo); // Lo agrega al buffer
// //                         break;

// //                     case TRIAN:
// //                         printf("Boton TRIAN\n");
// //                         Figuras *triangulo = boton_triangulo(); // Crea un nuevo triángulo
// //                         pushto_array(estadosrender.figuras_buffer, *triangulo); // Lo agrega al buffer
// //                         break;

// //                     default:
// //                         break; // No hace nada si el tipo no es reconocido
// //                 }
// //                 break;

// //             // Si el botón cambia el color del borde de las figuras
// //             case BOTON_TIPO_COLOR_BORDE:
// //                 printf("Boton COLOR BORDE\n");

// //                 // Alterna entre dos colores de borde predefinidos
// //                 if (estadosrender.color_borde_actual.hex == 0x140140FF) {
// //                     estadosrender.color_borde_actual.hex = 0x00FF00FF; // Verde
// //                 } else {
// //                     estadosrender.color_borde_actual.hex = 0x140140FF; // Azul oscuro
// //                 }

// //                 // Aplica el nuevo color de borde a todas las figuras en el buffer
// //                 for (int i = 0; i < array_size(estadosrender.figuras_buffer); i++) {
// //                     Figuras *fig = &estadosrender.figuras_buffer[i];

// //                     // Aplica el color según el tipo de figura
// //                     switch (fig->data.type) {
// //                         case CUADRO:
// //                             fig->cuadro.color = estadosrender.color_borde_actual;
// //                             break;

// //                         case CIRC:
// //                             fig->circulo.color = estadosrender.color_borde_actual;
// //                             break;

// //                         case TRIAN:
// //                             fig->triangulo.color = estadosrender.color_borde_actual;
// //                             break;

// //                         default:
// //                             break;
// //                     }
// //                 }
// //                 break;

// //             // Si el botón cambia el color de relleno de las figuras
// //             case BOTON_TIPO_COLOR_RELLENO:
// //                 printf("Boton COLOR RELLENO\n");

// //                 // Alterna entre negro y rojo como color de relleno
// //                 if (estadosrender.color_relleno_actual.hex == 0x00000000) {
// //                     estadosrender.color_relleno_actual.hex = 0xFF0000FF; // Rojo
// //                 } else {
// //                     estadosrender.color_relleno_actual.hex = 0x00000000; // Negro
// //                 }

// //                 // Aplica el nuevo color de relleno a todas las figuras
// //                 for (int i = 0; i < array_size(estadosrender.figuras_buffer); i++) {
// //                     rellenar_figura(&estadosrender.figuras_buffer[i], estadosrender.color_relleno_actual.hex);
// //                 }
// //                 break;
// //         }
// //     }
// // }
// // Figuras* boton_cuadrado(void) {
// //     Figuras *cuadro = (Figuras*)calloc(1, sizeof(Figuras));

// //     cuadro->cuadro.pos.unpack.x = 50;
// //     cuadro->cuadro.pos.unpack.y = 100;
    
// //     cuadro->cuadro.w = 100;
// //     cuadro->cuadro.h = 100;
// //     cuadro->cuadro.color = estadosrender.color_borde_actual;
// //     cuadro->cuadro.type = CUADRO;

// //     return cuadro;
// // }

// // Figuras* boton_circulo(void) {
// //     Figuras *circulo = (Figuras*)calloc(1, sizeof(Figuras));

// //     circulo->circulo.pos.unpack.x = 100;
// //     circulo->circulo.pos.unpack.y = 270;

// //     circulo->circulo.r = 50;
// //     circulo->circulo.vert = 32;
// //     circulo->circulo.color = estadosrender.color_borde_actual;
// //     circulo->circulo.type = CIRC;

// //     return circulo;
// // }

// // Figuras* boton_triangulo(void) {
// //     Figuras *triangulo = (Figuras*)calloc(1, sizeof(Figuras));

// //     triangulo->triangulo.p[0].unpack.x = 50;
// //     triangulo->triangulo.p[0].unpack.y = 430;

// //     triangulo->triangulo.p[1].unpack.x = 100;
// //     triangulo->triangulo.p[1].unpack.y = 350;

// //     triangulo->triangulo.p[2].unpack.x = 150;
// //     triangulo->triangulo.p[2].unpack.y = 430;
// //     triangulo->triangulo.color = estadosrender.color_borde_actual;
// //     triangulo->triangulo.type = TRIAN;

// //     return triangulo;
// // }
