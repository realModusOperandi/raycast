//
//  light.c
//  raycast
//
//  Created by Liam Westby on 2/20/13.
//  Copyright (c) 2013 Liam Westby. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "light.h"
#include "vector.h"

/* Read in a light file and convert the lights into a struct. Currently returns hardcoded values.
 *
 * Return: An array of pointers to point_light structs.
 */
point_light** get_lights() {
    point_light **lights = (point_light**)malloc(sizeof(point_light*)*2);
    
    lights[0] = (point_light*)malloc(sizeof(point_light));
    lights[0]->position = (float*)malloc(sizeof(float)*3);
    v_init(0.0, 10.0, 0.0, lights[0]->position);
    lights[0]->color.r = 255;
    lights[0]->color.g = 255;
    lights[0]->color.b = 255;
    
    lights[1] = (point_light*)malloc(sizeof(point_light));
    lights[1]->position = (float*)malloc(sizeof(float)*3);
    v_init(-5.0, 7.0, 3.0, lights[1]->position);
    lights[1]->color.r = 255;
    lights[1]->color.g = 255;
    lights[1]->color.b = 255;
    
    return lights;
}