//
//  raycast.h
//  raycast
//
//  Created by Liam Westby on 2/6/13.
//  Copyright (c) 2013 Liam Westby. All rights reserved.
//

#include "sphere.h"

#ifndef raycast_raycast_h
#define raycast_raycast_h

void raycast(ppm_image* img, sphere** objects, int num_objects, int image_width, int image_height, float world_width, float world_height, float *origin, int parallel);
int shoot(sphere** objects, int num_objects, float *direction, float *origin);
pixel shade(sphere** objects, int object_number);

#endif
