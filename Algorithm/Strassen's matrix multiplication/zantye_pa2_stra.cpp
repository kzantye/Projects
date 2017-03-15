/*
 Program Name: zantye_pa2_stra.cpp
 Author: Kunal Zantye
 Program Intent: Implement Strassen’s matrix multiplication algorithm
 Input Data: Integers for standard input
 Output Data: Prints Multiplied Matrix using Strassen's algorith
 Compile Note: Use g++ to compile.
 */

/*---------------
 Include Section
 ----------------*/
#include <iostream>
#include <ctime>
#include <time.h> 
#include <stdlib.h>

 /*--------------------
 Preprocessor Section
 ---------------------*/

using namespace std;
/*----------------------------  function ------------------------------------
 Name: allocate
 Purpose: Crates a Matrix
 Arguments:Size of the matrix to be created.
 Returns: Pointer to the matrix
 Calls: None
 ----------------------------------------------------------------------------*/
int** allocate(int size)
{
	int i;
	int **mat= new int*[size];
	for (i = 0; i < size; ++i)
		mat[i] = new int[size];
	return mat;
}
/*----------------------------  function ------------------------------------
 Name: DeleteMat
 Purpose: Deletes the space allocated to the Matrix
 Arguments:Matrix to be deleted , Size of the Matrix
 Returns: None
 Calls: None
 ----------------------------------------------------------------------------*/
void DeleteMat(int **mat,int size)
{
	for(int i = 0; i < size; ++i) 
	delete [] mat[i];
	delete [] mat;
}
/*----------------------------  function ------------------------------------
 Name: MatMul
 Purpose: Function to perform standard matrix multiplication
 Arguments:Two Matrix A & B  , Size of the Matrix
 Returns: Returns multiplied matrix
 Calls: allocate, DeleteMat
 ----------------------------------------------------------------------------*/

int** MatMul(int **matA, int **matB,int n)
{
	int i,j,k,sum=0;
	int **result=allocate(n);
	for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
        for (k = 0; k < n; k++) {
          sum = sum + matA[i][k]*matB[k][j];
        }
        result[i][j] = sum;
        sum = 0;
      }
    }
    return result;
    DeleteMat(result,n);

}
/*----------------------------  function ------------------------------------
 Name: MatAdd
 Purpose: Function to perform standard matrix addition
 Arguments:Two Matrix A & B  , Size of the Matrix
 Returns: Returns result of matrix adition.
 Calls: allocate, DeleteMat
 ----------------------------------------------------------------------------*/

int** MatAdd(int **matA, int **matB,int n)
{
	int i,j;
	int **result=allocate(n);
	for (i= 0; i < n; i++) {
      for (j= 0 ; j< n; j++) {
         result[i][j] = matA[i][j] + matB[i][j];
     }
      }
      return result;
      DeleteMat(result,n);
}
/*----------------------------  function ------------------------------------
 Name: MatSub
 Purpose: Function to perform standard matrix Substraction
 Arguments:Two Matrix A & B  , Size of the Matrix
 Returns: Returns result of matrix substraction
 Calls: allocate, DeleteMat
 ----------------------------------------------------------------------------*/

int** MatSub(int **matA, int **matB,int n)
{
	int i,j;
	int **result=allocate(n);
	for (i= 0; i < n; i++) {
      for (j= 0 ; j< n; j++) {
         result[i][j] = matA[i][j] - matB[i][j];
     }
      }
      return result;
      DeleteMat(result,n);
}
/*----------------------------  function ------------------------------------
 Name: MatDivide
 Purpose: Divides the input matrix into size of n/2xn/2
 Arguments:Matrix to be divided  , Size of the Matrix
 Returns: Returns matrix of size n/2xn/2
 Calls: allocate, DeleteMat
 ----------------------------------------------------------------------------*/
int** MatDivide(int **mat,int startr,int endr,int startc,int endc)
{
	int i,j,m=0,n=0;
	int size=endr-startr;
	int **result=allocate(size);
	for (i= startr,m=0; i < endr & m<size; i++,m++) {
      for (j= startc,n=0 ; j< endc && n<size; j++,n++) {
         result[m][n] = mat[i][j];
     }
     
      }
      return result;
      DeleteMat(result,size);
}
/*----------------------------  function ------------------------------------
 Name: MatMerge
 Purpose: Merges the input matrix of size n/2xn/2 to nxn
 Arguments:Four matrix to be merged , Size of the Matrix
 Returns: Returns matrix of size nxn
 Calls: allocate
 ----------------------------------------------------------------------------*/
int** MatMerge(int **C1,int **C2,int **C3,int **C4,int n)
{
	int i,j;
	int size=2*n;
	int **result=allocate(size);
	for (i = 0; i < n; i++)
	{
		for (int j= 0; j< n; j++)
		{
			result[i][j]=C1[i][j];
			result[i][j+n]=C2[i][j];
			result[i+n][j]=C3[i][j];
			result[i+n][j+n]=C4[i][j];
		}
		
	}
	return result;

}
/*----------------------------  function ------------------------------------
 Name: GenMatrix
 Purpose: Function used to Generate rand the matrix
 Arguments:Two matrix A & B  , Size of the Matrix
 Returns: None
 Calls: None
 ----------------------------------------------------------------------------*/
void GenMatrix(int **matA,int **matB,int n)
{
	int i,j;
	//int **mat=allocate(n);
	srand (time(NULL));
	for (i = 0; i < n; ++i)
	{
		for (int j= 0; j < n; ++j)
		{
			//random generator between the range (-10)- 10
			matA[i][j]=rand() % (21) + (-10); 
			matB[i][j]=rand() % (21) + (-10); 
		}
	}

}
/*----------------------------  function ------------------------------------
 Name: PrintMatrix
 Purpose: Function used to print the matrix
 Arguments: Matrix to be printed  , Size of the Matrix
 Returns: None
 Calls: None
 ----------------------------------------------------------------------------*/
void PrintMat(int **mat,int n)
{
	int i,j;
	for (i = 0; i < n; ++i)
	{
		cout<<"\n";
		for (int j= 0; j < n; ++j)
		{
			cout<<mat[i][j]<<"\t";
		}
	}
	cout<<"\n";
}

/*--------------------------- main function ----------------------------------
 Purpose: Start the program
 Arguments: None
 Returns: EXIT_SUCCESS
 Calls: allocates, GenMatrix, Mat Divide, MatMul, MatAdd, MatSub, PrintMat
 ----------------------------------------------------------------------------*/
int main(int argc, char *argv[] )
{
  int n,i,j;
  if ( argc != 2 ) 

    cout<<"Enter Size of Matrix\n";
  else {

	n=atoi(argv[1]);
	if (n%2!=0)
	{
		cout<<"Improper size of Matrix (should be in 2^k)\n";
		exit(1);
	}
	else
	{
	int **matA=allocate(n);
	int **matB=allocate(n);


	//GenMatrix(matA,n);
	
	GenMatrix(matA,matB,n);
	cout<<"\nMatrix A\n";
	PrintMat(matA,n);

	cout<<"\nMatrix B\n";
	PrintMat(matB,n);

	
	int **A11=MatDivide(matA,0,n/2,0,n/2);
	int **A12=MatDivide(matA,0,n/2,n/2,n);
	int **A21=MatDivide(matA,n/2,n,0,n/2);
	int **A22=MatDivide(matA,n/2,n,n/2,n);
	
	int **B11=MatDivide(matB,0,n/2,0,n/2);
	int **B12=MatDivide(matB,0,n/2,n/2,n);
	int **B21=MatDivide(matB,n/2,n,0,n/2);
	int **B22=MatDivide(matB,n/2,n,n/2,n);


	int **M1=MatMul(MatAdd(A11,A22,n/2),MatAdd(B11,B22,n/2),n/2);
	int **M2=MatMul(MatAdd(A21,A22,n/2),B11,n/2);
	int **M3=MatMul(A11,MatSub(B12,B22,n/2),n/2);
	int **M4=MatMul(A22,MatSub(B21,B11,n/2),n/2);
	int **M5=MatMul(MatAdd(A11,A12,n/2),B22,n/2);
	int **M6=MatMul(MatSub(A21,A11,n/2),MatAdd(B11,B12,n/2),n/2);
	int **M7=MatMul(MatSub(A12,A22,n/2),MatAdd(B21,B22,n/2),n/2);

	int **C1=MatAdd(MatSub(MatAdd(M1,M4,n/2),M5,n/2),M7,n/2);
	int **C2=MatAdd(M3,M5,n/2);
	int **C3=MatAdd(M2,M4,n/2);
	int **C4=MatAdd(MatSub(MatAdd(M1,M3,n/2),M2,n/2),M6,n/2);

	
	cout<<"\nStandard Multiplication\n";
	PrintMat(MatMul(matA,matB,n),n);
	cout<<"\nStrassen Multiplication\n";
	PrintMat(MatMerge(C1,C2,C3,C4,n/2),n);
	}
	}
	
	return 0;
}