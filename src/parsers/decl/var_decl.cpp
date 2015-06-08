/*
 *  Copyright (C) 2015  Andrei Karas
 *
 *  This file is part of AstDumper.
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

    fillDeclAutoGenerated(node);
    fillDeclAttributes(node);

    node->declSize = static_cast<IntegerCstNode*>(createParseNode(
        node,
        DECL_SIZE(node->gccNode),
        INTEGER_CST,
        "decl size"));

    node->varType = static_cast<TypeNode*>(createParseNode(
        node,
        TREE_TYPE(node->gccNode),
        "var type"));

    // not loading because it reference self recursivly
/*
    node->initial = createParseNode(
        node,
        DECL_INITIAL(node->gccNode),
        "initial");
*/
}

}
