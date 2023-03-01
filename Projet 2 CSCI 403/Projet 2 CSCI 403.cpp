

#include <iostream>
#include <thread>
#include <algorithm>
#include <cmath>
#include <chrono>
#include "matrix.h"

using namespace std;
const int THREADS_NUM = 14; //THREAD COUNT

void mat_multiplication(double** A, double** B, double** C, int row, int size, double& sum, double& avg, double& stdev); //need to figure out how to calculate matrix multiplication

int main()
{
    auto start = chrono::steady_clock::now(); // start time
    int row, col, r = 0; //r is row counter for for loop 
    double ** mat_A, ** mat_B,**mat_C;
    double sum = 0, st_dev = 0,avg = 0; //sum 
    double average = 0;

    mat_A = read2d("a.mat", row, col); 
    mat_B = read2d("b.mat", row, col);
    mat_C = allocate2d(row, col);

    print2d("\nMatrix A ", mat_A, row, col); 	// printing matrices
    print2d("\nMatrix B ", mat_B, row, col);

   thread threads[THREADS_NUM];
   // for loop to create threads
    for (int i = 0; i < THREADS_NUM; i++) 
    {
        for (int j = r*(row/THREADS_NUM) ; j < min((r+1)*(row/THREADS_NUM),row);j++) 
        {
            threads[i] = thread(mat_multiplication, mat_A, mat_B, mat_C, r, row, ref(sum), ref(avg),ref(st_dev));
            threads[i].join(); // <<feels wrong to place this here, but will abort without
            r++; //row increment
        }  
    }  

    print2d("\nMatrix C", mat_C, row, col);
    cout << "\n SUM: " << sum << endl;
    cout << "\n AVERAGE: " << avg << endl;
    st_dev = sqrt(st_dev - pow(avg,2)); //standard deviation
    cout << "\n STANDARD DEVIATION: " << st_dev << endl;

    free2d(mat_A); 			// deallocate the dynamic memory
    free2d(mat_B);
    free2d(mat_C);

    auto end = chrono::steady_clock::now(); //end time

    cout << "\n Elapsed time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds";
    return 0;

}

void mat_multiplication(double ** A, double **B, double **C, int row, int size, double &sum, double &avg,double& stdev ) {
    double temp = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
           // cout << temp << " = " << A[row - 1][i] << "*" << B[i][j] << "\n\n";
            temp += A[row][i] * B[i][j];
        }
      //  cout << "C[" << row << "][" << i << "] = " << temp << endl;
       C[row][i] = temp;
       sum += C[row][i];
       avg += (C[row][i]) / (size * size);
       stdev += (pow(C[row][i], 2)) / (size*size);
    }
}
