//
//  Visitor.c
//  OperatingSystemsAssignment
//
//  Created by Kirty Bol on 12/06/2019.
//  Copyright © 2019 Kirty Bol. All rights reserved.
//

#include "Visitor.h"

// Make a visitor to walk the tree
struct Visitor *create_visitor(struct Tree *start)
{
    struct Visitor *new_visitor = malloc(sizeof(struct Visitor));
    new_visitor->current = start;
    
    return new_visitor;
}

// Makes sure the visitor can go to the parent
bool go_left(struct Visitor *visitor)
{
    if(visitor->current->parent)
    {
        visitor->current = visitor->current->parent;
        return true;
    }
    else
    {
        //printf("%s\n", "There's no parent");
        return false;
    }
}

// Makes sure that the visitor can go to the child
bool go_right(struct Visitor *visitor)
{
    if(visitor->current->child_head)
    {
        visitor->current = visitor->current->child_head;
        return true;
    }
    else
    {
        //printf("%s\n", "Guess there is no child yet....");
        return false;
    }
    
}

// To be able to go up to his sibling
bool go_up(struct Visitor *visitor)
{
    if(visitor->current->previous)
    {
        visitor->current = visitor->current->previous;
        return true;
    }
    else
    {
        //printf("%s\n", "You're at the highest level");
        return false;
    }
}


// To be able to go down to his sibling
bool go_down(struct Visitor *visitor)
{
    if(visitor->current->next)
    {
        visitor->current = visitor->current->next;
        return true;
    }
    else
    {
        //printf("%s\n", "We can't go lower");
        return false;
    }
}

// To be able to go to the bottom of the tree
bool go_last_child(struct Visitor *visitor)
{
    if(visitor->current->open && visitor->current->child_head)
    {
        
        visitor->current = visitor->current->child_head;
        while (visitor->current->open && visitor->current->child_head)
        {
            visitor->current = visitor->current->next;
        }
        return true;
    }
    return false;
}

// Checks for the end of the tree
bool go_last_leaf(struct Visitor *visitor)
{
    // For when the files are not collapsed and the current has a child
    if (visitor->current->open && visitor->current->child_head)
    {
        // For as long as there are children to be found
        // Just continue
        while (visitor->current->open && visitor->current->child_head)
        {
            go_last_child(visitor);
        }
        return true;
    }
    return false;
}

// To be able to go up in the tree
bool go_previous(struct Visitor *visitor)
{
    if (visitor->current->previous)
    {
        visitor->current = visitor->current->previous;
        go_last_leaf(visitor);
        
        return true;
    }
    
    else if (visitor->current->parent)
    {
        visitor->current = visitor->current->parent;
        
        return true;
    }
    
    else {
        printf("No 'previous' exists!\n");
        
        return false;
    }
}

// To be able to go down in the tree
bool go_next(struct Visitor *visitor)
{
    // Checks if it's not collapsed and if there is a child
    if (visitor->current->open && visitor->current->child_head)
    {
        visitor->current = visitor->current->child_head;
        
        return true;
    }
    
    // Otherwise it goes to the sibling
    else if (visitor->current->next)
    {
        visitor->current = visitor->current->next;
        
        return true;
    }
    
    // For as long as the current has a parent
    while (visitor->current->parent)
    {
        // Check if the parent of the current has a sibling
        if (visitor->current->parent->next)
        {
            visitor->current = visitor->current->parent->next;
            
            return true;
        }
        // Otherwise goes to the parent of the current
        else
        {
            visitor->current = visitor->current->parent;
        }
    }
    return false;
}

// Close or open children
bool fold(struct Visitor *visitor)
{
    if (visitor->current->open)
    {
        visitor->current->open = false;
        
        return true;
    }
    else
    {
        visitor->current->open = true;
        
        return false;
    }
}
