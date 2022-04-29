//
// Created by huan.yang on 2022-04-28.
//

    #ifndef MIN_WEB_LOCKER_H
#define MIN_WEB_LOCKER_H

#include <semaphore.h>
#include <exception>
#include <pthread.h>

namespace halosky {
    namespace locker {

        /**
         * 信号量
         */
        class sem {
        public:
            sem() {

                /**
                 * s: 信号量结构的指正
                 * pshard: 不为0时则在所有进程间共享，否则在所有线程间共享
                 */
                if (sem_init(&s, 0, 0) != 0) {
                    throw std::exception();
                }
            }

            sem(int init_num) {
                if (sem_init(&s, 0, init_num) != 0) {
                    throw std::exception();
                }
            }

            ~sem() {
                sem_destroy(&s);
            }


            bool wait() {
                return sem_wait(&s) == 0;
            }

            bool post() {
                return sem_wait(&s) == 0;
            }

        private:
            sem_t s;
        };

        /**
         * 同步锁
         */
        class synchronized {
        public:
            synchronized() {
                /**
                 * mutex: 互斥锁结构体
                 * mutexattr: 互斥锁属性
                 */
                if (pthread_mutex_init(&mutex, NULL) == 0) {
                    throw std::exception();
                }
            }
            ~synchronized() {
                pthread_mutex_destroy(&mutex);
            }
            bool lock() {
                return pthread_mutex_lock(&mutex) == 0;
            }
            bool unlock() {
                return pthread_mutex_unlock(&mutex) == 0;
            }
            pthread_mutex_t* get(){
                return &mutex;
            }
        private:
            pthread_mutex_t mutex;
        };


        /**
         * con:条件锁
         * cond_attr: 条件锁属性
         */
        class condition{

        public:
            condition(){
                if(pthread_cond_init(&con,NULL) != 0){
                    throw std::exception();
                }
            }
            ~condition(){
                pthread_cond_destroy(&con);
            }

            bool wait(pthread_mutex_t *m_mutex)
            {
                int ret = 0;
                ret = pthread_cond_wait(&con, m_mutex);
                return ret == 0;
            }
            bool timewait(pthread_mutex_t *m_mutex, struct timespec t)
            {
                int ret = pthread_cond_timedwait(&con, m_mutex, &t);
                return ret == 0;
            }
            bool signal()
            {
                return pthread_cond_signal(&con) == 0;
            }
            bool broadcast()
            {
                return pthread_cond_broadcast(&con) == 0;
            }
        private:
            pthread_cond_t con;
        };
    }
}


#endif //MIN_WEB_LOCKER_H
