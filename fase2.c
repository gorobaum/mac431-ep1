#include <stdio.h>
#include <stdlib.h>

long trataarg(int argc, char** argv) {
  if (argc < 2 || argc > 2) {
    printf("O programa recebe o número de passos. Adeus cara\n");
    exit(0);
  }
  return atol(argv[1]);
}

void main (int argc, char** argv) {
  int i; 
  double x, pi;
  double step;
  long num_steps = trataarg(argc, argv);
  step = 1.0/(double) num_steps;

  #pragma omp parallel for reduction(+:pi)
  for (i = 0; i < num_steps; i++){
    x = (i+0.5)*step;
    pi = pi + 4.0/(1.0+x*x);
  }
  pi *= step;
  printf("Pi = %g\n", pi);
}
