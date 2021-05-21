#ifndef BT
#define BT

#include "Node.h"

class Btree {
private:
	int order;
	Node* root;
public:
	Btree(int order);
	void insert(int key);
	void splitChild(Node* parent, int childIndex, Node* child);
	void insertNonfull(Node* node, int key);
};


#endif // !BT
