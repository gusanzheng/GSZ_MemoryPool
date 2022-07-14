//
// Created by 10702 on 2022/7/14.
//

#ifndef GSZ_MEMORYPOOL_GSZLOCK_H
#define GSZ_MEMORYPOOL_GSZLOCK_H
#include <exception>
#include <pthread.h>

class MutexLock
{
public:
    MutexLock() {
        if (pthread_mutex_init(&m_mutex, nullptr) != 0)
            throw std::exception();
    }

    ~MutexLock() {
        pthread_mutex_destroy(&m_mutex);
    }

    bool lock() {
        if (pthread_mutex_lock(&m_mutex) != 0)
            return false;
        return true;
    }

    bool unlock() {
        if (pthread_mutex_unlock(&m_mutex) != 0)
            return false;
        return true;
    }

    int tryLock() {
        int state = pthread_mutex_trylock(&m_mutex);
        if (state == EBUSY) {
            return 1;
        }
        if (state != 0) {
            return -1;
        }
        return 0;
    }

    pthread_mutex_t* get(){

        return &m_mutex;
    }

    //禁止自动生成拷贝构造、拷贝赋值、移动构造、移动赋值
    MutexLock(const MutexLock&) = delete;
    MutexLock& operator=(const MutexLock&) = delete;
    MutexLock(MutexLock&&) = delete;
    MutexLock& operator=(MutexLock&&) = delete;
private:
    pthread_mutex_t m_mutex;
};
class SpinLock {
public:
    SpinLock() {
        if (pthread_spin_init(&m_spin, PTHREAD_PROCESS_PRIVATE) != 0)
            throw std::exception();
    }

    ~SpinLock() {
        pthread_spin_destroy(&m_spin);
    }

    bool lock(){
        if (pthread_spin_lock(&m_spin) != 0)
            return false;
        return true;
    }
    bool unlock() {
        if (pthread_spin_unlock(&m_spin) != 0)
            return false;
        return true;
    }
    int tryLock() {
        int state = pthread_spin_trylock(&m_spin);
        if (state == EBUSY) {
            return 1;
        }
        if (state != 0) {
            return -1;
        }
        return 0;
    }

    pthread_spinlock_t* get() {
        return &m_spin;
    }

    //禁止自动生成拷贝构造、拷贝赋值、移动构造、移动赋值
    SpinLock(const SpinLock&) = delete;
    SpinLock(SpinLock&&) = delete;
    SpinLock& operator=(const SpinLock&) = delete;
    SpinLock& operator=(SpinLock&&) = delete;
private:
    pthread_spinlock_t m_spin;
};
class RwLock {
public:
    RwLock() {
        if (pthread_rwlock_init(&m_rwlock, nullptr) != 0)
            throw std::exception();
    }

    ~RwLock() {
        pthread_rwlock_destroy(&m_rwlock);
    }

    bool rdLock() {
        if (pthread_rwlock_rdlock(&m_rwlock) != 0)
            return false;
        return true;
    }

    bool wrLock() {
        if (pthread_rwlock_wrlock(&m_rwlock) != 0)
            return false;
        return true;
    }

    bool unlock()
    {
        if (pthread_rwlock_unlock(&m_rwlock) != 0)
            return false;
        return true;
    }

    int tryRdLock()
    {
        int state = pthread_rwlock_tryrdlock(&m_rwlock);
        if (state == EBUSY) {
            return 1;
        }
        if (state != 0) {
            return -1;
        }
        return 0;
    }

    int tryWrLock() {
        int state = pthread_rwlock_trywrlock(&m_rwlock);
        if (state == EBUSY) {
            return 1;
        }
        if (state != 0) {
            return -1;
        }
        return 0;
    }

    pthread_rwlock_t* get() {
        return &m_rwlock;
    }

    //禁止自动生成拷贝构造、拷贝赋值、移动构造、移动赋值
    RwLock(const RwLock&) = delete;
    RwLock(RwLock&&) = delete;
    RwLock& operator=(const RwLock&) = delete;
    RwLock& operator=(RwLock&&) = delete;
private:
    pthread_rwlock_t  m_rwlock;
};
#endif //GSZ_MEMORYPOOL_GSZLOCK_H
