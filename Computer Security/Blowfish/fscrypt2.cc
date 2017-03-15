#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "openssl/blowfish.h"


const int BLOCKSIZE = 8;

void *fs_encrypt(void *plaintext, int bufsize, char *keystr, int *resultlen)
{
	int i=0,k,x=0,y=0,z=0;
	unsigned char *cipher;
	unsigned char* plainT = (unsigned char *)plaintext;

	int bnum = bufsize / BLOCKSIZE;
  	if(bufsize % BLOCKSIZE != 0)
  	{
    	bnum++;
    }
    int padLen=0;
    if((bufsize)%BLOCKSIZE!=0)
    padLen=BLOCKSIZE-(bufsize)%BLOCKSIZE;
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
	BF_KEY *key = (BF_KEY*) malloc(sizeof(BF_KEY));
	BF_set_key(key,strlen((char *)keystr),(unsigned char*) keystr);
	int s = 0;
	unsigned char *plain = (unsigned char *)malloc(bnum*BLOCKSIZE);
	for(int i = 0; i < bnum; i++){
		for(int j = 0; j < BLOCKSIZE; j++){
			plain[s] = pt[i][j];
			s++;
		}
	}
	
	unsigned char ivec[BLOCKSIZE];
	for(k=0;k<BLOCKSIZE; k++) ivec[k] = '0';
  			
  	unsigned char *cout = (unsigned char *)malloc(bnum*BLOCKSIZE);
	BF_cbc_encrypt(plain,cout,(bnum*BLOCKSIZE),key,ivec,BF_ENCRYPT);
		printf("\n");

		*resultlen=strlen((char*) cout);

	return (void*)cout;
}
void *fs_decrypt(void *ciphertext, int bufsize, char *keystr, int *resultlen)
{

	int i=0,k;
	unsigned char* cipherT = (unsigned char *)ciphertext;
	int bnum = bufsize / BLOCKSIZE;
  	if(bufsize % BLOCKSIZE != 0)
  	{
    	bnum++;
    }
    BF_KEY *key = (BF_KEY*) malloc(sizeof(BF_KEY));
	BF_set_key(key,strlen((char *)keystr),(unsigned char*) keystr);
	unsigned char ivec[BLOCKSIZE];
  	
  	for(k=0;k<BLOCKSIZE; k++) 
  	ivec[k] = '0';
	
	unsigned char deciphered[bnum*BLOCKSIZE];
	BF_cbc_encrypt(cipherT,deciphered,bufsize,key,ivec,BF_DECRYPT);
	
	int rmpad=deciphered[bufsize-2]-'0';
	unsigned char *dout = (unsigned char *)malloc(bnum*BLOCKSIZE);
	
	//remove pad
	if(rmpad<BLOCKSIZE && rmpad>0)
	{
	for(int  i=0;i<bufsize-rmpad-1;i++){ dout[i] = deciphered[i]; }	
	*resultlen=bufsize-rmpad;
	}
	else
	{
		for (i = 0;i<bufsize;i++)
		{
		dout[i]=deciphered[i];
		}
		*resultlen=bufsize;
	}

	return (void*)dout;
}
