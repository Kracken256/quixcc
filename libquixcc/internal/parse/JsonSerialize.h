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

#ifndef __QUIXCC_PARSE_NODES_JSON_SERIALIZE_H__
#define __QUIXCC_PARSE_NODES_JSON_SERIALIZE_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <string>

#include <parse/NodeType.h>

namespace libquixcc
{
    class ParseNodeJsonSerializerVisitor
    {
    public:
        std::string visit(const ParseNode *node) const;
        std::string visit(const ASTNopNode *node) const;
        std::string visit(const ExprNode *node) const;
        std::string visit(const ConstExprNode *node) const;
        std::string visit(const StmtNode *node) const;
        std::string visit(const NopStmtNode *node) const;
        std::string visit(const TypeNode *node) const;
        std::string visit(const DeclNode *node) const;
        std::string visit(const DefNode *node) const;
        std::string visit(const BlockNode *node) const;
        std::string visit(const BasicTypeNode *node) const;
        std::string visit(const UnaryExprNode *node) const;
        std::string visit(const BinaryExprNode *node) const;
        std::string visit(const ConstUnaryExprNode *node) const;
        std::string visit(const ConstBinaryExprNode *node) const;
        std::string visit(const IdentifierNode *node) const;
        std::string visit(const U8TypeNode *node) const;
        std::string visit(const U16TypeNode *node) const;
        std::string visit(const U32TypeNode *node) const;
        std::string visit(const U64TypeNode *node) const;
        std::string visit(const I8TypeNode *node) const;
        std::string visit(const I16TypeNode *node) const;
        std::string visit(const I32TypeNode *node) const;
        std::string visit(const I64TypeNode *node) const;
        std::string visit(const F32TypeNode *node) const;
        std::string visit(const F64TypeNode *node) const;
        std::string visit(const BoolTypeNode *node) const;
        std::string visit(const CharTypeNode *node) const;
        std::string visit(const VoidTypeNode *node) const;
        std::string visit(const PointerTypeNode *node) const;
        std::string visit(const StringTypeNode *node) const;
        std::string visit(const EnumTypeNode *node) const;
        std::string visit(const StructTypeNode *node) const;
        std::string visit(const UnionTypeNode *node) const;
        std::string visit(const ArrayTypeNode *node) const;
        std::string visit(const FunctionTypeNode *node) const;
        std::string visit(const UserTypeNode *node) const;
        std::string visit(const LiteralNode *node) const;
        std::string visit(const IntegerLiteralNode *node) const;
        std::string visit(const FloatLiteralNode *node) const;
        std::string visit(const StringLiteralNode *node) const;
        std::string visit(const CharLiteralNode *node) const;
        std::string visit(const BoolLiteralNode *node) const;
        std::string visit(const NullLiteralNode *node) const;
        std::string visit(const TypedefNode *node) const;
        std::string visit(const VarDeclNode *node) const;
        std::string visit(const LetDeclNode *node) const;
        std::string visit(const StructDeclNode *node) const;
        std::string visit(const UnionDeclNode *node) const;
        std::string visit(const EnumDeclNode *node) const;
        std::string visit(const FunctionDeclNode *node) const;
        std::string visit(const StructDefNode *node) const;
        std::string visit(const StructFieldNode *node) const;
        std::string visit(const UnionDefNode *node) const;
        std::string visit(const UnionFieldNode *node) const;
        std::string visit(const EnumDefNode *node) const;
        std::string visit(const EnumFieldNode *node) const;
        std::string visit(const FunctionDefNode *node) const;
        std::string visit(const FunctionParamNode *node) const;
        std::string visit(const SubsystemNode *node) const;
        std::string visit(const ExportNode *node) const;
        std::string visit(const ReturnStmtNode *node) const;
        std::string visit(const RetifStmtNode *node) const;
        std::string visit(const RetzStmtNode *node) const;
        std::string visit(const RetvStmtNode *node) const;
        std::string visit(const IfStmtNode *node) const;
        std::string visit(const WhileStmtNode *node) const;
        std::string visit(const ForStmtNode *node) const;
    };
}

#endif // __QUIXCC_PARSE_NODES_JSON_SERIALIZE_H__