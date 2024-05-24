#ifndef C_IMPLEMENTATION_TREE_H
#define C_IMPLEMENTATION_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    /**
     * Left child of this node
     */
    struct Node* left;
    /**
     * Right child of this node
     */
    struct Node* right;
    /**
     * The age of the data in this node
     */
    int age;
    /**
     * The name of the data in this node
     */
    char* name;

    /**
     * Node's height
     */
    int height;
} Node;

typedef struct Tree {
    Node *root;
} Tree;

/**
 * Create a new tree
 *
 * DO NOT MODIFY THE METHOD SIGNATURE
 * @param age The age value for the first data point
 * @param name The name value for the first data point
 * @return The root Node of the tree
 */
Tree* tree_create();

/**
 * Delete an entire tree. This will delete the passed Node and all children below it
 *
 * DO NOT MODIFY THE METHOD SIGNATURE
 * @param node The root Node of the tree to delete.
 */
void tree_delete(Tree* tree);

/**
 * Insert a new data point into the tree
 *
 * DO NOT MODIFY THE METHOD SIGNATURE
 * @param tree The root node of the tree
 * @param age The age part of the data point
 * @param name The name part of the data point
 */
void tree_insert(Tree* tree, int age, char* name);

/**
 * Remove a data point from a tree
 *
 * DO NOT MODIFY THE METHOD SIGNATURE
 * @param tree The root node of the tree
 * @param age The age part of the data point to delete
 * @param name The name part of the data point to delete
 */
void tree_erase(Tree* tree, int age, char* name);

/**
 * Print a tree in the following format:
 * [<data>, <left>, <right>]
 * where the elements above have the following format:
 *  <data>             {<age:int>: "<name:string>"}
 *  <left>, <right>:   The same format as the root node. When a child node is NULL, the string NULL is to be printed.
 *
 * DO NOT MODIFY THE METHOD SIGNATURE
 * @param tree The root node for the tree to print
 * @param printNewline Whether or not to print a newline
 */
void tree_print(Tree *tree, int printNewline);

/**
 * Find an item in the tree. Should return the tree node containing the data specified if found, or NULL if not
 *
 * DO NOT MODIFY THE METHOD SIGNATURE
 * @param tree The tree to search in
 * @param age The age to look for
 * @param name The name to look for
 * @return
 */
Node* tree_find(Tree* node, int age, char* name);


Node* find_parent(Tree* tree, Node* node, int age, char* name);
Node* find_candidate_to_replace(Node* node);
void recount_height(Node* node);

Node* rebalance(Node* node);
Node* ll_turn(Node* node);
Node* rr_turn(Node* node);
Node* rl_turn(Node* node);
Node* lr_turn(Node* node);

int calculate_balance(Node* node);
int check_ok(Node* node);

#endif //C_IMPLEMENTATION_TREE_H
