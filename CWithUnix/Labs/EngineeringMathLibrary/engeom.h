#ifndef __ENGEOM_H
#define __ENGEOM_H

extern void eng_sphere(float radius, float *surface, float *volume);
extern float eng_volCylinder(float radius, float height);
extern float eng_sumFloats(float x[], int numFloats);
extern double eng_sin(float angle);

#endif