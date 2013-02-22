//
//  light.h
//  raycast
//
//  Created by Liam Westby on 2/20/13.
//  Copyright (c) 2013 Liam Westby. All rights reserved.
//

#ifndef raycast_light_h
#define raycast_light_h

#include "ppm.h"

#define LIGHTS_COUNT 2

typedef struct {
    float *position;
    pixel color;
} point_light;

point_light** get_lights();



#endif
