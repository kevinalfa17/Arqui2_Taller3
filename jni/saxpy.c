/* Instituto Tecnologico de Costa Rica
 * Area academica de Ingenieria en Computadores
 * Curso de Arquitectura en Computadores II
 * Profesor: Jefferson Gonzales Gomez 
 * Taller 1: Saxpy Serial
 * Kevin Alfaro Vega - 2015027603
 * II Semestre 2018
 * Referencias: https://devblogs.nvidia.com/six-ways-saxpy/
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main ()
{
	float a = 2.0;
	int n = 1000000;
	float x[n]; 
	float y[n];
	int i;

	//full x and y vector
	for (i=0; i < n; i++){
		y[i] = rand();
		x[i] = rand();
	}


	double start_time, run_time;

	/*start timer */
	start_time = omp_get_wtime();

	for (i = 0; i < n; ++i){
		y[i] = a*x[i] + y[i];
	}


	run_time = omp_get_wtime() - start_time;

	printf("\n Execution time: %f seconds \n",run_time);
	
}	
