/**
* Logan Amar
* CPE 2600 Lab5
* vectarray.h
* Header for vector calculations
*/

#ifndef MYVECTOP_H
#define MYVECTOP_H

typedef struct{
    char name;
    double x;
    double y;
    double z;
} vect;

vect add(vect a, vect b);

vect sub(vect a, vect b);

vect scalar(vect a, double scale);

vect cross(vect a, vect b);

double dot(vect a, vect b);

#endif