//
//  raycast.h
//  raycast
//
//  Created by Liam Westby on 2/6/13.
//  Copyright (c) 2013 Liam Westby. All rights reserved.
//

#include "object.h"
#include "light.h"

#ifndef raycast_raycast_h
#define raycast_raycast_h

void raycast_perspective(ppm_image* img, object** objects, int num_objects, point_light **lights, int num_lights, int image_width, int image_height, float world_width, float world_height, float *origin);
void raycast_parallel(ppm_image* img, object** objects, int num_objects, point_light **lights, int num_lights, int image_width, int image_height, float world_width, float world_height, float *direction);
int shoot(object** objects, int num_objects, float *origin, float *direction, float *distance_out);
pixel shade(object** objects, int object_number, point_light **lights, float *position, float *direction, int level);
pixel direct_shade(object *the_object, float *position, float *direction, float *from_light, pixel light_color);

#endif
