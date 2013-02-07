//
//  ppm.c
//  raycast
//
//  Created by Liam Westby on 2/6/13.
//  Copyright (c) 2013 Liam Westby. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "ppm.h"

void write_image(ppm_image *the_image, char *outfilepath) {
    FILE *outfile;
    if ((outfile = fopen(outfilepath, "w")) == NULL) {
        fprintf(stderr, "There was a problem opening the output file %s.\n", outfilepath);
        exit(1);
    }
    
    fprintf(outfile, "P6\n");
    
    fprintf(outfile, "%d\n", the_image->width);
    fprintf(outfile, "%d\n", the_image->height);
    fprintf(outfile, "%d\n", the_image->maxval);
    
    for (int i = 0; i < the_image->width; i++) {
        for (int j = 0; j < the_image->height; j++) {
            fputc(the_image->data[i][j].r, outfile);
            fputc(the_image->data[i][j].g, outfile);
            fputc(the_image->data[i][j].b, outfile);
        }
    }
    
    fclose(outfile);
}

