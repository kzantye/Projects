/*
 Program Name: lcs.cpp
 Author: Kunal Zantye
 Program Intent: Implement LCS Algorith to find the longest common subsequence
 Input Data: Input File
 Output Data: 
 Compile Note: Use g++ to compile.
 */

/*---------------
 Include Section
 ----------------*/
#include <iostream>
#include <cstring>
#include <stdlib.h>
 #include <fstream>
 using namespace std;

 /*--------------------
 Preprocessor Section
 ---------------------*/

int c[1000][1000];
char b[1000][1000];
int length; 
/*----------------------------  function ------------------------------------
 Name: printLCS
 Purpose: Print longest common subsequence
 Arguments:1st String
 Returns: void
 Calls: None
 ----------------------------------------------------------------------------*/

void printLCS(char *X, int m,int n)
{
    if(m==0 || n==0)
                    return;
    if(b[m][n]=='D')
    {
        length++;
        printLCS(X,m-1,n-1);        
        cout<<X[m-1];
    }
    else if(b[m][n]=='U')
		    printLCS(X,m-1,n);
	else
        	printLCS(X,m,n-1); 
}
/*----------------------------  function ------------------------------------
 Name: lcs
 Purpose: Implementation of LCS algorithm
 Arguments:1st String
 Returns: void
 Calls: None
 ----------------------------------------------------------------------------*/

void lcs(char *X, char *Y, int m, int n)
{
    int i,j;
    for(i=0;i<=m;i++)
        c[i][0]=0;
    for(i=0;i<=n;i++)
        c[0][i]=0;
                    
    for(i=1;i<=m;i++)
        for(j=1;j<=n;j++)
        {
            if(X[i-1]==Y[j-1])
            {
                c[i][j]=c[i-1][j-1]+1;
                b[i][j]='D';
            }
            else
            {	
            	if(c[i-1][j]>=c[i][j-1])
            	{
	                c[i][j]=c[i-1][j];
	                b[i][j]='U';
	        	}
	            else
	            {
		            c[i][j]=c[i][j-1];
	    	        b[i][j]='L';
	            }
	        }
        }
}
 /*--------------------------- main function ----------------------------------
 Purpose: Start the program
 Arguments: None
 Returns: EXIT_SUCCESS
 Calls: lcs & printLCS
 ----------------------------------------------------------------------------*/

int main(int argc, char *argv[])
{
	char *X,*Y;
	//X =(char *) malloc(sizeof (char));
	//Y=(char *) malloc(sizeof (char));
	
	int m,n;
 	ifstream in;
    in.open (argv[1]); 

	if (!in.is_open())
    {
      cout<<"\nError opening file\n";
      exit(1);
    }
    string str1,str2;
	getline(in,str1); 
    cout<<"X = "<<str1<<"\n";
    getline(in,str2); 
    cout<<"Y = "<<str2;
	
    m=str1.length();
    n=str2.length();
    X=new char[m+1];
    Y=new char[n+1];
    memcpy(X,str1.c_str(),m);
    memcpy(Y,str2.c_str(),n);

    lcs(X,Y,m,n);   
    cout<<"\n";
    
    printLCS(X,m,n);   
    
    cout<<"\t"<<length<<"\n";
    return 0;
}