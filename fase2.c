#include <stdio.h>
#include <stdlib.h>

long pegapassos(int argc, char** argv) {
  if (argc < 2 || argc > 2) {
    printf("O programa recebe o número de passos. Adeus cara\n");
    exit(0);
  }
  return atol(argv[1]);
}

void main (int argc, char** argv) {
  double x, pi, i;
  double step;  
  long num_steps = pegapassos(argc, argv);
  step = 1.0/(double) num_steps;

  #pragma omp parallel for reduction(+:pi) private(x, step)
  for (i = 0.5; i < num_steps; i++) {
    pi += 4.0/(1.0+(i*step)*(i*step));
  }
  pi *= step;
  printf("Pi = %.16g\n", pi);
}
