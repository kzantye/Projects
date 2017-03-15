#include <stdio.h>
#include <stdlib.h>

void prompt(int r){
	char buf[100 + r];

	gets(buf);
	printf("You entered: %s\n", buf);

}

int main(int argc, char** argv){
	if (argc != 2) {
		printf("Usage: ./exec random_integer\n");
		return -1;
	}

	int r = atoi(argv[1]);
	prompt(r);
	return 0;
}

void target(){
	printf("You just got pwned!\n");
	exit(0);
}


