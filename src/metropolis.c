#include "metropolis.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int metropolis(int *lattice, int n, float T, float B) {
    int sitio;
    sitio = pick_site(lattice, n);
    int delta_e;
    delta_e = flip(lattice, n, T, sitio, B);
  return delta_e;
}

int pick_site(int *lattice, int n) {
    return (int)round(((double)rand())/RAND_MAX * (n * n - 1));
}

int flip(int *lattice, int n, float T, int sitio, float B) {
    int S, E, O, N;
    float J = 1.0;;
    E = (sitio%(n-1) == 0) ? sitio-n+1 : sitio+1;
    if(E<0) E = 1;
    S = (sitio>=n*(n-1)-1) ? sitio-(n*(n-1))+1 : sitio+n;
    O = (sitio%(n)== 0) ? sitio+n-1 : sitio-1;
    N = (sitio<(n-1)) ? sitio+(n*(n-1)) : sitio-n;
//    printf("E: %i, S: %i, O: %i, N: %i, sitio: %i\n", E, S, O, N, sitio); 

    float aleatorio = (float)rand()/RAND_MAX;
//    printf("Aleatorio: %f\n", aleatorio);
    int energia_inicial = lattice[sitio]*(lattice[E]+lattice[N]+lattice[O]+lattice[S]);
    lattice[sitio] *= -1;
    int energia_final = lattice[sitio]*(lattice[E]+lattice[N]+lattice[O]+lattice[S]);
    int delta_e = -J*(energia_final - energia_inicial) - B*(lattice[sitio]*(-1)-lattice[sitio]);;
//    printf("Energia final: %i, Energia inicial: %i\n", energia_final, energia_inicial);

    float pi = exp(-(1.0/T)*delta_e);
    if (pi>1) { 
        return 0;
    }else{
        if (aleatorio > pi) lattice[sitio] *= -1;
    }
  return 0;

}
