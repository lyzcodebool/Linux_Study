/*************************************************************************
	> File Name: fifo_read.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月24日 01时32分51秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
    printf("open fifo read...\n");
    //打开命名管道
//    int fd = open(argv[1], O_RDONLY);
    //阻塞版本
    int fd = open(argv[1], O_RDONLY| O_NONBLOCK);
    if(fd < 0){
        perror("open error");
        exit(1);
    }else{
        printf("open file %d success!\n", fd);
    }

    //从命名管道中读取数据
    char buf[512];
    memset(buf, 0, sizeof(buf));
    while(read(fd, buf, sizeof(buf))< 0){
        perror("read error");
    }
    printf("%s\n", buf);
    close(fd);
    exit(0);
}
