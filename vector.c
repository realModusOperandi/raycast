//
//  vector.c
//  raycast
//
//  Created by Liam Westby on 2/6/13.
//  Copyright (c) 2013 Liam Westby. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "vector.h"

void v_init(float x, float y, float z, float *out) {
    out[0] = x;
    out[1] = y;
    out[2] = z;
}

float v_magnitude(float *v) {
    return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

void v_unit(float *in, float *out) {
    float mag = v_magnitude(in);
    out[0] = in[0]/mag;
    out[1] = in[1]/mag;
    out[2] = in[2]/mag;
}

void v_add(float *f1, float *f2, float *out) {
    out[0] = f1[0] + f2[0];
    out[1] = f1[1] + f2[1];
    out[2] = f1[2] + f2[2];
}

void v_sub(float *f1, float *f2, float *out) {
    out[0] = f1[0] - f2[0];
    out[1] = f1[1] - f2[1];
    out[2] = f1[2] - f2[2];
}

void v_scale(float *v, float s, float *out) {
    out[0] = v[0] * s;
    out[1] = v[1] * s;
    out[2] = v[2] * s;
}

float v_dot(float *v1, float *v2) {
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

void v_cross(float *v1, float *v2, float *out) {
    out[0] = v1[1]*v2[2] - v1[2]*v2[1];
    out[1] = v1[2]*v2[0] - v1[0]*v2[2];
    out[2] = v1[0]*v2[1] - v1[1]*v2[0];
}

