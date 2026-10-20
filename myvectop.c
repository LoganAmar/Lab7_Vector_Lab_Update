/**
* Logan Amar
* CPE 2600 Lab5
* vectarray.h
* Implements vector calculations
*/

#include "myvectop.h"

vect add(vect a, vect b){
    vect returnval;
    returnval.x = a.x + b.x;
    returnval.y = a.y + b.y;
    returnval.z = a.z + b.z;

    return returnval;
}

vect sub(vect a, vect b){
    vect returnval;
    returnval.x = a.x - b.x;
    returnval.y = a.y - b.y;
    returnval.z = a.z - b.z;

    return returnval;
}

vect scalar(vect a, double scale){
    vect returnval;

    returnval.x = a.x * scale;
    returnval.y = a.y * scale;
    returnval.z = a.z * scale;

    return returnval;
}

vect cross(vect a, vect b){
    vect returnval;
    returnval.x = (a.y * b.z) - (a.z * b.y);
    returnval.y = (a.z * b.x) - (a.x * b.z);
    returnval.z = (a.x * b.y) - (a.y * b.x);

    return returnval;
}

double dot(vect a, vect b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}