//
//  main.c
//  INTERVAL-TREE
//
//  Created by dorothy on 15/11/18.
//  Copyright © 2015年 dorothy. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef enum int_color
{
    RED = 0,
    BLACK = 1
}INT_COLOR;

typedef int INT_MAX;

typedef struct interval
{
    int low;
    int high;
}*INT;

typedef struct int_node
{
    struct int_node *parent, *left, *right;
    INT interval;
    INT_MAX max;
    INT_COLOR color;
    
}*INT_NODE;

typedef struct int_tree
{
    INT_NODE root;
}*INT_TREE;

INT_NODE interval_search(INT_TREE tree, INT i);
void interval_insert(INT_TREE tree, INT_NODE node);
void interval_insert_fixup(INT_TREE tree, INT_NODE node);
void left_rotate(INT_TREE tree,INT_NODE node);
void right_rotate(INT_TREE tree, INT_NODE node);
void print_interval_tree(INT_TREE tree, INT_NODE node);
INT_NODE int_new_node(int low, int high);
bool is_overlap(INT_NODE node, INT i);
INT_MAX max_of_node(INT_NODE node);

int main(int argc, const char * argv[]) {
    INT_TREE tree = (INT_TREE) malloc(sizeof(struct int_tree));
    srand((unsigned)time(NULL));
    for(int i = 0; i < 10; i++)
    {
        int low = rand() % 30;
        int high = rand() % 30;
        if(low > high)
        {
            int tmp = low;
            low = high;
            high = tmp;
        }
        INT_NODE node = int_new_node(low, high);
        interval_insert(tree, node);
    }
    print_interval_tree(tree, tree -> root);
    INT i = (INT) malloc(sizeof(struct interval));
    i -> high = 18;
    i -> low = 15;
    INT_NODE node = interval_search(tree, i);
    printf("selected interval is: [%d, %d], max: %d, color %s", node -> interval -> low, node -> interval -> high, node -> max , node -> color == RED?"red":"black");
    printf("\n");
    
    return 0;
}

void print_interval_tree(INT_TREE tree, INT_NODE node)
{
    if(node != NULL)
    {
        printf("interval: [%d, %d] ", node -> interval -> low, node -> interval -> high);
        printf("max: %d ", node -> max);
        if(node -> color == BLACK)
        {
            printf("black\n");
        }else
        {
            printf("red\n");
        }
        print_interval_tree(tree, node -> left);
        print_interval_tree(tree, node -> right);
    }
}

void interval_insert(INT_TREE tree, INT_NODE node)
{
    INT_NODE node_y = NULL;
    INT_NODE node_x = tree -> root;
    while(node_x != NULL)
    {
        node_y = node_x;
        if(node -> interval -> low < node_x -> interval -> low)
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
    }else if(node -> interval -> low < node_y -> interval -> low)
    {
        node_y -> left = node;
    }else
    {
        node_y -> right = node;
    }
    node -> left = NULL;
    node -> right = NULL;
    node -> color = RED;
    INT_NODE tmp_node = node;
    while(tmp_node -> parent != NULL)
    {
        tmp_node = tmp_node -> parent;
        INT_MAX max = max_of_node(tmp_node);
        tmp_node -> max = max;
    }
    interval_insert_fixup(tree, node);
}

INT_NODE interval_search(INT_TREE tree, INT i)
{
    INT_NODE node_x = tree -> root;
    while (node_x != NULL && !is_overlap(node_x, i))
    {
        if(node_x -> left != NULL && node_x -> left -> max >= i -> low)
        {
            node_x = node_x -> left;
        }else
        {
            node_x = node_x -> right;
        }
    }
    return node_x;
}

bool is_overlap(INT_NODE node, INT i)
{
    if(i -> low < node -> interval -> high && node -> interval -> low < i -> high)
    {
        return true;
    }
    return false;
}

void interval_insert_fixup(INT_TREE tree, INT_NODE node)
{
    while(node -> parent != NULL && node -> parent -> color == RED)
    {
        if(node -> parent == node -> parent -> parent -> left)
        {
            INT_NODE node_uncle = node -> parent -> parent -> right; // uncle's node
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
            INT_NODE node_uncle = node -> parent -> parent -> left;
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

void left_rotate(INT_TREE tree, INT_NODE node)
{
    INT_NODE node_y = node -> right;
    node -> right = node_y -> left;
    if(node_y -> left != NULL)
    {
        node_y -> left -> parent = node;
    }
    node_y -> parent = node -> parent;
    if(node -> parent == NULL)
    {        tree -> root = node_y;
    }else if(node == node -> parent -> left)
    {
        node -> parent -> left = node_y;
    }else
    {
        node -> parent -> right = node_y;
    }
    node_y -> left = node;
    node -> parent = node_y;
    node_y -> max = node -> max;
    node -> max = max_of_node(node);
}

void right_rotate(INT_TREE tree, INT_NODE node)
{
    INT_NODE node_x = node -> left;
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
    node_x -> max = node -> max;
    node -> max = max_of_node(node);
}

INT_NODE int_new_node(int low, int high)
{
    INT interval = (INT) malloc(sizeof(struct interval));
    interval -> low = low;
    interval -> high = high;
    INT_NODE new_node = (INT_NODE) malloc(sizeof(struct int_node));
    new_node -> interval = interval;
    new_node -> max = interval -> high;
    new_node -> color = RED;
    new_node -> right = NULL;
    new_node -> left = NULL;
    new_node -> parent = NULL;
    return new_node;
}

INT_MAX max_of_node(INT_NODE node)
{
    INT_MAX max1 = node -> interval -> high;
    INT_MAX max2 = max1;
    INT_MAX max3 = max1;
    
    if(node -> left != NULL)
    {
        max2 = node -> left -> max;
    }
    if(node -> right != NULL)
    {
        max3 = node -> right -> max;
    }
    
    INT_MAX max = max1;
    if(max < max2)
    {
        max = max2;
    }
    if(max < max3)
    {
        max = max3;
    }
    return max;
}
