//
// Created by 10702 on 2022/7/14.
//

#ifndef GSZ_MEMORYPOOL_PAGECACHE_H
#define GSZ_MEMORYPOOL_PAGECACHE_H
#include "Common.h"
#include "PageMap.h"
#include "ObjectPool.h"


//单例模式
class PageCache
{
public:
    //提供一个全局访问点
    static PageCache* GetInstance()
    {
        return &_sInst;
    }
    //获取一个k页的span
    Span* NewSpan(size_t k);

    //获取从对象到span的映射
    Span* MapObjectToSpan(void* obj);

    //释放空闲的span回到PageCache，并合并相邻的span
    void ReleaseSpanToPageCache(Span* span);

    std::mutex _pageMtx; //大锁
private:
    SpanList _spanLists[N_PAGES];
    //std::unordered_map<PAGE_ID, Span*> _idSpanMap;
    TCMalloc_PageMap1<32 - PAGE_SHIFT> _idSpanMap;

    ObjectPool<Span> _spanPool;

    PageCache() //构造函数私有
    {}
    PageCache(const PageCache&) = delete; //防拷贝

    static PageCache _sInst;
};
#endif //GSZ_MEMORYPOOL_PAGECACHE_H
