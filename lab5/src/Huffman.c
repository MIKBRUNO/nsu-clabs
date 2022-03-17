#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include "Huffman.h"

Node* createTree(Node* elem, unsigned int* freq, unsigned int count) {
	Node** list;
	if (!(list = malloc(count * sizeof(Node*))))
		exit(0);
	*list = NULL;
	for (size_t i = 0; i < count; ++i) {
		elem->link[0] = NULL;
		elem->link[1] = NULL;
		elem->freq = 0;
		for (size_t j = 0; j < 256; ++j) {
			if (freq[j] && (!elem->freq || freq[j] >= elem->freq)) {
				elem->freq = freq[j];
				elem->value = j;
				list[i] = elem;
			}
		}
		freq[elem->value] = 0;
		++elem;
	}
	for (size_t i = count - 1; i > 0; --i) {
		elem->link[0] = list[i];
		elem->link[1] = list[i - 1];
		elem->freq = list[i]->freq + list[i - 1]->freq;
		list[i - 1] = elem;
		list[i] = NULL;
		size_t j = i - 1;
		while ((j != 0) && (list[j]->freq > list[j - 1]->freq)) {
			Node* t = list[j - 1];
			list[j - 1] = list[j];
			list[j] = t;
			--j;
		}
		++elem;
	}
	return list[0];
}

void treeTraversal(
					const Node* cur, struct Data_st* data,
					void (*onNode)(struct Data_st*),
					void (*onLeaf)(struct Data_st*, const Node*)
				  ) {
	if (NULL == cur)
		return;
	if (NULL == cur->link[0]) {
		onLeaf(data, cur);
	}
	else {
		onNode(data);
		treeTraversal(cur->link[0], data, onNode, onLeaf);
		treeTraversal(cur->link[1], data, onNode, onLeaf);
	}
}
