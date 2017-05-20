#include <stdio.h>
float energia(int *lattice, int n, float T, float B, float J2){
    int i;
    float energ =0;
    int S, E, SE, SW;
    float J = 1.0/T;
    J = 1;
    for(i=0;i<(n*n-1);i++){
        E = (i%(n-1) == 0) ? i-n+1 : i+1;
        if(E<0) E = 1;
        S = (i>=n*(n-1)-1) ? i-(n*(n-1))+1 : i+n;
        SW = (S%n) ? S+n-1: S-1;
        SE = (S%(n-1)) ? S-n+1: S+1; 
        if(SW<0) SW += n;
        if(SE < 0) SE += n;

        energ += -J*lattice[i]*(lattice[E]+lattice[S])-B*lattice[i]-J2*lattice[i]*(lattice[SE]+lattice[SW]);
    }
    return energ;
}

float magnetizacion(int *lattice, int n){
    int i;
    float magnet = 0; 
    for(i=0;i<n*n;i++){
        magnet += lattice[n];
    }
    return magnet;
}
