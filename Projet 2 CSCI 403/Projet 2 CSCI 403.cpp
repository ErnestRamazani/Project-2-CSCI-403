

#include <iostream>
#include <thread>
#include <algorithm>
//#include <pthread.h>
#include "matrix.h"

using namespace std;
const int THREADS_NUM = 4;
const int MAT_SIZE = 1028;

void mat_multiplication(double** A, double** B, double** C, int row, int size, double& sum); //need to figure out how to calculate matrix multiplication
void func1();

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
            threads[i] = thread(func1);
            r++; //row increment
            //add parallel calculations of avg, standard dev, etc. 
        }  
    }


    //joining threads
    for (int i = 0; i < THREADS_NUM; i++) {
        threads[i].join();
    }

    //print2d("\nMatrix C", mat_C, row, col);

    free2d(mat_A); 			// deallocate the dynamic memory
    free2d(mat_B);
  //  free2d(mat_C);
    return 0;

}


void func1() {
    cout << "++++" << endl;
}


void mat_multiplication(double ** A, double **B, double **C, int row, int size, double &sum ) {

    for (int i = 0; i < size; i++) { 
        for (int j = 0; j < size; j++) {
            C[row][i] += A[row][i] * B[i][j];
         }
        sum += C[row][i];
    }
}
