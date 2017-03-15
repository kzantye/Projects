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
#include<iostream>
#include <time.h>

 /*--------------------
 Preprocessor Section
 ---------------------*/
using namespace std;
int id=0;
int size=0;
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
		for (j= 0; j < n; ++j)
		{
			if (mat[i][j]==-1)
			{
				cout<<"X\t";
			}
			else
			cout<<mat[i][j]<<"\t";
		}
	}
	cout<<"\n";
}
/*----------------------------  function ------------------------------------
 Name: TrominoTile
 Purpose: Function used to implement Tromino tile Algorithm
 Arguments: Matrix to be printed  , Size of the Matrx, location of holes
 			(Lx,Ly) and Initail point(x,y)
 Returns: None
 Calls: None
 ----------------------------------------------------------------------------*/
void TrominoTile(int **tiles,int n,int x,int y,int Lx,int Ly)
{
	int half=n/2,i,j;
	int xcenter=x+half;
	int ycenter=y+half;

	id++;

	if(n==2)
	{
		if ( x == Lx )
		{
            if ( y == Ly )
               tiles[x][y+1] = tiles[x+1][y] = tiles[x + 1][y + 1] = id;	
            else
                tiles[x][y] = tiles[x + 1][y] = tiles[x + 1][y + 1] = id; 
		}
        else
        {
            if ( y== Ly )           
                tiles[x][y] = tiles[x][y + 1] = tiles[x + 1][y + 1] = id;	
            else
             	tiles[x][y] = tiles[x][y+1] = tiles[x+1][y] = id;
		}
	}
	else
	{	
		
		if (Lx<xcenter)
		{
			
			if (Ly<ycenter)
			{
				tiles[x + half-1][y + half] = tiles[x + half][y + half-1] = tiles[x + half][y + half] = id;	
				TrominoTile(tiles, half,x,y,Lx,Ly); 
				TrominoTile(tiles, half,x,y+half,half-1,y+half); 
				TrominoTile(tiles, half,x+half,y,x+half,half-1);	
    			TrominoTile(tiles, half,x+half,y+half,x+half,y+half);	
    			
			}
			else
			{
				tiles[x + half-1][y + half-1] = tiles[x + half][y + half-1] = tiles[x + half][y + half] = id;
				TrominoTile(tiles, half,x,y,half-1,half-1); 
				TrominoTile(tiles, half,x,y+half,Lx,Ly);
				TrominoTile(tiles, half,x+half,y,x+half,half-1);
    			TrominoTile(tiles, half,x+half,y+half,x+half,y+half);
			}
		}
		else
		{
			if (Ly<ycenter)
			{
				tiles[x + half-1][y + half-1] = tiles[x + half-1][y + half] = tiles[x + half][y + half] = id;	
				TrominoTile(tiles, half,x,y,half-1,half-1); 
				TrominoTile(tiles, half,x,y+half,half-1,y+half);
				TrominoTile(tiles, half,x+half,y,Lx,Ly); 
    			TrominoTile(tiles, half,x+half,y+half,x+half,y+half);	
			}
			else
			{
				tiles[x + half-1][y + half-1] = tiles[x + half-1][y + half]=tiles[x + half][y + half-1] = id; 					
				TrominoTile(tiles, half,x,y,half-1,half-1);
				TrominoTile(tiles, half,x,y+half,half-1,y+half);
				TrominoTile(tiles, half,x+half,y,x+half,half-1); 
    			TrominoTile(tiles, half,x+half,y+half,Lx,Ly);	
			}	
		}

	} 

}
/*--------------------------- main function ----------------------------------
 Purpose: Start the program
 Arguments: Args command line argument
 Returns: EXIT_SUCCESS
 Calls: allocates, TrominoTile, PrintMat
 ----------------------------------------------------------------------------*/

int main(int argc, char *argv[] )
{
  int n,i,j,x,y;
  if ( argc != 2 )
  	cout<<"Enter Size of Matrix\n";
  else 
  {

		n=atoi(argv[1]);
		if (n%2!=0)
		{
			cout<<"Improper size of Matrix (should be in 2^k)\n";
			exit(1);
		}
		else
		{
			srand(time(NULL));
			x=rand()%(n-1);
			y=rand()%(n-1);
			int **tile=allocate(n);
			for (i = 0; i < n; ++i)
			{
				for (int j = 0; j < n; j++)
				{
					tile[i][j]=0;
				}
			}
			tile[x-1][y-1]=-1;
			size=n;
			TrominoTile(tile,n,0,0,x-1,y-1);
			cout<<"\n=======================================\nAfter Tromino Tiling\n=======================================\n";
			PrintMat(tile,n);
		}
	}	
	return 0;
}