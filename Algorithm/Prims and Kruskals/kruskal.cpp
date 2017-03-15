/*
 Program Name: Kruskal.cpp
 Author: Kunal Zantye
 Program Intent: Implement Kruskal’s algorithm to find the minimum spaning tree in the  given Graph
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
#include <stdio.h>
#include <stdlib.h>
#include <string> 
#include <limits> 
 /*--------------------
 Preprocessor Section
 ---------------------*/
using namespace std;
int size=0;
int e=0;

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
  int i=0;
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
	while (getline(infile, str) && i<size )
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
struct Edge
{
	int src, dest, weight;
};


/*int myComp(const void* a, const void* b)
{
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight > b1->weight;
}*/

void swap(struct Edge *a,struct Edge *b)
{
	struct Edge temp = *a;
	*a = *b;
	*b = temp;
}
/* Function:  Rand_Quick
 * --------------------------
 * Parameters: Array ,left index, right index & Input Size
 * Description: Sorts the array using Random Quick sort algorithm.
 *
*/

void Rand_Quick(struct Edge *edge, int left, int right)
{
    int l = left;
    int r = right - 1;
    int size = right - left;

    if (size > 1) {
        struct Edge pivot = edge[rand() % size + l];

        while (l < r) {
            while (edge[r].weight > pivot.weight && r > l) {
                r--;
            }

            while (edge[l].weight < pivot.weight && l <= r) {
                l++;
            }

            if (l < r) {
                swap(&edge[l], &edge[r]);
                l++;
            }
        }

        Rand_Quick(edge, left, l);
        Rand_Quick(edge, r, right);
    }
}


/*--------------------------- find function ----------------------------------
 Purpose: Creates the edges structure
 Arguments: Graph matrix & size
 Returns: Structure edge
 Calls: None
 ----------------------------------------------------------------------------*/
 struct Edge* createGraph(int **W,int n)
 {
 	struct Edge *edge=(struct Edge*)malloc(sizeof(struct Edge));
 	//struct Edge *edge=new Edge;
 	int i,j;
	for (i = 0; i<n; i++)
	{
		for (j= 0; j <i; j++)
		{
			
			if(W[i][j]!=0 && W[i][j]!=999)
			{
				edge[e].src=i;
				edge[e].dest=j;
				edge[e].weight=W[i][j];
				e++;

			}
		}
	}
	return edge;

 }
/*--------------------------- find function ----------------------------------
 Purpose: A function to find root of an element i
 Arguments: set matrix, element i
 Returns: root
 Calls: None
 ----------------------------------------------------------------------------*/

int find(int set[][2], int i)
{
  
	int root=i;
  while (root != set[root][0])
       root=set[root][0];
  int node=i;
  while (node != root){
      int parent=set[node][0];
      set[node][0]=root; // node points to root
      node=parent;}

  return root;
}

/*--------------------------- Union function ----------------------------------
 Purpose: A function that does union of two sets of x and y
 Arguments: set matrix, sets x & y
 Returns: void
 Calls: find
 ----------------------------------------------------------------------------*/
void Union(int set[][2], int x, int y)
{
    int repx = find(set, x);
    int repy = find(set, y);
    if (set[repx][1] == set[repy][1])
    {
    	set[repy][0]= repx;
        set[repx][1]++;
    }
    else if (set[repx][1] > set[repy][1])
        set[repy][0] = repx;
    else
    {
        set[repx][0] = repy;
    }
}
/*--------------------------- Kruskal function ----------------------------------
 Purpose: Implementation of Kruskal Algorithm
 Arguments: input graph matrix and size
 Returns: void
 Calls: createGraph, find & Union
 ----------------------------------------------------------------------------*/
 void Kruskal(int **W,int V)
 {
 	int i,v;
 	struct Edge result[V];
 	struct Edge *edge=createGraph(W,V);
 	//qsort(edge,e, sizeof(edge[0]), myComp);
	Rand_Quick(edge,0,e);
	/*for (i = 0; i < e; ++i)
	{
		cout<<edge[i].src<<edge[i].dest<<edge[i].weight;
		cout<<"\n\n";
	}*/

 	int set[V][2];
    //Create V set with single elements
    for (v = 0; v < V; ++v)
    {
        set[v][0] = v;
        set[v][1] = 0;
    }

    e=0;
    i=0;
   	while (e < V - 1)
    {
        struct Edge next_edge = edge[i++];
 
        int x = find(set, next_edge.src);
        int y = find(set, next_edge.dest);
 		if (x != y)
        {
            result[e++] = next_edge;
            Union(set, x, y);
        }
       
    }
    printf("\n\nMinimum Spaning Tree using Kruskal’s algorithm\n");
    cout<<"Source\tDest\tWeight\n";
    for (i = 0; i < e; ++i)
        cout<<result[i].src+1<<" =>\t"<<result[i].dest+1<<"\t"<<result[i].weight<<"\n";

 }
 /*--------------------------- main function ----------------------------------
 Purpose: Start the program
 Arguments: None
 Returns: EXIT_SUCCESS
 Calls: FileOP, PrintMat & Kruskal
 ----------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
  	int n,j;
  	if ( argc != 2 ) 
    cout<<"\nEnter File Name as Argument\n";
  	else {
		char *input=argv[1];
		//char input[10]="graph.txt";
		int **W=FileOp(input);
		cout<<"\nInput Matrix\n";
		PrintMat(W,size);
    		Kruskal(W,size);
		
	}
	return 0;
}
