/*
 Program Name: prim.cpp
 Author: Kunal Zantye
 Program Intent: Implement Prim’s algorithm to find the minimum spaning tree in the  given Graph
 Input Data: Input File
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
struct Graph
{
	int src, dest, weight;
};
struct MST
{
	int cost;
	int prev;
	int index;
};
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
	int i;
	for(i = 0; i < size; ++i) 
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
		for (j= 0; j < n; ++j)
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
	
	int **mat=allocate(size);
	int x=0;
	
	in.close();
	ifstream infile(filename);
    string str;  
	i=0;
	while (getline(infile, str) && i<size)
    {
        istringstream ss(str);
        string token;
        j=0;
        while(getline(ss, token, ',') && j<size)
        {
            mat[i][j]=atoi(token.c_str());
            j++;
        }
        i++;
    }
    return mat;

}
/*----------------------------  function ------------------------------------
 Name: MakeQueue
 Purpose: Makes Priority Queue
 Arguments:Priority Queue, queue size, Input Queue
 Returns: void
 Calls: None
 ----------------------------------------------------------------------------*/

void MakeQueue(struct MST queue[], int n, struct MST value)
{
    queue[n] = value;
    int i = n;
    struct MST temp;
    while (i >= 1) {
        if (queue[i / 2].cost > queue[i].cost) {
            temp = queue[i / 2];
            queue[i / 2] = queue[i];
            queue[i] = temp;  
            i = i / 2;
        } 
        else 
            break;
    }
    
}

/*----------------------------  function ------------------------------------
 Name: ExtractMin
 Purpose: Get the vertex with minimum cost
 Arguments:Priority Queue, queue size
 Returns: Structure of Minimum Vetex
 Calls: 
 ----------------------------------------------------------------------------*/

struct MST DeleteMin(struct MST queue[], int n)
{
    struct MST min = queue[0];
    return min;
}
/*----------------------------  function ------------------------------------
 Name: Prims
 Purpose: Implementation of Prims Algorithm
 Arguments:Input Matrix
 Returns: void
 Calls: MakeQueue, DeleteMin
 ----------------------------------------------------------------------------*/

void Prims(int **W)
{
	struct MST PrimsMST[size];
	struct Graph *MST=(struct Graph*)malloc(sizeof(struct Graph));
	int qSize=0,i,x;
	bool visited[size-1];
	
	for (i = 0; i < size; ++i)
	{
			PrimsMST[i].cost=999;
			PrimsMST[i].prev=-1;
			visited[i]=false;
			PrimsMST[i].index=i;
	}
		PrimsMST[0].cost=0;
		PrimsMST[0].prev=0;
		struct MST PQ[2*(size-1)];
		int V=0;
		int m=0;
		while(V<size)
		{
			int flag=0;
			for (x= 0; x < size; ++x)
			{
				if (visited[x]==true)
				{
					flag++;
				}
			}
			if (flag==size)
				break;

			qSize=0;
			for (i = 0; i < size; ++i)
			{
				if (!visited[i])
				{		
				MakeQueue(PQ,qSize,PrimsMST[i]);
				qSize++;
				}
			}
			
			struct MST MinMST=DeleteMin(PQ,qSize);
			MST[m].src=MinMST.prev;
			MST[m].dest=MinMST.index;
			MST[m].weight=MinMST.cost;
			m++;

			int v=MinMST.index;
			visited[v]=true;
			int z=0;
			for (z = 0; z < size; ++z)
			{
				if(PrimsMST[z].cost>W[v][z])
				{
					PrimsMST[z].cost=W[v][z];
					PrimsMST[z].prev=v;
				}
			}

		}
		cout<<"\n\nMinimum Spaning Tree using Prims algorithm\n";
		cout<<"Source\tDest\tWeight\n";
		for (x = 1; x < m; ++x)
		{
			cout<<MST[x].src+1<<" =>\t"<<MST[x].dest+1<<"\t"<<MST[x].weight<<"\n";
		}
}
/*--------------------------- main function ----------------------------------
 Purpose: Start the program
 Arguments: None
 Returns: EXIT_SUCCESS
 Calls: FileOp, PrintMat
 ----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
  	int n,i,j;
  	if ( argc != 2 ) 
    cout<<"\nEnter File Name as Argument\n";
  	else {

	
		char *input=argv[1];
		//char input[10]="graph.txt";
		int **W=FileOp(input);
		cout<<"\nInput Matrix\n";
		PrintMat(W,size);
		Prims(W);


	}
	return 0;
}