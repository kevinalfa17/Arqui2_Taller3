/* Instituto Tecnologico de Costa Rica
 * Area academica de Ingenieria en Computadores
 * Curso de Arquitectura en Computadores II
 * Profesor: Jeferson Gonzales Gomez 
 * Taller 3: Aplicacion paralela
 * Kevin Alfaro Vega - 2015027603
 * II Semestre 2018
 * Referencias: http://supercomputingblog.com/optimization/getting-started-with-sse-programming/
*/

#include <math.h>
#include <omp.h>
#include <stdio.h>



int main(){

	// Calculus of y = sqrt(x)/x, for x = 1->400000
	int n = 400000;
	float y[n];

	double start_time, run_time;

	/*start timer */
	start_time = omp_get_wtime();

	for (int x = 0; x < n; x++){
		y[x] = sqrt(x)/x;
	}

	run_time = omp_get_wtime() - start_time;

	printf("\n Execution time: %f seconds \n",run_time);

	return 0;
}

