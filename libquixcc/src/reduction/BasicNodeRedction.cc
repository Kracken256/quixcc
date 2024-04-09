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
///     * Copyright (C) 2020-2024 Wesley C. Jones                                ///
///                                                                              ///
///     The QUIX Compiler Suite is free software; you can redistribute it and/or ///
///     modify it under the terms of the GNU Lesser General Public               ///
///     License as published by the Free Software Foundation; either             ///
///     version 2.1 of the License, or (at your option) any later version.       ///
///                                                                              ///
///     The QUIX Compiler Suite is distributed in the hope that it will be       ///
///     useful, but WITHOUT ANY WARRANTY; without even the implied warranty of   ///
///     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU        ///
///     Lesser General Public License for more details.                          ///
///                                                                              ///
///     You should have received a copy of the GNU Lesser General Public         ///
///     License along with the GNU C Library; if not, see                        ///
///     <https://www.gnu.org/licenses/>.                                         ///
///                                                                              ///
////////////////////////////////////////////////////////////////////////////////////

#define QUIXCC_INTERNAL

#include <parse/nodes/BasicNodes.h>
#include <parse/nodes/SubsystemNode.h>
#include <parse/nodes/ExportNode.h>

std::unique_ptr<libquixcc::StmtNode> libquixcc::ExprStmtNode::reduce() const
{
    return std::make_unique<libquixcc::ExprStmtNode>(m_expr);
}

std::unique_ptr<libquixcc::StmtNode> libquixcc::NopStmtNode::reduce() const
{
    return nullptr;
}

std::unique_ptr<libquixcc::StmtNode> libquixcc::BlockNode::reduce() const
{
    std::unique_ptr<libquixcc::BlockNode> block = std::make_unique<libquixcc::BlockNode>();

    for (const auto &stmt : m_stmts)
    {
        auto reduced_stmt = stmt->reduce();
        if (reduced_stmt)
            block->m_stmts.push_back(std::move(reduced_stmt));
    }

    return block;
}

std::unique_ptr<libquixcc::StmtNode> libquixcc::StmtGroupNode::reduce() const
{
    std::unique_ptr<libquixcc::StmtGroupNode> stmt_group = std::make_unique<libquixcc::StmtGroupNode>();

    for (const auto &stmt : m_stmts)
    {
        auto reduced_stmt = stmt->reduce();
        if (reduced_stmt)
            stmt_group->m_stmts.push_back(std::move(reduced_stmt));
    }

    return stmt_group;
}

std::unique_ptr<libquixcc::StmtNode> libquixcc::SubsystemNode::reduce() const
{
    auto reduced_block = m_block->reduce();

    if (!reduced_block)
        return nullptr;

    return std::make_unique<libquixcc::SubsystemNode>(m_name, m_deps, std::shared_ptr<libquixcc::BlockNode>(dynamic_cast<libquixcc::BlockNode *>(reduced_block.release())));
}

std::unique_ptr<libquixcc::StmtNode> libquixcc::ExportNode::reduce() const
{
    std::vector<std::shared_ptr<libquixcc::StmtNode>> reduced_stmts;

    for (const auto &stmt : m_stmts)
    {
        auto reduced_stmt = stmt->reduce();
        if (reduced_stmt)
            reduced_stmts.push_back(std::move(reduced_stmt));
    }

    return std::make_unique<libquixcc::ExportNode>(reduced_stmts, m_lang_type);
}