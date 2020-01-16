#include <rbtree.h>
#include <malloc.h>

static void rotate34(MapElement *a, MapElement *b, MapElement *c, MapElement *t0, MapElement *t1, MapElement *t2, MapElement *t3, int type);

static void add_rebalance(MapElement *node, MapElement *parent, MapElement *grandpa, MapElement *uncle);

static int search_element(const char *key, MapElement **node, MapElement *root);

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

lestring
tree_search(EdtpMap *map, const char *key)
{
	lestring ret = {.str = NULL, .size = 0};
	MapElement *node = NULL;
	int ret = search_element(key, &node, map->root);
	if (ret == 0) {
		lestring_copy(&ret, MapElement->value, MapElement->value_size, COPY_AND_NEW);
	}
	return ret;
}

void 
delete_all_tree(EdtpMap *map)
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

void 
add_rebalance(MapElement *node, MapElement *parent, MapElement *grandpa, MapElement *uncle);
{
	do {
		int yesorno = 0;
		if (uncle != NULL) {
			if (uncle->color == 1)
				yesorno = 1;
		}
		if (yesorno) {     
			grandpa->color = 1;
			parent->color = 0;
			uncle->color = 0;
	
			if (grandpa == root) {
				grandpa->color = 0;
				break;
			}
			if (grandpa->parent == root) {
				break;
			}
			node = grandpa;
	
		} else {
			if (grandpa->left == parent && strcmp(node->key, parent->key) > 0) { //LL
				parent->parent = grandpa->parent;
				if (grandpa->parent != NULL) {
					if (grandpa->parent->left == grandpa)
						grandpa->parent->left = parent;
					else
						grandpa->parent->right = parent;
				} else {
					root = parent;
				}
				rotate34(node, parent, grandpa, node->left, node->right, parent->right, grandpa->right, 1);
				node = parent;
			} else if (grandpa->left == parent && strcmp(node->key, parent->key) < 0) { //LR
				node->parent = grandpa->parent;
				if (grandpa->parent != NULL) {
					if (grandpa->parent->left == grandpa)
						grandpa->parent->left = node;
					else
						grandpa->parent->right = node;
				} else {
					root = node;
				}
				rotate34(parent, node, grandpa, parent->left, node->left, node->right, grandpa->right, 1);
			} else if (grandpa->right == parent && strcmp(node->key, parent->key) < 0) { //RL 
				node->parent = grandpa->parent;
				if (grandpa->parent != NULL) {
					if (grandpa->parent->left == grandpa)
						grandpa->parent->left = node;
					else
						grandpa->parent->right = node;
				} else {
					root = node;
				}
				rotate34(grandpa, node, parent, grandpa->left, node->left, node->right, parent->right, 1);
			} else if (grandpa->right == parent && strcmp(node->key, parent->key) > 0) { //RR
				parent->parent = grandpa->parent;
				if (grandpa->parent != NULL) {
					if (grandpa->parent->left == grandpa)
						grandpa->parent->left = parent;
					else
						grandpa->parent->right = parent;
				} else {
					root = parent;
				}
				rotate34(grandpa, parent, node, grandpa->left, parent->left, node->left, node->right, 1);
				node = parent;
			}
		}
		parent = node->parent;
		if (parent == NULL || parent == root)
			break;
		grandpa = parent->parent;
		uncle = (parent == grandpa->left ? grandpa->right : grandpa->left);
	} while (node->parent->color == 1 && node->color == 1);
}
