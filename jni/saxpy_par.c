/* Instituto Tecnologico de Costa Rica
 * Area academica de Ingenieria en Computadores
 * Curso de Arquitectura en Computadores II
 * Profesor: Jeferson Gonzales Gomez 
 * Taller 3: Saxpy Paralelo
 * Kevin Alfaro Vega - 2015027603
 * II Semestre 2018
 * Referencias: https://devblogs.nvidia.com/six-ways-saxpy/
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
 #include <arm_neon.h>

int main ()
{
	
	int n = 400000;

	float32_t x[n] __attribute__((aligned(32)));
	float32_t y[n] __attribute__((aligned(32)));
	

	//full x and y vector
	for (int i=0; i < n; i++){
		y[i] = rand();
		x[i] = rand();
	}


	float32x4_t a =  vdupq_n_f32(2.0);
	float32x4_t neon_x;
	float32x4_t neon_y;

	double start_time, run_time;

	//Number of threads to use
	int nprocs=2*omp_get_num_procs();
	omp_set_num_threads(nprocs);

	//start timer
	start_time = omp_get_wtime();

	//Pointer vectors to load data in loop
	float32_t * vec_x = x;
	float32_t * vec_y = y;

	#pragma omp parallel for
	for (int i = 0; i < n; i += 4){



		//load 4 values in parallel from the array
        neon_x = vld1q_f32(vec_x);
        neon_y = vld1q_f32(vec_y);

        //increment the array pointer to the next element
        vec_x+=4;
        vec_y+=4;

 		neon_y = vmlaq_f32(neon_y, a, neon_x); // y[i] = y[i] + a*x[i];
	}

	float32_t result = vgetq_lane_f32(neon_y, 0); 


	run_time = omp_get_wtime() - start_time;

	printf("\n Execution time: %f seconds \n",run_time);
	
}	
