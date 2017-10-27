/*************************************************************************
	> File Name: fifo_write.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月24日 01时42分11秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
    if(argc < 2){
        printf("-usage: %s fifo\n", argv[0]);
        exit(1);
    }
    printf("open fifo write ...\n");
    //打开命名管道
    int fd = open(argv[1], O_WRONLY);
    if(fd < 0){
        perror("open file error");
        exit(1);
    }else{
        printf("open write file %d success!\n", fd);
    }

    char *s = "1234567890";
    size_t size = strlen(s);
    if(write(fd, s, size) != size){
        perror("write error");
        exit(1);
    }

    close(fd);
    exit(0);
}
