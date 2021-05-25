#ifndef LRUC
#define LRUC
//Least recently used
class ListNode {
public:
	int value;
	ListNode* next;
	ListNode(int value) {
		this->value = value;
		next = nullptr;
	}
	~ListNode() {
		next = nullptr;
	}
};

class LRUCache {
private:
	int cacheMaxLength, currCacheLength;
	ListNode* firstElem;
	void popNodeToBack(ListNode* nodeBefore);
	void pushBack(int value);
	void popFront();
public:
	LRUCache(int length);
	bool search(int value);
	~LRUCache();
};


#endif
