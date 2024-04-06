#include "coroutine.h"
#include <ucontext.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

struct _coroutine
{
    ucontext_t *node;
    ucontext_t *head;
    int stack_size;
};

ucontext_t* _new_node(void(*uc_func)(void*), void* args, int size)
{
    ucontext_t* uc = (ucontext_t*)malloc(sizeof(ucontext_t));
    if(!uc) return NULL;
    getcontext(uc);
    uc->uc_link = NULL;
    uc->uc_stack.ss_sp = malloc(size);
    uc->uc_stack.ss_size = size;
    makecontext(uc, (void(*)(void))uc_func, 1, args);

    return uc;
}

coroutine_t* coroutine_create(int stack_size)
{
    coroutine_t* cor = (coroutine_t*)malloc(sizeof(coroutine_t));
    if(!cor) return NULL;
    cor->head = _new_node(NULL, NULL, stack_size);
    cor->node = cor->head;
    cor->node->uc_link = cor->head;
    cor->stack_size = stack_size;

    return cor;
}

int coroutine_add(coroutine_t* cor, void(*func)(void*), void* args)
{
    ucontext_t *node=NULL;
    if(!cor || !func) return -1;

    node = _new_node(func, args, cor->stack_size);
	node->uc_link = cor->head->uc_link;
	cor->head->uc_link = node;

    return 0;
}

void coroutine_remove(coroutine_t* cor)
{
    int flag=1;
    ucontext_t *prev=cor->head, *tmp = cor->head->uc_link;

    while(tmp != cor->head) {
        if(tmp == cor->node) {
            prev->uc_link = cor->node->uc_link;
            flag=0;
            cor->node = prev->uc_link;
            break;
        }
        tmp = tmp->uc_link;
        prev = prev->uc_link;
    }

    if(flag && cor->node==cor->head){
        tmp = cor->head;
        prev->uc_link = cor->node->uc_link;
        cor->node = prev->uc_link;
        cor->head = cor->node;
    }
    free(tmp->uc_stack.ss_sp);
    free(tmp);
    setcontext(cor->node);
}

void coroutine_yield(coroutine_t* cor)
{
    ucontext_t *tmp = cor->node;
    cor->node = cor->node->uc_link;
    swapcontext(tmp, tmp->uc_link);
}

void coroutine_destory(coroutine_t* cor)
{
    ucontext_t *node, *tmp;
    
    if(!cor) return;
    do{
        if(!cor->head) break;
        node= cor->head->uc_link;

        while(node != cor->head){
            tmp = node;
            node = node->uc_link;
            free(tmp->uc_stack.ss_sp);
            free(tmp);
        }
        tmp = cor->head;
        free(tmp->uc_stack.ss_sp);
        free(tmp);
    }while(0U);

    free(cor);
}

#ifdef __cplusplus
}
#endif
