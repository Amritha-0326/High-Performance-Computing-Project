/*GROUP 2: Amritha Preetha Anil, Ajay Soorya Madhav, Bryan Dunsheng See, Jiss Mariam Babu
TASK 6.2(a), 
This task is done by Bryan Dunsheng See*/

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

	int m=5;
	int n=10000;
	int p=1000;
	double duration = 0.0;

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
	
	for(rows=0;rows<m1.rows;rows++) {
		for(columns=0;columns<m1.columns;columns++) {
			*(m1.data+rows*m1.columns+columns) = (double)rand()/RAND_MAX ;
		}
	}
	
	for(rows=0;rows<m2.rows;rows++) {
		for(columns=0;columns<m2.columns;columns++) {
			*(m2.data+rows*m2.columns+columns) = (double)rand()/RAND_MAX ;
		}
	}
	
	int i;
	
	double sum=0;
	double start = omp_get_wtime();
	for(rows=0;rows<m3.rows;rows++) {
		for(columns=0;columns<m3.columns;columns++) {
			for (i=0;i<m1.columns;i++){
				*(m3.data+rows*m3.columns+columns) += *(m1.data+i+rows*m1.columns) * *(m2.data+columns+i*m2.columns);
				}
			}
	}
	double end = omp_get_wtime();
	printf("Time taken to execute in seconds: %.5f s\n", (end - start));
	
	
	free(m1.data);
	free(m2.data);
	free(m3.data);
}
