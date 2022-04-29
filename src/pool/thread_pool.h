//
// Created by huan.yang on 2022-04-29.
//

#ifndef MIN_WEB_THREAD_POOL_H
#define MIN_WEB_THREAD_POOL_H

#include <pthread.h>
#include <list>
#include "../locker/locker.cpp"

using namespace halosky::locker;

namespace halosky {
    namespace pool {

        template<class T>
        class ThreadPoll {

        public:
            ThreadPoll(int actor_model, int thread_size = 8, int max_request = 1024);

            ~ThreadPoll();

            bool append(T *request, int state);

            bool append_p(T *request);

        private:
            static void* worker(void *args);
            void run();


            // 线程池中的线程数
            int m_thread_size;
            // 请求队列中允许的最大请求数
            int m_max_thread_size;
            // 描述线程池的数组，其大小为m_thread_size
            pthread_t *m_threads;
            // 请求队列
            std::list<T *> m_work_queue;
            // 互斥锁
            synchronized syn;
            sem s;
            condition con;
            // 模式切换
            int m_actor_model;
        };

    }
}


#endif //MIN_WEB_THREAD_POOL_H
