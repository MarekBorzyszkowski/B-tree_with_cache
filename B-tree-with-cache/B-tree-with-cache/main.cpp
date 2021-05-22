#define _CRT_SECURE_NO_WARNINGS
#include "Btree.h"
#include <stdio.h>

enum {
	NEW,
	INSERT,
	SEARCH,
	PRINT,
	INPORT,
	EXPORT,
	REMOVE,
	CACHE,
	IGNORE,
	END,
	ERROR
} ecmd;

int parseEnum(char cmd) {
	return cmd == 'I' ? NEW :
		cmd == 'A' ? INSERT :
		cmd == '?' ? SEARCH :
		cmd == 'P' ? PRINT :
		cmd == 'L' ? INPORT :
		cmd == 'S' ? EXPORT :
		cmd == 'R' ? REMOVE :
		cmd == 'C' ? CACHE :
		cmd == '#' ? IGNORE :
		cmd == 'X' ? END : ERROR;
}

int main() {
	Btree* tree = nullptr;
	char action;
	int input, height;
	while (scanf("%c", &action) > 0) {
		switch (parseEnum(action)) {
		case NEW: {
			scanf("%d", &input);
			if (tree != nullptr) delete tree;
			tree = new Btree(input);
			break;
		}
		case INSERT: {
			scanf("%d", &input);
			tree->insert(input);
			break;
		}
		case SEARCH: {
			scanf("%d", &input);
			height = 1;
			if (tree->search(tree->getRoot(), input, height)>0) {
				printf("%d +\n", input);
			}
			else printf("%d -\n", input);
			break;
		}
		case IGNORE: {
			break;
		}
		case END: {
			delete tree;
			tree = nullptr;
			return 0;
		}
		case ERROR: {
			break;
		}
		}
	}
}