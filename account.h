/*************************************************************************
	> File Name: account.h
	> Author: 
	> Mail: 
	> Created Time: 2017年10月05日 20时34分31秒 PDT
 ************************************************************************/

#ifndef _ACCOUNT_H
#define _ACCOUNT_H
typedef struct{
    int code; //银行帐户的号码
    double balance;//银行余额
    /*
    * 定义一把互斥锁，用来对多线程操作的银行帐户进行保护
    * 建议呼出锁用来锁定一个账户(共享资源)，
    * 和账户绑定在一起，进来能够不要设置成全局变量，否则可能出现一把所锁
    * 几百个账户
    */
    //pthread_mutex_t mutex;
    //定义一把读写锁
    pthread_rwlock_t rwlock;
}Account;

//创建账户
extern Account* creat_account(int code, int balance);
//销毁账户
extern void destroy_account(Account* account);
//存款
extern double withdraw(Account* account, double amt);
//取款
extern double deposit(Account* account, double amt);

extern double get_balance(Account* account);
#include<stdio.h>
#include<stdlib.h>
#include "account.h"
#include<malloc.h>
#include<string.h>
#include<assert.h>

//创建账户
extern Account* creat_account(int code, int balance)
{
    Account* a = (Account *)malloc(sizeof(Account));
    //assert(a != NULL);

    a->code = code;
    a->balance = balance;
    //pthread_mutex_init(&mutex);
    pthread_rwlock_init(&a->rwlock, NULL);//注意这里是两个参数
    return a;
}

//销毁账户
extern void destroy_account(Account* account)
{
    assert(account != NULL);
    //销毁读写锁
    pthread_rwlock_destroy(&account->rwlock);
    free(account);
}
//存款
extern double withdraw(Account* account, double amt)
{
    assert(account != NULL);
    //对共享资源进行操作的临界区
    //pthread_mutex_lock(&account->mutex);
    //写写锁
    pthread_rwlock_wrlock(&account->rwlock);
    //对共享资源上锁
    if(amt < 0 || amt > account->balance)
    {
        //释放锁
        //pthread_mutex_unlock(&account->mutex);
        pthread_rwlock_unlock(&account->rwlock);
        return 0.0;
    }
    double balance = account->balance;//模拟银行取款，先取出来
    sleep(1);//延迟1s
    balance -= amt;
    account->balance = balance;//把取款后的余额存入账户
    //释放锁
    //pthread_mutex_unlock(&account->mutex);
    //释放写锁
    pthread_rwlock_unlock(&account->rwlock);
    
    return amt;
}
//取款
extern double deposit(Account* account, double amt)
{
    assert(account != NULL);
    //pthread_mutex_lock(&account->mutex);
    pthread_rwlock_unlock(&account->rwlock);
    if(amt < 0)
    {
        //pthread_mutex_unlock(&account->mutex);
        pthread_rwlock_unlock(&account->rwlock);
        return 0.0;
    }
    double balance = account->balance;
    sleep(1);
    balance += amt;
    account->balance = balance;
    //pthread_mutex_unlock(&account->mutex);
    pthread_rwlock_unlock(&account->rwlock);
    return amt;
}
double get_balance(Account *account)
{
    assert(account != NULL);
    //pthread_mutex_lock(&account->mutex);
    pthread_rwlock_rdlock(&account->rwlock);
    double balance = account->balance;
    //pthread_mutex_unlock(&account->mutex);
    pthread_rwlock_unlock(&account->rwlock);
    return balance;
}
#endif
