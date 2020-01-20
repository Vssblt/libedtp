#ifndef RBTREE_H
#define RBTREE_H

/* This file only cares about how to create a rb tree. Do not do anything else in this file. */

#include "common.h"

struct MapElement{
	char *key;
	char *value;
	int value_size;
	struct MapElement *left;
	struct MapElement *right;
	struct MapElement *parent;
	int color;
};

MapElement *tree_add(MapElement *root, const char *key, const char *value, int value_size);

MapElement *tree_del(MapElement *root, const char *key);

MapElement *tree_first(const MapElement *root);

MapElement *tree_last(const MapElement *root);

MapElement *tree_next(const MapElement *node);

lestring tree_search(const MapElement *map, const char *key);

void delete_tree(MapElement *map);

void free_element(MapElement *node);


#endif
