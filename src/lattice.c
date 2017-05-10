#include "lattice.h"
#include <stdlib.h>
#include <stdio.h>

int fill_lattice(int *lattice, int n, float p) {
    float valor_aleatorio;
    int i;
    for(i=0; i<(n*n); i++){
        valor_aleatorio = rand()%RAND_MAX;
        if (valor_aleatorio < (p*RAND_MAX)){
            lattice[i] = 1;

        }
        else {
            lattice[i] = 0;
        }
    }

  return 0;
}

int print_lattice(int *lattice, int n) {
    int i;
    for(i=0;i<(n*n);i++) {
        if((i%n)==0) {
            printf("\n %i ", lattice[i]);
        }
        else {
            printf(" %i ", lattice[i]);
        }
    }
    printf("\n \n");

  return 0;
}
