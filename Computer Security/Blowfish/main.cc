#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "fscrypt.h"

int main()
{
  char s[] = "Use the openssl library (www.openssl.org) to write the following two functions for encryption and decryption in a file fscrypt.cc.You should use block cipher method blowfish for encryption. Blowfish uses 64-bit blocks and typically 128-bit keysBoth functions allocate the result buffer of at least the required size (using new()) and return a pointer to it. Both functions also return the number of valid bytes in the result buffer in result";
  unsigned char *outbuf, *recvbuf;
  char pass[] = "top secret key";
  int len = 0;
  int recvlen = 0;
  outbuf = (unsigned char *) fs_encrypt((void *) s, strlen(s)+1, pass, &len);
  printf("%s %d\n", "length after encryption = ", len);

  int i = 0;
  printf("Ciphertext = ");
  for (i = 0; i < len; i++)
  printf("%02x", outbuf[i]);
  printf("\n");

  recvbuf  = (unsigned char *) fs_decrypt((void *) outbuf, len, pass, &recvlen);
  assert(memcmp(s, recvbuf, recvlen) == 0);
  assert(recvlen == (strlen(s) + 1));
  printf("Plaintext = %s\n", recvbuf);
}

