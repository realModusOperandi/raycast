//
//  ppm.c
//  raycast
//
//  Created by Liam Westby on 2/6/13.
//  Functions for dealing with PPM images.
//

#include <stdio.h>
#include <stdlib.h>

#include "ppm.h"

/* Write an image out to disk in PPM format (P6 variant).
 * Will exit if file could not be opened for writing.
 *
 * the_image: Pointer to a ppm_image struct (see ppm.h) containing the image data to be written.
 * outfilepath: String containing the file path that should be written to.
 */
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
    
    for (int i = 0; i < the_image->height; i++) {
        for (int j = 0; j < the_image->width; j++) {
            fputc(the_image->data[i][j].r, outfile);
            fputc(the_image->data[i][j].g, outfile);
            fputc(the_image->data[i][j].b, outfile);
        }
    }
    
    fclose(outfile);
}

