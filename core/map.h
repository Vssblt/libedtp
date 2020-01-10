#ifndef LIBEDTP_MAP_H
#define LIBEDTP_MAP_H

typedef MapElement;

typedef struct EdtpMap {
	MapElement *root;
	int size;
};

char *map_value(EdtpMap *map, const char *key);

void map_insert(EdtpMap *map, const char *key, const char *value);

void map_set(EdtpMap *map, const char *key, const char *value);

void map_erase(EdtpMap *map, const MapElement *element);

MapElement map_begin(EdtpMap *map);

MapElement map_end(EdtpMap *map);

MapElement map_next(EdtpMap *map);

void delete_map(EdtpMap *map);

#endif
