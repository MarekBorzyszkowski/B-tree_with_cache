#include "Btree.h"

Btree::Btree(int order)
	:order(order),
	root(new Node(true, order, nullptr)) {}

Node* Btree::getRoot() const {
	return root;
}

int Btree::prepareNodeForInsertion(Node* node, int key) {
	int index = node->keysAmount - 1;
	while (index >= 0 && key < node->keys[index]) {
		node->keys[index + 1] = node->keys[index];
		index--;
	}
	return index;
}

void Btree::insertNonfull(Node* node, int key) {
	int index = prepareNodeForInsertion(node, key);
	if (node->isItLeaf) {
		node->keys[index + 1] = key;
		node->keysAmount++;
	}
	else {
		index++;
		if (node->children[index]->keysAmount == 2 * order - 1) {
			splitChild(node, index, node->children[index]);
			if (key > node->keys[index]) {
				index++;
			}
		}
		insertNonfull(node->children[index], key);
	}
}

void Btree::splitChild(Node* parent, int childIndex, Node* child) {
	Node* siblingNode = new Node(child->isItLeaf, order, parent);
	siblingNode->keysAmount = order - 1;
	for (int i = 0; i < order - 1; i++) {
		siblingNode->keys[i] = child->keys[i + order];
	}
	if (!child->isItLeaf) {
		for (int i = 0; i < order; i++) {
			siblingNode->children[i] = child->children[i + order];
		}
	}
	child->keysAmount = order - 1;
	for (int i = parent->keysAmount; i > childIndex; i--) {
		parent->children[i + 1] = parent->children[i];
	}
	parent->children[childIndex + 1] = siblingNode;
	for (int i = parent->keysAmount; i > childIndex; i--) {
		parent->keys[i] = parent->keys[i - 1];
	}
	parent->keys[childIndex] = child->keys[order - 1];
	parent->keysAmount++;
}

void Btree::insert(int key) {
	if (root->keysAmount == 2 * order - 1) {
		Node* oldRoot;
		oldRoot = root;
		root = new Node(false, order, nullptr);
		oldRoot->parent = root;
		root->children[0] = oldRoot;
		splitChild(root, 0, oldRoot);
		insertNonfull(root, key);
	}
	else {
		insertNonfull(root, key);
	}
}

int Btree::search(Node* node, int key, int &height) {
	int index = 0;
	while (index < node->keysAmount && key > node->keys[index]) {
		index++;
	}
	if (index < node->keysAmount && key == node->keys[index]) {
		return height;
	}
	if (node->isItLeaf) {
		return -1;
	}
	else {
		height++;
		return search(node->children[index], key, height);
	}
}

void Btree::deleteNode(Node* node) {
	if (node->isItLeaf) {
		delete node;
	}
	else {
		for (int i = 0; i <= node->keysAmount; i++) {
			deleteNode(node->children[i]);
		}
		delete node;
	}
}

Btree::~Btree() {
	deleteNode(root);
}
