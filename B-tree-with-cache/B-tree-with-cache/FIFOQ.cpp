#include "FIFOQ.h"

FIFOQ::FIFOQ(int lenght)
	:QMaxLength(lenght),
	QLength(0),
	firstElem(nullptr){}

void FIFOQ::pushBack(int value) {
	if (firstElem == nullptr) {
		firstElem = new FIFONode(value);
		QLength = 1;
	}
	else if (QLength == QMaxLength) {
		popFront();
		pushBack(value);
	}
	else {
		FIFONode* pomNode = firstElem;
		while (pomNode->next != nullptr) {
			pomNode = pomNode->next;
		}
		pomNode->next = new FIFONode(value);
		QLength++;
		pomNode = nullptr;
	}
}
void FIFOQ::popFront() {
	if (firstElem == nullptr) return;
	else {
		FIFONode* pomNode = firstElem->next;
		delete firstElem;
		firstElem = pomNode;
		pomNode = nullptr;
		QLength--;
	}
}
bool FIFOQ::search(int value) {
	if (QLength == 0) return false;
	else {
		FIFONode* pomNode = firstElem;
		while (pomNode->next != nullptr) {
			if (pomNode->value == value) {
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
			return false;
		}
	}
}

FIFOQ::~FIFOQ() {
	FIFONode* pomNode;
	if (firstElem != nullptr) {
		while (firstElem->next != nullptr) {
			pomNode = firstElem->next;
			delete firstElem;
			firstElem = pomNode;
		}
		delete firstElem;
		pomNode = nullptr;
	}
}