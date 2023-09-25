#ifndef __COROUTINE_H__
#define __COROUTINE_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _coroutine coroutine_t;

/**
 * @brief 创建协程
 * @param stack_size 每个协程栈大小
 * @return 创建的句柄
*/
coroutine_t* coroutine_create(int stack_size);

/**
 * @brief 添加一个协程处理函数
 * @param cor 协程管理句柄
 * @param func 协程函数入口
 * @param args 传入的参数
 * @return -1:err 0:ok
*/
int coroutine_add(coroutine_t* cor, void(*func)(void*), void* args);

/**
 * @brief 从管理句柄中移除某个协程处理函数
 * @param cor 协程管理句柄
 * @return none
*/
void coroutine_remove(coroutine_t* cor);

/**
 * @brief 调度协程,由用户决定某个时机进行调度
 * @param cor 协程管理句柄
 * @return none
*/
void coroutine_yield(coroutine_t* cor);

/**
 * @brief 销毁协程
 * @param cor 协程管理句柄
 * @return none
*/
void coroutine_destory(coroutine_t* cor);

#ifdef __cplusplus
}
#endif

#endif // !__COROUTINE_H__
