/*************************************************************************
	> File Name: cmd_pipe.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月24日 22时35分39秒 PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

char *cmd1[3] = {"/bin/cat", "/etc/passwd", NULL};
char *cmd2[3] = {"/bin/grep", "root", NULL};

int main(void)
{
    int fd[2];
    if(pipe(fd)< 0){
        perror("pipe error");
        exit(1);
    }
    int i = 0; 
    pid_t pid;
    for(; i < 2; ++i){
        //创建进程扇
        pid = fork();
        if(pid < 0){
            perror("fork error");
            exit(1);
        }else if(pid == 0){//子进程
            if(i == 0){
                //第一个子进程负责向管道内写入数据
                //关闭读端
                
                /*
                *将标准输出重定向到管道的写端
                *下面命令的结果是写入管道中，而不是输出到
                *屏幕上
                */
                close(fd[0]);

                if(dup2(fd[1], STDOUT_FILENO) != STDOUT_FILENO){
                    perror("DUP2 error");
                    exit(1);
                }
                //调用exec函数执行cat命令
                if(execvp(cmd1[0], cmd2)< 0){
                    perror("execvp error");
                    exit(1);
                }
                break;
            }
            if(i == 1){
                //第二个子进程负责从管道读出数据
                //关闭写端
                close(fd[1]);

                if(dup2(fd[0],  STDIN_FILENO) != STDIN_FILENO){
                    perror("dup2 stdin error");
                    exit(1);
                }
                close(fd[0]);
                //调用exec函数执行grep
                if(execvp(cmd2[0], cmd2)< 0){
                    perror("execvp error");
                    exit(1);
                }
                break;
            }
        }else{//父进程
              if(i == 1){
                  //父进程要等到子进程全都创建完才回收
                  close(fd[0]);
                  close(fd[1]);

                  wait(0);
                  wait(0);
              }
        }
    }

    exit(0);
}
