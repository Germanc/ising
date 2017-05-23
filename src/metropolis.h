#ifndef METROPOLIS_H
#define METROPOLIS_H
int metropolis(int *lattice, int n, float T, float B, float J2, float *energ, float *magnet);
int pick_site(int *lattice, int n);
int flip(int *lattice, int n, float T, int sitio, float B, float J2, float *energ, float *magnet);
#endif
