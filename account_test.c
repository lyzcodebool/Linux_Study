/*************************************************************************
	> File Name: account_test.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月05日 23时37分22秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>
#include"account.h"

typedef struct{
    //操作者信息
    char name[20];
    Account* account;
    double amt;
}OperArg;

//定义取款操作的线程运行函数
void *withdraw_fn(void *arg)
{
    OperArg* oa = (OperArg *)arg;
    double amt = withdraw(oa->account, oa->amt);

    printf("%8s(0x%lx) withdraw %f from %d\n", oa->name, pthread_self(), amt, oa->account->code);
    return (void *)0;
}
//定义存款操作的线程运行函数
void *deposit_fn(void *arg)
{
    OperArg* oa = (OperArg *)arg;
    double amt = deposit(oa->account, oa->amt);

    printf("%8s(0x%lx) deposit %f from %d\n", oa->name, pthread_self(), amt, oa->account->code);
    return (void *)0;

}

//定义检查银行账户的线程运行函数
void *check_fn(void *arg)
{
    
}

int main(void)
{
    int err;
    pthread_t boy, girl;
    Account *a = creat_account(100001, 10000);

    OperArg o1, o2;
    //操作者boy信息初始化
    strcpy(o1.name, "boy");
    o1.account = a;
    o1.amt = 10000;
    //操作者girl信息初始化
    strcpy(o2.name, "girl");
    o2.account = a;
    o2.amt = 10000;
    //启动两个子线程同时操作同一个银行帐户
    if((err = pthread_create(&boy, NULL, withdraw_fn, (void *)&o1)) != 0)
    {
        perror("boy pthread create error");
        exit(1);
    }
    if((err = pthread_create(&girl, NULL, withdraw_fn, (void *)&o2)) != 0)
    {
        perror("girl pthread create error");
        exit(1);
    }
    pthread_join(boy, NULL);
    pthread_join(girl, NULL);

    printf("account balance = %lf\n", get_balance(a));
    destroy_account(a);
}
