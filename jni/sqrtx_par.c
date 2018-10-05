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
#include <arm_neon.h>


int main(){

	// Calculus of y = sqrt(x)/x, for x = 1->400000
	int n = 400000;
	float32_t x[n] __attribute__((aligned(32)));
	float32_t y[n] __attribute__((aligned(32)));

	//full x and y vector
	for (int i=0; i < n; i++){
		x[i] = i;
	}

	float32x4_t neon_x;
	float32x4_t neon_y;

	double start_time, run_time;

	/*start timer */
	start_time = omp_get_wtime();

	//Pointer vectors to load data in loop
	float32_t * vec_x = x;
	float32_t * vec_y = y;

	for (int x = 0; x < n; x++){

		//load 4 values in parallel from the array
        neon_x = vld1q_f32(vec_x);
        neon_y = vld1q_f32(vec_y);

        //increment the array pointer to the next element
        vec_x+=4;
        vec_y+=4;

        neon_y = vrsqrteq_f32(neon_x);//sqrt(y)
        neon_x = vrecpeq_f32(neon_x);//x = 1/x
        neon_y = vmulq_f32(neon_x,neon_y);//sqrt(y)/x
	}

	run_time = omp_get_wtime() - start_time;

	printf("\n Execution time: %f seconds \n",run_time);

	return 0;
}

