#include "metropolis.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int metropolis(int *lattice, int n, float T, float B, float J2) {
    int sitio;
    sitio = pick_site(lattice, n);
    int delta_e;
    delta_e = flip(lattice, n, T, sitio, B, J2);
  return delta_e;
}

int pick_site(int *lattice, int n) {
    return (int)round(((double)rand())/RAND_MAX * (n * n - 1));
}

int flip(int *lattice, int n, float T, int sitio, float B, float J2) {
    int S, E, O, N, SW, SE, NW, NE;
    float J = 1.0;;
    E = (sitio%(n-1) == 0) ? sitio-n+1 : sitio+1;
    if(E<0) E = 1;
    S = (sitio>=n*(n-1)-1) ? sitio-(n*(n-1))+1 : sitio+n;
    O = (sitio%(n)== 0) ? sitio+n-1 : sitio-1;
    N = (sitio<(n)) ? sitio+(n*(n-1)) : sitio-n;
    SW = (S%n) ? S+n-1: S-1;
    if(SW<0) SW += n;
    SE = (S%(n-1)) ? S-n+1: S+1; 
    if(SE < 0) SE += n;
    NW = (N%n) ? N+n-1: N-1;
    if(NW<0) NW+=n;
    NE = (N%(n-1)) ? N-n+1: N+1; 
    if(NE<0) NE+=n;
//    printf("SE %i SW %i NW %i NE %i S %i N %i\n", SE, SW, NW, NW, S, N);

//    printf("E: %i, S: %i, O: %i, N: %i, sitio: %i\n", E, S, O, N, sitio); 

    float aleatorio = (float)rand()/RAND_MAX;
//    printf("Aleatorio: %f\n", aleatorio);
    int energia_inicial = -J*lattice[sitio]*(lattice[E]+lattice[N]+lattice[O]+lattice[S])-J2*lattice[sitio]*(lattice[SE]+lattice[NE]+lattice[SW]+lattice[NW]);
    lattice[sitio] *= -1;
    int energia_final = -J*lattice[sitio]*(lattice[E]+lattice[N]+lattice[O]+lattice[S])-J2*lattice[sitio]*(lattice[SE]+lattice[NE]+lattice[SW]+lattice[NW]);
    int delta_e = (energia_final - energia_inicial) - B*(lattice[sitio]*(-1)-lattice[sitio]);;
//    printf("Energia final: %i, Energia inicial: %i\n", energia_final, energia_inicial);

    float pi = exp(-(1.0/T)*delta_e);
    if (pi>1) { 
        return 0;
    }else{
        if (aleatorio > pi) lattice[sitio] *= -1;
    }
  return 0;

}
