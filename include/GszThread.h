//
// Created by 10702 on 2022/7/14.
//

#ifndef GSZ_MEMORYPOOL_GSZTHREAD_H
#define GSZ_MEMORYPOOL_GSZTHREAD_H
#include <pthread.h>

class Thread {
public:
    Thread() =default;
    void run(void* handle(void*), void* arg){
        if (pthread_create(&tid, nullptr, handle, arg) != 0){
            throw std::runtime_error("线程创建错误");
        }
        status = true;
    }
    bool join(){
        if (pthread_join(tid, nullptr) != 0){
            return false;
        }
        status = false;
        return true;
    }
    bool detach(){
        if (pthread_detach(tid) != 0){
            return false;
        }
        status = false;
        return true;
    }
    bool cancel(){
        if (pthread_cancel(tid) != 0){
            return false;
        }
        status = false;
        return true;
    }
    pthread_t getID() const{
        return tid;
    }
    bool getState() const{
        return status;
    }
    ~Thread()=default;
    Thread(const Thread&) = delete;
    Thread(Thread&&) = delete;
    Thread& operator=(const Thread&) = delete;
    Thread& operator=(Thread&&) = delete;
private:
    pthread_t tid;
    bool status;
};

#endif //GSZ_MEMORYPOOL_GSZTHREAD_H
