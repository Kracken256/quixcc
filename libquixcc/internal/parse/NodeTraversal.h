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

#ifndef __QUIXCC_PARSE_NODES_TRAVERSAL_H__
#define __QUIXCC_PARSE_NODES_TRAVERSAL_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <string>
#include <memory>
#include <parse/NodeType.h>

namespace libquixcc
{
    typedef void (*ParseNodePreorderVisitorCallback)(libquixcc::ParseNode *parent, std::shared_ptr<libquixcc::ParseNode> *node);
    typedef void (*ParseNodePostorderVisitorCallback)(libquixcc::ParseNode *parent, std::shared_ptr<libquixcc::ParseNode> *node);

    class ParseNodePreorderVisitor
    {
        ParseNodePreorderVisitorCallback m_callback;

    public:
        ParseNodePreorderVisitor(ParseNodePreorderVisitorCallback callback) : m_callback(callback) {}

        size_t visit(ParseNode *node);
        size_t visit(ExprNode *node);
        size_t visit(ConstExprNode *node);
        size_t visit(StmtNode *node);
        size_t visit(TypeNode *node);
        size_t visit(DeclNode *node);
        size_t visit(DefNode *node);
        size_t visit(BlockNode *node);
        size_t visit(BasicTypeNode *node);
        size_t visit(ConstUnaryExprNode *node);
        size_t visit(ConstBinaryExprNode *node);
        size_t visit(IdentifierNode *node);
        size_t visit(U8TypeNode *node);
        size_t visit(U16TypeNode *node);
        size_t visit(U32TypeNode *node);
        size_t visit(U64TypeNode *node);
        size_t visit(I8TypeNode *node);
        size_t visit(I16TypeNode *node);
        size_t visit(I32TypeNode *node);
        size_t visit(I64TypeNode *node);
        size_t visit(F32TypeNode *node);
        size_t visit(F64TypeNode *node);
        size_t visit(BoolTypeNode *node);
        size_t visit(CharTypeNode *node);
        size_t visit(VoidTypeNode *node);
        size_t visit(StringTypeNode *node);
        size_t visit(StructTypeNode *node);
        size_t visit(UnionTypeNode *node);
        size_t visit(ArrayTypeNode *node);
        size_t visit(UserTypeNode *node);
        size_t visit(LiteralNode *node);
        size_t visit(IntegerLiteralNode *node);
        size_t visit(FloatLiteralNode *node);
        size_t visit(StringLiteralNode *node);
        size_t visit(CharLiteralNode *node);
        size_t visit(BoolLiteralNode *node);
        size_t visit(VarDeclNode *node);
        size_t visit(LetDeclNode *node);
        size_t visit(ConstDeclNode *node);
        size_t visit(StructDeclNode *node);
        size_t visit(UnionDeclNode *node);
        size_t visit(EnumDeclNode *node);
        size_t visit(FunctionDeclNode *node);
        size_t visit(StructDefNode *node);
        size_t visit(StructFieldNode *node);
        size_t visit(UnionDefNode *node);
        size_t visit(UnionFieldNode *node);
        size_t visit(EnumDefNode *node);
        size_t visit(EnumFieldNode *node);
        size_t visit(FunctionDefNode *node);
        size_t visit(FunctionParamNode *node);
        size_t visit(SubsystemNode *node);
        size_t visit(ExportNode *node);
    };

    class ParseNodePostorderVisitor
    {
        ParseNodePostorderVisitorCallback m_callback;

    public:
        ParseNodePostorderVisitor(ParseNodePostorderVisitorCallback callback) : m_callback(callback) {}

        size_t visit(ParseNode *node);
        size_t visit(ExprNode *node);
        size_t visit(ConstExprNode *node);
        size_t visit(StmtNode *node);
        size_t visit(TypeNode *node);
        size_t visit(DeclNode *node);
        size_t visit(DefNode *node);
        size_t visit(BlockNode *node);
        size_t visit(BasicTypeNode *node);
        size_t visit(ConstUnaryExprNode *node);
        size_t visit(ConstBinaryExprNode *node);
        size_t visit(IdentifierNode *node);
        size_t visit(U8TypeNode *node);
        size_t visit(U16TypeNode *node);
        size_t visit(U32TypeNode *node);
        size_t visit(U64TypeNode *node);
        size_t visit(I8TypeNode *node);
        size_t visit(I16TypeNode *node);
        size_t visit(I32TypeNode *node);
        size_t visit(I64TypeNode *node);
        size_t visit(F32TypeNode *node);
        size_t visit(F64TypeNode *node);
        size_t visit(BoolTypeNode *node);
        size_t visit(CharTypeNode *node);
        size_t visit(VoidTypeNode *node);
        size_t visit(StringTypeNode *node);
        size_t visit(StructTypeNode *node);
        size_t visit(UnionTypeNode *node);
        size_t visit(ArrayTypeNode *node);
        size_t visit(UserTypeNode *node);
        size_t visit(LiteralNode *node);
        size_t visit(IntegerLiteralNode *node);
        size_t visit(FloatLiteralNode *node);
        size_t visit(StringLiteralNode *node);
        size_t visit(CharLiteralNode *node);
        size_t visit(BoolLiteralNode *node);
        size_t visit(VarDeclNode *node);
        size_t visit(LetDeclNode *node);
        size_t visit(ConstDeclNode *node);
        size_t visit(StructDeclNode *node);
        size_t visit(UnionDeclNode *node);
        size_t visit(EnumDeclNode *node);
        size_t visit(FunctionDeclNode *node);
        size_t visit(StructDefNode *node);
        size_t visit(StructFieldNode *node);
        size_t visit(UnionDefNode *node);
        size_t visit(UnionFieldNode *node);
        size_t visit(EnumDefNode *node);
        size_t visit(EnumFieldNode *node);
        size_t visit(FunctionDefNode *node);
        size_t visit(FunctionParamNode *node);
        size_t visit(SubsystemNode *node);
        size_t visit(ExportNode *node);
    };

}

#endif // __QUIXCC_PARSE_NODES_TRAVERSAL_H__