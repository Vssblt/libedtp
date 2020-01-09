#include "map.h"
#include "rbtree.h"

void 
map_insert(EdtpMap *map, const char *key, const char *value)
{

	tree_search(key);
	(*map)->root = tree_add(, key, value);
}

void map_erase(EdtpMap *map, const MapElement *element)
{
	(*map)->root = tree_del(, key, element);
}

MapElement 
map_begin(EdtpMap *map)
{
	return tree_first((*map)->root);
}

MapElement 
map_end(EdtpMap *map)
{
	return tree_last((*map)->root);
}

MapElement 
map_next(EdtpMap *map)
{
	return tree_next((*map)->root);
}
