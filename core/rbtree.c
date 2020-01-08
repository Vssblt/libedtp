#include <rbtree.h>

#include <malloc.h>

//#define INPUT_DATA

#ifdef __GNUC__
#define max(x, y) ({ \
	typeof(x) _max1 = (x); \
	typeof(y) _max2 = (y); \
	(void)(&_max1 == &_max2); \
	_max1 > _max2 ? _max1 :_max2; \
})
#else
#define max(x, y) ({ \
	x > y ? x : y; \
})
#endif

typedef struct Tree{
	int data;
	struct Tree *left;
	struct Tree *right;
	struct Tree *parent;
	int color;
}Tree;

Tree *root = NULL;

int search(int data, Tree **node);


void add(int data);

void rotate34(Tree *a, Tree *b, Tree *c, Tree *t0, Tree *t1, Tree *t2, Tree *t3, int type);

int tree_delete(int data);

void LOG(Tree *root);

void add_rebalance(Tree *node, Tree *parent, Tree *grandpa, Tree *uncle);

void del_rebalance(Tree *node);

int
search(int data, Tree **node)
{
	Tree *pointer = root, *parent = NULL;
	while (pointer != NULL) {
		parent = pointer;
		if (data > pointer->data) {
			pointer = pointer->right;
		} else if (pointer->data > data) {
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
rotate34(Tree *a, Tree *b, Tree *c, Tree *t0, Tree *t1, Tree *t2, Tree *t3, int type)
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

void 
add(int data)
{
	Tree *search_temp = NULL;
	Tree *parent = NULL;
	if (root == NULL) {
		root = (Tree *)malloc(sizeof(Tree));
		root->parent = NULL;
		root->data = data;
		root->left = NULL;
		root->right = NULL;
		root->color = 0;
		return ;
	}

	if (0 == search(data, &parent)) {
		return ;
	}

	Tree *node = (Tree *)malloc(sizeof(Tree));
	node->color = 1;
	node->parent = parent;
	node->left = NULL;
	node->right = NULL;
	node->data = data;

	if (parent->color == 0) {
		if (parent->data > data)
			parent->left = node;
		else 
			parent->right = node;
		return ;
	}

	Tree *grandpa = parent->parent;
	Tree *uncle = (parent == grandpa->left ? grandpa->right : grandpa->left);

	if (node->data > parent->data)
		parent->right = node;
	else
		parent->left = node;

	add_rebalance(node, parent, grandpa, uncle);

	return ;
}

void 
add_rebalance(Tree *node, Tree *parent, Tree *grandpa, Tree *uncle)
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
			if (grandpa->left == parent && node->data > parent->data) { //LL
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
			} else if (grandpa->left == parent && node->data < parent->data) { //LR
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
			} else if (grandpa->right == parent && node->data < parent->data) { //RL 
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
			} else if (grandpa->right == parent && node->data > parent->data) { //RR
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

int
tree_delete(int data)
{
	Tree *node = NULL;
	Tree *child = NULL;
	Tree *parent = NULL;

	if (1 == search(data, &node)) {
		return 0;
	}
	parent = node->parent;

	if (node->left != NULL && node->right != NULL) { 
		Tree *pointer = node->left;
		while(pointer->right != NULL) {
			pointer = pointer->right;
		}
		node->data = pointer->data;
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
			free(node);
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
	free(node);
	return 0;
}

void 
del_rebalance(Tree *node)
{
	Tree *parent = node->parent;
	Tree *brother = (parent->left == node ? parent->right : parent->left);

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
