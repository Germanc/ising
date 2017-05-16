#include "stdlib.h"
#include "time.h"
#include <unistd.h>
#include <stdio.h>
#include "auxiliares.h"
#include <math.h>

#include "metropolis.h"
#include "lattice.h"

int main(int argc, char **argv) {
	int c;
	int n = 8;
    float T = 10;
	int niter = 2000;
    float B = 0;
	float prob = 0.5;
	int npre = n*n*5000;

    while ((c = getopt (argc, argv, "n:T:i:B:p:r:h")) != -1)
		switch (c)
		  {
			case 'n':
				n = atoi(optarg);
				break;
			case 'i':
				niter = atoi(optarg);
				break;
			case 'T':
				T = atof(optarg);
				break;
			case 'p':
				prob = atoi(optarg);
				break;
			case 'B':
				B  = atoi(optarg);
				break;
			case 'r':
				npre = atoi(optarg);
				break;


		  case 'h':
			  fprintf (stderr, "-n lado de la red\n"
				"-T temperatura\n"
                "-B campo\n"
                "-p probabilidad de ocupacion inicial\n"
				"-i numero de iteraciones\n"
				"-r numero de pasos de pretermalizacion\n"
				"El formato de saluda es \'T B energia varenergia magnet varmagnet\'\n");
              return 0;
		  default:
			break;
      }

	int *lattice = (int *)malloc(n * n * sizeof(int));
	srand(time(NULL));
	fill_lattice(lattice, n, prob);
	float* magneti;
	float* energi;
	float* rmagnet;
	float* renerg;
	magneti = (float *)malloc(sizeof(float)*niter);
	energi = (float *)malloc(sizeof(float)*niter);
	rmagnet = (float *)malloc(sizeof(float)*niter);
	renerg = (float *) malloc(sizeof(float)*niter);
	for ( int k = 0; k<npre; k++ ){
		metropolis(lattice, n, T, B);
	}
	float magnet = 0, magnetsq = 0, energ = 0, energsq = 0;
	float magnetizacion_ahora, energia_ahora;
	for (int i = 0; i < niter; i++) {
		for (int j = 0; j < n*n; j++){
			metropolis(lattice, n, T, B)/(n*n);
		}
		magnetizacion_ahora = magnetizacion(lattice, n)/(n*n);
		energia_ahora = energia(lattice, n, T, B)/(n*n);

		magnet = magnet + magnetizacion_ahora/niter;
		magnetsq = magnetsq + magnetizacion_ahora*magnetizacion_ahora/niter;

		energ = energ + energia_ahora/niter;
		energsq = energsq + energia_ahora*energia_ahora/niter;
		energi[i] = energia_ahora/niter;
		magneti[i] = magnetizacion_ahora/niter;
	}
	float sumam , sumae , sumamd=0, sumaed=0;
	for (int i=0; i<niter;i++){
		sumamd = sumamd + (magneti[i]-magnet)*(magneti[i]-magnet);
		sumaed = sumaed + (energi[i]-energ)*(energi[i]-energ);
	}
	for (int k = 0; k<niter; k++){
		sumam = 0;
		sumae = 0;
		for ( int i = 0; i<niter-k; i++){
			sumam = sumam + (magneti[i]-magnet)*(magneti[i+k]-magnet);
			sumae = sumae + (energi[i]-energ)*(energi[i+k]-energ);
		}
		rmagnet[k] = sumam/sumamd;
		renerg[k] = sumae/sumaed;	
	}
	float magnet_varianza = sqrt(magnetsq - magnet*magnet);
	float energia_varianza = sqrt(energsq - energ*energ);
    printf("%f %f %.15f %.15f %.15f %.15f\n", T, B, energ, energia_varianza, magnet, magnet_varianza);
//	print_lattice(lattice, n);
	FILE *correlacion;
	correlacion = fopen("correlacion.dat", "w");

	for(int i=0; i<niter; i++){
		fprintf(correlacion, "%i %f %f\n", i, rmagnet[i], renerg[i]);
	}

	fclose(correlacion);
	free(magneti);
	free(energi);
	return 0;
}
