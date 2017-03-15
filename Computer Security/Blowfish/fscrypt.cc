#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "openssl/blowfish.h"


const int BLOCKSIZE = 8;
void *fs_encrypt(void *plaintext, int bufsize, char *keystr, int *resultlen)
{
	int i=0,k,x=0,y=0,z=0;
	unsigned char* plainT = (unsigned char *)plaintext;
	int bnum = bufsize / BLOCKSIZE;
  	if(bufsize% BLOCKSIZE != 0)
  	{
    	bnum++;
    }
   	
    int padLen=0;
    if(bufsize%BLOCKSIZE!=0)
    padLen=BLOCKSIZE-bufsize%BLOCKSIZE;
	
	//Padding as per needed
	unsigned char pt[bnum][BLOCKSIZE], ct[bnum][BLOCKSIZE];
	
	for (x = 0; x <= bnum-1; x++)
	{
		if (x==bnum-1)
		{
			y=0;
			while(z<bufsize-1)
			{
			pt[x][y++]=plainT[z++];
			}
			for(i=0;i<padLen;i++){
			pt[x][y++] = padLen + '0';
			}
		}
		else
		{	
			y=0;
			while(y<BLOCKSIZE)
			{
			pt[x][y++]=plainT[z++];
			}
		}

	}
	/*for(x=0;x<bnum;x++)
	for(y=0;y<BLOCKSIZE;y++)
		printf("%c",pt[x][y] );*/


	//Key Steup
	BF_KEY *key = (BF_KEY*) malloc(sizeof(BF_KEY));
	BF_set_key(key,strlen((char *)keystr),(unsigned char*) keystr);
	unsigned char *plain=(unsigned char*)malloc(BLOCKSIZE);
	unsigned char *out = (unsigned char*) malloc(BLOCKSIZE);
	//CBC encryption
for (i = 0; i <bnum; ++i)
{
	if (i==0)
	{
		
		//for(i=0;i<bnum;i++)
		for(x=0;x<BLOCKSIZE;x++){
		plain[x]=pt[0][x];
		}
		//printf("%s\n",plain);
		unsigned char ivec[BLOCKSIZE];
  		for(k=0;k<BLOCKSIZE; k++) ivec[k] = '0';
  		for (int j = 0; j < BLOCKSIZE; ++j)
		{
		plain[j]=plain[j]^ivec[j];
		}
			
		BF_ecb_encrypt((unsigned char*) plain, (unsigned char*) out, key, BF_ENCRYPT);
		for(k=0;k<BLOCKSIZE;k++)
		ct[i][k]=out[k];
		
	}
	else
	{
		unsigned char *result = (unsigned char*) malloc(sizeof(BLOCKSIZE));
		
		for(x=0;x<BLOCKSIZE;x++){
		plain[x]=pt[i][x];
		}
		//printf("%s\n",plain);
		for (int j = 0; j < BLOCKSIZE; ++j)
		{
		result[j]=ct[i-1][j]^plain[j];
		}
		BF_ecb_encrypt((unsigned char*) result, (unsigned char*) out, key, BF_ENCRYPT);
		for(k=0;k<BLOCKSIZE;k++)
		ct[i][k]=out[k];
	}

}
	


	int n = 0;
	unsigned char *cout = (unsigned char *)malloc(sizeof(unsigned char *));
	for(int i = 0; i < bnum; i++){
		for(int j = 0; j < BLOCKSIZE; j++){
			cout[n++] = ct[i][j];
		}
	}
	*resultlen =strlen((char*)cout);
	return (void*)cout;

}


void *fs_decrypt(void *ciphertext, int bufsize, char *keystr, int *resultlen)
{

	
	int i=0,k,x=0,y=0,z=0;
	unsigned char* cipherT = (unsigned char *)ciphertext;
	//printf("bufsize%d\n",bufsize );
	int bnum = bufsize / BLOCKSIZE;
  	if(bufsize % BLOCKSIZE != 0)
  	{
    	bnum++;
    }
	unsigned char ct[bnum][BLOCKSIZE], dt[bnum*BLOCKSIZE];
	
	for (x = 0; x <= bnum-1; x++)
	{
		
			y=0;
			while(y<BLOCKSIZE)
			{
			ct[x][y++]=cipherT[z++];
			}

	}

	BF_KEY *key = (BF_KEY*) malloc(sizeof(BF_KEY));
	BF_set_key(key,strlen((char *)keystr),(unsigned char*) keystr);
	
	unsigned char *decrypt = (unsigned char*) malloc(BLOCKSIZE);		    
	unsigned char *dtext = (unsigned char*) malloc(BLOCKSIZE);
	unsigned char *result = (unsigned char*) malloc(BLOCKSIZE);
	//CBC Decryption
int n=0;
for(i=0;i<bnum;i++)
{
	if(i==0)
	{	
		for(k=0;k<BLOCKSIZE;k++)
		{
		decrypt[k]=ct[0][k];
		}	    
		BF_ecb_encrypt((unsigned char*) decrypt, (unsigned char*) dtext, key, BF_DECRYPT);
		unsigned char ivec[BLOCKSIZE];
  		for(k=0; k<BLOCKSIZE; k++) ivec[k] = '0';
  		for (int k= 0; k < BLOCKSIZE; k++)
		{
		result[k]=dtext[k]^ivec[k];
		}

		for(k = 0; k < BLOCKSIZE; k++)
		{	
			dt[n++]=result[k];   
		}

	}
	else
	{		    
	
		for(k=0;k<BLOCKSIZE;k++)
		{
		decrypt[k]=ct[i][k];

		}	
		BF_ecb_encrypt((unsigned char*) decrypt, (unsigned char*) dtext, key, BF_DECRYPT);
		
		for(k=0;k<BLOCKSIZE;k++)
		{
		result[k]=dtext[k]^ct[i-1][k];

		}
		for(k = 0; k < BLOCKSIZE; k++)
		{	
			dt[n++]=result[k];    
		}
	}
}

	int rmpad=dt[bufsize-2]-'0';
	unsigned char *dout = (unsigned char *)malloc(sizeof(unsigned char));
	
	if(rmpad<BLOCKSIZE && rmpad>0)
	{
	for(int  i=0;i<bufsize-rmpad-1;i++){ dout[i] = dt[i]; }	
	*resultlen=bufsize-rmpad;
	}
	else
	{
		for (i = 0;i<bufsize;i++)
		{
		dout[i]=dt[i];
		}
		*resultlen=bufsize;
	}

	return (void*)dout;
}
