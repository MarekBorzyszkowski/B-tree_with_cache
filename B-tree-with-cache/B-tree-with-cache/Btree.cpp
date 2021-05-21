#include "Btree.h"

Btree::Btree(int order) 
	:order(order),
	root(new Node(true, order, nullptr)){}

void Btree::insert(int key) {
	//TODO
}

void Btree::insertNonfull(Node* node, int key) {
	//TODO
}

void Btree::splitChild(Node* parent, int childIndex, Node* child) {
	//TODO
}