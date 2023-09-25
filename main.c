#include "coroutine.h"
#include <unistd.h>
#include <stdio.h>

coroutine_t* cor;

void ts1(void* args)
{
    // while(1)
    {
        printf("ts1111\n");
        sleep(1);
        coroutine_yield(cor);
    }
    coroutine_remove(cor);

}

void ts2(void* args)
{
    // while(1)
    {
        printf("ts2222\n");
        sleep(1);
        coroutine_yield(cor);
    }
    coroutine_remove(cor);
}

void ts3(void* args)
{
    // while(1)
    {
        printf("ts3333\n");
        sleep(1);
        coroutine_yield(cor);
    }
    coroutine_remove(cor);
}


int main(void)
{
    cor = coroutine_create(2048);
    
    coroutine_add(cor, ts1, NULL);
    coroutine_add(cor, ts2, NULL);
    coroutine_add(cor, ts3, NULL);

    while(1)
    {
        printf("main func...\n");
        coroutine_yield(cor);
    }
    // coroutine_remove(cor);
    coroutine_destory(cor);

    printf("-----finish...\n");
    return 0;
}