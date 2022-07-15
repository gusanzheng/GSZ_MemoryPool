//
// Created by 10702 on 2022/7/14.
//

#ifndef GSZ_MEMORYPOOL_CENTRALCACHE_H
#define GSZ_MEMORYPOOL_CENTRALCACHE_H
#include "Common.h"

//单例模式
class CentralCache
{
public:
    //提供一个全局访问点
    static CentralCache* GetInstance()
    {
        return &_sInst;
    }

    //从central cache获取一定数量的对象给thread cache
    size_t FetchRangeObj(void*& start, void*& end, size_t n, size_t size);

    //获取一个非空的span
    static Span* GetOneSpan(SpanList& spanList, size_t size);

    //将一定数量的对象还给对应的span
    void ReleaseListToSpans(void* start, size_t size);
private:
    SpanList _spanLists[N_FREE_LISTS];
    static CentralCache _sInst; //只有一个单例

public:
    CentralCache() = default;
    ~CentralCache() = default;
    //禁止自动生成拷贝构造，拷贝赋值，移动构造，移动赋值
    CentralCache(const CentralCache&) = delete;
    CentralCache& operator=(const CentralCache&) = delete;
    CentralCache(CentralCache&&) = delete;
    CentralCache& operator=(CentralCache&&) = delete;

};
#endif //GSZ_MEMORYPOOL_CENTRALCACHE_H
