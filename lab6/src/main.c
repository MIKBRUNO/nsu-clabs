#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "AVLTree.h"

int main(void) {
	unsigned int count;
	if (0 == scanf("%ud", &count))
		return 0;
	Node* place;
	if (0 == (place = malloc(sizeof(Node) * count)))
		exit(0);
	Node* root = NULL;
	for (size_t i = 0; i < count; ++i) {
		Node* elem = place + i;	
		if (0 == scanf("%d", &(elem->value)))
			return 0;
		elem->height = 1;
		elem->link[0] = NULL;
		elem->link[1] = NULL;
		root = insert(elem, root);
	}
	printf("%u\n", (unsigned int)height(root));

	free(place);
	return 0;
}
