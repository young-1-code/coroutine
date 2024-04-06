#include "coroutine.h"
#include <unistd.h>
#include <stdio.h>

coroutine_t* cor;

void ts1(void* args)
{
    /* while(1) */
    {
        printf("ts1 coroutine runing...\n");
        sleep(1);
        coroutine_yield(cor); /* 调度 */
    }
    printf("ts1 finish...\n");
    coroutine_remove(cor);    /* 协程结束后,移除对应节点 */
}

void ts2(void* args)
{
    while(1)
    {
        printf("ts2 coroutine runing...\n");
        sleep(1);
        coroutine_yield(cor); /* 调度 */
    }
    coroutine_remove(cor);
}

void ts3(void* args)
{
    while(1)
    {
        printf("ts3 coroutine runing...\n");
        sleep(1);
        coroutine_yield(cor); /* 调度 */
    }
    coroutine_remove(cor);
}


int main(void)
{
    cor = coroutine_create(16384);  /* 创建协程 */
    
    coroutine_add(cor, ts1, NULL); /* 添加协程函数 */
    coroutine_add(cor, ts2, NULL);
    coroutine_add(cor, ts3, NULL);

    while(1)
    {
        printf("main coroutine runing...\n");
        coroutine_yield(cor); /* 调度 */
    }

    coroutine_destory(cor);   /* 释放资源 */

    return 0;
}
