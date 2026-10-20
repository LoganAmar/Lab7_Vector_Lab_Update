/**
* Logan Amar
* CPE 2600 Lab5
* myveclab.c
* Main source file
* gcc -Wall -o main myveclab.c myvectop.c vectarray.c vectinterface.c
*/

#include <stdio.h>
#include <string.h>
#include "vectinterface.h"

int main(int argc, char *argv[]){

    if (argc > 1 && strcmp(argv[1], "-h") == 0){
        print_help();
        return 0;
    }

    run_interface();

    return 0;
}