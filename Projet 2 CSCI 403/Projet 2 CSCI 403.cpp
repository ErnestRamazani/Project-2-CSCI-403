

#include <iostream>
#include <thread>
#include <algorithm>
#include <cmath>
#include <chrono>
#include "matrix.h"

using namespace std;
const int THREADS_NUM = 14;
const int MAT_SIZE = 1028;

void mat_multiplication(double** A, double** B, double** C, int row, int size, double& sum); //need to figure out how to calculate matrix multiplication
void func1();

int main()
{

    auto start = chrono::steady_clock::now(); // start time
    int row, col, r = 0; //r is row counter for for loop 
    double ** mat_A, ** mat_B,**mat_C;
    double sum = 0, st_dev = 0,avg = 0; //sum 

    mat_A = read2d("a.mat", row, col); 
    mat_B = read2d("b.mat", row, col);
    mat_C = allocate2d(row, col);

    //DEBUG SORRY
   

    print2d("\nMatrix A ", mat_A, row, col); 	// printing matrices
    print2d("\nMatrix B ", mat_B, row, col);
   


   thread threads[THREADS_NUM];
   // for loop to create threads
    for (int i = 0; i < THREADS_NUM; i++) 
    {
        for (int j = r*(row/THREADS_NUM) ; j < min((r+1)*(row/THREADS_NUM),row);j++) 
        {
            threads[i] = thread(mat_multiplication,mat_A,mat_B,mat_C,r,row,ref(sum));
            threads[i].join(); // <<-- feels wrong to place this here, but will abort without
            r++; //row increment
        }  
    }  

    write2d("TEST", mat_C, row, col);
   print2d("\nMatrix C", mat_C, row, col);
    cout << "\n SUM: " << sum << endl;
    cout << "\n AVERAGE: " << avg << endl;
    cout << "\n STANDARD DEVIATION: " << st_dev << endl;


    free2d(mat_A); 			// deallocate the dynamic memory
    free2d(mat_B);
    free2d(mat_C);
    auto end = chrono::steady_clock::now(); //end time

    cout << "\n Elapsed time: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds";
    return 0;

}

//DUMMY FUNTION FOR TESTING
void func1() {
    for(int i = 0; i < 4; i++)
     cout << "++++" << endl;
}


void mat_multiplication(double ** A, double **B, double **C, int row, int size, double &sum ) {
    double temp = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
           // cout << temp << " = " << A[row - 1][i] << "*" << B[i][j] << "\n\n";
            temp += A[row][i] * B[i][j];
        }
      //  cout << "C[" << row << "][" << i << "] = " << temp << endl;
       C[row][i] = temp;
       sum += C[row][i];
    }
}
