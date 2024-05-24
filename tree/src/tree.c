#include "tree.h"

int check_ok(Node* node) {
    int cur = 0;
    if ((!node->left || node->left->age <= node->age) && ((!node->right || node->right->age > node->age))) {
        cur = 1;
    }
    int left = node->left ? check_ok(node->left) : 1;
    int right = node->right ? check_ok(node->right) : 1;

    return cur && left && right;
}

/**
 * Please correct the contents of this file to make sure all functions here do what they are supposed to do if you find
 * that they do not work as expected.
 */

// Tree function: you are allowed to change the contents, but not the method signature
Tree* tree_create(){
    Tree *tree = malloc(sizeof(Tree));
    tree->root = NULL;

    return tree;
}

// Helper function: you are allowed to change this to your preferences
void tree_node_delete(Node* node) {
    if (node == NULL) return;

    tree_node_delete(node->left);
    tree_node_delete(node->right);

    free(node->name);
    free(node);
}

// Tree function: you are allowed to change the contents, but not the method signature
void tree_delete(Tree* tree) {
    tree_node_delete(tree->root);
}


// Helper function: you are allowed to change this to your preferences
void node_insert(Node* node, int age, char* name) {
    if (age <= node->age){
        if (node->left == NULL){
            Node* newLeft = malloc(sizeof(Node));
            newLeft->age = age;
            newLeft->name = name;
            newLeft->height = 0;
            newLeft->left = NULL;
            newLeft->right = NULL;
            node->left = newLeft;
        } else {
            node_insert(node->left, age, name);
        }
    } else {
        if (node->right == NULL){
            Node* newRight = malloc(sizeof(Node));
            newRight->age = age;
            newRight->name = name;
            newRight->height = 0;
            newRight->left = NULL;
            newRight->right = NULL;
            node->right = newRight;
        } else {
            node_insert(node->right, age, name);
        }
    }
}

// Tree function: you are allowed to change the contents, but not the method signature
void tree_insert(Tree* tree, int age, char* name) {
    if (tree->root == NULL) {
        Node *node = malloc(sizeof(Node));
        node->name = name;
        node->age = age;
        node->height = 0;
        node->left = NULL;
        node->right = NULL;
        tree->root = node;
    } else {
        node_insert(tree->root, age, name);
    }

    recount_height(tree->root);
    tree->root = rebalance(tree->root);
    recount_height(tree->root);
}

Node* find_candidate_to_replace(Node* node) {
    if (node->left != NULL) {
        return find_candidate_to_replace(node->left);
    }

    return node;
}

// Tree function: you are allowed to change the contents, but not the method signature
void tree_erase(Tree* tree, int age, char* name) {
    Node* node_to_delete = tree_find(tree, age, name);
    if (node_to_delete == NULL) {
        return;
    }
    Node* node_parent = find_parent(tree, tree->root, age, name);
    Node* replacement = NULL;

    if (node_to_delete->left != NULL || node_to_delete->right != NULL) {
        if (node_to_delete->right == NULL) {
            replacement = node_to_delete->left;
        }
        else if (node_to_delete->left == NULL) {
            replacement = node_to_delete->right;
        } else {
            replacement = find_candidate_to_replace(node_to_delete->right);
            Node* to_delete_left = node_to_delete->left;
            Node* to_delete_right = node_to_delete->right;
            Node* replacement_parent = find_parent(tree, tree->root, replacement->age, replacement->name);

            if (replacement->age <= replacement_parent->age) {
                replacement_parent->left = replacement->right ? replacement->right : NULL;
            } else {
                replacement_parent->right = replacement->right ? replacement->right : NULL;
            }

            replacement->left = to_delete_left;
            replacement->right = replacement != to_delete_right ? to_delete_right : replacement->right;
        }
    }

    if (node_parent != NULL) {
        if (node_to_delete->age <= node_parent->age) {
            node_parent->left = replacement;
        } else {
            node_parent->right = replacement;
        }
    } else {
        tree->root = replacement;
    }

    free(node_to_delete->name);
    free(node_to_delete);

    recount_height(tree->root);
    tree->root = rebalance(tree->root);
    recount_height(tree->root);
}

// Helper function: you are allowed to change this to your preferences
void tree_print_node(Node* node){
    if (node == NULL) {
        printf("null");
        return;
    }

    printf("[");
    printf("{\"%d\":\"%s\"},", node->age, node->name);
    tree_print_node(node->left);
    printf(",");
    tree_print_node(node->right);
    printf("]");
}

// Tree function: you are allowed to change the contents, but not the method signature
void tree_print(Tree* tree, int printNewline){
    if (tree == NULL) {
        printf("null\n");
        return;
    }

    tree_print_node(tree->root);

    if (printNewline){
        printf("\n");
    }
}

Node* find_parent(Tree* tree, Node* node, int age, char* name) {
    if (tree->root == node && node->age == age && !strcmp(node->name, name)) {
        return NULL;
    }

    if ((node->left && node->left->age == age && !strcmp(node->left->name, name))
        ||
        (node->right && node->right->age == age && !strcmp(node->right->name, name))
    ) {
        return node;
    }

    if (age <= node->age && node->left) {
        return find_parent(tree, node->left, age, name);
    } else if (age > node->age && node->right) {
        return find_parent(tree, node->right, age, name);
    }
    return NULL;
}

// Helper function: you are allowed to change this to your preferences
Node* node_find(Node* node, int age, char* name) {
    if (node == NULL) {
        return NULL;
    }

    if (node->age == age && !strcmp(node->name, name)) {
        return node;
    }

    if (age <= node->age) {
        return node_find(node->left, age, name);
    } else {
        return node_find(node->right, age, name);
    }
}

// Tree function: you are allowed to change the contents, but not the method signature
Node* tree_find(Tree* tree, int age, char* name) {
    return node_find(tree->root, age, name);
}

void recount_height(Node* node) {
    if (node == NULL) return;

    recount_height(node->right);
    recount_height(node->left);

    if (node->left == NULL && node->right == NULL) {
        node->height = 1;
    } else {
        int leftHeight = node->left ? node->left->height : 0;
        int rightHeight = node->right ? node->right->height : 0;
        node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
    }
}

Node* rebalance(Node* node) {
    if (node == NULL) return node;

    recount_height(node);
    node->right = rebalance(node->right);
    recount_height(node);
    node->left = rebalance(node->left);
    recount_height(node);

    int balance = calculate_balance(node);
    
    Node* newTop = node;
    if (balance >= 2) {
        int right_balance = calculate_balance(node->right);
        if (right_balance > 0) {
            newTop = ll_turn(node);
        } else {
            newTop = rl_turn(node);
        }
    } else if (balance <= -2) {
        int left_balance = calculate_balance(node->left);
        if (left_balance < 0) {
            newTop = rr_turn(node);
        } else {
            newTop = lr_turn(node);
        }
    }

    return newTop;
}

Node* ll_turn(Node* node) {
    Node* right = node->right;

    node->right = right->left;
    right->left = node;

    return right;
}

Node* rr_turn(Node* node) {
    Node* left = node->left;

    node->left = left->right;
    left->right = node;

    return left;
}

Node* lr_turn(Node* node) {
    node->left = ll_turn(node->left);
    return rr_turn(node);
}

Node* rl_turn(Node* node) {
    node->right = rr_turn(node->right);
    return ll_turn(node);
}

int calculate_balance(Node* node) {
    int leftHeight = node->left ? node->left->height : 0;
    int rightHeight = node->right ? node->right->height : 0;
    return rightHeight - leftHeight;
}
