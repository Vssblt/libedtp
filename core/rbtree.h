#ifndef RBTREE_H
#define RBTREE_H

typedef struct map{
	char *key;
	char *value;
	struct Tree *left;
	struct Tree *right;
	struct Tree *parent;
	int color;
};


#endif
