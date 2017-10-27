/*************************************************************************
	> File Name: lock_type.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月07日 18时08分09秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

int main(int argc, char *argv[])
{
    pthread_mutex_t  mutex;
    if(argc < 2)
    {
        printf("-usage: %s [error|normal|recursive]\n",argv[1]);
        exit(1);
    }
    //定义互斥锁属性
    pthread_mutexattr_t mutexattr;
    pthread_mutexattr_init(&mutexattr);

    if(strcmp(argv[1], "error"))
    {
        pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_ERRORCHECK);
    }
    else if(strcmp(argv[1], "normal"))
    {
        pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_NORMAL);
    }
    else if(strcmp(argv[1], "recursive"))
    {
        pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE);
    }

    pthread_mutex_init(&mutex, &mutexattr);
    //上锁两次
    if(pthread_mutex_lock(&mutex)!= 0)
    {
        perror("lock failed!");
        exit(1);
    }
    else
    {
        printf("lock success\n");
    }
    if(pthread_mutex_lock(&mutex)!= 0)
    {
        perror("lock failed!");
        exit(1);
    }
    else
    {
        printf("lock success\n");
    }
    //释放锁
    pthread_mutex_unlock(&mutex);
    pthread_mutex_unlock(&mutex);

    pthread_mutexattr_destroy(&mutexattr);
    pthread_mutex_destroy(&mutex);

    return 0;
}
