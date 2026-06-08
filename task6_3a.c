/*GROUP 2: Amritha Preetha Anil, Ajay Soorya Madhav, Bryan Dunsheng See, Jiss Mariam Babu
TASK 6.3(a), 
This task is done by Amritha Preetha Anil*/

#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

#define ROW1 5
#define COL1 4
#define ROW2 4
#define COL2 6
#define ROW3 6
#define COL3 4

struct matrix {									
    int rows;									
    int cols;									
    double *data;								
};										

 int main()
{
    struct matrix A, B, C, X, Y;
    int i, j, k;
    double sum = 0;

    A.rows = ROW1;
    A.cols = COL1;
    B.rows = ROW2;
    B.cols = COL2;
    C.rows = ROW3;
    C.cols = COL3;

    srand(1200);

    printf("\nThe number of rows of matrix A is: %d\t",A.rows);    
    printf("\nThe number of columns of matrix A is: %d\t",A.cols);    
    printf("\nThe number of rows of matrix B is: %d\t",B.rows);    
    printf("\nThe number of columns of matrix B is: %d\t",B.cols);    
    printf("\nThe number of rows of matrix C is: %d\t",C.rows);    
    printf("\nThe number of columns of matrix c is: %d\t",C.cols);
    
    C.data = (double*) malloc(sizeof(double)*C.rows*C.cols);   //dynamically allocating memory on heap			
    X.data = (double*) malloc(sizeof(double)*A.rows*C.cols);			
    A.data = (double*) malloc(sizeof(double)*A.rows*A.cols);			
    B.data = (double*) malloc(sizeof(double)*B.rows*B.cols);			
    Y.data = (double*) malloc(sizeof(double)*A.rows*B.cols);			
    
    
    
        for(i = 0; i < A.rows; i++)						
	        for(j = 0; j < A.cols; j++)					
        	    (*(A.data + i*A.cols + j)) = (double)rand() / RAND_MAX;	  //assigning random numbers between [0,1]
        
    
    	printf("\n\nThe matrix A is\n");

	for(i = 0; i < A.rows; i++)
    	{
		for(j = 0; j < A.cols; j++)
        	{	printf("%lf ",*(A.data + i*A.cols +j));
            }
		printf("\n");
    	}

	for(i = 0; i < B.rows; i++)						
		for(j = 0; j < B.cols; j++)					
	        	(*(B.data+i*B.cols+j))= (double)rand()/RAND_MAX;	    //assigning random numbers between [0,1]	
        
    
	printf("\n\nThe matrix B is:\n");

	for(i = 0; i < B.rows; i++)
    	{
		for(j = 0; j < B.cols; j++)
        	{	printf("%lf ",*(B.data + i*B.cols + j));
            }
        	printf("\n");
    	}

	double t1=omp_get_wtime();	                            // getting time before A*B						

	for(i = 0; i < A.rows; i++)						
    		for(j = 0; j < B.cols; j++)					
		{								//
        		for(k=0;k<A.cols;k++)					
			{							
		            sum+=(*(A.data+i*A.cols+k))*(*(B.data+k*B.cols+j));  //Multiplying and adding respective elements
                	    *(Y.data+i*B.cols+j) = sum;				          // assigning value to resultant matrix Y
       		}							
        		sum = 0;						
    		}								

    	double t2=omp_get_wtime();							                  // getting time after A*B

	printf("\nThe matrix multiplication A*B is:\n");

	for(i = 0; i < A.rows; i++)
    	{
        	for(j = 0; j < B.cols; j++)
        	{	printf("%lf ",*(Y.data+i*B.cols+j));
            }
        	printf("\n");
    	}

	printf("\nThe order of matrix C should be 4*6(columns*rows) so that the resultant matrix X will have the order 4*5 (columns*rows).\n");
    


    for(i = 0; i < C.rows; i++)							
	    for(j = 0; j < C.cols; j++)						
        	   (*(C.data + i*C.cols + j)) = (double)rand() / RAND_MAX;    //assigning random numbers between [0,1]	
         
    printf("\n\nThe matrix C is\n");

    for(i = 0; i < C.rows; i++)
    {
	for(j = 0; j < C.cols; j++)
	         {   printf("%lf  ", *(C.data + i*C.cols + j));
             }
     	printf("\n");
    }

    double t3 = omp_get_wtime();					                     // getting time before (A*B)*C		

    for(i=0;i<A.rows;i++)							
    	for(j=0;j<C.cols;j++)							
	{									
        	for(k=0;k<B.cols;k++)						
            {	sum+=(*(Y.data+i*B.cols+k))*(*(C.data+k*C.cols+j));  //Multiplying and adding respective elements	
		        *(X.data+i*C.cols+j)=sum;				                // assigning value to resultant matrix X
        	}								
        	sum=0;								
    }									
    
    double t4 = omp_get_wtime();							                // getting time after (A*B)*C
    
    printf("\nThe matrix multiplication is X = (A * B) * C:\n");

    for(i = 0; i < A.rows; i++)
    {
        for(j=0;j<C.cols;j++)
            printf("%lf  ",*(X.data+i*C.cols+j));
        
        printf("\n");
    }
    
    free(A.data);								
    free(B.data);								
    free(Y.data);								
    free(C.data);								                        //free heap memory after use
    free(X.data);								

    printf("\nThe time taken for multiplication A*B is =%f seconds",t2-t1);
    printf("\nThe time taken for multiplication of (A*B)*C is =%f seconds",t4-t3);
    printf("\nThe total time taken for multiplications is =%f seconds",t4-t3+t2-t1);
    printf("\n");
    return 0;
}

