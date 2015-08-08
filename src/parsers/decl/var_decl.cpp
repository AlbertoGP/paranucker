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

#include "includes/parserincludes.h"

parserDefine(VarDecl);

#include "nodesmap.h"

#include "parsers/base/decl.h"

#include "nodes/decl/var_decl.h"

namespace Generic
{

void parseVarDeclNode(VarDeclNode *node)
{
    fillType(node);
    fillLocation(node);
    fillDeclLabel(node);

    Log::dump(node);

    setPrintField(node, DECL_THIS_STATIC, isStatic);
    setPrintField(node, DECL_REGISTER, isRegister);
    setPrintField(node, TREE_USED, isUsed);
    setPrintField(node, DECL_VIRTUAL_P, isVirtual);

    fillDeclAutoGenerated(node);

    if (isIn(node->gccNode, foundNodesMap))
    {
        VarDeclNode *const oldNode = static_cast<VarDeclNode*>(
            foundNodesMap[node->gccNode]);
        if (node->parseChilds <= 0)
        {
            updateNodesMap[node] = oldNode;
            return;
        }

        node->declSize = static_cast<IntegerCstNode*>(createParseNode(
            node,
            DECL_SIZE(node->gccNode),
            INTEGER_CST,
            "decl size 2",
            15));

        node->initial = createParseNode(
            node,
            DECL_INITIAL(node->gccNode),
            "initial 2",
            20);

        node->varType = static_cast<TypeNode*>(createParseNode(
            node,
            TREE_TYPE(node->gccNode),
            "var type 2",
            15));

        return;
    }
    else
    {
        foundNodesMap[node->gccNode] = node;
    }

    fillDeclAttributes(node);

    if (node->parseChilds <= 0)
        return;

    node->declSize = static_cast<IntegerCstNode*>(createParseNode(
        node,
        DECL_SIZE(node->gccNode),
        INTEGER_CST,
        "decl size"));

    // not loading because it reference self recursivly
    node->initial = createParseNode(
        node,
        DECL_INITIAL(node->gccNode),
        "initial",
        20);

    node->varType = static_cast<TypeNode*>(createParseNode(
        node,
        TREE_TYPE(node->gccNode),
        "var type"));

    node->complete = true;
}

void parseVarDeclNode(VarDeclNode *node1, VarDeclNode *node2)
{
    if (!node1 || !node2)
        return;

    node1->declSize = node2->declSize;
    node1->initial = node2->initial;
    node1->varType = node2->varType;
}

}
