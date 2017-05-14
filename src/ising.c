#include "stdlib.h"
#include "time.h"
#include <unistd.h>
#include <stdio.h>
#include "auxiliares.h"

#include "metropolis.h"
#include "lattice.h"

int main(int argc, char **argv) {
	int c;
	int n = 8;
    float T = 10;
	int niter = 2000;
    float B = 0;
	float prob = 0.5;
	int npre = n*n*500;

    while ((c = getopt (argc, argv, "n:T:i:B:p:h")) != -1)
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
				"El formato de saluda es \'energia varenergia magnet varmagnet\'\n");
              return 0;
		  default:
			break;
      }

	int *lattice = (int *)malloc(n * n * sizeof(int));
	srand(time(NULL));
	fill_lattice(lattice, n, prob);
	for ( int k = 0; k<npre; k++ ){
		metropolis(lattice, n, T, B);
	}
	float magnet = 0, magnetsq = 0, energ = 0, energsq = 0;
	float magnetizacion_ahora, energia_ahora;
	for (int i = 0; i < niter; i++) {
		for (int j = 0; j < n*n; j++){
			metropolis(lattice, n, T, B)/(n*n);
		}
		magnetizacion_ahora = magnetizacion(lattice, n)/(n*n*niter);
		magnet = magnet + magnetizacion_ahora;
		magnetsq = magnetsq + magnetizacion_ahora*magnetizacion_ahora;
		energia_ahora = energia(lattice, n, T, B)/(n*n*niter);
		energ = energ + energia_ahora;
		energsq = energsq + energia_ahora*energia_ahora;
	}
	float magnet_varianza = magnetsq - magnet*magnet;
	float energia_varianza = energsq - energ*energ;
    printf("%.15f %.15f %.15f %.15f\n", energ, energia_varianza, magnet, magnet_varianza);
//	print_lattice(lattice, n);
	return 0;
}
