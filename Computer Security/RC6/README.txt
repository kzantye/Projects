Auther:— Kunal Zantye
email: kzantye1@binghamton.edu

The code was tested on bingsuns
/u0/users/5/kzantye1/Security/p1-kzantye1/


Make File has been created. 
Command: make
Update makefile according to Text Cases Input/Output for Encryption/Decryption.
MakeFile 
--> Compiles the C Code (RC6.C)
--> Runs the Code (Eg: ./rc6 input.txt output.txt)

The input file is according to the files given by you in the mail.
The name of the input file should be input.txt
The Code reads the first word(Plaintext or Ciphertext) and identifies whether it is an encryption or decryption.
Note:The word “ Plaintext” should start with capital letter ‘P’. 
	Plaintext or Usertext or Ciphertext should follow by colon [ : ] 

*****************************************************
Input Format of the Encryption File:
*****************************************************
Plaintext: 
Userkey: 
*****************************************************

*****************************************************
Input Format of the Decryption File:
*****************************************************
Cipher text: 
Userkey: 
*****************************************************
ALGORITHM

Functions: 
For rc6 
w=32 
r=20
P32 B7E15163(magic constant
Q32 9E3779B9
1. KeySchedule
INPUT: UserKey[], b bytes
OUTPUT: w-bit round keys S[]
-> Compute L and initialise S
-> do the Mixing of S


2.Encryption:
INPUT: PlainText[A,B,C,D]
OUTPUT: Cipher Text [A,B,C,D]


3. Decryption
INPUT:Cipher Text [A,B,C,D]
OUTPUT:PlainText[A,B,C,D]

4.Functions to remove little endian
Output: Swaped MSB and LSB

