#include "map.h"
#include "rbtree.h"
#include <string.h>

void 
delete_map(EdtpMap *map)
{
	delete_tree(map->root);
}

lestring
map_value(EdtpMap *map, const char *key)
{
	return tree_search(map->root, key);
}

void 
map_insert(EdtpMap *map, const char *key, const char *value, int value_size)
{
	if (value_size == -1) 
		value_size = strlen(value) + 1;
	map->root = tree_add(map->root, key, value, value_size);
}

void
map_set(EdtpMap *map, const char *key, const char *value, int value_size)
{
	map_insert(map, key, value, value_size);
}

void 
map_erase(EdtpMap *map, MapElement *element)
{
	map->root = tree_del(map->root, element->key);
}

void
map_erase(EdtpMap *map, const char *key)
{
	map->root = tree_del(map->root, key);
}

MapElement *
map_begin(EdtpMap *map)
{
	return tree_first(map->root);
}

MapElement *
map_end(EdtpMap *map)
{
	return tree_last(map->root);
}

MapElement *
map_next(MapElement *element)
{
	return tree_next(element);
}
