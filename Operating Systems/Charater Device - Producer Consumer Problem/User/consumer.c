#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

int main() {
    
    int count = 5;
    int fd = open("/dev/mydevice", O_RDONLY);
    if(fd <0){
        printf("Can't open the device.\n");
        exit(1);
    }	
    else{
	printf("Device has been successfully opened.\n");}
    size_t ret;
    char buffer[1000] = { 0 };
    memset(buffer, 0, 1000);
    while(1) {
        ret = read(fd, buffer, count);
	if(ret < 0) {
            printf("Can't read from device.\n");  
	    exit(1);
        } else {
            printf("String read from device: %s\n", buffer);
        }
    }
    close(fd);
    return 0;
}
