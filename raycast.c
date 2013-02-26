//
//  raycast.c
//  raycast
//
//  Created by Liam Westby on 2/7/13.
//  Functions to raycast an image.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "raycast.h"
#include "vector.h"

#define MAX_RAY_LEVEL 7
#define DIFFUSE_COEFFICIENT 0.7
#define SPECULAR_COEFFICIENT 0.3
#define AMBIENT_COEFFICIENT 0.15
#define SPECULAR_SPREAD 5

/* Raycast an image with the given scene of the given size using perspective projection from the given origin.
 *
 * img: The image to write to.
 * objects: The objects in the scene
 * num_objects: The number of objects in the scene
 * image_width: The width of the final image, in pixels
 * image_height: The height of the final image, in pixels
 * world_width: The width of the image in world units
 * world_height: The height of the image in world units
 * origin: vector to the origin viewpoint.
 */
void raycast_perspective(ppm_image* img, object** objects, int num_objects, point_light **lights, int num_lights, int image_width, int image_height, float world_width, float world_height, float *origin) {
    float pixheight = world_height / image_height;
    float pixwidth = world_width / image_width;
    float *pixelvec = (float*)malloc(sizeof(float)*3);
    float *unitvec = (float*)malloc(sizeof(float)*3);
    float *position = (float*)malloc(sizeof(float)*3);
    float distance;
    
    for (int i = 0; i < image_height; i++) {
        pixelvec[1] = 0 + world_height / 2 - pixheight * (i + 0.5);
        
        for (int j = 0; j < image_width; j++) {
            pixelvec[0] = 0 - world_width / 2 + pixwidth * (j + 0.5);
            pixelvec[2] = -0.4;
            v_unit(pixelvec, unitvec);

            int object_number = shoot(objects, num_objects, origin, unitvec, &distance);
            
            //distance -= 0.0001;
            v_scale(unitvec, distance, position);
            v_add(origin, position, position);
            img->data[i][j] = shade(objects, object_number, lights, position, unitvec, 0);
        }
    }
}

/* Raycast an image with the given scene of the given size using parallel projection in the given direction.
 *
 * img: The image to write to.
 * objects: The objects in the scene
 * num_objects: The number of objects in the scene
 * image_width: The width of the final image, in pixels
 * image_height: The height of the final image, in pixels
 * world_width: The width of the image in world units
 * world_height: The height of the image in world units
 * direction: vector from each origin into the scene.
 */
void raycast_parallel(ppm_image* img, object** objects, int num_objects, point_light **lights, int num_lights, int image_width, int image_height, float world_width, float world_height, float *direction) {
    float pixheight = world_height / image_height;
    float pixwidth = world_width / image_width;
    float *origin = (float*)malloc(sizeof(float)*3);
    float *unitvec = direction;
    float *position = (float*)malloc(sizeof(float)*3);
    float distance;
    
    for (int i = 0; i < image_height; i++) {
        origin[1] = 0 + world_height / 2 - pixheight * (i + 0.5);
        
        for (int j = 0; j < image_width; j++) {
            origin[0] = 0 - world_width / 2 + pixwidth * (j + 0.5);
            origin[2] = -0.4;
            
            int object_number = shoot(objects, num_objects, origin, unitvec, &distance);
            //distance -= 0.0001;
            v_scale(unitvec, distance, position);
            v_add(origin, position, position);
            img->data[i][j] = shade(objects, object_number, lights, position, unitvec, 0);
        }
    }
}

/* Shoots the ray defined by the given origin and direction into the scene of objects and determines which (if any) is hit first.
 *
 * objects: The objects in the scene
 * num_objects: The number of objects in the scene
 * origin: The point of origin of the ray.
 * direction: The direction the ray is going, as a unit vector.
 *
 * Return: The index of the object in objects that was hit first, or -1 if no object was hit.
 */
int shoot(object **objects, int num_objects, float *origin, float *direction, float *distance_out) {
    float distance = INFINITY;
    int object_num = -1;
    float tempdistance;
    for (int i = 0; i < num_objects; i++) {
        tempdistance = object_intersect(objects[i], origin, direction);
        if (tempdistance < distance) {
            distance = tempdistance;
            object_num = i;
        }
    }
    distance -= 0.00001;
    if (distance_out != NULL) *(distance_out) = distance;
    return object_num;
}

/* Get the color of the given shape.
 *
 * objects: The objects in the scene
 * object_number: The index in objects of the object whose color is requested.
 *
 * Return: a pixel with color values the same as the specified shape.
 */
pixel shade(object** objects, int object_number, point_light **lights, float *position, float *direction, int level) {
    pixel color;
    if (level > MAX_RAY_LEVEL || object_number == -1) {
        color.r = 0;
        color.g = 0;
        color.b = 0;
        
        return color;
    }
    float *reflection = reflection_vector(objects[object_number], position, direction);
    float distance;
    int object_hit = shoot(objects, OBJECTS_COUNT, position, reflection, &distance);
    if (distance == INFINITY) {
        color.r = 0;
        color.g = 0;
        color.b = 0;
    }
    else {
        //distance -= 0.000001;
        float *reflected_position = (float*)malloc(sizeof(float)*3);
        v_scale(reflection, distance, reflected_position);
        v_add(position, reflected_position, reflected_position);
        
        pixel m_color = shade(objects, object_hit, lights, reflected_position, reflection, level+1);
        m_color.r *= objects[object_number]->reflectivity;
        m_color.g *= objects[object_number]->reflectivity;
        m_color.b *= objects[object_number]->reflectivity;
        
        float *from_reflected = (float*)malloc(sizeof(float)*3);
        v_scale(reflection, -1.0, from_reflected);
        color = direct_shade(objects[object_number], position, direction, from_reflected, m_color);
        color.r *= objects[object_number]->reflectivity;
        color.g *= objects[object_number]->reflectivity;
        color.b *= objects[object_number]->reflectivity;
        
    }
    float *light_direction = (float*)malloc(sizeof(float)*3);
    pixel light;
    for (int i = 0; i < LIGHTS_COUNT; i++) {
        //float* light_location = lights[i]->position;
        v_sub(position, lights[i]->position, light_direction);
        float light_distance = v_magnitude(light_direction);
        v_unit(light_direction, light_direction);
        float shoot_distance;
        int closest_object = shoot(objects, OBJECTS_COUNT, lights[i]->position, light_direction, &shoot_distance);
        //shoot_distance -= 0.0001;
        if (closest_object == object_number && fabs(shoot_distance - light_distance) < 0.001) {
            light = direct_shade(objects[object_number], position, direction, light_direction, lights[i]->color);
            
            int red = color.r + light.r;
            if (red > 255) red = 255;
            else if (red < 0) red = 0;
            color.r = red;
            
            int green = color.g + light.g;
            if (green > 255) green = 255;
            else if (green < 0) green = 0;
            color.g = green;
            
            int blue = color.b + light.b;
            if (blue > 255) blue = 255;
            else if (blue < 0) blue = 0;
            color.b = blue;
        }
    }
    
    return color;
    
}

pixel direct_shade(object *the_object, float *position, float *direction, float *from_light, pixel light_color) {
    // Vector here is used in the sense of multiple values, not a direction in space
    float *illumation_vector = (float*)malloc(sizeof(float)*3);
    float *diffuse_vector = (float*)malloc(sizeof(float)*3);
    float *specular_vector = (float*)malloc(sizeof(float)*3);
    float *ambient_vector = (float*)malloc(sizeof(float)*3);
    float *normal = get_normal(the_object, position);
    float *reflected = reflection_vector(the_object, position, from_light);
    float *view = (float*)malloc(sizeof(float)*3);
    v_scale(direction, -1.0, view);
    //v_unit(view, view);
    
    // Convert the pixel values to floats between 0.0 and 1.0 for use in the equation
    float *object_color_vector = (float*)malloc(sizeof(float)*3);
    object_color_vector[0] = the_object->color.r/255.0;
    object_color_vector[1] = the_object->color.g/255.0;
    object_color_vector[2] = the_object->color.b/255.0;
    
    float *light_color_vector = (float*)malloc(sizeof(float)*3);
    light_color_vector[0] = light_color.r/255.0;
    light_color_vector[1] = light_color.g/255.0;
    light_color_vector[2] = light_color.b/255.0;
    
    // For use in specular and ambient calculations
    float *white_color = (float*)malloc(sizeof(float)*3);
    white_color[0] = 1.0;
    white_color[1] = 1.0;
    white_color[2] = 1.0;
    
    // Calculate diffuse value I_d
    diffuse_vector[0] = light_color_vector[0] * object_color_vector[0] * -(v_dot(from_light, normal));
    diffuse_vector[1] = light_color_vector[1] * object_color_vector[1] * -(v_dot(from_light, normal));
    diffuse_vector[2] = light_color_vector[2] * object_color_vector[2] * -(v_dot(from_light, normal));
    
    // Calculate specular value I_s
    specular_vector[0] = light_color_vector[0] * powf(v_dot(reflected, view), SPECULAR_SPREAD);
    specular_vector[1] = light_color_vector[1] * powf(v_dot(reflected, view), SPECULAR_SPREAD);
    specular_vector[2] = light_color_vector[2] * powf(v_dot(reflected, view), SPECULAR_SPREAD);
    
    // Calculate final illumination vector
    v_scale(diffuse_vector, DIFFUSE_COEFFICIENT, diffuse_vector);
    v_scale(specular_vector, SPECULAR_COEFFICIENT, specular_vector);
    v_scale(white_color, AMBIENT_COEFFICIENT, ambient_vector);
    
    v_add(diffuse_vector, specular_vector, illumation_vector);
    v_add(illumation_vector, ambient_vector, illumation_vector);
    
    pixel illumination;
    int illum_r = (int)(illumation_vector[0] * 255);
    if (illum_r > 255) illum_r = 255;
    else if (illum_r < 0) illum_r = 0;
    
    int illum_g = (int)(illumation_vector[1] * 255);
    if (illum_g > 255) illum_g = 255;
    else if (illum_g < 0) illum_g = 0;
    
    int illum_b = (int)(illumation_vector[2] * 255);
    if (illum_b > 255) illum_b = 255;
    else if (illum_b < 0) illum_b = 0;
    
    illumination.r = illum_r;
    illumination.g = illum_g;
    illumination.b = illum_b;
    
    return illumination;
}

float* reflection_vector(object *the_object, float *position, float *direction) {
    float *reflection = (float*)malloc(sizeof(float)*3);
    float *normal = get_normal(the_object, position);
    v_scale(normal, -2*v_dot(direction, normal), reflection);
    v_add(reflection, direction, reflection);
    v_unit(reflection, reflection);

    return reflection;
}

float* get_normal(object *the_object, float *position) {
    float *normal;
    if (the_object->type == PLANE_TYPE) normal = the_object->definition.plane.normal;
    else {
        normal = (float*)malloc(sizeof(float)*3);
        v_sub(position, the_object->definition.sphere.center, normal);
        v_unit(normal, normal);
    }
    return normal;
}