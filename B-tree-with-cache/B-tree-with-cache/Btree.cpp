#define _CRT_SECURE_NO_WARNINGS
#include "Btree.h"
#include <stdio.h>

Btree::Btree(int order)
	:order(order),
	root(new Node(true, order, nullptr)) {}

int Btree::getOrder() const {
	return order;
}

Node* Btree::getRoot() const {
	return root;
}

void Btree::insertNonfull(Node* node, int key) {
	int index = node->keysAmount - 1;
	if (node->isItLeaf) {
		while (index >= 0 && key < node->keys[index]) {
			node->keys[index + 1] = node->keys[index];
			index--;
		}
		node->keys[index + 1] = key;
		node->keysAmount++;
	}
	else {
		while (index >= 0 && key < node->keys[index]) {
			index--;
		}
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

int Btree::findKeyInNode(Node* node, int key) {
	int index = 0;
	while (index < node->keysAmount && key > node->keys[index]) {
		index++;
	}
	return index;
}

int Btree::search(Node* node, int key, int &height) {
	int index = findKeyInNode(node, key);
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

void Btree::print(Node* node) {
	if (node->isItLeaf) {
		for (int i = 0; i < node->keysAmount; i++) {
			printf("%d ", node->keys[i]);
		}
	}
	else {
		for (int i = 0; i < node->keysAmount; i++) {
			print(node->children[i]);
			printf("%d ", node->keys[i]);
		}
		print(node->children[node->keysAmount]);
	}
}

void Btree::load(int order) {
	deleteNode(root);
	this->order = order;
	root = new Node(true, this->order, nullptr);
	Node* currNode = root;
	int number;
	char input[100] = "(";
	int height = 1;
	scanf("%s", input);
	while (!(input[0] == ')' && height == 0)) {
		scanf("%s", input); 
		if (input[0] == '(') {
			height++;
			currNode->isItLeaf = false;
			currNode->children[currNode->keysAmount] = new Node(true, this->order, currNode);
			currNode = currNode->children[currNode->keysAmount];
		}
		else if (input[0] == ')') {
			height--;
			currNode = currNode->parent;
		}
		else {
			sscanf(input, "%d", &number);
			currNode->keys[currNode->keysAmount] = number;
			currNode->keysAmount++;
		}
	}
}

void Btree::save(Node* node) {
	printf("( ");
	if (node->isItLeaf) {
		for (int i = 0; i < node->keysAmount; i++) {
			printf("%d ", node->keys[i]);
		}
		printf(")");
	}
	else {
		for (int i = 0; i < node->keysAmount; i++) {
			save(node->children[i]);
			printf(" %d ", node->keys[i]);
		}
		save(node->children[node->keysAmount]);
		printf(" )");
	}
}

void Btree::margeNodes(Node* node1, Node* node2, int key) {
	node1->keys[order - 1] = key;
	for (int i = 0; i < order-1; i++) {
		node1->keys[i + order] = node2->keys[i];
	}
	if (!node1->isItLeaf) {
		for (int i = 0; i < order; i++) {
			node1->children[i + order] = node2->children[i];
		}
	}
	node1->keysAmount = 2 * order - 1;
	delete node2;
}

int Btree::findLargestKey(Node* node) {
	if (!node->isItLeaf) {
		return findLargestKey(node->children[node->keysAmount]);
	}
	else {
		return node->keys[node->keysAmount - 1];
	}
}

int Btree::findSmallestKey(Node* node) {
	if (!node->isItLeaf) {
		return findSmallestKey(node->children[0]);
	}
	else {
		return node->keys[0];
	}
}

void Btree::deleteKey(Node* node, int key) {
	int index = findKeyInNode(node, key);
	bool found = false;
	if (index < node->keysAmount && key == node->keys[index]) {
		found = true;
	}
	if (found && node->isItLeaf) {
		for (int i = index; i < node->keysAmount - 1; i++) {
			node->keys[i] = node->keys[i + 1];
		}
		node->keysAmount--;
		return;
	}
	else if (node->isItLeaf) {
		return;
	}
	else if (found) {
		Node* beforeKey = node->children[index];
		Node* afterKey = node->children[index+1];
		int newKey;
		if (beforeKey->keysAmount >= order) {
			newKey = findLargestKey(beforeKey);
			node->keys[index] = newKey;
			deleteKey(beforeKey, newKey);
		}
		else if (afterKey->keysAmount >= order) {
			newKey = findSmallestKey(afterKey);
			node->keys[index] = newKey;
			deleteKey(afterKey, newKey);
		}
		else {
			margeNodes(beforeKey, afterKey, key);
			for (int i = index; i < node->keysAmount-1; i++) {
				node->keys[i] = node->keys[i + 1];
			}
			for (int i = index+1; i < node->keysAmount; i++) {
				node->children[i] = node->children[i+1];
			}
			node->keysAmount--;
			deleteKey(beforeKey, key);
		}
		afterKey = beforeKey = nullptr;
	}
	else {
		Node* child = node->children[index];
		Node* leftBrother,* rightBrother;
		leftBrother = rightBrother = nullptr;
		if (child->keysAmount >= order) {
			deleteKey(child, key);
		}
		else {
			if (index < node->keysAmount) {
				rightBrother = node->children[index + 1];
				if (rightBrother->keysAmount >= order) {
					child->keys[child->keysAmount] = node->keys[index];
					node->keys[index] = rightBrother->keys[0];
					for (int i = 0; i < rightBrother->keysAmount - 1; i++) {
						rightBrother->keys[i] = rightBrother->keys[i + 1];
					}
					if (!child->isItLeaf) {
						child->children[child->keysAmount + 1] = rightBrother->children[0];
						for (int i = 0; i < rightBrother->keysAmount; i++) {
							rightBrother->children[i] = rightBrother->children[i + 1];
						}
					}
					rightBrother->keysAmount--;
					child->keysAmount++;
					deleteKey(child, key);
					child = leftBrother = rightBrother = nullptr;
				}
				else {
					child->keys[order - 1] = node->keys[index];
					for (int i = 0; i < order - 1; i++) {
						child->keys[i + order] = rightBrother->keys[i];
					}
					if (!child->isItLeaf) {
						for (int i = 0; i < order; i++) {
							child->children[i + order] = rightBrother->children[i];
						}
					}
					for (int i = index; i < node->keysAmount-1; i++) {
						node->keys[i] = node->keys[i + 1];
						node->children[i + 1] = node->children[i + 2];
					}
					node->keysAmount--;
					if (node == root && node->keysAmount == 0) {
						delete root;
						root = child;
						child->parent = nullptr;
					}
					child->keysAmount = 2 * order - 1;
					delete rightBrother;
					deleteKey(child, key);
					child = leftBrother = rightBrother = nullptr;
				}
			}
			else if (index > 0) {
				leftBrother = node->children[index - 1];
				if (leftBrother->keysAmount >= order) {
					for (int i = child->keysAmount - 1; i >= 0; i--) {
						child->keys[i + 1] = child->keys[i];
					}
					if (!child->isItLeaf) {
						for (int i = child->keysAmount; i >= 0; i--) {
							child->children[i + 1] = child->children[i];
						}
						child->children[0] = leftBrother->children[leftBrother->keysAmount];
					}
					child->keys[0] = node->keys[index - 1];
					node->keys[index - 1] = leftBrother->keys[leftBrother->keysAmount - 1];
					leftBrother->keysAmount--;
					child->keysAmount++;
					deleteKey(child, key);
					child = leftBrother = nullptr;
				}
				else {

					leftBrother->keys[order - 1] = node->keys[index-1];
					for (int i = 0; i < order - 1; i++) {
						leftBrother->keys[i + order] = child->keys[i];
					}
					if (!child->isItLeaf) {
						for (int i = 0; i < order; i++) {
							leftBrother->children[i + order] = child->children[i];
						}
					}
					for (int i = index-1; i < node->keysAmount - 1; i++) {
						node->keys[i] = node->keys[i + 1];
						node->children[i + 1] = node->children[i + 2];
					}
					node->keysAmount--;
					if (node == root && node->keysAmount == 0) {
						delete root;
						root = leftBrother;
						leftBrother->parent = nullptr;
					}
					leftBrother->keysAmount = 2 * order - 1;
					delete child;
					deleteKey(leftBrother, key);
					child = leftBrother = rightBrother = nullptr;
				}
			}
		}
	}
}


Btree::~Btree() {
	deleteNode(root);
}
