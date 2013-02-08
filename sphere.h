//
//  sphere.h
//  raycast
//
//  Created by Liam Westby on 2/6/13.
//  Copyright (c) 2013 Liam Westby. All rights reserved.
//

#include "ppm.h"

#ifndef raycast_sphere_h
#define raycast_sphere_h

typedef struct {
    float *center;
    float radius;
    pixel color;
} sphere;

sphere** read_spheres(char *file_path);
float sphere_intersect(sphere *to_check, float *origin, float *direction);

#endif
