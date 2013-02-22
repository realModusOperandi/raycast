//
//  object.h
//  raycast
//
//  Created by Liam Westby on 2/19/13.
//  Copyright (c) 2013 Liam Westby. All rights reserved.
//

#include "ppm.h"

#ifndef raycast_object_h
#define raycast_object_h

#define SPHERE_TYPE 1
#define PLANE_TYPE 2
#define OBJECTS_COUNT 7

typedef struct {
    int type;
    
    union {
        struct {
            float *center;
            float radius;
        } sphere;
        struct {
            float *point;
            float *normal;
        } plane;
    } definition;
    
    float reflectivity;
    pixel color;
} object;

object** get_objects();
float object_intersect(object *to_check, float *origin, float *direction);


#endif
