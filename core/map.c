#include "map.h"
#include "rbtree.h"

void 
map_insert(EdtpMap *map, const char *key, const char *value)
{
	tree_add(map, key, value);
}

void map_erase(EdtpMap *map, const MapElement *element)
{
	tree_del(map, key, element);
}

MapElement map_begin(EdtpMap *map)
{
	return tree_first(map);
}

MapElement map_end(EdtpMap *map)
{
	return tree_last(map);
}

