#ifndef __COROUTINE_H__
#define __COROUTINE_H__


typedef struct _coroutine coroutine_t;

coroutine_t* coroutine_create(int stack_size);
int coroutine_add(coroutine_t* cor, void(*func)(void*), void* args);
void coroutine_remove(coroutine_t* cor);
void coroutine_yield(coroutine_t* cor);
void coroutine_destory(coroutine_t* cor);


#endif // !__COROUTINE_H__
