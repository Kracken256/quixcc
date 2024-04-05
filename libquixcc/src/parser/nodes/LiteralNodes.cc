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

#include <parse/nodes/AllNodes.h>

std::unordered_map<std::string, std::shared_ptr<libquixcc::StringLiteralNode>> libquixcc::StringLiteralNode::m_instances;
std::unordered_map<std::string, std::shared_ptr<libquixcc::CharLiteralNode>> libquixcc::CharLiteralNode::m_instances;
std::shared_ptr<libquixcc::BoolLiteralNode> libquixcc::BoolLiteralNode::m_true_instance;
std::shared_ptr<libquixcc::BoolLiteralNode> libquixcc::BoolLiteralNode::m_false_instance;
std::unordered_map<std::string, std::shared_ptr<libquixcc::FloatLiteralNode>> libquixcc::FloatLiteralNode::m_instances;
std::unordered_map<std::string, std::shared_ptr<libquixcc::IntegerLiteralNode>> libquixcc::IntegerLiteralNode::m_instances;
std::shared_ptr<libquixcc::NullLiteralNode> libquixcc::NullLiteralNode::m_instance;

uint8_t get_numbits(std::string s);

libquixcc::TypeNode *libquixcc::IntegerLiteralNode::type() const
{
    bool _signed = m_val.front() == '-';
    uint8_t numbits = get_numbits(m_val);

    if (_signed)
    {
        switch (numbits)
        {
        case 8:
            return I8TypeNode::create();
        case 16:
            return I16TypeNode::create();
        case 32:
            return I32TypeNode::create();
        case 64:
            return I64TypeNode::create();
        default:
            throw std::runtime_error("Invalid integer literal size");
        }
    }
    else
    {
        switch (numbits)
        {
        case 8:
            return U8TypeNode::create();
        case 16:
            return U16TypeNode::create();
        case 32:
            return U32TypeNode::create();
        case 64:
            return U64TypeNode::create();
        default:
            throw std::runtime_error("Invalid integer literal size");
        }
    }
}

libquixcc::TypeNode *libquixcc::FloatLiteralNode::type() const
{
    uint8_t numbits = get_numbits(m_val);

    switch (numbits)
    {
    case 32:
        return F32TypeNode::create();
    case 64:
        return F64TypeNode::create();
    default:
        throw std::runtime_error("Invalid float literal size");
    }
}

libquixcc::TypeNode *libquixcc::StringLiteralNode::type() const
{
    return StringTypeNode::create();
}

libquixcc::TypeNode *libquixcc::CharLiteralNode::type() const
{
    return I8TypeNode::create();
}

libquixcc::TypeNode *libquixcc::BoolLiteralNode::type() const
{
    return BoolTypeNode::create();
}

libquixcc::TypeNode *libquixcc::NullLiteralNode::type() const
{
    return PointerTypeNode::create(VoidTypeNode::create());
}