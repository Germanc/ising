#include "stdlib.h"
#include "time.h"
#include <unistd.h>
#include <stdio.h>

#include "metropolis.h"
#include "lattice.h"

int main(int argc, char **argv) {
	int c;
	int n = 8;
	float T = 10.0;
	int niter = 2000;

    while ((c = getopt (argc, argv, "n:t:i:h")) != -1)
		switch (c)
		  {
		  case 'n':
			n = atoi(optarg);
			break;
		  case 't':
			T = atof(optarg);
			break;
		  case 'i':
			niter = atoi(optarg);
			break;
		  case 'h':
			  fprintf (stderr, "-n lado de la red\n"
				"-t temperatura\n"
				"-i numero de iteraciones\n");
		  default:
			break;
      }

	int *lattice = (int *)malloc(n * n * sizeof(int));
	float prob = 0.5;
	srand(time(NULL));
	fill_lattice(lattice, n, prob);
	for (int i = 0; i < niter; i++) {
		metropolis(lattice, n, T);
	}
	print_lattice(lattice, n);
	return 0;
}
