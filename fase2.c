#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

unsigned pegapassos(int argc, char** argv) {
  if (argc < 2 || argc > 2) {
    printf("O programa recebe o número de passos.\n");
    exit(0);
  }
  return strtoul(argv[1], NULL, 10);
}

int main (int argc, char** argv) {
  register unsigned i;
  register double   pi = 0.0,
                    x;
  unsigned          num_steps = pegapassos(argc, argv);
  double            step = 1.0/(double) num_steps;
  #pragma omp parallel for reduction(+:pi) private(x) firstprivate(step,num_steps)
  for (i = 0; i < num_steps; i++) {
    x = (i+0.5)*step;
    pi += 4.0/(1.0+x*x);
  }
  pi *= step;
  printf("Pi = %.16g\n", pi);
  return 0;
}
