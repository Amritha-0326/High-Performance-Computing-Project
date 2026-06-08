/*GROUP 2: Amritha Preetha Anil, Ajay Soorya Madhav, Bryan Dunsheng See, Jiss Mariam Babu
TASK 6.1(b), 
This task is done by Jiss Mariam Babu*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define SEED 350


struct matrix
{
	int columns;
	int rows;
	double* data;
};


void main() {
	int m=10;
	int n=10;
	int p=10;



	struct matrix m1;
	m1.rows = n;
	m1.columns = m;
	m1.data = (double*)malloc(m1.rows*m1.columns*sizeof(double));
	
	struct matrix m2;
	m2.rows = m;
	m2.columns = p;
	m2.data = (double*)malloc(m2.rows*m2.columns*sizeof(double));
	
	struct matrix m3;
	m3.rows = n;
	m3.columns = p;
	m3.data = (double*)malloc(m3.rows*m3.columns*sizeof(double));
	
	srand(SEED);
	
	int rows, columns;
	int i;

	//setting the number of cores
	omp_set_num_threads(omp_get_max_threads());


	//we initialise the threads
	#pragma omp parallel 
	/*private(rows, columns) need not be specified because the matrices are assigned one after the other*/
{	
	#pragma omp for collapse (2)
	//we use collapse because we cannot nest the for statements
		for(rows=0;rows<m1.rows;rows++) {
			for(columns=0;columns<m1.columns;columns++) {
				*(m1.data+rows*m1.columns+columns) = (double)rand()/RAND_MAX ;
		}
	}
	#pragma omp for collapse (2)

		for(rows=0;rows<m2.rows;rows++) {
			for(columns=0;columns<m2.columns;columns++) {
				*(m2.data+rows*m2.columns+columns) = (double)rand()/RAND_MAX ;	
		}
	}
	#pragma omp for collapse (2)
	//we initialise the resultant matrix as well
		for(rows=0;rows<m3.rows;rows++) {
	
			for(columns=0;columns<m3.columns;columns++) {
				*(m3.data+rows*m3.columns+columns) = 0;
			
		}
		
	}
	#pragma omp for collapse (3) 

		for(rows=0;rows<m3.rows;rows++) {
			for(columns=0;columns<m3.columns;columns++) {
				for (i=0;i<m1.columns;i++){
					*(m3.data+rows*m3.columns+columns) += *(m1.data+i+rows*m1.columns) * *(m2.data+columns+i*m2.columns);
			}
		}
	}
}
	

	printf("Threads in main:%d\n",omp_get_num_threads());
	
// to print out the matrices 
/*-- we cannot print out the matrices while assigning values as they are assigned parallel-ly */

	//we set threads to sections
	#pragma omp parallel
	{
	#pragma omp sections
	{
	#pragma omp section
	//we do this to print out the number of threads
	//we cannot however, guarantee the order that the lines are printed
		printf("Number of threads (threads in parallel region): %d\n", omp_get_num_threads());
	#pragma omp section
		printf("This is a matrix multiplication (parallel code)\n");
	}
	#pragma omp single
	//we print out entire matrices one after another with a single thread
		{
		printf("\n");
		printf("A=\n");
		for (rows=0; rows < m1.rows; rows++){
			for (columns=0; columns< m1.columns; columns++){
				printf("%2.15f\t", *(m1.data+rows*m1.columns+columns));
				}
			printf("\n"); 
		}
		printf("\n"); 
		

		{
		printf("\n");
		printf("B=\n");
		for (rows=0; rows < m2.rows; rows++){
			for (columns=0; columns< m2.columns; columns++){
				printf("%2.15f\t", *(m2.data+rows*m2.columns+columns));
				}
			printf("\n"); 
			}
		printf("\n"); 
		}
			
		printf("\n");
		printf("AB=\n");
		for (rows=0; rows < m3.rows; rows++){
			for (columns=0; columns< m3.columns; columns++){
				printf("%2.15f\t", *(m3.data+rows*m3.columns+columns));
				}
			printf("\n");
		}
		printf("\n"); 
		}
	}
	free(m1.data);
	free(m2.data);
	free(m3.data);
}
