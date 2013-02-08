//
//  raycast.c
//  raycast
//
//  Created by Liam Westby on 2/7/13.
//  Copyright (c) 2013 Liam Westby. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "raycast.h"
#include "vector.h"

void raycast(ppm_image* img, sphere** objects, int num_objects, int image_width, int image_height, float world_width, float world_height, float *origin, int parallel) {
    if (parallel) {
        
    }
    else {
        float pixheight = world_height / (float)image_height;
        float pixwidth = world_width/ (float)image_width;
        float *pixelvec = (float*)malloc(sizeof(float)*3);
        for (int i = 0; i < image_height; i++) {
            pixelvec[1] = origin[1] - world_height / 2 + pixheight * (i + 0.5);
            for (int j = 0; j < image_width; j++) {
                pixelvec[0] = origin[0] - world_width / 2 + pixwidth * (j + 0.5);
                pixelvec[2] = -0.4;
                v_unit(pixelvec, pixelvec);
                int object_number = shoot(objects, num_objects, pixelvec, origin);
                img->data[i][j] = *(shade(objects, object_number));
            }
        }
    }
}

int shoot(sphere **objects, int num_objects, float *direction, float *origin) {
    float distance = INFINITY;
    int object_num = -1;
    float tempdistance;
    for (int i = 0; i < num_objects; i++) {
        tempdistance = sphere_intersect(objects[i], origin, direction);
        if (tempdistance < distance) {
            distance = tempdistance;
            object_num = i;
        }
    }
    return object_num;
}

pixel* shade(sphere** objects, int object_number) {
    pixel* color = (pixel*)malloc(sizeof(pixel));
    color->r = 0;
    color->g = 0;
    color->b = 0;
    
    if (object_number > -1) {
        color = &objects[object_number]->color;
    }
    
    return color;
}