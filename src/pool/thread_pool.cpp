//
// Created by huan.yang on 2022-04-29.
//
#include "thread_pool.h"
#include <exception>

using halosky::pool::ThreadPoll;

namespace halosky { namespace pool {

template<class T>
ThreadPoll<T>::ThreadPoll(int actor_model, int thread_size, int max_request) : m_actor_model(actor_model),m_thread_size(thread_size), m_max_thread_size(max_request) {
    if (thread_size <= 0 || max_request <= 0) {
        throw std::exception();
    }
    m_threads = new pthread_t[thread_size];
    if (!m_threads) {
        throw std::exception();
    }
    for (int i = 0; i < thread_size; i++) {
        if (pthread_create(m_threads + i,NULL,worker,this) != 0) {
            delete[] m_threads;
            throw std::exception();
        }
        if(pthread_detach(m_threads[i])){
            delete[] m_threads;
            throw std::exception();
        }
    }
}

template<class T>
ThreadPoll<T>::~ThreadPoll() {
    delete[] m_threads;
}


template<class T>
bool ThreadPoll<T>::append(T *request, int state){
    syn.lock();
    if(m_work_queue.size() >= m_max_thread_size){
        syn.unlock();
        return false;
    }

    request->m_state = state;
    m_work_queue.push_back(request);
    syn.unlock();
    m_work_queue.post();
    return true;
}

template<class T>
bool ThreadPoll<T>::append_p(T *request) {
    syn.lock();
    if(m_work_queue.size() >= m_max_thread_size){
        syn.unlock();
        return false;
    }

    m_work_queue.push_back(request);
    syn.unlock();
    m_work_queue.post();
    return true;
}

template<class T>
void* ThreadPoll<T>::worker(void *args) {
    ThreadPoll *pool = (ThreadPoll*) args;
    pool->run();
    return pool;
}

template<class T>
void ThreadPoll<T>::run(){
    while (true){
        s.wait();
        syn.lock();
        if(m_work_queue.empty()){
            syn.unlock();
            continue;
        }
        T *request = m_work_queue.front();
        m_work_queue.pop_front();
        syn.unlock();
        if(!request){
            continue;
        }

        // TODO PROCESSOR

    }
}


}}
