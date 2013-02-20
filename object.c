//
//  object.c
//  raycast
//
//  Created by Liam Westby on 2/19/13.
//  Copyright (c) 2013 Liam Westby. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "object.h"
#include "vector.h"

/* Read in a scene file and convert the shapes into a struct. Currently returns hardcoded values.
 *
 * file_path: The path to the file to be read.
 *
 * Return: An array of pointers to object structs.
 */
object** get_objects(char *file_path) {
    object** objects = (object**)malloc(sizeof(object*)*6);
    for (int i = 0; i < 6; i++) {
        objects[i] = (object*)malloc(sizeof(object));
        objects[i]->definition.sphere.center = (float*)malloc(sizeof(float)*3);
    }
    
    //Red object
    objects[0]->type = SPHERE_TYPE;
    v_init(-0.3, 0.2, -0.6, objects[0]->definition.sphere.center);
    objects[0]->definition.sphere.radius = 0.2;
    objects[0]->color.r = 255;
    objects[0]->color.g = 0;
    objects[0]->color.b = 0;
    
    //Orange object
    objects[1]->type = SPHERE_TYPE;
    v_init(0.15, -0.2, -0.6, objects[1]->definition.sphere.center);
    objects[1]->definition.sphere.radius = 0.15;
    objects[1]->color.r = 255;
    objects[1]->color.g = 165;
    objects[1]->color.b = 0;
    
    //Yellow object
    objects[2]->type = SPHERE_TYPE;
    v_init(0.1, 0.175, -0.15, objects[2]->definition.sphere.center);
    objects[2]->definition.sphere.radius = 0.05;
    objects[2]->color.r = 255;
    objects[2]->color.g = 255;
    objects[2]->color.b = 0;
    
    //Green object
    objects[3]->type = SPHERE_TYPE;
    v_init(0.0, 0.13, -0.3, objects[3]->definition.sphere.center);
    objects[3]->definition.sphere.radius = 0.025;
    objects[3]->color.r = 0;
    objects[3]->color.g = 255;
    objects[3]->color.b = 0;
    
    //Blue object
    objects[4]->type = SPHERE_TYPE;
    v_init(0.3, -0.2, -0.2, objects[4]->definition.sphere.center);
    objects[4]->definition.sphere.radius = 0.125;
    objects[4]->color.r = 0;
    objects[4]->color.g = 0;
    objects[4]->color.b = 255;
    
    //Magenta object
    objects[5]->type = SPHERE_TYPE;
    v_init(-0.2, 0.0, -0.4, objects[5]->definition.sphere.center);
    objects[5]->definition.sphere.radius = 0.06;
    objects[5]->color.r = 255;
    objects[5]->color.g = 0;
    objects[5]->color.b = 255;
    
    return objects;
}

/* Determine whether the given vector created by the point and direction intersects at any point on the given sphere.
 *
 * to_check: The sphere to check for intersection.
 * origin: The origin of the ray.
 * direction: unit vector representing the direction of the ray.
 *
 * Return: The shortest distance to intersection if it happens, or INFINITY if it does not.
 */
float object_intersect(object *to_check, float *origin, float *direction) {
    if (to_check->type == SPHERE_TYPE) {
        float a = v_dot(direction, direction);
        
        float *temp = (float*)malloc(sizeof(float)*3);
        v_sub(origin, to_check->definition.sphere.center, temp);
        v_scale(temp, 2, temp);
        float b = v_dot(temp, direction);
        
        v_sub(origin, to_check->definition.sphere.center, temp);
        float c = v_dot(temp, temp);
        c -= to_check->definition.sphere.radius * to_check->definition.sphere.radius;
        
        
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
}

