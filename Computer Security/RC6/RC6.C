#include<stdio.h>
#include<math.h>
#include<string.h>

#define w 32
#define r 20

#define Pw 0xB7E15163
#define Qw 0x9E3779B9

#define v (w/8)
#define c (b/v)
#define rt (2*r+4)
#define lg 5


int hex(char a)
{
     int value = (int)a;
     if(value<58 && value>47)
     {
      return (value-48); 
     }
     if(value<103 && value>96)
     {
      return (value - 87);
     }
      return value;
}


unsigned int S[rt-1];

//Rotation

unsigned int rotateL(unsigned int a,unsigned int  n)
{
 	n &= 0x1f; 
 	return ((a<<n)| (a>>(32-n)));
}

unsigned int rotateR(unsigned int a, unsigned int n)
{
 	n &= 0x1f; 
 	return ((a>>n)| (a<<(32-n)));
}
unsigned int toLE(unsigned int a)
{
	unsigned le;
				le = ((a>>24)&0xff) | ((a<<8)&0xff0000) | ((a>>8)&0xff00) | ((a<<24)&0xff000000); 

     return le;
}
unsigned int revLE(unsigned int a)
{
	unsigned le;
			le = ((a<<24)&0xff000000) | ((a>>8)&0xff00) | ((a<<8)&0xff0000) | ((a>>24)&0xff); 
     return le;
}
//max function;
void key_expansion(unsigned char *K, int b)
{
    int i,j,s,m;
    unsigned int L[c],A,B;
    L[c- 1]=0;
    for(i=b-1;i>=0;i--)
        L[i/v]=(L[i/v]<<8)+K[i];
    
    S[0]=Pw;
    for(i=1;i<=2*r+3;i++)
        S[i]=S[i-1]+Qw;
 
    i=j=0;
    A=B=0;
    //max
    m=rt;
    if(c>m) 
    m=c;
    
    
    for(s=1;s<=(m*3);s++)
    {
        A=S[i]=rotateL(S[i]+A+B,3);
        B=L[j]=rotateL(L[j]+A+B,A+B);
        i=(i+1)%rt;
        j=(j+1)%c;
    }
   
    
}
void encryption(unsigned int *plain,unsigned int *cipher)
{
	unsigned int A,B,C,D,i,t,u,x;
	A=toLE(plain[0]);
	B=toLE(plain[1]);
	C=toLE(plain[2]);
	D=toLE(plain[3]);
	
	//printf("E1:%08x %08x %08x %08x \n",A,B,C,D);
	

	B=B+S[0];
	D=D+S[1];

	for(i=1;i<=r;i++)
	{
		t=rotateL(B*(2*B+1),lg);
		u=rotateL(D*(2*D+1),lg);
		A=rotateL(A ^ t,u) + S[2*i];
		C=rotateL(C ^ u,t) + S[2*i+1];
		x=A;
		A=B;
		B=C;
		C=D;
		D=x;
		
	}
	A=A+S[2*r+2];
	C=C+S[2*r+3];
	//printf("E2:%x %x %x %x \n",A,B,C,D);
	

	cipher[0]=toLE(A);
	cipher[1]=toLE(B);
	cipher[2]=toLE(C);
	cipher[3]=toLE(D);

}
void decryption(unsigned int *cipher)
{
	unsigned int A,B,C,D,i,t,u,x,z[16],j;
	unsigned int plain[4];
	FILE *fp3;
	
	A=revLE(cipher[0]);
	B=revLE(cipher[1]);
	C=revLE(cipher[2]);
	D=revLE(cipher[3]);
	//printf("D1:%08x %08x %08x %08x \n",A,B,C,D);
	C=C-S[2*r+3];
	A=A-S[2*r+2];
	
	

	for(i=r;i>=1;i--)
	{
		x=D;
		D=C;
		C=B;
		B=A;
		A=x;
		u=rotateL(D*(2*D+1),lg);
		t=rotateL(B*(2*B+1),lg);
		C=rotateR(C-S[2*i+1],t)^u;
		A=rotateR(A-S[2*i],u) ^ t;
		
	}
	
	D=D-S[1];
	B=B-S[0];
	
	plain[0]=revLE(A);
	plain[1]=revLE(B);
	plain[2]=revLE(C);
	plain[3]=revLE(D);

	j=0;
	for(i=0;i<16;i+=4)
	{
	z[i]=(plain[j]>>24)& 0xFF ;
	z[i+1]=(plain[j]>>16)& 0xFF ;
		
	z[i+2]=(plain[j]>>8)& 0xFF;
	z[i+3]=plain[j]& 0xFF;
	j++;
		
	}
	fp3=fopen("output.txt","w");
	fprintf(fp3, "Plaintext: ");
	for(i=0;i<16;i++)
	fprintf(fp3,"%02x ",z[i]);
	fclose(fp3);
	printf("\nPlain: %08x %08x %08x %08x\n",plain[0],plain[1],plain[2],plain[3]);
}

int main()
{
	unsigned int plain[4],cipher[4];
	
	   FILE *fp,*fp2 ;
	  // fp= fopen("inputP.txt","r"); 
	   unsigned char c1,c2;
	   unsigned int result,P[4];
       int i=0,count=0,flag,j;
       char ch,select[10];
       unsigned char sum;
       unsigned char pt[32],key[32];
        
   
     	fp = fopen("input.txt","r"); 
     	i=0;
     	while((ch=fgetc(fp))!=':')
        {
        	select[i]=ch;
        	i++;
        }
      
        
        i=0;
     	while((ch=fgetc(fp))!=EOF)
     	{
     	
     		if (ch=='\n')
     		break;
     		if(ch==' ')
     		continue;
     		else
     		{	
     		
                c1 = hex(ch);
                c2 = hex(fgetc(fp));
                sum = c1<<4 | c2;
                pt[i] = sum;
        		i++;
        	}
     	}

     
        //break the plain text into four parts
        for(i=0,j=0;i<32;j++,i+=4)
        {
      	result = (pt[i]<<24) | (pt[i+1]<<16)| (pt[i+2]<<8) | pt[i+3];
      	P[j]=result;
		}

     	while((ch=fgetc(fp))!=':')
     	{
     		continue;
     	}
     	i=0;
     	while((ch=fgetc(fp))!=EOF)
     	{
 
     		if(ch==' ')
     		continue;
     		else
        	{
        		count++;
                c1 = hex(ch);
                c2 = hex(fgetc(fp));
                sum = c1<<4 | c2;
                key[i] = sum;
                i++;
        
        	}
    	}
    	
    	
    	fclose(fp);
		//printf("\nInput: %08x %08x %08x %08x\n",P[0],P[1],P[2],P[3]);
		
		if(strcmp(select,"Plaintext")==0)
			flag=1;
		else
			flag=0;
		
		switch(flag)
		{
		case 0: key_expansion(key,count);
				decryption(P);
				break;
		case 1:
				key_expansion(key,count);
				encryption(P,cipher);
				unsigned int x[16];
				j=0;
				for(i=0;i<16;i+=4)
				{
				x[i]=(cipher[j]>>24)& 0xFF ;
				x[i+1]=(cipher[j]>>16)& 0xFF ;
		
				x[i+2]=(cipher[j]>>8)& 0xFF;
				x[i+3]=cipher[j]& 0xFF;
				j++;
		
				}
				fp2=fopen("output.txt","w");
				fprintf(fp2, "Ciphertext: ");
				for(i=0;i<16;i++)
				fprintf(fp2,"%02x ",x[i]);
				fclose(fp2);
		
				printf("Ciphertext: %08x %08x %08x %08x\n",cipher[0],cipher[1],cipher[2],cipher[3]);
				break;
		
			}

		

	return 0;
	
	
}