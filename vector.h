//
//  vector.h
//  raycast
//
//  Created by Liam Westby on 2/6/13.
//  Copyright (c) 2013 Liam Westby. All rights reserved.
//

#ifndef raycast_vector_h
#define raycast_vector_h

#include "object.h"

void v_init(float x, float y, float z, float *out);
float v_magnitude(float *v);
void v_unit(float *in, float *out);
void v_add(float *v1, float *v2, float *out);
void v_sub(float *f1, float *f2, float *out);
void v_sum(float *v1, float *v2, float *out);
void v_scale(float *v, float s, float *out);
float v_dot(float *v1, float *v2);
void v_cross(float *v1, float *v2, float *out);
float* reflection_vector(object *the_object, float *position, float *direction);
float* get_normal(object *the_object, float *position);

#endif
