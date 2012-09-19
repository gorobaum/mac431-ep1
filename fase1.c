#include <stdio.h>

static long num_steps = 1000000;
double step;

void main () {
  int i; 
  double x, pi;
  step = 1.0/(double) num_steps;

  #pragma omp parallel for reduction(+:pi)
  for (i = 0; i < num_steps; i++){
    x = (i+0.5)*step;
    pi = pi + 4.0/(1.0+x*x);
  }
  pi *= step;
  printf("Pi = %g\n", pi);
}
