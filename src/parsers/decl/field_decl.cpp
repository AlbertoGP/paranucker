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

parserDefine(FieldDecl);

#include "parsers/base/decl.h"

#include "nodes/decl/field_decl.h"

namespace Generic
{

void parseFieldDeclNode(FieldDeclNode *node)
{
    fillType(node);
    fillLocation(node);
    fillDeclLabel(node);
    Log::dump(node);

    setPrintField(node, DECL_C_BIT_FIELD, isBitField);
    node->isUnsigned = DECL_UNSIGNED(node->gccNode);
    if (node->isUnsigned)
        Log::dumpRaw(node, "- unsigned");
    else
        Log::dumpRaw(node, "- signed");
    setPrintField(node, DECL_VIRTUAL_P, isVirtual);
    setPrintField(node, DECL_PACKED, isBitPacked);

    fillDeclAutoGenerated(node);
    fillDeclAttributes(node);

    if (node->isBitField)
    {
        node->declBitType = static_cast<TypeNode*>(createParseNode(
            node,
            DECL_BIT_FIELD_TYPE(node->gccNode),
            "decl bit type"));
    }

    node->declSize = static_cast<IntegerCstNode*>(createParseNode(
        node,
        DECL_SIZE(node->gccNode),
        INTEGER_CST,
        "decl size"));

    node->initial = createParseNode(
        node,
        DECL_INITIAL(node->gccNode),
        "initial");

    node->qualifier = createParseNode(
        node,
        DECL_QUALIFIER(node->gccNode),
        "qualifier");
}

}