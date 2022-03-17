#pragma once

typedef struct Node_st Node;
struct Node_st {
	Node* link[2];
	
	unsigned char value;
	unsigned int freq;
};

Node* createTree(Node* elem, unsigned int* freq, unsigned int count);

struct Data_st;
void treeTraversal(	const Node* tree, struct Data_st* data,
					void (*onNodeArrived)(struct Data_st*),
					void (*onLeafArrived)(struct Data_st*, Node*)
				  );
