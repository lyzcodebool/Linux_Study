/*************************************************************************
	> File Name: pthread_race2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月03日 10时10分52秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
typedef struct 
{
    char name[20];
    int time;
    int start; 
    int end;
}RaceArg;

void* th_fd(void *arg)
{
    RaceArg *r = (RaceArg *)arg;//强制转换
    int i = r->start;
    for(; i < r->end; ++i)
    {
        printf("%s (%lx) run %d\n", r->name, pthread_self(), i);
        usleep(r->time);
    }
//    return (void *)0;
    //return (void*)(r->end - r->start);
    return (void *)r;
}

int main(void)
{
    int err;
    pthread_t rabbit, turtle;

    RaceArg r_a = {"rabbit", (int)drand48()*1000000000, 10, 50};
    RaceArg t_a = {"turtle", (int)drand48()*1000000000, 20, 60};

    if((err = pthread_create(&rabbit, NULL, th_fd, (void *)&r_a)) != 0)
    {
        perror("pthread_create rabbit error");
        exit(1);
    }
    if((err = pthread_create(&turtle, NULL, th_fd, (void *)&t_a)) != 0)
    {
        perror("pthread_create turtle error");
        exit(1);
    }

   // pthread_join(rabbit, NULL);
    //pthread_join(turtle, NULL);

    /*
    int result;
    pthread_join(rabbit, (void *)&result);
    printf("rabbit destance = %d\n",result);
    pthread_join(turtle, (void *)&result);
    printf("turtle destance = %d\n",result);
    */

    int *result;//这里必须要用指针，因为下面强转为结构体类型，如果定义成整形，内存不匹配，断错误。
    pthread_join(rabbit, (void **)&result);
    printf("rabbit destance = %d\n", ((RaceArg *)result)->end-((RaceArg *)result)->start);

    pthread_join(turtle, (void **)&result);
    printf("turtle destance = %d\n", (((RaceArg *)result)->end)-((RaceArg *)result)->start);

    printf("control thread %lx run finished!\n", pthread_self());
    return 0;
}
