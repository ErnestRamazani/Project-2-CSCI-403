

#include <iostream>
#include <thread>
//#include <pthread.h>
#include "matrix.h"

using namespace std;
const int THREADS_NUM = 20;
const int MAT_SIZE = 1028;

void* mat_multiplication();

int main()
{
    int row, col;
    double ** mat_A, ** mat_B,**mat_C;
    double sum; //sum 

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
      //for(int j = 0; j < )
        threads[i] = thread(mat_multiplication());

    }

    //joining threads
    free2d(mat_A); 			// deallocate the dynamic memory
    free2d(mat_B);
    
    return 0;

}

void* mat_multiplication() {

    

    
}
