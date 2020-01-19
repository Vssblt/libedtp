#ifndef RBTREE_H
#define RBTREE_H
#include "common.h"

typedef struct MapElement{
	char *key;
	char *value;
	int value_size;
	struct MapElement *left;
	struct MapElement *right;
	struct MapElement *parent;
	int color;
};

typedef struct EdtpMap {
	MapElement *root;
	int size;
};

void tree_add(MapElement *root, const char *key, const char *value, int value_size);

void tree_del(MapElement *root, const char *key);

MapElement *tree_first(EdtpMap *root);

MapElement *tree_last(EdtpMap *root);

MapElement *tree_next(MapElement *node);

lestring tree_search(EdtpMap *map, const char *key);

void delete_tree(EdtpMap *map);

void free_element(MapElement *node);


#endif
