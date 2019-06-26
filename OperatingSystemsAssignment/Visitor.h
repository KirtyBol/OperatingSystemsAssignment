//
//  Visitor.h
//  OperatingSystemsAssignment
//
//  Created by Kirty Bol on 12/06/2019.
//  Copyright © 2019 Kirty Bol. All rights reserved.
//

#pragma once

#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Visitor
{
    struct Tree *current;
};

struct Visitor *create_visitor(struct Tree *start);
bool go_left(struct Visitor *visitor);
bool go_right(struct Visitor *visitor);
bool go_up(struct Visitor *visitor);
bool go_down(struct Visitor *visitor);
bool go_last_child(struct Visitor *visitor);
bool go_previous(struct Visitor *visitor);
bool go_next(struct Visitor *visitor);
bool fold(struct Visitor *visitor);
