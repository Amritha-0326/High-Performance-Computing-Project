/*GROUP 2: Amritha Preetha Anil, Ajay Soorya Madhav, Bryan Dunsheng See, Jiss Mariam Babu
TASK 6.1(a), 
This task is done by Jiss Mariam Babu*/
#include <stdio.h>
#include <stdlib.h>

#define SEED 350

//defining a structure of a matrix
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
	m1.data = (double*)malloc(m1.rows*m1.columns*sizeof(double)); //assigning data to heap
	
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
	
	printf("This is a matrix multiplication (sequential code)\n");
	printf("A=\n");
	for(rows=0;rows<m1.rows;rows++) {
		for(columns=0;columns<m1.columns;columns++) {
			*(m1.data+rows*m1.columns+columns) = (double)rand()/RAND_MAX ;
			printf("%2.15f  ", *(m1.data+rows*m1.columns+columns));
		}
		printf("\n");
	}
	
	printf("\n");
	printf("B=\n");
	for(rows=0;rows<m2.rows;rows++) {
		for(columns=0;columns<m2.columns;columns++) {
			*(m2.data+rows*m2.columns+columns) = (double)rand()/RAND_MAX ;
			printf("%2.15f  ", *(m2.data+rows*m2.columns+columns));
		}
		printf("\n");
	}
	
	//initializing the resultant matrix with value 0
	for(rows=0;rows<m3.rows;rows++) {
		for(columns=0;columns<m3.columns;columns++) {
			*(m3.data+rows*m3.columns+columns) = 0 ;
			}
	}
	
	int i;
	
	printf("\n");
	printf("AB=\n");
	for(rows=0;rows<m3.rows;rows++) {
		for(columns=0;columns<m3.columns;columns++) {
			for (i=0;i<m1.columns;i++){
				*(m3.data+rows*m3.columns+columns) += *(m1.data+i+rows*m1.columns) * *(m2.data+columns+i*m2.columns);
				}
				printf("%2.15f  ", *(m3.data+rows*m3.columns+columns));
			}
			printf("\n");
	}
	
	
	free(m1.data);
	free(m2.data);
	free(m3.data);
}
