/**
* Logan Amar
* CPE 2600 Lab5
* vectinterface.c
* Reads commands and prints results
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "vectarray.h"
#include "myvectop.h"
#include "vectinterface.h"

int print_help(void){
    printf("Commands:\n");
    printf("  -h                 Display this help message\n");
    printf("  quit               Exit the program\n");
    printf("  clear              Clear all stored vectors\n");
    printf("  list               Display all stored vectors\n\n");
    printf("Vector Operations:\n");
    printf("  a = 1 2 3          Create or update a vector\n");
    printf("  a = 1, 2, 3        Create vector using commas\n");
    printf("  a                  Display vector a\n");
    printf("  a + b              Add two vectors\n");
    printf("  a - b              Subtract two vectors\n");
    printf("  a * 2              Multiply vector by scalar\n");
    printf("  2 * a              Multiply scalar by vector\n");
    printf("  a x b              Cross product of two vectors\n");
    printf("  a . b              Dot product of two vectors\n");
    printf("  c = a + b          Store result in vector c\n\n");
    printf("Notes:\n");
    printf("  - Maximum of 10 stored vectors\n");
    printf("  - All vectors contain 3 components (x, y, z)\n");
    printf("  - Spaces are required around operators\n");

    return 0;
}

int print_vect(vect v){
    printf("%c = %g %g %g\n", v.name, v.x, v.y, v.z);

    return 0;
}

int list_vects(void){
    vect v;

    for (int i = 0; i < ARRAY_SIZE; i++){
        if (get_vect_at(i, &v) == 0){
            print_vect(v);
        }
    }

    return 0;
}

// a vector name is a single letter
int is_name(char *s){
    return (strlen(s) == 1 && isalpha((unsigned char)s[0]));
}

// Does the math for "s1 op s2"
// returns 0 if c has a vector result, 1 if dp has a dot product, -1 on error
int calculate(char *s1, char op, char *s2, vect *c, double *dp){
    vect a;
    vect b;

    if (strchr("+-*x.", op) == NULL){
        printf("Unknown operation\n");
        return -1;
    }

    if (op == '*'){
        char *vname;
        char *num;
        char *end;

        // vector * number or number * vector
        if (is_name(s1) && !is_name(s2)){
            vname = s1;
            num = s2;
        } else if (!is_name(s1) && is_name(s2)){
            vname = s2;
            num = s1;
        } else {
            printf("For scalar multiplication, multiply vector by number\n");
            return -1;
        }

        a = find_vect(vname);
        if (a.name == '\0'){
            printf("Vector %s does not exist\n", vname);
            return -1;
        }

        double sc = strtod(num, &end);
        if (end == num || *end != '\0'){
            printf("Invalid scalar\n");
            return -1;
        }

        *c = scalar(a, sc);
        return 0;
    }

    if (!is_name(s1) || !is_name(s2)){
        printf("This operation needs two vectors\n");
        return -1;
    }

    a = find_vect(s1);
    b = find_vect(s2);

    if (a.name == '\0'){
        printf("Vector %s does not exist\n", s1);
        return -1;
    }
    if (b.name == '\0'){
        printf("Vector %s does not exist\n", s2);
        return -1;
    }

    if (op == '+'){
        *c = add(a, b);
    } else if (op == '-'){
        *c = sub(a, b);
    } else if (op == 'x'){
        *c = cross(a, b);
    } else {
        *dp = dot(a, b);
        return 1;
    }

    return 0;
}

// Handles any line with = in it
int do_assignment(char *input){
    vect v;
    vect c;
    char name;
    char op;
    char extra;
    char s1[32];
    char s2[32];
    double dp;

    // Try c = a + b first
    int parsed = sscanf(input, " %c = %31s %c %31s %c", &name, s1, &op, s2, &extra);

    if (parsed == 4 && strchr("+-*x.", op) != NULL && isalpha((unsigned char)name)){
        int result = calculate(s1, op, s2, &c, &dp);

        if (result == 0){
            c.name = name;
            print_vect(c);
            if (add_vect(c) == -1){
                printf("Vector limit reached!\n");
            }
        } else if (result == 1){
            printf("Cannot store a dot product in a vector\n");
        }

        return 0;
    }

    parsed = sscanf(input, " %c = %lf %lf %lf %c", &v.name, &v.x, &v.y, &v.z, &extra);

    if (parsed == 3){
        if (sscanf(input, " %c = %lf %lf %c", &v.name, &v.x, &v.y, &extra) == 3){
            v.z = 0.0;
            parsed = 4;
        }
    }

    if (parsed == 4 && isalpha((unsigned char)v.name)){
        if (add_vect(v) == -1){
            printf("Vector limit reached!\n");
        } else {
            print_vect(v);
        }
    } else {
        printf("Invalid vector assignment\n");
    }

    return 0;
}

// Handles a lone vector name or "a op b"
int do_expression(char *input){
    vect c;
    char op;
    char extra;
    char s1[32];
    char s2[32];
    double dp;

    int parsed = sscanf(input, " %31s %c %31s %c", s1, &op, s2, &extra);

    if (parsed == 1 && is_name(s1)){
        c = find_vect(s1);

        if (c.name == '\0'){
            printf("Vector %s does not exist\n", s1);
        } else {
            print_vect(c);
        }
    } else if (parsed == 3){
        int result = calculate(s1, op, s2, &c, &dp);

        if (result == 0){
            printf("%s %c %s = %g %g %g\n", s1, op, s2, c.x, c.y, c.z);
        } else if (result == 1){
            printf("%s %c %s = %g\n", s1, op, s2, dp);
        }
    } else {
        printf("Unknown command\n");
    }

    return 0;
}

int run_interface(void){

    while(1){
        printf("myveclab> ");

        char input[100];

        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        // Remove newline
        input[strcspn(input, "\n")] = '\0';

        // Commas work like spaces
        for (int i = 0; input[i] != '\0'; i++){
            if (input[i] == ','){
                input[i] = ' ';
            }
        }

        // Blank line, just prompt again
        if (strspn(input, " \t") == strlen(input)){
            continue;
        }

        if (strcmp(input, "quit") == 0) {
            break;
        }
        else if (strcmp(input, "list") == 0) {
            list_vects();
        }
        else if (strcmp(input, "clear") == 0) {
            clear();
        } else if (strcmp(input, "-h") == 0){
            print_help();
        } else if (strchr(input, '=') != NULL) {
            do_assignment(input);
        } else {
            do_expression(input);
        }
    }

    return 0;
}