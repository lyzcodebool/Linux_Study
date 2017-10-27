/*************************************************************************
	> File Name: account.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月05日 20时45分06秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include "account.h"
#include<malloc.h>
#include<string.h>

//创建账户
extern Account* creat_account(int code, int balance)
{
    Account* a = (Account *)malloc(sizeof(Account));
    assert(a != NULL);

    a->code = code;
    a->balance = balance;
    return a;
}

//销毁账户
extern void destory_account(Account* account)
{
    assert(account != NULL);
    free(account);
}
//存款
extern double withdraw(Account* account, double amt)
{
    if(amt < 0 || amt > account->balance)
    {
        return 0.0;
    }
    double balance = account->balance;//模拟银行取款，先取出来
    sleep(1);//延迟1s
    balance -= amt;
    account->balance = balance;//把取款后的余额存入账户
    return amt;
}
//取款
extern double deposit(Account* account, double amt)
{
    assert(account != NULL)
    if(amt < 0)
    {
        return 0.0;
    }
    double balance = account->balance;
    sleep(1);
    balance += amt;
    account->balance = balance;
    return amt;
}
double get_balance(Account *account)
{
    assert(account != NULL);
    double balance = account->balance;
    return balance;
}

