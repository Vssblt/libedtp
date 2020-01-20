#ifndef LIBEDTP_MAP_H
#define LIBEDTP_MAP_H
#include "rbtree.h"

struct EdtpMap {
	MapElement *root;
	int size;
};


lestring map_value(EdtpMap *map, const char *key);

void map_insert(EdtpMap *map, const char *key, const char *value, int value_size);

void map_set(EdtpMap *map, const char *key, const char *value, int value_size);

void map_erase(EdtpMap *map, const MapElement *element);

void map_erase(EdtpMap *map, const char *key);

MapElement *map_begin(EdtpMap *map);

MapElement *map_end(EdtpMap *map);

MapElement *map_next(MapElement *map);

void delete_map(EdtpMap *map);

#endif
