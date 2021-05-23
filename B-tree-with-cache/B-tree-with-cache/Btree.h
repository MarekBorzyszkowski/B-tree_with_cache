#ifndef BT
#define BT

#include "Node.h"

class Btree {
private:
	int order;
	Node* root;
	
	void insertNonfull(Node* node, int key);
	void splitChild(Node* parent, int childIndex, Node* child);
	void deleteNode(Node* node);
	int findKeyInNode(Node* node, int key);
	void margeNodes(Node* node1, Node* node2, int key);

public:
	Btree(int order);
	int getOrder() const;
	Node* getRoot() const;
	void insert(int key);
	int search(Node* node, int key, int &height);
	void print(Node* node);
	void load(int order);
	void save(Node* node);
	void deleteKey(Node* node, int key);
	~Btree();
};


#endif
