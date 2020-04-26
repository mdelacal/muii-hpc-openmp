/********************************************************
 * Autor: Miguel de la Cal Bravo
 * Asignatura: Computación de Altas Prestaciones (HCP)
 * Práctica OpenMP #1
 ********************************************************/

/* Bibliotecas */
#include <stdio.h>
#include <omp.h>

/* Función para el cálculo de la integral, con n iteraciones y t threads */
double pi(int n, int t); 

/* Función main */
int main()
{
    /* Variables */
    int sumas = 10000000; /* Realizamos 10 Millones de iteraciones (sumas) */
    float result; /* Resultado del cálculo de la integral */

    /* Reloj */
    double t_ini, t_fin;
    double secs;

    /* Realizamos el cálculo de la integral con entre 1-8 threads */
    for (int thr = 1; thr <= 8; thr++)
    {
        /* Iniciamos el reloj, para medir cuánto tardan en realizarse los cálculos */
        t_ini = omp_get_wtime();

        /* Realizamos los cálculos*/
        result = pi(sumas, thr);
        t_fin = omp_get_wtime();
        secs = t_fin - t_ini;
    
        /* Imprimos los resultados */
        printf("\nNº Threads: %d\tResultado final calculado: %1.15f\n", thr, result);
        printf("Tiempo de cómputo: %5.5f ms\n", secs * 1000.0);
    }
}

double pi(int n, int t)
{
    /* Variables para los cálculos de la integral */
    int i;
    double dx, sum, x;
    dx = 1.0 / n;
    
    /* Establecer numero de threads t en esta ejecución */
    omp_set_num_threads(t);

    /* Paralelización con OpenMP de un bucle for, aplicando reducción en la operación de suma 
       y variable privada x en los cálculos */
    #pragma omp parallel for private(x) reduction(+: sum)
        for (i = 0; i < n; i++){
            x = i * dx;
            sum += 1.0 / (1 + x * x);
        }
        sum *= 4.0 / n;
        
    return sum;
}