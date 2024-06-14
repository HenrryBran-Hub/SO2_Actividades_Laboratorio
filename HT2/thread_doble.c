#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  
#include <pthread.h>
#include <time.h>

// Estructura para pasar los argumentos a los hilos
typedef struct {
    long start;
    long end;
    long sum_total;
} ThreadArgs;

void* sum(void* args){
    ThreadArgs* thread_args = (ThreadArgs*)args;
    thread_args->sum_total = 0;
    for(long i = thread_args->start; i <= thread_args->end; i++){
        thread_args->sum_total += i;
    }
    return NULL;
}

int main(){

    struct timespec start, end;  
    pthread_t thread1, thread2;      

    // Capturar el tiempo de inicio
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Crear argumentos para los hilos
    ThreadArgs args1 = {0, 50000, 0};
    ThreadArgs args2 = {50001, 100000, 0};

    // Crear hilos
    pthread_create(&thread1, NULL, sum, &args1);
    pthread_create(&thread2, NULL, sum, &args2);

    printf("Esperando a hilos...\n");

    // Esperar a que los hilos terminen
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Hilos terminados!\n");

    // Capturar el tiempo de finalización
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calcular la duración en microsegundos
    long duration;
    duration = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
    printf("Los hilos tardaron %ld microsegundos en ejecutarse.\n", duration);

    // Sumar los resultados de ambos hilos
    long total_sum = args1.sum_total + args2.sum_total;
    printf("Total de la suma: %ld\n", total_sum);

    return 0;
}
