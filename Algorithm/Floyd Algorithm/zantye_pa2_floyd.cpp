/*
 Program Name: zantye_pa2_floyd.cpp
 Author: Kunal Zantye
 Program Intent: Implement Floyd’s algorithm to find the shortest PrintPath for each pair of node in the  given Graph
 Input Data: Integers for standard input
 Output Data: 
 Compile Note: Use g++ to compile.
 */

/*---------------
 Include Section
 ----------------*/
#include <iostream>
#include <fstream>
#include <sstream> 
#include <stdlib.h>
#include <string>  
 /*--------------------
 Preprocessor Section
 ---------------------*/
using namespace std;
int size=0;

/*----------------------------  function ------------------------------------
 Name: allocate
 Purpose: Crates a Matrix
 Arguments:Size of the matrix to be created.
 Returns: Pointer to the matrix
 Calls: None
 ----------------------------------------------------------------------------*/

int** allocate(int n)
{
	int i;
	int **mat= new int*[n];
	for (i = 0; i < n; ++i)
		mat[i] = new int[n];
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
/*----------------------------  function ------------------------------------
 Name: FileOp
 Purpose: To read the matrix from a file
 Arguments: Filename
 Returns: Matrix readed from a file
 Calls: allocates
 ----------------------------------------------------------------------------*/
int** FileOp(char *filename)
{
	int i,j;
	
	string line;
   	ifstream in;
   	in.open (filename); 
  
  	if (!in.is_open())
  	{
      cout<<"Error opening file";
      exit(1);
  	}

	while(!in.eof()) 
	{
	  getline(in,line); 
	  size++;
	}
	
	//in.clear();
	//in.seekg(0);
	
	int **mat=allocate(size-1);
	int x=0;
	
	in.close();
	ifstream infile(filename);
    string str;  
	i=0;
	while (getline(infile, str) && i<size-1 )
    {
        istringstream ss(str);
        string token;
        j=0;
        while(getline(ss, token, ',') && j<size-1)
        {
            mat[i][j]=atoi(token.c_str());
            j++;
        }
        i++;
    }
    return mat;

}
/*----------------------------  function ------------------------------------
 Name: PrintPath
 Purpose: To print the PrintPath between two nodes
 Arguments: Path Matrix, starting node and end node
 Returns: None
 Calls: None
 ----------------------------------------------------------------------------*/
void PrintPath(int **P,int s,int e)
{

	int k=P[s][e];
	if (k==0)
	{
		return;
	}
	if (s!=e)
	{
		PrintPath(P,s,k);
		cout<<" "<<k<<"->";
		//PrintPath(P,k,e);
	}
}
/*----------------------------  function ------------------------------------
 Name: FloydAlgo
 Purpose: Algorith to implement Floyd
 Arguments: Input weight Matrix and size
 Returns: Path matrix
 Calls: None
 ----------------------------------------------------------------------------*/ 
int** FloydAlgo(int **mat,int n)
{
	int i,j,k;
	int **P=allocate(n);
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		P[i][j]=0;
	}
	for(k=0;k<n;k++)
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				if(mat[i][j]>(mat[i][k]+mat[k][j]))
				{
					mat[i][j]=mat[i][k]+mat[k][j]; 					
					P[i][j]=k+1;
				} 
	//DeleteMat(mat,n);
	return P;
} 
/*--------------------------- main function ----------------------------------
 Purpose: Start the program
 Arguments: None
 Returns: EXIT_SUCCESS
 Calls: allocates, GenMatrix, Mat Divide, MatMul, MatAdd, MatSub, PrintMat
 ----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
  	int n,i,j;
  	if ( argc != 2 ) 
    	cout<<"\nEnter File Name as Argument\n";
  	else {

	
		char *input=argv[1];
		int **W=FileOp(input);
		cout<<"\nInput Weight Matrix\n";
		PrintMat(W,size-1);
		
		int **P=FloydAlgo(W,size-1);
		cout<<"\nPath Matrix\n";
		PrintMat(P,size-1);
		
		for (i = 0; i < size-1; ++i)
		{
			for (j = 0; j < size-1; ++j)
			{
				cout<<"Path Between : "<<i+1<<" and "<<j+1<<": ";
				cout<<" "<<i+1<<"->";	
				PrintPath(P,i,j);
				cout<<" "<<j+1<<"\n";
				
			}
		}
	}
	
	return 0;
}	