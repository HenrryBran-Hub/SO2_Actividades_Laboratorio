#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  
#include <pthread.h>
#include <time.h>

// Estructura para pasar los argumentos a los hilos
typedef struct {
    long sum_total;
} ThreadArgs;

void* sum(void* args){
    ThreadArgs* thread_args = (ThreadArgs*)args;
    thread_args->sum_total = 0;
    for(int i = 0; i <= 100000; i++){
        thread_args->sum_total+=i;
    }
    return NULL;
}

int main(){

    struct timespec start, end;
    pthread_t thread;    

    // Capturar el tiempo de inicio
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Crear argumentos para los hilos
    ThreadArgs args = {0};

    pthread_create(&thread, NULL, sum, &args);

    printf("Esperando a hilo...\n");

    // Esperar a que los hilos terminen
    pthread_join(thread, NULL);

    printf("Hilo terminado!\n");

    // Capturar el tiempo de finalización
    clock_gettime(CLOCK_MONOTONIC, &end);

    /// Calcular la duración en microsegundos
    long duration;
    duration = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;

    printf("El hilo tardó %ld microsegundos en ejecutarse.\n", duration);

    // Sumar los resultados de ambos hilos
    long total_sum = args.sum_total;
    printf("Total de la suma: %ld\n", total_sum);

    return 0;
}