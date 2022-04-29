//
// Created by huan.yang on 2022-04-28.
//

#include <cstdlib>
#include "../locker/locker.cpp"

using halosky::locker::synchronized;
using halosky::locker::condition;

template<class T>
class block_queue {
public:
    block_queue(int max_size = 100) {

        if(max_size <= 0){
            exit(-1);
        }
        m_max_size = max_size;
        m_array = new T[max_size];
        m_size = 0;
        m_front = -1;
        m_back = -1;
    }


    void clear(){
        syn.lock();
        m_size = 0;
        m_front = -1;
        m_back = -1;
        syn.unlock();
    }

    ~block_queue(){
        syn.lock();
        if (m_array != NULL){
            delete [] m_array;
        }
        syn.unlock();
    }

    bool full(){
        bool r = false;
        syn.lock();
        if(m_size >= m_max_size){
            r = true;
        }
        syn.unlock();
        return r;
    }

    bool empty(){
        bool r = false;
        syn.lock();
        if(m_size == 0){
            r = true;
        }
        syn.unlock();
        return r;
    }

    bool get_front(T& val){
        syn.lock();
        if(m_size == 0){
            return false;
        }
        val = m_array[m_front];
        syn.unlock();
        return true;
    }

    bool get_back(T& val){
        syn.lock();
        if(m_size == 0){
            return false;
        }
        val = m_array[m_back];
        syn.unlock();
        return true;
    }

    int size(){
        int size = 0;
        syn.lock();
        size = m_size;
        syn.unlock();
        return size;
    }

    int max_size(){
        int max_size = 0;
        syn.lock();
        max_size = m_max_size;
        syn.unlock();
        return max_size;
    }


    bool push(T& t){

        syn.lock();
        if(m_size >= m_max_size){
            con.broadcast();
            syn.unlock();
            return false;
        }

        m_back = (m_back + 1) % m_max_size;
        m_array[m_back] = t;

        m_size ++;

        con.broadcast();
        syn.unlock();
        return true;
    }


    bool pop(T& t){
        syn.lock();

        while (m_size <= 0){
            if(!con.wait(syn.get())){
                syn.unlock();
                return false;
            }
        }

        t = m_array[m_front];
        m_front = (m_front + 1) % m_max_size;
        m_size --;
        syn.unlock();
        return true;
    }



private:
    synchronized syn;
    condition con;

    T *m_array;
    int m_size;
    int m_max_size;
    int m_front;
    int m_back;
};