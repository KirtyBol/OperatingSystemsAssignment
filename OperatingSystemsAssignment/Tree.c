//
//  Tree.c
//  OperatingSystemsAssignment
//
//  Created by Kirty Bol on 29/05/2019.
//  Copyright © 2019 Kirty Bol. All rights reserved.
//

#include "Tree.h"

// Create a datatype for Tree
struct Tree *createTree (char *name)
{
    struct Tree *new_tree = malloc(sizeof(struct Tree));
    strcpy(new_tree->store_name, name);
    
    new_tree->parent = 0;
    new_tree->child_head = 0;
    new_tree->previous = 0;
    new_tree->next = 0;
    new_tree->open = true;
    
    return new_tree;
}

// Build the branches of the tree by looking for the children and linking them back to the parents
void insertTree(struct Tree *parent, struct Tree *child)
{
    if(!parent->child_head)
    {
        parent->child_head = child;
        child->parent = parent;
    }
    
    else
    {
        struct Tree *temp = parent->child_head;
        
        while (temp->next)
        {
            temp = temp->next;
        }
        
        temp->next = child;
        child->previous = temp;
        child->parent = parent;
    }
}

// Print the tree with indentations and all the children
void dumpTree(struct Tree *tree, struct Visitor *visitor, int tabLevel)
{
    indent(tabLevel);
    
    if(tree == visitor->current)
    {
        // Shows where you are in the directory
        printf("{%s}\n", tree->store_name);
    }
    else{
        printf("%s\n", tree->store_name);
    }
    
    // Works better when put before checking on the children
    // Check if the files have to collapse or not
    if(!tree->open)
    {
        indent(tabLevel + 1);
        printf("[Closed]\n");
        return;
    }
    
    // Check the children as long as there is a next
    // Make the tree storing the children with indentations
    if(tree->child_head)
    {
        struct Tree *temp = tree->child_head;
        dumpTree(temp, visitor, tabLevel + 1);
        
        while (temp->next)
        {
            temp = temp->next;
            dumpTree(temp, visitor, tabLevel + 1);
        }
    }
}

// for the indentation in the Dumptree
void indent (int tabLevel)
{
    for(int tabIndex = 0; tabIndex < tabLevel; tabIndex++)
    {
        printf("    ");
    }
    printf("-");
}
