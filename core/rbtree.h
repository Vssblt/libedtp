#ifndef RBTREE_H
#define RBTREE_H

typedef struct MapElement{
	char *key;
	char *value;
	struct Tree *left;
	struct Tree *right;
	struct Tree *parent;
	int color;
};

void tree_add(EdtpMap *)



#endif
