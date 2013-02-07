//
//  ppm.h
//  Project 1
//
//  Created by Liam Westby on 1/20/13.
//  Structures to store an image.
//

#ifndef Project_1_ppm_h
#define Project_1_ppm_h

typedef struct {
    unsigned char r, g, b;
} pixel;

typedef struct {
    int height, width, maxval;
    pixel** data;
} ppm_image;

void write_image(ppm_image*, char*);

#endif
