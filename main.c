//
//  main.c
//  raycast
//
//  Created by Liam Westby on 2/6/13.
//  Copyright (c) 2013 Liam Westby. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "ppm.h"
#include "vector.h"
#include "sphere.h"
#include "raycast.h"

int main(int argc, const char * argv[])
{

    char *output_path = "/Users/lw322/Documents/raycast.ppm";
    ppm_image *the_image = (ppm_image*)malloc(sizeof(ppm_image));
    the_image->height = 640;
    the_image->width = 512;
    the_image->maxval = 255;
    the_image->data = (pixel**)malloc(sizeof(pixel*)*the_image->width);
    for (int i = 0; i < the_image->width; i++) {
        the_image->data[i] = (pixel*)malloc(sizeof(pixel)*the_image->height);
        
    }
    float *origin = (float*)malloc(sizeof(float)*3);
    v_init(0.0, 0.0, 0.4, origin);
    sphere **objects = read_spheres(NULL);
    raycast(the_image, objects, 6, the_image->width, the_image->height, 0.5, 0.4, origin, 0);
    write_image(the_image, output_path);
    return 0;
}

