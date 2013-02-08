//
//  sphere.c
//  raycast
//
//  Created by Liam Westby on 2/6/13.
//  Copyright (c) 2013 Liam Westby. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector.h"
#include "sphere.h"

sphere** read_spheres(char *file_path) {
    sphere** objects = (sphere**)malloc(sizeof(sphere*)*6);
    for (int i = 0; i < 6; i++) {
        objects[i] = (sphere*)malloc(sizeof(sphere));
        objects[i]->center = (float*)malloc(sizeof(float)*3);
    }
    
    //Red sphere
    v_init(-0.3, 0.2, -0.6, objects[0]->center);
    objects[0]->radius = 0.2;
    objects[0]->color.r = 255;
    objects[0]->color.g = 0;
    objects[0]->color.b = 0;
    
    //Orange sphere
    v_init(0.15, -0.2, -0.6, objects[1]->center);
    objects[1]->radius = 0.15;
    objects[1]->color.r = 255;
    objects[1]->color.g = 165;
    objects[1]->color.b = 0;
    
    //Yellow sphere
    v_init(0.1, 0.175, -0.15, objects[2]->center);
    objects[2]->radius = 0.05;
    objects[2]->color.r = 255;
    objects[2]->color.g = 255;
    objects[2]->color.b = 0;
    
    //Green sphere
    v_init(0.0, 0.13, -0.3, objects[3]->center);
    objects[3]->radius = 0.025;
    objects[3]->color.r = 0;
    objects[3]->color.g = 255;
    objects[3]->color.b = 0;
    
    //Blue sphere
    v_init(0.3, -0.2, -0.2, objects[4]->center);
    objects[4]->radius = 0.125;
    objects[4]->color.r = 0;
    objects[4]->color.g = 0;
    objects[4]->color.b = 255;
    
    //Magenta sphere
    v_init(-0.2, 0.0, -0.4, objects[5]->center);
    objects[5]->radius = 0.06;
    objects[5]->color.r = 255;
    objects[5]->color.g = 0;
    objects[5]->color.b = 255;
    
    return objects;
}

float sphere_intersect(sphere *to_check, float *origin, float *direction) {
    float a = v_dot(direction, direction);

    float *temp = (float*)malloc(sizeof(float)*3);
    v_sub(origin, to_check->center, temp);
    v_scale(temp, 2, temp);
    float b = v_dot(temp, direction);

    v_sub(origin, to_check->center, temp);
    float c = v_dot(temp, temp);
    c -= to_check->radius * to_check->radius;
    

    float discriminant = b*b - 4*a*c;

    if (discriminant < 0) {

        return INFINITY;
    }
    
    float t1 = (-b + sqrtf(b*b - 4*a*c))/2*a;
    float t2 = (-b - sqrtf(b*b - 4*a*c))/2*a;
    

    if (t1 > 0 && t2 > 0) {
        return t1 < t2 ? t1 : t2;
    }
    if (t1 > 0) return t1;
    if (t2 > 0) return t2;
    else {

        return INFINITY;
    }
}