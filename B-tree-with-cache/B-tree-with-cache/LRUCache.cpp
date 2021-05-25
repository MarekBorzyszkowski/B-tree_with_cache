#include "LRUCache.h"

LRUCache::LRUCache(int length)
	:cacheMaxLength(length),
	currCacheLength(0),
	firstElem(nullptr){}

void LRUCache::pushBack(int value) {
	if (currCacheLength == 0) {
		firstElem = new ListNode(value);
		currCacheLength++;
	}
	else if (currCacheLength < cacheMaxLength) {
		ListNode* pomNode = firstElem;
		while (pomNode->next != nullptr) {
			pomNode = pomNode->next;
		}
		pomNode->next = new ListNode(value);
		currCacheLength++;
	}
}

void LRUCache::popFront() {
	if (currCacheLength > 1) {
		ListNode* pomNode = firstElem->next;
		delete firstElem;
		firstElem = pomNode;
		currCacheLength--;
	}
	else if (currCacheLength == 1) {
		delete firstElem;
		firstElem = nullptr;
		currCacheLength--;
	}
}

void LRUCache::popNodeToBack(ListNode* nodeBefore) {
	ListNode* result = nodeBefore->next;
	nodeBefore->next = result->next;
	currCacheLength--;
	pushBack(result->value);
}

bool LRUCache::search(int value) {
	if (currCacheLength > 1) {
		ListNode* pomNode = firstElem;
		if (firstElem->value == value) {
			firstElem = firstElem->next;
			currCacheLength--;
			pushBack(value);
			delete pomNode;
			return true;
		}
		while (pomNode->next != nullptr) {
			if (pomNode->next->value == value) {
				if (pomNode->next->next == nullptr) {
					return true;
				}
				popNodeToBack(pomNode);
				pomNode = nullptr;
				return true;
			}
			pomNode = pomNode->next;
		}
		if (pomNode->value == value) {
			pomNode = nullptr;
			return true;
		}
		else { 
			pomNode = nullptr;
			if (currCacheLength == cacheMaxLength) {
				popFront();
			}
			pushBack(value);
			return false; 
		}
	}
	else if (currCacheLength == 1) {
		if (firstElem->value == value) {
			return true;
		}
		else {
			if (currCacheLength == cacheMaxLength) {
				popFront();
			}
			pushBack(value);
			return false;
		}
	}
	else { 
		if (cacheMaxLength > 0) {
			pushBack(value);
		}
		return false; 
	}
}

LRUCache::~LRUCache() {
	for (int i = currCacheLength; i > 0; i--) {
		popFront();
	}
}