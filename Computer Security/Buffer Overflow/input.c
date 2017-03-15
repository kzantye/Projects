#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
int i,n=atoi(argv[2]);
char *hack=(char*)malloc(sizeof(char));
for(i=0;i<n;i++)
hack[i]='A';
fputs(hack, stdout);
fputs(argv[1], stdout);
return 0;
}

