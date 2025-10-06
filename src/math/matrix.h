#pragma once
#include "vectores.h"
#include <math.h>

typedef struct _mat4{
    float data[4 * 4];
    // struct {
    //     float x;
    //     float y;
    //     float z;
    //     float w;
    // }unpack;
}Mat4;

Mat4 mat4_eye(void);

void mat4_push_escala(Mat4 *matriz, Vec3 escala);
void mat4_push_traslado(Mat4 *matriz, Vec3 pos);
void mat4_push_rotar_x(Mat4 *matriz, float radianes);
void mat4_push_rotar_y(Mat4 *matriz, float radianes);
void mat4_push_rotar_z(Mat4 *matriz, float radianes);
void mat4_push_rotar(Mat4 *matriz, Vec3 rotacion);

Vec4 mat4_dot_vec4(Mat4 *matriz, Vec4 *punto);