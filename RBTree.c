//
//  main.c
//  RBTree
//
//  Created by dorothy on 15/11/6.
//  Copyright © 2015年 dorothy. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int RB_KEY;

typedef enum rb_color
{
    RED = 0,
    BLACK = 1
}RB_COLOR;

typedef struct rbx_node
{
    struct rbx_node *left, *right, *parent;
    RB_KEY key;
    RB_COLOR color;
}*RB_NODE;

typedef struct rbx_tree
{
    RB_NODE root;
}*RB_TREE;

RB_NODE rb_new_node(RB_KEY key);
void rb_insert(RB_TREE tree, RB_NODE node);
void rb_insert_fixup(RB_TREE tree, RB_NODE node);
void rb_delete(RB_TREE tree, RB_NODE node);
void rb_delete_fixup(RB_TREE tree, RB_NODE node);
void rb_transplant(RB_TREE tree, RB_NODE node_u, RB_NODE node_v);
RB_NODE tree_minimum(RB_NODE node);
void left_rotate(RB_TREE tree, RB_NODE node);
void right_rotate(RB_TREE tree, RB_NODE node);
void print_rb_tree(RB_TREE tree, RB_NODE node);

int main()
{
    RB_TREE tree = (RB_TREE ) malloc(sizeof(struct rbx_tree));
    srand((unsigned)time(NULL));
    for(int i = 0; i < 15; i++)
    {
        RB_KEY key = rand() % 30;
        RB_NODE node = rb_new_node(key);
        rb_insert(tree, node);
    }
    print_rb_tree(tree, tree -> root);
    printf("\n");
    
    return 0;
}

void print_rb_tree(RB_TREE tree, RB_NODE node)
{
    if(node != NULL)
    {
		printf("%d", node -> key);
        if(node -> color == BLACK)
        {
            printf("black");
        }else
        {
            printf("red");
        }
        print_rb_tree(tree, node -> left);
        print_rb_tree(tree, node -> right);
    }
}

RB_NODE rb_new_node(RB_KEY key)
{
    RB_NODE new_node = (RB_NODE) malloc(sizeof(struct rbx_node));
    new_node -> key = key;
    new_node -> color = RED;
    new_node -> right = NULL;
    new_node -> left = NULL;
    new_node -> parent = NULL;
    return new_node;
}

void rb_insert(RB_TREE tree, RB_NODE node)
{
    RB_NODE node_y = NULL;
    RB_NODE node_x = tree -> root;
    while(node_x != NULL)
    {
        node_y = node_x;
        if(node -> key < node_x -> key)
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
    node -> color = RED;
    rb_insert_fixup(tree, node);
}

void rb_insert_fixup(RB_TREE tree, RB_NODE node)
{
    while(node -> parent != NULL && node -> parent -> color == RED)
    {
        if(node -> parent == node -> parent -> parent -> left)
        {
            RB_NODE node_uncle = node -> parent -> parent -> right; // uncle's node
                if(node_uncle != NULL && node_uncle -> color == RED)    // case 1
                {
                    node -> parent -> color = BLACK;
                    node_uncle -> color = BLACK;
                    node -> parent -> parent -> color = RED;
                    node = node -> parent -> parent;
                }else
                {
                    if(node == node -> parent -> right) // case 2: uncle is black, parent's right child
                    {
                        node = node -> parent;
                        left_rotate(tree, node);
                    }  // turn to case 3
                    node -> parent -> color = BLACK;
                    node -> parent -> parent -> color = RED;
                    right_rotate(tree, node -> parent -> parent);
                }
        
        }else
        {
            RB_NODE node_uncle = node -> parent -> parent -> left;
                if(node_uncle != NULL && node_uncle -> color == RED)
                {
                    node -> parent -> color = BLACK;
                    node_uncle -> color = BLACK;
                    node -> parent -> parent -> color = RED;
                    node = node -> parent -> parent;
                }else
                {
                    if(node == node -> parent -> left)
                    {
                        node = node -> parent;
                        right_rotate(tree, node);
                    }
                    node -> parent -> color = BLACK;
                    node -> parent -> parent -> color = RED;
                    left_rotate(tree, node -> parent -> parent);
                }
        }
    }
    tree -> root -> color = BLACK;
}

void rb_delete(RB_TREE tree, RB_NODE node)
{
    RB_NODE node_x;   // store original position of node
    RB_NODE node_y = node;   // store deleted node or the node moved to deleted node
    RB_COLOR y_origin_color = node_y -> color;
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
    if(y_origin_color == BLACK)
    {
        rb_delete_fixup(tree, node_x);
    }
}

void rb_delete_fixup(RB_TREE tree, RB_NODE node)
{
    RB_NODE node_w;
    while(node != tree -> root && node -> color == BLACK)
    {
        if(node == node -> parent -> left)
        {
            node_w = node -> parent -> right;
            if(node_w -> color == RED) // case 1
            {
                node_w -> color = BLACK;
                node -> parent -> color = RED;
                left_rotate(tree, node -> parent);
                node_w = node -> parent -> right;    // turn to case 2 3 4
            }
            if(node_w -> left -> color == BLACK && node_w -> right -> color == BLACK) // case 2
            {
                /*
                 * 1. enter from case 1, node -> parent's color is RED.  break out loop
                 * 2. node -> parent 's color is RED. break out loop
                 * 3. node -> parent 's color is BLACK. node = node -> parent. continue to iterate
                 */
                node_w -> color = RED;
                node = node -> parent;
            }else
            {
                if(node_w -> right -> color == BLACK)
                {
                    node_w -> left -> color = BLACK;
                    node_w -> color = RED;
                    right_rotate(tree, node_w);
                    node_w = node -> parent -> right;   // turn to case 4
                }
                node_w -> color = node -> parent -> color;
                node -> parent -> color = BLACK;
                node_w -> right -> color = BLACK;
                left_rotate(tree, node -> parent);
                node = tree -> root;
            }
        }else
        {
            
            node_w = node -> parent -> left;
            if(node_w -> color == RED) // case 1
            {
                node_w -> color = BLACK;
                node -> parent -> color = RED;
                right_rotate(tree, node -> parent);
                node_w = node -> parent -> left;    // turn to case 2 3 4
            }
            if(node_w -> left -> color == BLACK && node_w -> right -> color == BLACK) // case 2
            {
                /*
                 * 1. enter from case 1, node -> parent's color is RED.  break out loop
                 * 2. node -> parent 's color is RED. break out loop
                 * 3. node -> parent 's color is BLACK. node = node -> parent. continue to iterate
                 */
                node_w -> color = RED;
                node = node -> parent;
            }else
            {
                if(node_w -> left -> color == BLACK)
                {
                    node_w -> right-> color = BLACK;
                    node_w -> color = RED;
                    left_rotate(tree, node_w);
                    node_w = node -> parent -> right;   // turn to case 4
                }	
                node_w -> color = node -> parent -> color;
                node -> parent -> color = BLACK;
                node_w -> left -> color = BLACK;
                right_rotate(tree, node -> parent);
                node = tree -> root;
            }
        }
    }
    node -> color = BLACK;
}

void rb_transplant(RB_TREE tree, RB_NODE node_u, RB_NODE node_v)
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

RB_NODE tree_minimum(RB_NODE node)
{
    while(node -> left != NULL)
    {
        node = node -> left;
    }
    return node;
}

void left_rotate(RB_TREE tree,RB_NODE node)
{
    RB_NODE node_y = node -> right;
    node -> right = node_y -> left;
    if(node_y -> left != NULL)
    {
      node_y -> left -> parent = node;
    }
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

void right_rotate(RB_TREE tree, RB_NODE node)
{
    RB_NODE node_x = node -> left;
    node -> left = node_x -> right;
    if(node_x -> right != NULL)
    {
        node_x -> right -> parent = node;
    }
    node_x -> parent = node -> parent;
    if(node -> parent == NULL)
    {
        tree -> root = node_x;
    }else if(node -> parent -> left == node)
    {
        node -> parent -> left = node_x;
    }else
    {
        node -> parent -> right = node_x;
    }
    node_x -> right = node;
    node -> parent = node_x;
}
