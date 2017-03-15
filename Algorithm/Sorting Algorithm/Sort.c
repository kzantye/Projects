#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int k=0;

/*
 * Function:  printArray
 * ----------------------
 * Parameters: Array and Input Size
 * Description: To display the array.
 *
 */
void printArray(int arr[],int n)
{
	int i=0;
	printf("\n");
	for (i = 0; i < n; ++i)
		printf("%d |",arr[i] );
}
/*
 * Function:  printStars 
 * --------------------
 * Description: To show the graphical representation
 */
void printStars(int arr[],int n)
{	
	int k,i;
	printf("\n ==============================================================================\n");
	printArray(arr,n);
			printf("\n");
			//printf("Pass %d\n",n);
			for (k = 0; k < n; k++)
			{
				printf("\n");

				for (i = 0; i < arr[k]; ++i) /* To Print the jber stars*/
				{
					printf("*");
				}
			}
	


}
/*
 * Function:  createArray
 * --------------------
 * Parameters: Array and Input Size
 * Description: To generate random array.
 *
 */
void createArray(int *arr,int n)
{
	int i;
	srand(time(NULL));
	if (n>20)
	{
		for (i = 0; i < n; ++i) /* To generate random jbers */
			arr[i]=rand();
	}
	else
	{
		for (i = 0; i < n; ++i)
			arr[i]=rand()%16;		/* To generate random jbers if input less than 20 */
	}	
	
	
}

/*
 * Function:  Insertion Sort
 * --------------------------
 * Parameters: Array and Input Size
 * Description: Sorts the array using insertion algorithm.
 *
 */
void Insertion(int arr[], int n)
{
	int i,j;
	for (i = 0; i < n; ++i)
	{	
		/*To compare the two array elements and swap if smaller*/
		for (j = i; j>0 && arr[j-1]>arr[j]; j--)
		{
			int temp=arr[j];
			arr[j]=arr[j-1];
			arr[j-1]=temp;
		}
		if (n<=20)
			printStars(arr,n);
		
	}

}

/*
 * Function:  Counting_Sort
 * ------------------------
 * Parameters: Array and Input Size
 * Description: To sort the given array using counting sort algorithm.
 */
void Counting_Sort(int * arr,int n)
{
	int i=0;
	/*To initialize the array with 0*/
  int * count = calloc(100, sizeof(int));
  k=1;

  // to count the jber repeated
  for(i = 0; i < n; i++)
  {
    count[arr[i]]+=1;
  }
  
  int j = 0;
  i = 0;


  while(i <= n)
  {
  	
    while(count[j] > 0)
    {
      arr[i] = j;
      if (n<=20)
      	printStars(arr,n);
      count[j]-=1;
      i++;
      if(i > n)
      	break;
    }
    j++;
  }

}

/*
 * Function:  Merge
 * --------------------
 * Parameters: Left Array, Left array size , Right Array & Right Size
 * Description: To merge the left partition and right partition.
 *
 *
 */
void Merge(int *arr, int left, int mid, int right,int n)
{
        
        int temp[right-left+1];
        int pos=0,leftpos = left,rightpos = mid + 1;
        while(leftpos <= mid && rightpos <= right)
        {
                if(arr[leftpos] < arr[rightpos])
                {
                        temp[pos++] = arr[leftpos++];
                }
                else
                {
                        temp[pos++] = arr[rightpos++];
                }
        }
        while(leftpos <= mid)  
        	temp[pos++] = arr[leftpos++];
        while(rightpos <= right)
        	temp[pos++] = arr[rightpos++];
        int i;
        
        for(i = 0;i < pos; i++)
        {
                arr[i+left] = temp[i];/* To Copy the sorted array to the original array */
        }
        if (n<=20)
		printStars(arr,n);

        return;
}
/* Function:  MergeSort
 * --------------------------
 * Parameters: Array and Input Size
 * Description: Sorts the array using MergeSort algorithm.
 *
 *
*/
void MergeSort(int *arr, int left, int right,int n)
{
        int mid = (left+right)/2;
        if(left<right)
        {
                
                MergeSort(arr,left,mid,n);/* Sort the left part */
                MergeSort(arr,mid+1,right,n);/* Sort the right part */
                Merge(arr,left,mid,right,n);/* Merge the two sorted parts */
        }
}

/*
 * Function:  divide
 * --------------------------
 * Parameters: Array ,left index, right index & Input Size
 * Description: Divide the array with respect to pivot.
 *
*/
 
int divide( int arr[], int low, int high,int x)
{
	 
	 int pelement;
	 int left = low; 
	 int temp;
	 int right = high;
	 int pivot=left + rand()%(right - left + 1);
	 pelement = arr[pivot]; 
	 
	 while ( left < right ) 
	 {
	  
	  	while( arr[left] <= pelement ) // Move left if the array element < pivot
	  	left++;
	  	while( arr[right] > pelement ) // Move right if the array element > pivot
	  	right--;
	  	if ( left < right ) 
	  	{  
		  	 temp=arr[left];
		 	 arr[left]=arr[right];
		 	 arr[right]=temp;
		}
	}
	 
	arr[low] = arr[right]; // right is final position for the pivot 
	arr[right] = pelement;
	if (x<=20)
		printStars(arr,x);
	 return right;
}//end partition

/* Function:  Rand_Quick
 * --------------------------
 * Parameters: Array ,left index, right index & Input Size
 * Description: Sorts the array using Random Quick sort algorithm.
 *
*/
void Rand_Quick( int arr[], int low, int high,int x )
{
 int pivot;
 // Termination condition! 
 if ( high > low )
 {
  pivot = divide( arr, low, high,x);
  Rand_Quick( arr, low, pivot-1,x);
  Rand_Quick( arr, pivot+1, high, x);
 }
} //e

/*
 * Function:  main
 * --------------------------
 * Parameters: -
 * Description: Accepts the choice of sort from the user 
 				and also accepts the input size.
 *
 */
int main()
{

	int n,choice,i;
	while(1)
	{
		printf("\nSorting Algorithms:");
		printf("\n1] Insertion Sort\n2] Counting Sort\n3] Merge Sort\n4] Randomized Quick Sort\n5] Exit");
		printf("\nEnter your choice:\t");
		scanf("%d",&choice);
		if (choice>5 || choice<1)
		{
			printf("Invalid choice\n");
		}
		else
		{
			if (choice==5)
				exit(1);
			else
			{
				while(1)
				{

					printf("Enter the jber of input data(n):\t");
					scanf("%d",&n);
					if (n<1 || n>1000)
					{
						printf("Invalid input\n");
					}
					else
						break;
				}
				int arr[n];

				
				
				switch(choice)
				{
					case 1:		createArray(arr,n);
								printArray(arr,n);
								Insertion(arr,n);
								printf("\n=====================================\nSorted Using Insertion Sort\n**************************************\n");
								printArray(arr,n);
							break;
					case 2:		srand(time(NULL));
								if (n>20)
								{
									for (i = 0; i < n; ++i)
										arr[i]=rand()%100;
								}
								else
								{
									for (i = 0; i < n; ++i)
										arr[i]=rand()%16;
								}
								printArray(arr,n);
								Counting_Sort(arr,n);
								printf("\n**************************************\nSorted Using Counting Sort\n**************************************\n");
								printArray(arr,n);
							break;
					case 3: 	createArray(arr,n);
								printArray(arr,n);
								MergeSort(arr,0,n,n);
								printf("\n**************************************\nSorted Using Merge Sort\n**************************************\n");
								printArray(arr,n);
								
							break;
					case 4: 	createArray(arr,n);
								printArray(arr,n);
								Rand_Quick(arr,0,n,n);
								printf("\n**************************************\nSorted Using Random QuickSort\n**************************************\n");
								printArray(arr,n);
							
							break;
					default:exit(0);
							break;
				}
				
			}

		}
	}
	
}