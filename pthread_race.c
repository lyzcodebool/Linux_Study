/*************************************************************************
	> File Name: pthread_race.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月03日 07时00分14秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<pthread.h>
//使用线程模拟龟兔赛跑
//
void*  th_fd(void *arg)//通用指针
{
    int destance = (int)arg;
    int i ;
    for(int i =1; i < destance; ++i)
    {
        printf("%lx run %d\n", pthread_self(), i);
        int time = (int)(drand48()*100000);
        usleep(time);//微秒
    }
    return (void *)0;
}
int main(void)
{
    pthread_t robbit, turtle;//定义线程标识符
    int err;

    //创建robbit线程
    if((err = pthread_create(&robbit, NULL, th_fd, (void *)50)) != 0)
    {
        perror("pthread_create robbit error");
        exit(1);
    }
    //创建turtle线程
    if((err = pthread_create(&turtle, NULL, th_fd, (void *)50)) != 0)
    {
        perror("pthread_create turtle error");
        exit(1);
    }

    //主控线程的id
    //为了保证两个子线程正常运行，得让主控线程阻塞，等待子线程运行。
    //方法1：
    //sleep(10);
    //方法2：调用join的线程会自动阻塞，谁调用谁阻塞，等待传入的线程标识符结束，才可能再次运行。
    pthread_join(robbit, NULL);
    pthread_join(turtle, NULL);
    printf("control thread id = %lx\n", pthread_self());


}
