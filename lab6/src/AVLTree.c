#include "AVLTree.h"

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

inline unsigned int height(Node* elem) {
	return (NULL != elem) ? elem->height : 0;
}

static inline Node* rotTree(Node* tree, unsigned int idx) {
	Node* newRoot = tree->link[idx];
	tree->link[idx] = newRoot->link[!idx];
	tree->height = max(height(tree->link[0]), height(tree->link[1])) + 1;
	newRoot->link[!idx] = tree;
	newRoot->height = max(height(newRoot->link[0]), height(newRoot->link[1])) + 1;
	return newRoot;
}

Node* insert(Node* elem, Node* tree) {
	if (NULL == elem)
		return tree;
	if (NULL == tree)
		return elem;
	unsigned int idx = (elem->value >= tree->value);
	tree->link[idx] = insert(elem, tree->link[idx]);
	tree->height = max(height(tree->link[0]), height(tree->link[1])) + 1;

	if ((1 < height(tree)) && (abs((int)height(tree->link[idx]) - (int)height(tree->link[!idx])) > 1)) {
		if (height((tree->link[idx])->link[idx]) > height((tree->link[idx])->link[!idx]))
			tree = rotTree(tree, idx);
		else {
			tree->link[idx] = rotTree(tree->link[idx], !idx);
			tree = rotTree(tree, idx);
		}
	}
	return tree;
}