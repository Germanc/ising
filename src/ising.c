#include "stdlib.h"
#include "time.h"
#include <unistd.h>
#include <stdio.h>
#include "auxiliares.h"
#include <math.h>
#include "metropolis.h"
#include "lattice.h"

#define PROMEDIO_CORR 100

int main(int argc, char **argv) {
	int c;
	int n = 8;
    float T = 10;
	int niter = 2000;
    float B = 0;
	float prob = 0.5;
	int npre = n*n*5000;
	int corr = 0;

	//parametros, nunca mas muchos ejecutables cuando puedo tener parametros
    while ((c = getopt (argc, argv, "n:T:i:B:p:r:ch")) != -1)
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
			case 'c':
				corr = 1;
				break;


		  case 'h':
			  fprintf (stderr, "-n lado de la red\n"
				"-T temperatura\n"
                "-B campo\n"
                "-p probabilidad de ocupacion inicial\n"
				"-i numero de iteraciones\n"
				"-r numero de pasos de pretermalizacion\n"
				"-c calcula la funcion de correlacion\n"
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
	//pretermalizacion
	for ( int k = 0; k<npre; k++ ){
		metropolis(lattice, n, T, B);
	}
	float magnet = 0, magnetsq = 0, energ = 0, energsq = 0;
	float magnetizacion_ahora, energia_ahora;
	//inicializo variables
	if(corr==0){
		for (int i = 0; i < niter; i++) {
			//j> tiempo de correlacion
			for (int j = 0; j < n*n; j++){
				metropolis(lattice, n, T, B)/(n*n);
			}
			//calcular la magnetizacion y la energia en cada paso es lo suficientemente 
			//rapido como para que no valga la pena pasarme las delta. si en algun momento 
			//veo que me limita lo cambio y fue
			magnetizacion_ahora = magnetizacion(lattice, n)/(n*n);
			energia_ahora = energia(lattice, n, T, B)/(n*n);

			magnet = magnet + magnetizacion_ahora/niter;
			magnetsq = magnetsq + magnetizacion_ahora*magnetizacion_ahora/niter;

			energ = energ + energia_ahora/niter;
			energsq = energsq + energia_ahora*energia_ahora/niter;
		}
		float magnet_varianza = sqrt(magnetsq - magnet*magnet);
		float energia_varianza = sqrt(energsq - energ*energ);
		printf("%f %f %.15f %.15f %.15f %.15f\n", T, B, energ, energia_varianza, magnet, magnet_varianza);
	//si paso -c calculo la correlacion
	}else{
		int cola = n*n;
		for(int i;i<niter-cola;i++) {
			rmagnet[i] = 0;
			renerg[i] = 0;
		}
		float sumam, sumae;
		for(int j; j<PROMEDIO_CORR; j++){
			magnet = 0;
			energ = 0;
			for (int h = 0; h < niter; h++) {
				metropolis(lattice, n, T, B)/(n*n);
				magnetizacion_ahora = magnetizacion(lattice, n)/(n*n);
				energia_ahora = energia(lattice, n, T, B)/(n*n);

				magnet = magnet + magnetizacion_ahora/niter;
				energ = energ + energia_ahora/niter;
				
				energi[h] = energia_ahora;
				magneti[h] = magnetizacion_ahora;
			}

			float sumamd=0, sumaed=0;
			for (int i=0; i<niter;i++){
				sumamd += (magneti[i]-magnet)*(magneti[i]-magnet)/niter;
				sumaed += (energi[i]-energ)*(energi[i]-energ)/niter;
			}
			for (int k = 0; k<niter-cola; k++){
				sumam = 0;
				sumae = 0;
				for ( int i = 0; i<niter-k; i++){
					sumam += (magneti[i]-magnet)*(magneti[i+k]-magnet)/niter;
					sumae += (energi[i]-energ)*(energi[i+k]-energ)/niter;
				}
				rmagnet[k] += sumam/(sumamd*PROMEDIO_CORR);
				renerg[k] += sumae/(sumaed*PROMEDIO_CORR);	
			}
			fill_lattice(lattice, n, prob);
			for ( int k = 0; k<npre*n*n; k++ ){
				metropolis(lattice, n, T, B);
			}
		}
	//	print_lattice(lattice, n);
		FILE *correlacion;
		char archivo[100];
		snprintf(archivo, (int)100, "correlacion_%i_%3f_%3f.dat", n, T, B);
		correlacion = fopen(archivo, "w");

		for(int i=0; i<niter-cola; i++){
			fprintf(correlacion, "%i %f %f\n", i, rmagnet[i], renerg[i]);
		}

		fclose(correlacion);
	}
	free(magneti);
	free(energi);
	return 0;
}
