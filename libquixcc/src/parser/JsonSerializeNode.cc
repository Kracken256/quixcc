////////////////////////////////////////////////////////////////////////////////////
///                                                                              ///
///    ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░ ░▒▓██████▓▒░    ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░   ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░          ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓██████▓▒░░▒▓█▓▒░      ░▒▓█▓▒░          ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░          ///
///   ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░   ///
///    ░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░ ░▒▓██████▓▒░    ///
///      ░▒▓█▓▒░                                                                 ///
///       ░▒▓██▓▒░                                                               ///
///                                                                              ///
///     * QUIX LANG COMPILER - The official compiler for the Quix language.      ///
///     * Copyright (c) 2024, Wesley C. Jones. All rights reserved.              ///
///     * License terms may be found in the LICENSE file.                        ///
///                                                                              ///
////////////////////////////////////////////////////////////////////////////////////

#define QUIXCC_INTERNAL

#include <parse/JsonSerialize.h>
#include <parse/nodes/AllNodes.h>
#include <lexer/Lex.h>

std::string escape_json(const std::string &input)
{
    std::string output;
    output.reserve(input.length() * 2); // Reserving enough space for escaped characters

    for (char ch : input)
    {
        switch (ch)
        {
        case '"':
            output += "\\\"";
            break;
        case '\\':
            output += "\\\\";
            break;
        case '\b':
            output += "\\b";
            break;
        case '\f':
            output += "\\f";
            break;
        case '\n':
            output += "\\n";
            break;
        case '\r':
            output += "\\r";
            break;
        case '\t':
            output += "\\t";
            break;
        default:
            if (ch < ' ')
            {
                // Unicode escape sequence
                char hex[7];
                snprintf(hex, sizeof(hex), "\\u%04x", ch);
                output += hex;
            }
            else
            {
                output += ch;
            }
            break;
        }
    }

    return output;
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::ParseNode *node) const
{
    return "{\"ntype\":\"ParseNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::ExprNode *node) const
{
    return "{\"ntype\":\"ExprNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::ConstExprNode *node) const
{
    return "{\"ntype\":\"ConstExprNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::StmtNode *node) const
{
    return "{\"ntype\":\"StmtNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::TypeNode *node) const
{
    return "{\"ntype\":\"TypeNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::RootNode *node) const
{
    return "{\"ntype\":\"RootNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::DeclNode *node) const
{
    return "{\"ntype\":\"DeclNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::DefNode *node) const
{
    return "{\"ntype\":\"DefNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::BlockNode *node) const
{
    std::string str = "{\"ntype\":\"BlockNode\",\"children\":[";
    for (auto it = node->m_stmts.begin(); it != node->m_stmts.end(); ++it)
    {
        str += (*it)->to_json(*this);
        if (it != node->m_stmts.end() - 1)
        {
            str += ",";
        }
    }

    return str + "]}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::BasicTypeNode *node) const
{
    return "{\"ntype\":\"BasicTypeNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::ConstUnaryExprNode *node) const
{
    std::string str = "{\"ntype\":\"ConstUnaryExprNode\",\"op\":\"";
    str += operator_map_inverse.at(node->m_op);
    str += "\",\"operand\":";
    str += node->m_expr->to_json(*this);

    return str + "}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::ConstBinaryExprNode *node) const
{
    std::string str = "{\"ntype\":\"ConstBinaryExprNode\",\"op\":\"";
    str += operator_map_inverse.at(node->m_op);
    str += "\",\"lhs\":";
    str += node->m_lhs->to_json(*this);
    str += ",\"rhs\":";
    str += node->m_rhs->to_json(*this);

    return str + "}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::IdentifierNode *node) const
{
    return "{\"ntype\":\"IdentifierNode\",\"name\":\"" + escape_json(node->m_name) + "\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::U8TypeNode *node) const
{
    return "{\"ntype\":\"U8TypeNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::U16TypeNode *node) const
{
    return "{\"ntype\":\"U16TypeNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::U32TypeNode *node) const
{
    return "{\"ntype\":\"U32TypeNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::U64TypeNode *node) const
{
    return "{\"ntype\":\"U64TypeNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::I8TypeNode *node) const
{
    return "{\"ntype\":\"I8TypeNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::I16TypeNode *node) const
{
    return "{\"ntype\":\"I16TypeNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::I32TypeNode *node) const
{
    return "{\"ntype\":\"I32TypeNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::I64TypeNode *node) const
{
    return "{\"ntype\":\"I64TypeNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::F32TypeNode *node) const
{
    return "{\"ntype\":\"F32TypeNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::F64TypeNode *node) const
{
    return "{\"ntype\":\"F64TypeNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::BoolTypeNode *node) const
{
    return "{\"ntype\":\"BoolTypeNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::CharTypeNode *node) const
{
    return "{\"ntype\":\"CharTypeNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::VoidTypeNode *node) const
{
    return "{\"ntype\":\"VoidTypeNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::StringTypeNode *node) const
{
    return "{\"ntype\":\"StringTypeNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::StructTypeNode *node) const
{
    return "{\"ntype\":\"StructTypeNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::UnionTypeNode *node) const
{
    return "{\"ntype\":\"UnionTypeNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::ArrayTypeNode *node) const
{
    return "{\"ntype\":\"ArrayTypeNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::UserTypeNode *node) const
{
    return "{\"ntype\":\"UserTypeNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::LiteralNode *node) const
{
    return "{\"ntype\":\"LiteralNode\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::IntegerLiteralNode *node) const
{
    return "{\"ntype\":\"IntegerLiteralNode\",\"value\":\"" + node->m_val + "\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::FloatLiteralNode *node) const
{
    return "{\"ntype\":\"FloatLiteralNode\",\"value\":\"" + node->m_val + "\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::StringLiteralNode *node) const
{
    return "{\"ntype\":\"StringLiteralNode\",\"value\":\"" + escape_json(node->m_val) + "\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::CharLiteralNode *node) const
{
    return "{\"ntype\":\"CharLiteralNode\",\"value\":\"" + node->m_val + "\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::BoolLiteralNode *node) const
{
    return "{\"ntype\":\"BoolLiteralNode\",\"value\":\"" + std::string(node->m_val ? "true" : "false") + "\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::VarDeclNode *node) const
{
    std::string str = "{\"ntype\":\"VarDeclNode\",\"name\":\"";
    str += escape_json(node->m_name);
    str += "\",\"type\":";
    str += node->m_type->to_json(*this);
    str += ",\"value\":";
    str += node->m_init->to_json(*this);
    str += ",\"deprecated\":";
    str += std::string(node->m_is_deprecated ? "true" : "false");
    str += ",\"mutable\":";
    str += std::string(node->m_is_mut ? "true" : "false");
    str += ",\"static\":";
    str += std::string(node->m_is_static ? "true" : "false");
    str += ",\"thread_local\":";
    str += std::string(node->m_is_thread_local ? "true" : "false");
    return str + "}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::LetDeclNode *node) const
{
    std::string str = "{\"ntype\":\"LetDeclNode\",\"name\":\"";
    str += escape_json(node->m_name);
    str += "\",\"type\":";
    str += node->m_type->to_json(*this);
    str += ",\"value\":";
    str += node->m_init->to_json(*this);
    str += ",\"deprecated\":";
    str += std::string(node->m_is_deprecated ? "true" : "false");
    str += ",\"mutable\":";
    str += std::string(node->m_is_mut ? "true" : "false");
    str += ",\"static\":";
    str += std::string(node->m_is_static ? "true" : "false");
    str += ",\"thread_local\":";
    str += std::string(node->m_is_thread_local ? "true" : "false");
    return str + "}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::ConstDeclNode *node) const
{
    std::string str = "{\"ntype\":\"ConstDeclNode\",\"name\":\"";
    str += escape_json(node->m_name);
    str += "\",\"type\":";
    str += node->m_type->to_json(*this);
    str += ",\"value\":";
    str += node->m_init->to_json(*this);
    str += ",\"deprecated\":";
    str += std::string(node->m_is_deprecated ? "true" : "false");
    return str + "}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::StructDeclNode *node) const
{
    return "{\"ntype\":\"StructDeclNode\",\"name\":\"" + escape_json(node->m_name) + "\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::UnionDeclNode *node) const
{
    return "{\"ntype\":\"UnionDeclNode\",\"name\":\"" + escape_json(node->m_name) + "\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::EnumDeclNode *node) const
{
    return "{\"ntype\":\"EnumDeclNode\",\"name\":\"" + escape_json(node->m_name) + "\"}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::FunctionDeclNode *node) const
{
    std::string str = "{\"ntype\":\"FunctionDeclNode\",\"name\":\"";
    str += escape_json(node->m_name);
    str += "\",\"params\":[";
    for (auto it = node->m_params.begin(); it != node->m_params.end(); ++it)
    {
        str += (*it)->to_json(*this);
        if (it != node->m_params.end() - 1)
        {
            str += ",";
        }
    }

    str += "],\"return_type\":";
    str += node->m_return_type->to_json(*this);
    str += ",\"variadic\":";
    str += std::string(node->m_variadic ? "true" : "false");
    str += ",\"pure\":";
    str += std::string(node->m_pure ? "true" : "false");
    str += ",\"thread_safe\":";
    str += std::string(node->m_thread_safe ? "true" : "false");
    str += ",\"foreign\":";
    str += std::string(node->m_foreign ? "true" : "false");
    str += ",\"nothrow\":";
    str += std::string(node->m_nothrow ? "true" : "false");
    return str + "}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::StructDefNode *node) const
{
    std::string str = "{\"ntype\":\"StructDefNode\",\"name\":\"";
    str += escape_json(node->m_name);
    str += "\",\"fields\":[";
    for (auto it = node->m_fields.begin(); it != node->m_fields.end(); ++it)
    {
        str += (*it)->to_json(*this);
        if (it != node->m_fields.end() - 1)
        {
            str += ",";
        }
    }

    return str + "]}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::StructFieldNode *node) const
{
    std::string str = "{\"ntype\":\"StructFieldNode\",\"name\":\"";
    str += escape_json(node->m_name);
    str += "\",\"type\":";
    str += node->m_type->to_json(*this);
    str += ",\"value\":";
    str += (node->m_value ? node->m_value->to_json(*this) : "null");
    return str + "}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::UnionDefNode *node) const
{
    std::string str = "{\"ntype\":\"UnionDefNode\",\"name\":\"";
    str += escape_json(node->m_name);
    str += "\",\"fields\":[";
    for (auto it = node->m_fields.begin(); it != node->m_fields.end(); ++it)
    {
        str += (*it)->to_json(*this);
        if (it != node->m_fields.end() - 1)
        {
            str += ",";
        }
    }

    return str + "}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::UnionFieldNode *node) const
{
    std::string str = "{\"ntype\":\"UnionFieldNode\",\"name\":\"";
    str += escape_json(node->m_name);
    str += "\",\"type\":";
    str += node->m_type->to_json(*this);
    str += ",\"value\":";
    str += (node->m_value ? node->m_value->to_json(*this) : "null");
    return str + "}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::EnumDefNode *node) const
{
    std::string str = "{\"ntype\":\"EnumDefNode\",\"name\":\"";
    str += escape_json(node->m_name);
    str += "\",\"fields\":[";
    for (auto it = node->m_fields.begin(); it != node->m_fields.end(); ++it)
    {
        str += (*it)->to_json(*this);
        if (it != node->m_fields.end() - 1)
        {
            str += ",";
        }
    }

    return str + "]}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::EnumFieldNode *node) const
{
    std::string str = "{\"ntype\":\"EnumFieldNode\",\"name\":\"";
    str += escape_json(node->m_name);
    str += "\",\"value\":";
    str += node->m_value->to_json(*this);
    return str + "}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::FunctionDefNode *node) const
{
    std::string str = "{\"ntype\":\"FunctionDefNode\",\"decl\":";
    str += node->m_decl->to_json(*this);
    str += ",\"body\":";
    str += node->m_body->to_json(*this);
    return str + "}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::SubsystemNode *node) const
{
    std::string str = "{\"ntype\":\"SubsystemNode\",\"name\":\"";
    str += escape_json(node->m_name);
    str += "\",\"deps\":[";
    for (auto it = node->m_deps.begin(); it != node->m_deps.end(); ++it)
    {
        str += "\"" + escape_json(*it) + "\"";
        if (it != node->m_deps.end())
        {
            str += ",";
        }
    }

    str += "],\"block\":" + node->m_block->to_json(*this);
    return str + "}";
}

std::string libquixcc::ParseNodeJsonSerializerVisitor::visit(const libquixcc::ExportNode *node) const
{
    return "{\"ntype\":\"ExportNode\"}";
}
