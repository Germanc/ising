#include "stdlib.h"
#include "time.h"
#include <unistd.h>
#include <stdio.h>

#include "metropolis.h"
#include "lattice.h"

int main(int argc, char **argv) {
	int c;
	int n = 8;
    float T = 10;
	int niter = 2000;
    float B = 0;
	float prob = 0.5;

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
			T = atoi(optarg);
			break;
		  case 'p':
			prob = atoi(optarg);
			break;
		  case 'B':
			B  = atoi(optarg);
			break;


		  case 'h':
			  fprintf (stderr, "-n lado de la red\n"
				"-T temperatura\n"
                "-B campo\n"
                "-p probabilidad de ocupacion inicial\n"
				"-i numero de iteraciones\n");
              return 0;
		  default:
			break;
      }

	int *lattice = (int *)malloc(n * n * sizeof(int));
	srand(time(NULL));
	fill_lattice(lattice, n, prob);
	for (int i = 0; i < niter; i++) {
		metropolis(lattice, n, T, B);
	}
	print_lattice(lattice, n);
	return 0;
}
