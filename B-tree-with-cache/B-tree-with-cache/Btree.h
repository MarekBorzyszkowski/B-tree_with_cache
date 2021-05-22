#ifndef BT
#define BT

#include "Node.h"

class Btree {
private:
	int order;
	Node* root;
	
	int prepareNodeForInsertion(Node* node, int key);

	void insertNonfull(Node* node, int key);
	void splitChild(Node* parent, int childIndex, Node* child);
	void deleteNode(Node* node);

public:
	Btree(int order);
	Node* getRoot() const;
	void insert(int key);
	int search(Node* node, int key, int &height);
	~Btree();
};


#endif
