Name 		Email Address
Kunal Zantye   kzantye1@binghamton.edu
*************************************************************************************
Files provide:- main.cc fscrypt.h fscrypt.cc(cbc using ebc) fscrypt2.cc(using BF_cbc) 
*************************************************************************************
To execute the program, use below steps:
Step 1: Traverse to the path where the openssl libraries are present file is located.
	bingsuns2% cd Security/p2-kzantye1
	NOTE:Place your main.cc along with the provided fscrypt.cc,fscrypt2.cc(for BF_cbc) and fscrypt.h

Steps2: Command for execution on Mac machine
	gcc -isystem/Users/KUNAL/Desktop/openssl/compiled/include -isystem/Users/KUNAL/Desktop/openssl/compiled/lib main.cc fscrypt.cc -lcrypto -o ./exec

Step 3:To run
	./exec

*************************************************************************************
NOTE: I assume that the plain text never ends with a digit .
	To see the cipher text in hex ,please use outbuf and recvbuf as unsigned char
      The program works without this also;

The following plaintext was used for testing:
char s[] = "Use the openssl library (www.openssl.org) to write the following two functions for encryption and decryption in a file fscrypt.cc.You should use block cipher method blowfish for encryption. Blowfish uses 64-bit blocks and typically 128-bit keysBoth functions allocate the result buffer of at least the required size (using new()) and return a pointer to it. Both functions also return the number of valid bytes in the result buffer in resultl ";


