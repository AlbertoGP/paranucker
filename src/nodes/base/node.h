/*
 *  Copyright (C) 2015  Andrei Karas
 *
 *  This file is part of Paranoid null checker.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef NODES_BASE_NODE_H
#define NODES_BASE_NODE_H

#include "includes.h"

#include <string>
#include <vector>

extern int allocations;

struct Node
{
    Node() :
        parent(nullptr),
        nodeTypeName(),
        label(),
        file(),
        tag(),
        childs(),
        gccNode(nullptr),
        nodeType(ERROR_MARK),
        location(0),
        line(-1),
        column(-1),
        treeNumber(0),
        indent(0),
        parseChilds(INT_MAX),
        noLabel(false),
        complete(false)
    {
        allocations ++;
    }

    ~Node()
    {
        allocations --;
    }

    std::string getIndent() const
    {
        std::string str;
        for (int f = 0; f < indent; f ++)
            str.append(" ");
        return str;
    }

    Node *parent;
    std::string nodeTypeName;
    std::string label;
    std::string file;
    std::string tag;
    std::vector<Node*> childs;
    tree gccNode;
    tree_code nodeType;
    location_t location;
    int line;
    int column;
    int treeNumber;
    int indent;
    int parseChilds;
    bool noLabel;
    bool complete;
};

bool operator ==(const Node *const node, const tree_code &code);

bool operator !=(const Node *const node, const tree_code &code);

#endif // NODES_BASE_NODE_H
