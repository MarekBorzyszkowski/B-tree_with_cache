#ifndef FQ
#define FQ

class FIFONode {
public:
	int value;
	FIFONode* next;
	FIFONode(int value) {
		this->value = value;
		next = nullptr;
	}
	~FIFONode() {
		next = nullptr;
	}
};

class FIFOQ {
private:
	FIFONode* firstElem;
	int QMaxLength, QLength;
public:
	FIFOQ(int length);
	void pushBack(int value);
	void popFront();
	bool search(int value);
	~FIFOQ();
};

#endif
