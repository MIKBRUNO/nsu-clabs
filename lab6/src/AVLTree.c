#include "AVLTree.h"

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

inline unsigned int height(Node* elem) {
	return (NULL != elem) ? elem->height : 0;
}

static void rotTree(Node** tree, unsigned int idx) {
	Node* newRoot = (*tree)->link[idx];
	(*tree)->link[idx] = newRoot->link[!idx];
	(*tree)->height = max(height((*tree)->link[0]), height((*tree)->link[1])) + 1;
	newRoot->link[!idx] = (*tree);
	newRoot->height = max(height(newRoot->link[0]), height(newRoot->link[1])) + 1;
	(*tree) = newRoot;
}

void insert(Node* elem, Node** tree) {
	if (NULL == elem)
		return;
	if (NULL == *tree) {
		(*tree) = elem;
		return;
	}
	unsigned int idx = (elem->value >= (*tree)->value);
	insert(elem, &((*tree)->link[idx]));
	unsigned int maxIdx = height((*tree)->link[0]) > height((*tree)->link[1]) ? 0 : 1;
	(*tree)->height = height((*tree)->link[maxIdx]) + 1;

	if ((1 < height(*tree)) && (1 < (height((*tree)->link[maxIdx]) - height((*tree)->link[!maxIdx])))) {
		if (height(((*tree)->link[idx])->link[idx]) > height(((*tree)->link[idx])->link[!idx]))
			rotTree(tree, idx);
		else {
			rotTree(&((*tree)->link[idx]), !idx);
			rotTree(tree, idx);
		}
	}
}
