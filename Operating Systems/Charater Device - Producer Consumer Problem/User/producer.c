#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

int counter = 0;


static char *gen_string(size_t size)
{
	size_t i;
	    const char str[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *input = malloc(sizeof(char) * (size + 1));
   
        for (i = 0; i < size; i++) {
            int key = rand() % (int) (sizeof(str) - 1);
            input[i] = str[key];
        }
        input[size] = '\0';

    return input;
}

int main() {
   
    int count = 5;
     int fd = open("/dev/mydevice", O_WRONLY);
    if(fd <0){
        printf("Can't open the device.\n");
        exit(1);
    }	
    else{
	printf("Device has been successfully opened.\n");
    }
    while(1) {
        char* str =gen_string(count);
        counter++;
        int ret = write(fd, str, strlen(str));
        if(ret <0){
            printf("Can't write to device.\n");
	       exit(1);
        } 
        else {
  	    printf("String written to device: %s\n", str);
        }
    }
    close(fd);
return 0;
}


