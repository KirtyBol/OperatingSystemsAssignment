//
//  Tree.h
//  OperatingSystemsAssignment
//
//  Created by Kirty Bol on 29/05/2019.
//  Copyright © 2019 Kirty Bol. All rights reserved.
//

#pragma once

#include "Visitor.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Tree{
    //#define Tree struct Tree
    struct Tree *previous;
    struct Tree *next;
    struct Tree *child_head;
    struct Tree *parent;
    
    char store_name [100];
    char path [1000];
    bool open;
};

struct Tree *createTree (char *name);
void insertTree (struct Tree *parent, struct Tree *child);
void dumpTree (struct Tree *tree, struct Visitor *visitor, int tab);
void indent (int tabLevel);
