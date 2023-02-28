

#include <iostream>
#include <thread>
#include <algorithm>
//#include <pthread.h>
#include "matrix.h"

using namespace std;
const int THREADS_NUM = 20;
const int MAT_SIZE = 1028;

void* mat_multiplication(); //need to figure out how to calculate matrix multiplication

int main()
{
    int row, col, r = 0; //r is row counter for for loop 
    double ** mat_A, ** mat_B,**mat_C;
    double sum, st_dev,avg; //sum 

    mat_A = read2d("a.mat", row, col); 
    mat_B = read2d("b.mat", row, col);

    print2d("\nMatrix A ", mat_A, row, col); 	// printing matrices
    print2d("\nMatrix B ", mat_B, row, col);
    //multiplying matrices 

   thread threads[THREADS_NUM];
   // for loop to create threads
   // need to figure out how to divide threads and multiply matrix

    for (int i = 0; i < THREADS_NUM; i++) 
    {
        for (int j = r*(row/THREADS_NUM) ; j < min((r+1)*(row/THREADS_NUM),row);j++) 
        {
            threads[i] = thread(mat_multiplication());
            r++; //row increment

            //add parallel calculations of avg, standard dev, etc. 
        }  
    }

    //joining threads
    free2d(mat_A); 			// deallocate the dynamic memory
    free2d(mat_B);
    
    return 0;

}

void* mat_multiplication(double ** A, double **B, double **C, int row, int size, double &stdev, double &sum ) {
    double temp;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            C[][] += A[row][i] * B[i][j];
            
        }
    }
    

}
