/**
 * This file exists to help you check if your tree is working correctly. You can run it with the following command line:
 *
 * You are allowed to add or remove parts of the test code if you wish. The contents of this file will not be used to
 * grade your assignment.
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

// You are allowed to change anything about this function to your preferences
int main(){
    Tree* tree = tree_create();

    printf("Checking basic functionality doesn't crash...\n");
    char* name1 = malloc(sizeof(char) * 10);
    char* name2 = malloc(sizeof(char) * 10);
    char* name3 = malloc(sizeof(char) * 10);
    char* name4 = malloc(sizeof(char) * 10);
    strcpy(name1, "Peter");
    strcpy(name2, "Joanna");
    strcpy(name3, "Margareth");
    strcpy(name4, "Margareth");
    tree_insert(tree, 42, name1);
    tree_insert(tree, 21, name2);
    tree_insert(tree, 83, name3);

    printf("Checking tree print method...\n");
    tree_print(tree, 1);

    printf("Testing find method...\n");
    if (!tree_find(tree, 83, "Margareth")){
        fprintf(stderr, "Could not find an item that was recently inserted\n");
        return 1;
    }

    printf("Testing erase method...\n");
    char* name3_erase = malloc(sizeof(char) * 10);
    strcpy(name3_erase, "Margareth");
    tree_erase(tree, 83, name3);
    free(name3_erase);
    if(tree_find(tree, 83, "Margareth")){
        fprintf(stderr, "Found an item that was supposed to be removed (leaf node)\n");
        return 3;
    }
    tree_insert(tree, 83, name4);
    char* name1_erase = malloc(sizeof(char) * 10);
    strcpy(name1_erase, "Peter");
    tree_erase(tree, 42, name1_erase);
    free(name1_erase);
    if(tree_find(tree, 42, "Peter")){
        fprintf(stderr, "Found an item that was supposed to be removed (node with children)\n");
        return 4;
    }

    printf("Stress testing your tree (to help you check for possible memory errors)\n");

    // This makes the results reproducable
    srand(0xC0FFEE);
    for (int i = 0; i < 10000; i++){
        int age = (int) (random() % 1000);
        char* name = malloc(sizeof(char) * 10);
        sprintf(name, "Name%d", age);
        char* name_erase = malloc(sizeof(char) * 10);
        sprintf(name_erase, "Name%d", age);

        if (tree_find(tree, age, name)){
            tree_erase(tree, age, name_erase);
            free(name);
        } else {
            tree_insert(tree, age, name);
        }
        free(name_erase);
    }

    // Feel free to add your own tests here or somewhere else in this file

    free(name1);
    free(name2);
    free(name3);
    free(name4);
    tree_delete(tree);
    free(tree);
    printf("The test succeeded\n");
    return 0;
}