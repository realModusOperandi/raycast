//
//  main.c
//  raycast
//
//  Created by Liam Westby on 2/6/13.
//  This program raycasts an image given a scene file using either perspective or parallel projections.
//

#include <stdio.h>
#include <stdlib.h>

#include "ppm.h"
#include "vector.h"
#include "light.h"
#include "object.h"
#include "raycast.h"

#define WORLD_WIDTH 0.5
#define WORLD_HEIGHT 0.4

void print_usage();

int main(int argc, const char * argv[])
{

    if (argc < 4) {
        // Requires 3 arguments: l/v, width of image, and output file.
        print_usage();
        return 0;
    }
    
    // Get parallel or perspective
    int parallel;
    if (argv[1][0] == 'l') parallel = 1;
    else if (argv[1][0] == 'v') parallel = 0;
    else {
        // An invalid option was specified
        printf("The parallel/perspective option was invalid.\n");
        print_usage();
        return 0;
    }
    
    // Get the width of the image.
    int width = atoi(argv[2]);
    if (width == 0) {
        // Either they passed in 0 as the width, or atoi failed. Regardless, that won't work.
        printf("The given width was invalid.\n");
        print_usage();
        return 0;
    }
    
    // Get the output file, for writing at the end.
    char *output_path = argv[3];
    
    // Assemble the image in memory.
    ppm_image *the_image = (ppm_image*)malloc(sizeof(ppm_image));
    the_image->width = width;
    the_image->height = (width * 4) / 5;
    the_image->maxval = 255;
    the_image->data = (pixel**)malloc(sizeof(pixel*)*the_image->height);
    for (int i = 0; i < the_image->height; i++) {
        the_image->data[i] = (pixel*)malloc(sizeof(pixel)*the_image->width);
        
    }
    object **objects = get_objects();
    point_light **lights = get_lights();
    
    //Raycast the image
    if (parallel) {
        float *direction = (float*)malloc(sizeof(float)*3);
        v_init(0.0, 0.0, -1.0, direction);
        
        raycast_parallel(the_image, objects, OBJECTS_COUNT, lights, LIGHTS_COUNT, the_image->width, the_image->height, WORLD_WIDTH, WORLD_HEIGHT, direction);
    }
    else {
        float *origin = (float*)malloc(sizeof(float)*3);
        v_init(0.0, 0.0, 0.4, origin);
        
        raycast_perspective(the_image, objects, OBJECTS_COUNT, lights, LIGHTS_COUNT, the_image->width, the_image->height, WORLD_WIDTH, WORLD_HEIGHT, origin);
    }
    write_image(the_image, output_path);
    return 0;
}

/* Prints the correct invocation of this program.
 */
void print_usage() {
    printf("USAGE: raycast l|v width outputfile.ppm\n");
    printf("Where l means parallel, v means perspective, and width is an integer.\n");
}

