//
//  vector.c
//  raycast
//
//  Created by Liam Westby on 2/6/13.
//  Library of vector operations.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "vector.h"

/* Initializes three float values into a given vector.
 * 
 * x: The x component.
 * y: The y component.
 * z: The z component.
 * out: The preallocated float array to store the vector.
 */
void v_init(float x, float y, float z, float *out) {
    out[0] = x;
    out[1] = y;
    out[2] = z;
}

/* Compute the magnitude of the given vector.
 * 
 * v: Pointer to an array of three floats representing a vector.
 * 
 * Return: The magnitude of the vector.
 */
float v_magnitude(float *v) {
    return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

/* Normalize the given vector.
 *
 * in: The vector to normalize.
 * out: The location to store the result.
 */
void v_unit(float *in, float *out) {
    float mag = v_magnitude(in);
    out[0] = in[0]/mag;
    out[1] = in[1]/mag;
    out[2] = in[2]/mag;
}

/* Add two vectors together.
 * 
 * f1: The first vector to add.
 * f2: The second vector to add.
 * out: The location to store the result.
 */
void v_add(float *f1, float *f2, float *out) {
    out[0] = f1[0] + f2[0];
    out[1] = f1[1] + f2[1];
    out[2] = f1[2] + f2[2];
}

/* Subtract one vector from another.
 *
 * f1: First vector. Second is subtracted from this.
 * f2: Second vector. Subtracted from the first vector.
 * out: The location to store the result.
 */
void v_sub(float *f1, float *f2, float *out) {
    out[0] = f1[0] - f2[0];
    out[1] = f1[1] - f2[1];
    out[2] = f1[2] - f2[2];
}

/* Scale a vector by a scalar value.
 *
 * v: The vector to scale.
 * s: The scalar to multiply the vector by.
 * out: The location to store the vector.
 */
void v_scale(float *v, float s, float *out) {
    out[0] = v[0] * s;
    out[1] = v[1] * s;
    out[2] = v[2] * s;
}

/* Compute the dot product of two vectors.
 *
 * v1: The first vector.
 * v2: The second vector.
 *
 * Return: The dot product of the vectors.
 */
float v_dot(float *v1, float *v2) {
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

/* Compute the cross product of two vectors.
 *
 * v1: The first vector to multiply.
 * v2: The second vector to multiply.
 * out: The location to store the result.
 */
void v_cross(float *v1, float *v2, float *out) {
    out[0] = v1[1]*v2[2] - v1[2]*v2[1];
    out[1] = v1[2]*v2[0] - v1[0]*v2[2];
    out[2] = v1[0]*v2[1] - v1[1]*v2[0];
}


/* Compute the reflection of a vector on an object.
 *
 * the_object: The object to reflect off of.
 * position: The position hit.
 * direction: The direction of the vector to be reflected.
 *
 * Returns: the reflection of direction on the object at position.
 */
float* reflection_vector(object *the_object, float *position, float *direction) {
    float *reflection = (float*)malloc(sizeof(float)*3);
    float *normal = get_normal(the_object, position);
    v_scale(normal, -2*v_dot(direction, normal), reflection);
    v_add(reflection, direction, reflection);
    v_unit(reflection, reflection);
    
    return reflection;
}

/* Get the normal of a shape at a given position.
 *
 * the_object: The object to get the normal of.
 * position: The position on the object to calculate the normal.
 * 
 * Returns: The normal to the object at the given position.
 */
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

