#include "rbtree.h"
#include <malloc.h>

static void rotate34(MapElement *a, MapElement *b, MapElement *c, MapElement *t0, MapElement *t1, MapElement *t2, MapElement *t3, int type);

static void add_rebalance(MapElement *node, MapElement *parent, MapElement *grandpa, MapElement *uncle);

static int search(const char *key, MapElement **node, MapElement *root);

static void add(MapElement *root, const char *key, const char *value);

static void del_rebalance(MapElement *node);

static int del(const char *key, MapElement *root);

void 
tree_add(MapElement *root, const char *key, const char *value)
{
	add(root, key, value);
}

void 
tree_del(MapElement *root, const char *key)
{
	del(key, root);
}

MapElement *
tree_first(EdtpMap *root)
{
	MapElement *pointer = root->root;
	while (pointer->left) pointer = pointer->left;
	return pointer;
}

MapElement *
tree_last(EdtpMap *root)
{
	MapElement *pointer = root->root;
	while (pointer->right) pointer = pointer->right;
	return pointer;
}

MapElement *
tree_next(MapElement *node)
{
	if (node->right) {
		node = node->right;
		while (node->left)
			node = node->left;
	} else {
		if (node->parent == NULL || node->parent->left != node)
			return NULL;
		else 
			return node->parent;
	}
	return node;
}

lestring
tree_search(EdtpMap *map, const char *key)
{
	lestring ret = {.str = NULL, .size = 0};
	MapElement *node = NULL;
	int ret = search(key, &node, map->root);
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
search(const char *key, MapElement **node, MapElement *root)
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

void 
add(MapElement *root, const char *key, const char *value, int value_size)
{
	MapElement *search_temp = NULL;
	MapElement *parent = NULL;
	if (root == NULL) {
		root = (MapElement *)malloc(sizeof(MapElement));
		root->parent = NULL;
		root->key = (char *)malloc(strlen(key));
		root->value = (char *)malloc(value_size);
		memcpy(root->key, key, strlen(key));
		memcpy(root->value, value, value_size);
		root->value_size = value_size;
		root->left = NULL;
		root->right = NULL;
		root->color = 0;
		return ;
	}

	if (0 == search(key, &parent, root)) {
		return ;
	}

	MapElement *node = (MapElement *)malloc(sizeof(MapElement));
	node->color = 1;
	node->parent = parent;
	node->left = NULL;
	node->right = NULL;
	node->value = (char *)malloc(value_size);
	node->key = (char *)malloc(strlen(key));
	memcpy(node->value, value, value_size);
	memcpy(node->key, key, strlen(key));
	node->value_size = value_size;

	if (parent->color == 0) {
		if (strcmp(parent->key, key) > 0)
			parent->left = node;
		else 
			parent->right = node;
		return ;
	}

	MapElement *grandpa = parent->parent;
	MapElement *uncle = (parent == grandpa->left ? grandpa->right : grandpa->left);

	if (strcmp(node->value, parent->value) > 0)
		parent->right = node;
	else
		parent->left = node;

	add_rebalance(node, parent, grandpa, uncle);

	return ;
}

void 
del_rebalance(MapElement *node)
{
	MapElement *parent = node->parent;
	MapElement *brother = (parent->left == node ? parent->right : parent->left);

	if (brother->color == 1) {
		int temp_color = 0;
		temp_color = parent->color;
		parent->color = brother->color;
		brother->color = temp_color;

		if (parent == root)
			root = brother;
		
		if (parent->parent->left == parent)
			parent->parent->left = brother;
		else
			parent->parent->right = brother;
		
		if (parent->left == node) {
			rotate34(parent, brother, brother->right, node, brother->left, brother->right->left, brother->right->right, 0);
		} else {
			rotate34(brother->left, brother, parent, brother->left->left, brother->left->right, brother->right, node, 0);
		}
		brother = (parent->left == node ? parent->right : parent->left);
	}

	int temp_color = 0;
	if (parent->left == node && brother->left != brother->right) {
		if (brother->left != NULL) { //RL
			if (parent == root)
				root = brother->left;
			brother->left->color = parent->color;
			parent->color = 0;
			
			if (parent->parent->left == parent)
				parent->parent->left = brother->left;
			else
				parent->parent->right = brother->left;
			rotate34(parent, brother->left, brother, node, brother->left, brother->right, brother->right, 0);
		} else { //RR
			temp_color = parent->color;
			parent->color = brother->color;
			brother->color = temp_color;
			brother->right->color = 0;
			if (parent == root)
				root = brother;


			if (parent->parent->left == parent)
				parent->parent->left = brother;
			else
				parent->parent->right = brother;
			rotate34(parent, brother, brother->right, node, brother->left, brother->right->left, brother->right->right, 0);
		}
	} else if (parent->right == node && brother->left != brother->right) {
		if (brother->left != NULL) { //LL
			if (parent == root)
				root = brother;
			temp_color = parent->color;
			parent->color = brother->color;
			brother->color = temp_color;
			brother->left->color = 0;

			if (parent->parent->left == parent)
				parent->parent->left = brother;
			else
				parent->parent->right = brother;
			rotate34(brother->left, brother, parent, brother->left, brother->right, brother->right, node, 0);
		} else { //LR
			if (parent == root)
				root = brother->right;
			brother->right->color = parent->color;
			parent->color = 0;

			if (parent->parent->left == parent)
				parent->parent->left = brother->right;
			else
				parent->parent->right = brother->right;
			rotate34(brother, brother->right, parent, brother->left, brother->right->left, brother->right->right, node, 0);
		}
	} else if (brother->left == brother->right) {
		if (parent->color == 0) {
			brother->color = 1;
		} else {
			parent->color = 0;
			brother->color = 1;
		}
	}
}

int
del(const char *key, MapElement *root)
{
	Tree *node = NULL;
	Tree *child = NULL;
	Tree *parent = NULL;

	if (1 == search(key, &node, root)) {
		return 0;
	}
	parent = node->parent;

	if (node->left != NULL && node->right != NULL) { 
		Tree *pointer = node->left;
		while(pointer->right != NULL) {
			pointer = pointer->right;
		}
		free(node->value);
		free(node->key);
		node->value = (char *)malloc(pointer->value_size);
		node->key = (char *)malloc(strlen(pointer->key));
		memcpy(node->value, pointer->value, pointer->value_size);
		memcpy(node->key, pointer->key, strlen(pointer->key));
		node = pointer;
		parent = node->parent;
	}

	if (node->left != node->right) { 
		if (node->left != NULL)
			child = node->left;
		else
			child = node->right;

		if (parent != NULL) {
			if (node == parent->left)
				parent->left = child;
			else
				parent->right = child;
		} else {
			root = child;
		}
		child->color = 0;
		child->parent = parent;

	}
	if (node->left == node->right) { 
		if (parent == NULL) {
			root = NULL;
			free_element(node);
			return 0;
		}
		if (node->color == 0) {
			del_rebalance(node);
		}
		if (parent->left == node)
			parent->left = NULL;
		else
			parent->right = NULL;
	}
	free_element(node);
	return 0;
}

void 
free_element(MapElement *node)
{
	free(node->value);
	free(node->key);
	free(node);
}
