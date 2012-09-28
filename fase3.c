
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

long pegapassos(int argc, char** argv) {
  if (argc < 2 || argc > 2) {
    printf("O programa recebe o número de passos. Adeus cara\n");
    exit(0);
  }
  return atol(argv[1]);
}

static long   STEP_NUM;
static long   THREAD_NUM;
static double STEP;

static double           pi = 0.0;
static pthread_mutex_t  mutex;

static void* worker_thread (void* arg) {
  long            chunk_size = STEP_NUM/THREAD_NUM,
                  id = (long)arg;
  register int    i;
  register double sum = 0.0, x;
  register double step = STEP;
  register int    begin = id*chunk_size,
                  end = begin+chunk_size+(id+1==THREAD_NUM)*(STEP_NUM%THREAD_NUM);
  for (i = begin; i < end; i++) {
    x = (i+0.5)*step;
    sum += 4.0/(1.0+x*x);
  }
  pthread_mutex_lock(&mutex);
  pi += sum*step;
  pthread_mutex_unlock(&mutex);
  pthread_exit(NULL);
}

int main (int argc, char** argv) {
  register long   i;
  pthread_t *threads;
  THREAD_NUM = sysconf(_SC_NPROCESSORS_ONLN);
  STEP_NUM = pegapassos(argc, argv);
  STEP = 1.0/(double)STEP_NUM;
  threads = (pthread_t*)malloc(THREAD_NUM*sizeof(*threads));
  pthread_mutex_init(&mutex, NULL);
  for (i = 0; i < THREAD_NUM; i++)
    pthread_create(&threads[i], NULL, worker_thread, (void*)i);
  for (i = 0; i < THREAD_NUM; i++)
    pthread_join(threads[i], NULL);
  free(threads);
  pthread_mutex_destroy(&mutex);
  printf("Pi = %.16g\n", pi);
  pthread_exit(NULL);
}

