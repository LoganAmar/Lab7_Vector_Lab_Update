/**
* Logan Amar
* CPE 2600 Lab5
* vectarray.h
* Header for vector array handler
*/

#ifndef VECTARRAY_H
#define VECTARRAY_H

#include "myvectop.h"

#define ARRAY_SIZE 10

int add_vect(vect v);

vect find_vect(char *name);

int get_vect_at(int i, vect *out);

void clear(void);

#endif