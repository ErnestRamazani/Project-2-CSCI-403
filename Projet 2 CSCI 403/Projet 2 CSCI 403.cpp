/*
*  CURRENT PROBLEMS
*  MULTITHREADING IS SKIPPING ROWS
*  MATRIX CALCULATED IS NOT CONSISTENT
*  CANNOT CREATE DATA IN PARALLEL
* 
*/
#include <iostream>
#include <thread>
#include <cmath>
#include <chrono>
#include <fstream>
#include "matrix.h"

using namespace std;
const int THREADS_NUM = 10; //THREAD COUNT

void mat_multiplication(double** A, double** B, double** C, int row, int size, double& sum, double& avg, double& stdev); 
int main()
{
    auto start = chrono::steady_clock::now(); // start time
    int row, col, r = 0; // r is current row in loop 
    double ** mat_A, ** mat_B,**mat_C; //matrices
    double sum = 0, st_dev = 0,avg = 0; // data variables
    double sum_ar[THREADS_NUM], st_dev_ar[THREADS_NUM], avg_ar[THREADS_NUM]; //arrays, index for each thread to add together after all threads are finished
    thread threads[THREADS_NUM];

    //initializing arrays
    for (int i = 0; i < THREADS_NUM; i++) {
        sum_ar[i] = 0;
        st_dev_ar[i] = 0;
        avg_ar[0] = 0;
    }
    
    //lambda for threads to run
    auto lambda = [](int& r, int row, double** mat_A, double** mat_B, double** mat_C, int thread, double* sum_ar, double* avg_ar, double* st_dev_ar) {

        double sum = 0, st_dev = 0, avg = 0;

        for (int j = r * (row / THREADS_NUM); j < (min((r + 1) * (row / THREADS_NUM), row)) - 1; j++) {

            mat_multiplication(mat_A, mat_B, mat_C, r, row, ref(sum), ref(avg), ref(st_dev));
            if (r < row - 1) {
                r++;
            }
        }
        cout << "THREAD " << thread << " DONE!!" << endl;
    };

    //READING AND CREATING MATRICES
    mat_A = read2d("a.mat", row, col); 
    mat_B = read2d("b.mat", row, col);
    mat_C = allocate2d(row, col);

    print2d("\nMatrix A ", mat_A, row, col); 	// printing matrices
    print2d("\nMatrix B ", mat_B, row, col);

   // for loop to create threads
    for (int i = 0; i < THREADS_NUM; i++) 
    {
        // OLD THREADING ALGORITHM, ran threads sequentially, not parallel

        /*for (int j = r * (row / THREADS_NUM); j < min((r + 1) * (row / THREADS_NUM), row); j++)
        {
            threads[i] = thread(mat_multiplication, mat_A, mat_B, mat_C, r, row, ref(sum), ref(avg),ref(st_dev));
            threads[i].join();// <<feels wrong to place this here, but will abort without
            r++; //row increment
        }  
        

         r = current row
         row = row size
        */
        
        threads[i] = thread(lambda, ref(r), row, mat_A, mat_B, mat_C,i,sum_ar, avg_ar,st_dev_ar);
    }  
    for (int i = 0; i < THREADS_NUM; i++) { //JOINING THREADS
        threads[i].join();
    }

    //ADDING SUMS FROM EACH THREAD TOGETHER
    for (int i = 0; i < THREADS_NUM; i++) {
        sum += sum_ar[i];
        avg += avg_ar[i];
        st_dev += st_dev_ar[i];
    }

    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    // PRINTING

    print2d("\nMatrix C", mat_C, row, col);
    cout << "\n SUM: " << sum << endl;
    cout << "\n AVERAGE: " << avg << endl;
    st_dev = sqrt(st_dev - pow(avg,2)); //standard deviation
    cout << "\n STANDARD DEVIATION: " << st_dev << endl ;
    
    // deallocate the dynamic memory <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    free2d(mat_A); 			
    free2d(mat_B);
    free2d(mat_C);

    auto end = chrono::steady_clock::now(); //end time
    cout << "\n Elapsed time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds";
    return 0;

}

void mat_multiplication(double ** A, double **B, double **C, int row, int size, double &rowsum, double &avg,double& stdev ) {
    
    for (int i = 0; i < size; i++) {
        double temp = 0;
        for (int j = 0; j < size; j++) {
            temp += A[row][j] * B[j][i];
        } 
       C[row][i] = temp;
       //rowsum += C[row][i];
       //avg += (C[row][i]) / (size * size);
       //stdev += (pow(C[row][i], 2)) / (size*size);
    }
 
}
