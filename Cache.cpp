#include "Cache.h"
#include "LRU.h"
#include "LFU.h"
#include "FIFO.h"

Cache::Cache(int size)
{
}

CachePtr Cache::getCache(CacheType c, int size) {
	if (c == LRU_CACHE)
		return make_shared<LRUCache>(size);
	else if(c == LFU_CACHE)
		return make_shared<LFUCache>(size);
    else 
        return make_shared<FIFOCache>(size);
}
