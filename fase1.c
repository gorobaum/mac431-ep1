#include <stdio.h>

static long num_steps = 1000000;

void main () {
  int i; 
  double x, pi, sum = 0.0;
  const double step = 1.0/(double) num_steps;;
  
  #pragma omp parallel private(i, sum) shared(pi)
  {
    for (i = 0; i < num_steps; i++){
      x = (i+0.5)*step;
      sum = sum + 4.0/(1.0+x*x);
    }
    pi = step * sum;    
  }
  printf("Pi = %g\n", pi);
}
