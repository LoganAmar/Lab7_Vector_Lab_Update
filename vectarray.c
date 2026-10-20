/**
* Logan Amar
* CPE 2600 Lab5
* vectarray.c
* Stores vectors
*/

#include "vectarray.h"
#include "myvectop.h"

static vect vectors[ARRAY_SIZE];

int add_vect(vect v){

    // replace if the name already exists
    for (int i = 0; i < ARRAY_SIZE; i++){
        if (vectors[i].name == v.name){
            vectors[i] = v;
            return 0;
        }
    }

    // use the first empty slot
    for (int i = 0; i < ARRAY_SIZE; i++){
        if (vectors[i].name == '\0'){
            vectors[i] = v;
            return 0;
        }
    }
    return -1;  // array full
}

vect find_vect(char *name){
    for (int i = 0; i < ARRAY_SIZE; i++){
        if (vectors[i].name == name[0]){
            return vectors[i];
        }
    }
    vect notfound = {0};
    return notfound;
}

// copies the vector in slot i to out, returns -1 if the slot is empty
int get_vect_at(int i, vect *out){
    if (i < 0 || i >= ARRAY_SIZE || vectors[i].name == '\0'){
        return -1;
    }
    *out = vectors[i];
    return 0;
}

void clear(void){
    for (int i = 0; i < ARRAY_SIZE; i++){
        vectors[i].name = '\0';
    }
}