#include <rbtree.h>
#include <malloc.h>

static void rotate34(MapElement *a, MapElement *b, MapElement *c, MapElement *t0, MapElement *t1, MapElement *t2, MapElement *t3, int type);

static void add_rebalance(MapElement *node, MapElement *parent, MapElement *grandpa, MapElement *uncle);

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

char *
tree_search(EdtpMap *map, const char *key)
{

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
