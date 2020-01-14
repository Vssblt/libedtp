#include <rbtree.h>
#include <malloc.h>

static void rotate34(MapElement *a, MapElement *b, MapElement *c, MapElement *t0, MapElement *t1, MapElement *t2, MapElement *t3, int type);

static void add_rebalance(MapElement *node, MapElement *parent, MapElement *grandpa, MapElement *uncle);

int search_element(const char *key, MapElement **node, MapElement *root);

void 
tree_add(MapElement *root, const char *key, const char *value)
{

}

void 
tree_del(MapElement *root, const char *key, MapElement *element)
{

}

MapElement 
tree_first(EdtpMap *root)
{
}

MapElement 
tree_last(EdtpMap *root)
{
}

MapElement 
tree_next(MapElement *root)
{
}

int
tree_search(EdtpMap *map, const char *key, MapElement *ret_node)
{
	MapElement *node = NULL;
	int ret = search_element(key, &node, map->root);
	if (ret == 0)
		MapElement
}

void 
delete_tree(EdtpMap *map)
{

}

void 
rotate34(MapElement *a, MapElement *b, MapElement *c, MapElement *t0, MapElement *t1, MapElement *t2, MapElement *t3, int type)
{
	if (type == 1)
	{
		b->color = 0;
		a->color = 1;
		c->color = 1;
	}
	b->left = a;
	b->right = c;
	a->parent = b;
	a->left = t0;
	if (t0 != NULL) t0->parent = a;
	a->right = t1;
	if (t1 != NULL) t1->parent = a;
	c->parent = b;
	c->left = t2;
	if (t2 != NULL) t2->parent = c;
	c->right = t3;
	if (t3 != NULL) t3->parent = c;
}	

int
search_element(const char *key, MapElement **node, MapElement *root)
{
	MapElement *pointer = root, *parent = NULL;
	while (pointer != NULL) {
		parent = pointer;
		if (0 < strcmp(key, pointer->key) {
			pointer = pointer->right;
		} else if (0 < strcmp(pointer->key, key)) {
			pointer = pointer->left;
		} else {
			*node = pointer;
			return 0;
		}
	}
	*node = parent;
	return 1;
}
