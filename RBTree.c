#include <stdio.h>
#include <stdlib.h>

typedef int rb_key;
typedef enum rb_color 
{
	RED = 0,
	BLACK = 1
};
typedef struct rb_node
{
	struct rb_node *left, *right, *parent;
	rb_key key;
	rb_color color;
};

typedef struct rb_tree
{
	struct rb_node *root;
};

rb_node* rb_new_node(rb_key key)
{
	rb_node* new_node = (rb_node*) malloc(sizeof(rb_node));
	new_node -> key = key;
	new_node -> color = kb_color.RED;
	new_node -> right = NULL;
	new_node -> left = NULL;
	new_node -> parent = NULL;
	return new_node;
}

void rb_insert(rb_tree *tree, rb_node *node)
{
	rb_node *node_y = NULL;
	rb_node *node_x = tree -> root;
	while(node_x != NULL)
	{
		node_y = node_x;
		if(node->left->key < node_x -> key)
		{
			node_x = node_x -> left;
		}else
		{
			node_x = node_x -> right;
		}
	}
	node -> parent = node_y;
	if(tree -> root == NULL)
	{
		tree -> root = node;
	}else if(node -> key < node_y -> key)
	{
		node_y -> left = node;
	}else
	{
		node_y -> right = node;
	}
	node -> left = NULL;
	node -> right = NULL;
	node -> color = kb_color.RED;
	rb_insert_fixup(tree, node);
}

void rb_insert_fixup(rb_tree *tree, rb_node *node)
{
	while(node -> parent != NULL && node -> parent -> color == kb_color.RED)
	{
		if(node -> parent == node -> parent -> parent -> left)
		{
			rb_node *node_uncle = node -> parent -> parent -> right; // uncle's node
			if(node_uncle -> color == rb_color.RED)    // case 1
			{
				node -> parent -> color = rb_color.BLACK;
				node_uncle -> color = rb_color.BLACK;
				node -> parent -> parent -> color =rb_color.RED;
				node = node -> parent -> parent;
			}else
			{ 
				if(node == node -> parent -> right) // case 2: uncle is black, parent's right child
				{
					node = node -> parent;
					left_rotate(tree, node);
				}  // turn to case 3
				node -> parent -> color = rb_color.BLACK;
				node -> parent -> parent -> color = rb_color.RED;
				right_rotate(tree, node -> parent -> parent);
			}
		}else
		{
			rb_node *node_uncle = node -> parent -> parent -> left;
			if(node_uncle -> color == rb_color.RED)
			{
				node -> parent -> color = rb_color.BLACK;
				node_uncle -> color = rb_color.BLACK;
				node -> parent -> parent -> color = rb_color.RED;
				node = node -> parent -> parent;
			}else
			{
				if(node == node -> parent -> left)
				{
					node = node -> parent;
					right_rotate(tree, node);
				}
				node -> parent -> color = rb_color.BLACK;
				node -> parent -> parent -> color = rb_color.RED;
				left_rotate(tree, node -> parent -> parent);
			}
		}
	}
	tree -> root -> color = rb_color.BLACK;
}

void rb_delete(rb_tree *tree, rb_node *node)
{
	rb_node *node_x;   // store original position of node
	rb_node *node_y = node;   // store deleted node or the node moved to deleted node
	rb_color y_origin_color = node -> node_y -> color;
	if(node -> left == NULL)
	{
		node_x = node -> right;
		rb_transplant(tree, node, node -> right);
	}else if(node -> right == NULL)
	{
		node_x = node -> left;
		rb_transplant(tree, node, node -> left);
	}else
	{
		node_y = tree_minimum(node -> right);
		y_origin_color = node_y -> color;
		node_x = node_y -> right;
		if(node_y -> parent == node)
		{
			node_x -> parent = node_y;
		}else
		{
			rb_transplant(tree, node_y, node_y -> right);
			node_y -> right = node -> right;
			node_y -> right -> parent = node_y;
		}
		rb_transplant(tree, node, node_y);
		node_y -> left = node -> left;
		node_y -> left -> parent = node_y;
		node_y -> color = node -> color;
	}
	if(y_origin_color = rb_color.BLACK)
	{
		rb_delete_fixup(tree, node_x);
	}
}

void rb_delete_fixup(rb_tree *tree, rb_node *node)
{
	rb_node *node_w;
	while(node != tree -> root && node -> color == rb_color.BLACK)
	{
		if(node == node -> parent -> left)
		{
			node_w = node -> parent -> right;
			if(node_w -> color == rb_color.RED) // case 1 
			{
				node_w -> color = rb_color.BLACK;
				node -> parent -> color = rb_color.RED;
				left_rotate(tree, node -> parent);
				node_w = node -> parent -> right;    // turn to case 2 3 4
			}
			if(node_w -> left == rb_color.BLACK && node_w -> right == rb_color.BLACK) // case 2
			{
				/*
				 * 1. enter from case 1, node -> parent's color is RED.  break out loop 
				 * 2. node -> parent 's color is RED. break out loop
				 * 3. node -> parent 's color is BLACK. node = node -> parent. continue to iterate
				 */
				node_w -> color = rb_color.RED;
				node = node -> parent;
			}else
			{
				if(node_w -> right -> color == rb_color.BLACK)
				{
					node_w -> left -> color = rb_color.BLACK;
					node_w -> color = rb_color.RED;
					right_rotate(tree, node_w);
					node_w = node -> parent -> right;   // turn to case 4
				}	
				node_w -> color = node -> parent -> color;
				node -> parent -> color = rb_color.BLACK;
				node_w -> right -> color = rb_color.BLACK;
				left_rotate(tree, node -> parent);
				node = tree -> root;
			}
		}else
		{
		
			node_w = node -> parent -> left;
			if(node_w -> color == rb_color.RED) // case 1 
			{
				node_w -> color = rb_color.BLACK;
				node -> parent -> color = rb_color.RED;
				right_rotate(tree, node -> parent);
				node_w = node -> parent -> left;    // turn to case 2 3 4
			}
			if(node_w -> left == rb_color.BLACK && node_w -> right == rb_color.BLACK) // case 2
			{
				/*
				 * 1. enter from case 1, node -> parent's color is RED.  break out loop 
				 * 2. node -> parent 's color is RED. break out loop
				 * 3. node -> parent 's color is BLACK. node = node -> parent. continue to iterate
				 */
				node_w -> color = rb_color.RED;
				node = node -> parent;
			}else
			{
				if(node_w -> left -> color == rb_color.BLACK)
				{
					node_w -> right-> color = rb_color.BLACK;
					node_w -> color = rb_color.RED;
					left_rotate(tree, node_w);
					node_w = node -> parent -> right;   // turn to case 4
				}	
				node_w -> color = node -> parent -> color;
				node -> parent -> color = rb_color.BLACK;
				node_w -> left -> color = rb_color.BLACK;
				right_rotate(tree, node -> parent);
				node = tree -> root;
			}
		}
	}
	node -> color = rb_color.BLACK;
}

void rb_transplant(rb_tree *tree, rb_node *node_u, rb_node *node_v)
{
	if(node_u -> parent == NULL)
	{
		tree -> root = node_v;
	}else if(node_u == node_u -> parent -> left)
	{
		node_u -> parent -> left = node_v;
	}else
	{
		node_u -> parent -> right = node_v;
	}
	node_v -> parent = node_u -> parent;
}

rb_node* tree_minimum(rb_node *node)
{
	while(node -> left != NULL)
	{
		node = node -> left
	}
	return node;
}

void left_rotate(rb_tree *tree, rb_node *node)
{
	rb_node *node_y = node -> right;
	node -> right = node_y -> left;
	node_y -> left -> parent = node;
	node_y -> parent = node -> parent;
	if(node -> parent == NULL)
	{
		tree -> root = node_y;
	}else if(node == node -> parent -> left)
	{
		node -> parent -> left = node_y;
	}else
	{
		node -> parent -> right = node_y;
	}
	node_y -> left = node;
	node -> parent = node_y;
}

void right_rotate(rb_tree *tree, rb_node *node)
{
	rb_node *node_y = node -> parent;
	node_y -> left = node -> right;
	node -> right -> parent = node_y;
	node -> parent = node_y -> parent;
	if(node_y -> parent == NULL)
	{
		tree -> root = node;
	}else if(node_y  == node_y -> parent -> left)
	{
		node_y -> parent -> left = node;
	}else
	{
		node_y -> parent -> right = node;
	}
	node -> right = node_y;
	node_y -> parent = node;
}
