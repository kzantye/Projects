#include<stdio.h>
#include<stdlib.h>
#include<string.h>

long int PC=0,NPC=1,cycle_count=0;
typedef struct sc
{
	char addr[10],lb[10],mn[10],op1[10],op2[10],op3[10];
}sc;


sc *s;
FILE *fptr;
char dest[1000][10];
int src1[1000];
int src2[1000];
int opr[1000];
int result[1000];
int regx[8];
int memo[9999][2];
int depend[1000];
int waiting=0;
int global;
int stop;
int l,m,difference,jump=0,x;
void Decode(int i,int z);
int getmin(int i, int j)
{
	int small;
	small= i;
	if(small>j)  
	{  
			small= j;     
	} 
	return small; 	
}
int getmaxarr(int arr[1000],int size)
{
 
    int max = arr[0];
 
    for ( int c = 1 ; c < size; c++ ) 
    {
        if ( arr[c] > max ) 
           max = arr[c];
    } 
    return max;	
}
int getminarr(int arr[1000],int size)
{
 
    int min = arr[0];
 
    for ( int c = 1 ; c < size; c++ ) 
    {
        if ( arr[c] < min ) 
           min = arr[c];
    } 
    return min;	
}
void WB(int i,int decodecall,int z)
{
	int x;

	if(i>=0)
	{
		//printf("Instruction %d WB\n",i );
		if (strcmp(dest[i],"R0")==0)
			{regx[0]=result[i];}
		else if (strcmp(dest[i],"R1")==0)
			{regx[1]=result[i];}
		else if (strcmp(dest[i],"R2")==0)
			regx[2]=result[i];
		else if (strcmp(dest[i],"R3")==0)
			{regx[3]=result[i];}
		else if (strcmp(dest[i],"R4")==0)
			{regx[4]=result[i];}
		else if (strcmp(dest[i],"R5")==0)
			{regx[5]=result[i];}
		else if (strcmp(dest[i],"R6")==0)
			{regx[6]=result[i];}
		else if (strcmp(dest[i],"R7")==0)
			{regx[7]=result[i];}
		if (z==1)
		{
		
		printf("WriteBack Stage: ");
		for (x= 0; x< 8; x++)
		{
			printf("||R%d:%d ",x,regx[x]);
		}
		printf("||\n");
		}
		//printf("%d\n",i);
		//printf("%d\n",depend[i+difference]);
		
		if (decodecall==1 && i==(global))
		{
			//printf("Call to decode\n");
			depend[i+difference]=0;
			Decode((i+difference),0);
		}
		
	}

}





void Mem(int i,int z)
{
	int temp,x=0;
	if(i>=0)
	{
		
		switch(opr[i])
		{
		case 7:for (x = 0; x < 9999;x++)
				{
					if (result[i]==memo[x][0])
					{

						result[i]=memo[x][1];
						break;
					}
				}
				if (z==1)
				printf("Mem Stage: %s %d\n",dest[i],result[i]);
				break;
		case 8:temp=atoi(dest[i]);
				for (int x = 0; x < 9999;x++)
				{
					if (result[i]==memo[x][0])
					{
						memo[x][1]=temp;
						break;
					}
				}
				if (z==1)
				printf("Mem Stage: %s %d\n",dest[i],result[i]);
				break;
		default:if (z==1)
				printf("Mem Stage(pasing result using latch): %s %d\n",dest[i],result[i]);
				break;
		
		}
	}	
	
}






void Exe(int i,int z)
{
	if (i>=0)
	{
		//printf("Executing %d\n",i );
		switch(opr[i])
		{
			case 1:result[i]=0;
				result[i]+=src1[i]+src2[i];//Add ALU
				if (z==1)
				printf("Execution result: %d\n",result[i] );
				break;
			case 2:result[i]=0;
				result[i]+=src1[i]-src2[i];//Add SUB
				if (z==1)
				printf("Execution result: %d\n",result[i] );
				break;
			case 3:result[i]=1;
				result[i]*=src1[i]*src2[i];//Add MUL
				if (z==1)
				printf("Execution result: %d\n",result[i] );
				break;
			case 4:result[i]=0;
				result[i]+=src1[i]|src2[i];//Add OR
				if (z==1)
				printf("Execution result: %d\n",result[i] );
				break;
			case 5:result[i]=0;
				result[i]+=src1[i]&src2[i];//Add AND
				if (z==1)
				printf("Execution result: %d\n",result[i] );
				break;
			case 6:result[i]=0;
				result[i]+=src1[i]^src2[i];//Add EXOR
				if (z==1)
				printf("Execution result: %d\n",result[i] );
				break;
			case 7:result[i]=0;
				result[i]+=src1[i]+src2[i];//LOAD
				if (z==1)
				printf("Execution result: %d\n",result[i] );
				break;
			case 8:result[i]=0;
				result[i]+=src1[i]+src2[i];//STORE
				if (z==1)
				printf("Execution result: %d\n",result[i] );
				break;
			case 9:jump=0;
				jump+=src1[i]+src2[i];//STORE
				if (z==1)
				printf("Execution result(JUMP): %d\n",jump);
				break;
			case 10:if(result[i-1]==0)
					{jump=0;
					jump+=i+src1[i];//BZ
				if (z==1)
				printf("Execution result(BZ): %d\n",jump);
				}
				break;
			case 11:if(result[i-1]!=0)
					{jump=0;
					jump+=i+src1[i];//BNZ
				if (z==1)
				printf("Execution result(BNZ): %d\n",jump);
				}
				break;

		}
	}	
}





void Decode(int i,int z)
{
	int flag=0;
	if(i>=0)
	{	
		//printf("Decoding %d\n",i);
		if (depend[i]==-1) //To check for dependency
		{
			int p,k,temp1,temp2;
			int arr1[1000];
			l=0,m=0;
			for (k=0;k< i;k++)
			{
				if (strcmp(s[i].op2,s[k].op1)==0 && (i-k)<3 && depend[i]==-1)
				{
				arr1[l++]=k;
				flag=1;
				}
			}
			for (p=0;p< i;p++)
			{
				if (strcmp(s[i].op3,s[p].op1)==0 && (i-p)<3 && depend[i]==-1)
				{
				arr1[l++]=p;
				flag=1;
				}

			}
			if (flag!=1)
			{
				depend[i]=0;
				Decode(i,0);
			}
			else if(flag==1)
			{int k=depend[i];
				flag=0;
				int res=getminarr(arr1,l);
				//printf("Instruction %d is dependent %d \n",i,res);
				//printf("%s %s\n",s[i].op2,s[res].op1);
				difference=i-res;
				depend[i]=res;
				global=res;
				waiting=1;
				k=i-1;
				//printf("difference %d\n",difference);
				for (int x = 0; x<=(4-difference); x++)
				{

				Exe((k-1),0);
				Mem((k-2),0);
				WB((k-3),1,0);
				k++;

				}
				//printf("\n");

				//printf("WriteBack\n");
			}
		}
		else if (depend[i]==0)
		{
			//printf("Normal Decoding\n");
			
		if(strcmp(s[i].mn,"MOVC")==0)
		{
		
			strcpy(dest[i],s[i].op1);
			src1[i]=atoi(s[i].op2);
			src2[i]=0;
			if (z==1)
			printf("Decoded Instruction: %s %s %d %d\n",s[i].mn,dest[i],src1[i],src2[i]);
			opr[i]=1;
			
		}
	
		else if(strcmp(s[i].mn,"MUL")==0||strcmp(s[i].mn,"ADD")==0||strcmp(s[i].mn,"SUB")==0||strcmp(s[i].mn,"OR")==0||strcmp(s[i].mn,"AND")==0||strcmp(s[i].mn,"EX-OR")==0)
		{
			int temp1,temp2;
			temp1=atoi(&s[i].op2[1]);
			temp2=atoi(&s[i].op3[1]);
			strcpy(dest[i],s[i].op1);
			src1[i]=regx[temp1];
			src2[i]=regx[temp2];
			if (z==1)
			printf("Decoded Instruction: %s %s %d %d\n",s[i].mn,dest[i],src1[i],src2[i]);
			if (strcmp(s[i].mn,"ADD")==0)
					opr[i]=1;
			if (strcmp(s[i].mn,"SUB")==0)
			{opr[i]=2;}
			if (strcmp(s[i].mn,"MUL")==0)
					opr[i]=3;
			if (strcmp(s[i].mn,"OR")==0)
					opr[i]=4;
			if (strcmp(s[i].mn,"AND")==0)
					opr[i]=5;
			if (strcmp(s[i].mn,"EX-OR")==0)
					opr[i]=6;
		}

		else if(strcmp(s[i].mn,"LOAD")==0)
		{
		
			int temp1,temp2;
			strcpy(dest[i],s[i].op1);
			temp1=atoi(&s[i].op2[1]);
			src1[i]=regx[temp1];
			if (strcmp(s[i].op3,"R1")==0||strcmp(s[i].op3,"R2")==0||strcmp(s[i].op3,"R3")==0||strcmp(s[i].op3,"R4")==0||strcmp(s[i].op3,"R5")==0||strcmp(s[i].op3,"R6")==0||strcmp(s[i].op3,"R7")==0||strcmp(s[i].op3,"R0")==0)
			{
			temp2=atoi(&s[i].op3[1]);
			src2[i]=regx[temp2];
			}
			else
			src2[i]=atoi(s[i].op3);
			if (z==1)
			printf("Decoded Instruction: %s %s %d %d\n",s[i].mn,dest[i],src1[i],src2[i]);
			opr[i]=7;
		}
		else if(strcmp(s[i].mn,"STORE")==0)
		{
			
			int temp1,temp2,temp3;
			temp3=atoi(&s[i].op1[1]);
			snprintf(dest[i],10,"%d",regx[temp3]);
			temp1=atoi(&s[i].op2[1]);
			src1[i]=regx[temp1];
			if (strcmp(s[i].op3,"R1")==0||strcmp(s[i].op3,"R2")==0||strcmp(s[i].op3,"R3")==0||strcmp(s[i].op3,"R4")==0||strcmp(s[i].op3,"R5")==0||strcmp(s[i].op3,"R6")==0||strcmp(s[i].op3,"R7")==0||strcmp(s[i].op3,"R0")==0)
			{
			temp2=atoi(&s[i].op3[1]);
			src2[i]=regx[temp2];
			}
			else
			src2[i]=atoi(s[i].op3);
			if (z==1)
			printf("Decoded Instruction: %s %s %d %d\n",s[i].mn,dest[i],src1[i],src2[i]);
			opr[i]=8;
			
		}
		else if(strcmp(s[i].mn,"HALT")==0)
		{
			
			stop=1;
			
		}
		else if (strcmp(s[i].mn,"JUMP")==0)
		{
			int temp1,temp2;
			if (strcmp(s[i].op1,"R1")==0||strcmp(s[i].op1,"R2")==0||strcmp(s[i].op1,"R3")==0||strcmp(s[i].op1,"R4")==0||strcmp(s[i].op1,"R5")==0||strcmp(s[i].op1,"R6")==0||strcmp(s[i].op1,"R7")==0||strcmp(s[i].op1,"R0")==0)
			{
			temp1=atoi(&s[i].op1[1]);
			src1[i]=regx[temp1];
			temp2=atoi(s[i].op2);
			src2[i]=temp2-20000;
			
			}
			else if(strcmp(s[i].op1,"X")==0)
			{
				src1[i]=x;
				src2[i]=0;	
			}
			
			if (z==1)
			printf("Decoded Instruction: %s %d %d\n",s[i].mn,src1[i],src2[i]);
			opr[i]=9;
		}
		else if (strcmp(s[i].mn,"BAL")==0)
			{
			int temp1,temp2;
			
			temp1=atoi(&s[i].op1[1]);
			src1[i]=regx[temp1];
			temp2=atoi(s[i].op2);
			src2[i]=temp2;
			x=i+1;
			if (z==1)
			printf("Decoded Instruction: %s %d %d\n",s[i].mn,src1[i],src2[i]);
			opr[i]=9;
		}
		else if (strcmp(s[i].mn,"BZ")==0 || strcmp(s[i].mn,"BNZ")==0)
		{
			int temp1;
			temp1=atoi(s[i].op1);
			src1[i]=temp1;
			if (z==1)
			printf("Decoded Instruction: %s %d\n",s[i].mn,src1[i]);
			if (strcmp(s[i].mn,"BZ")==0)
					opr[i]=10;
			if (strcmp(s[i].mn,"BNZ")==0)
			{opr[i]=11;}
		}


		}
	}
}





void Fetch(int i,int z)
{
	

    if (!feof(fptr))
    {
    
    fscanf(fptr,"%s%s%s%s%s",&s[i].addr,&s[i].mn,&s[i].op1,&s[i].op2,&s[i].op3);
    if (z==1)
    {
    printf("Instruction %d Fetched: ",i );
    printf("%s %s %s %s %s\n",s[i].addr,s[i].mn,s[i].op1,s[i].op2,s[i].op3);
    
	}
    }
    else 
    {
    	if (z==1)
    	printf("Instruction Fetch completed\n");
    }

}




int main(int argc, char *argv[])
{
	FILE *p1,*p2,*p3,*p4;
	int x,y;
	char line[20],command[20];
	char ch='y',filename[20];
	waiting=0;
	s=(sc*)malloc(sizeof(sc));
	for (x = 0;x< 1000; x++)
	{
		depend[x]=-1;
	}
	for (x = 0; x < 9999; x++)
	{
			memo[x][0]=x;
			memo[x][1]=0;
	}
	printf("Enter the input file name:\t");
	scanf("%s",&filename);
	int i=0;
	while(ch=='y' || ch=='Y')
	{
	printf("\nEnter the command ($initialize,$simulate n,$display)\n");
	scanf("%s",&command);
	//initialize
	if (strcmp(command,"initialize")==0)
	{
		PC=20000;
		//Format the input file
		p1=fopen(filename,"r");
		if( p1 == NULL )
    	{
      	perror("Error while opening the file.\n");
      	exit(0);
    	}
		p2=fopen("Source.txt","w"); 
   		while(fgets(line, sizeof line,p1)!=NULL)
 		{
			if (line[0]=='M' && line[1]=='O')
	  		{
	  			fprintf(p2,"%ld ",PC);
	  			for (int i = 0; line[i]!='\n'; ++i)
	  			{
	  			fprintf(p2,"%c",line[i]);

	  			}
	  			fprintf(p2," *\n");
	  		} 
	 		else if (line[0]=='H' && line[1]=='A')
	  		{
	  			fprintf(p2,"%ld ",PC);
	  			for (int i = 0; line[i]!='\n'; ++i)
	  			{
	  			fprintf(p2,"%c",line[i]);

	  			}
	  			fprintf(p2," * * *");
	  		}
	  		else if ( (line[0]=='B' && line[1]=='Z')||(line[0]=='B' && line[1]=='N'))
	  		{
	  			fprintf(p2,"%ld ",PC);
	  			for (int i = 0; line[i]!='\n'; ++i)
	  			{
	  				fprintf(p2,"%c",line[i]);

	  			}
	  			fprintf(p2," * *\n");
	  		}  
	  		else
	  		{fprintf(p2,"%ld ",PC);
	  		fprintf(p2,"%s",line);}
    
   			PC=PC+1;
   		}
   		fclose(p2);
   		fclose(p1);

   		//Intialise the register file
   		for (x= 0; x< 8;x++)
    	{
    		regx[x]=0;
    	}
    	fptr=fopen("Source.txt","r");
		if( fptr == NULL )
    	{
      		perror("Error while opening the file.\n");
      		exit(0);
    	}
	}
    int n;
	
	//Simulation
	if (strcmp(command,"simulate")==0)
	{
		scanf("%d",&n);
		while(cycle_count!=n)
		{
		if (jump!=0)
		{
			rewind(fptr);
			i=0;
			while(i!=jump)
			{
			Fetch(i,0);
			i++;
			}
			i=jump;
			//printf("pointer reseted %d\n",i);
			jump=0;
		}
		else
		{
			
			if(stop!=1)
			{
			Fetch(i,0);
			Decode((i-1),0);
			}
			if (waiting==0)
			{
			Exe((i-2),0);
			Mem((i-3),0);
			WB((i-4),0,0);
			}
			else if (waiting==1)
			{
			//printf("waiting\n");	
			waiting=2;
			}
			else if (waiting==2)
			{
			Exe((i-2),0);
			waiting=3;
			}
			else if (waiting==3)
			{
			Exe((i-2),0);
			Mem((i-3),0);
			waiting=0;
			}
			i++;
			cycle_count++;
		}
		}
		//printf("%d\n",depend[2]);
		//printf("\nNumber of cycles: %ld\n",cycle_count);
		cycle_count=0;
		//i=i-1;
	}
	printf("completed\n");
	if (strcmp(command,"display")==0)
	{
		printf("\nMemory\n");
		for(x=0;x<100;x++)
		{
			printf("M%d : %d  ",memo[x][0],memo[x][1]);
		}
		 printf("\n\n");
		i=i-1;
		//Fetch(i-1,0);
		if(stop!=1)
		{
		printf("\nInstruction %d Fetched: ",i );
    	printf("%s %s %s %s %s\n",s[i].addr,s[i].mn,s[i].op1,s[i].op2,s[i].op3);
    	}
    	else
    	printf("\nInstruction Fetching HALT" );
    
		Decode((i-1),1);
		Exe((i-2),1);
		Mem((i-3),1);
		WB((i-4),0,1);
		printf("\n");
		exit(0);
	}	
	printf("\nDo you want to continue(Y/N)?");
	scanf("%s",&ch);
	}
   	return 0;
}
