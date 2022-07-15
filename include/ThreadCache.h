//
// Created by 10702 on 2022/7/14.
//

#ifndef GSZ_MEMORYPOOL_THREADCACHE_H
#define GSZ_MEMORYPOOL_THREADCACHE_H
#include "Common.h"

class ThreadCache
{
public:
    //申请内存对象
    void* Allocate(size_t size);

    //释放内存对象
    void Deallocate(void* ptr, size_t size);

    //从中心缓存获取对象
    void* FetchFromCentralCache(size_t index, size_t size);

    //释放对象导致链表过长，回收内存到中心缓存
    void ListTooLong(FreeList& list, size_t size);
private:
    FreeList _freeLists[N_FREE_LISTS]; //哈希桶
};

//TLS - Thread Local Storage
static thread_local ThreadCache* pTLSThreadCache = nullptr;

#endif //GSZ_MEMORYPOOL_THREADCACHE_H
