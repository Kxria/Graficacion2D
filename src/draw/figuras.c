#include "figuras.h"
#include "draw.h"

void draw_figura(Figuras *fig) {
    switch(fig -> data.type) {
        case LINEA: {
            Linea f = fig -> linea;
			
            draw_circuloPM(5.f, f.p1.unpack.x, f.p1.unpack.y, 0x0000FFFF);
            draw_circuloPM(5.f, f.p2.unpack.x, f.p2.unpack.y, 0x0000FFFF);
			
            draw_linea(f.p1.unpack.x, f.p1.unpack.y, f.p2.unpack.x, f.p2.unpack.y, f.color.hex);
            break;
		}
		
        case CURVA: {
            Curva c = fig -> curva;
            draw_circuloPM(5.f, c.p1.unpack.x, c.p1.unpack.y, 0x0000FFFF);
            draw_circuloPM(5.f, c.p2.unpack.x, c.p2.unpack.y, 0x0000FFFF);
            draw_circuloPM(5.f, c.p3.unpack.x, c.p3.unpack.y, 0x0000FFFF);
            draw_curva(c.p1, c.p2, c.p3, c.color.hex);
            break;
		}
			
        case CIRC:{
            Circulo circ = fig -> circulo;
            draw_circuloPM(circ.r, circ.pos.unpack.x, circ.pos.unpack.y, 0x0000FFFF);
            // fill_circulo(&circ, circ.color.hex);
            break;
		}
			
        case CUADRO: {
            Cuadro cuad = fig -> cuadro;
			
            draw_circuloPM(5.f, cuad.pos.unpack.x, cuad.pos.unpack.y, 0x0000FFFF);
            draw_circuloPM(5.f, (cuad.pos.unpack.x + cuad.w), cuad.pos.unpack.y, 0x0000FFFF);
            draw_circuloPM(5.f, (cuad.pos.unpack.x + cuad.w), (cuad.pos.unpack.y + cuad.h), 0x0000FFFF);
            draw_circuloPM(5.f, cuad.pos.unpack.x, (cuad.pos.unpack.y + cuad.h), 0x0000FFFF);
			
            draw_cuadrado(cuad.pos.unpack.x, cuad.pos.unpack.y, cuad.w, cuad.h, cuad.color.hex);
			// fill_cuadrado(&cuad, cuad.color.hex);
            break;
		}
		
        case TRIAN: {
            Triangulo triangulo = fig -> triangulo;
			
            draw_circuloPM(5.f, triangulo.p1.unpack.x, triangulo.p1.unpack.y, 0x0000FFFF);
            draw_circuloPM(5.f, triangulo.p2.unpack.x, triangulo.p2.unpack.y, 0x0000FFFF);
            draw_circuloPM(5.f, triangulo.p3.unpack.x, triangulo.p3.unpack.y, 0x0000FFFF);
			
            draw_trian(triangulo.p1.unpack.x, triangulo.p1.unpack.y,
                       triangulo.p2.unpack.x, triangulo.p2.unpack.y,
                       triangulo.p3.unpack.x, triangulo.p3.unpack.y,
                       triangulo.color.hex);
					   
            fill_triangulo(&triangulo, triangulo.color.hex);
            break;
		}
		
		default:
			break;
    }
}