#include "Node.h"

Node::Node(bool isItLeaf, int order, Node* parent)
	:isItLeaf(isItLeaf),
	keysAmount(0),
	keys(new int[2 * order - 1]),
	children(new Node* [2 * order]),
	parent(parent)
{}

Node::~Node() {
	delete[] keys;
	for (int i = 0; i <= keysAmount; i++) {
		children[i] = nullptr;
	}
	delete[] children;
	parent = nullptr;
}