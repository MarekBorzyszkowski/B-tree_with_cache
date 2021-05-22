#ifndef ND
#define ND

class Node {
public:
	bool isItLeaf;
	int keysAmount;
	int* keys;
	Node** children;
	Node* parent;

	Node(bool isItLeaf, int order, Node* parent);
	~Node();
};


#endif