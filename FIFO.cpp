#include "FIFO.h"
#include <iostream>
#include <chrono>
using namespace std;

FIFOCache::FIFOCache(int size):cacheSize(size) {
	cout << "FIFO Cache of size " << size << " created." << endl;
	DLL = make_shared<DoublyLinkedList<CacheDataPtr> >();
}

void FIFOCache::deleteCacheEntry(ListNode<CacheDataPtr> * node) {
	P.remove(node->val);
	M.erase(node->val->key);
	DLL->deleteNode(node);
}

void FIFOCache::removeExpiredEntry() {
	if (P.size() == 0) return;
	int time = (int)chrono::duration_cast<chrono::seconds>(chrono::system_clock::now().time_since_epoch()).count();
	while (P.size() && (P.top()->ttl < time)) {
		string key = P.top()->key;
		P.pop();
		deleteKey(key);
	}
}

void FIFOCache::print() {
	ListNode<CacheDataPtr> * cur = DLL->get_front();
	while (cur) {
		cout << cur->val->key << ":" << cur->val->value << " -> ";
		cur = cur->next;
	}
	cout << "NULL" << endl;
}

string FIFOCache::get(string key){
	removeExpiredEntry();
	string value;
	auto itr = M.find(key);
	if (itr != M.end()) {
		value = itr->second->val->value;
	} else {
        return key + " is not present in the cache!!\n";
    }
	print();
	return value;
}

void FIFOCache::put(string key, string value, int ttl) {
	removeExpiredEntry();
	auto itr = M.find(key);
	if (ttl < 0) {
		ttl = INT_MAX;
	}
	else {
		ttl += (int)chrono::duration_cast<chrono::seconds>(chrono::system_clock::now().time_since_epoch()).count();
	}
	if (itr == M.end()) {
		auto node = DLL->addNode(make_shared<CacheData>(key, value, ttl));
		M.insert(make_pair(key, node));
		curCnt++;
		if(curCnt > cacheSize){
			deleteCacheEntry(DLL->get_front());
			curCnt--;
		}
		P.push(node->val);
	}
	else {
		auto node = itr->second;
		node->val->value = value;
		node->val->ttl = ttl;
		P.remove(node->val);
		P.push(node->val);
	}
	print();
}

void FIFOCache::deleteKey(string key) {
	auto itr = M.find(key);
	if (itr != M.end()) {
		deleteCacheEntry(itr->second);
	}
	curCnt--;
	print();
}

void FIFOCache::clear() {
	M.clear();
	DLL->clear();
	curCnt = 0;
}

FIFOCache::~FIFOCache() {
	clear();
}
