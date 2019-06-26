//
//  main.c
//  OperatingSystemsAssignment
//
//  Created by Kirty Bol on 29/05/2019.
//  Copyright © 2019 Kirty Bol. All rights reserved.
//

#include "Tree.h"
#include "Visitor.h"

#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>

// Find and show files in the directory
void show_files(char *treePath, struct Tree *parent)
{
    char path [1000000];
    struct dirent *dir_path;
    DIR *dir = opendir(treePath);
    
    // To avoid NULL pointer and to make sure that we are reading a directory
    if(!dir)
    {
        return;
    }
    
    // Check the children and store them
    while ((dir_path = readdir(dir)) != 0)
    {
        // Check the strings to see if there are children around
        if(strcmp(dir_path->d_name, ".") != 0 && strcmp(dir_path->d_name, "..") != 0)
        {
            struct Tree *dir_tree = createTree(dir_path->d_name);
            
            // Compare the parts and store them
            strcpy(path, treePath);
            strcat(path, "/");
            strcat(path, dir_path->d_name);
            strcpy(dir_tree->path, path);
            
            insertTree(parent, dir_tree);
        }
    }
    closedir(dir);
    
    // Check the files from the children and store them
    struct Tree *temp = parent->child_head;
    
    // Keep continuing as long as there is a next
    while (temp->next)
    {
        temp = temp->next;
        strcpy(path, treePath);
        strcat(path, "/");
        strcat(path, temp->store_name);
        
        show_files(path, temp);
    }
}

void open_file(struct Tree *file)
{
    char command[1000];
    printf("File path: %s\n", file->path);
    if (strstr(file->path, ".") != NULL)
    {
        printf("why you no workinh");
        strcpy(command, "open");
        strcat(command, " ");
        strcat(command, file->path);
        
        printf(file->path);
        system(command);
    }
}

int main()
{
    struct Tree *rootTree = createTree("Start");
    struct Visitor *cursor = create_visitor(rootTree);
    
    // Read directory
    show_files("/Users/Kirty/Test", rootTree);
    
    // Show the directory tree
    dumpTree(rootTree, cursor, 0);
    char wait[3];
    printf("%s\n", wait);
    
    char command[3];
    
    while (true) {
        printf("\n");
        printf("w = go up           r = go up to sibling \n");
        printf("s = go down         f = go down to sibling \n");
        printf("a = go left         d = go right \n");
        printf("c = collapse files  q = quit program \n");
        printf("\n");
        printf("Make your choice: ");
        
        scanf("%s", command);
        if(command[0] == 'w')
        {
            go_previous(cursor);
        }
        else if(command[0] == 'r')
        {
            go_up(cursor);
        }
        else if (command[0] == 's')
        {
            go_next(cursor);
        }
        else if (command[0] == 'f')
        {
            go_down(cursor);
        }
        else if (command[0] == 'a')
        {
            go_left(cursor);
        }
        else if(command[0] == 'd')
        {
            go_right(cursor);
        }
        else if(command[0] == 'o')
        {
            open_file(cursor->current);
        }
        else if(command[0] == 'c')
        {
            fold(cursor);
        }
        else if(command[0] == 'q')
        {
            break;
        }
        system("clear");
        dumpTree(rootTree, cursor, 0);
    }
}
