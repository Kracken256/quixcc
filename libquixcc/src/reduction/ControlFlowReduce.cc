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

#include <parse/nodes/ControlFlow.h>
#include <parse/nodes/ExprNode.h>

std::unique_ptr<libquixcc::StmtNode> libquixcc::ReturnStmtNode::reduce() const
{
    return std::make_unique<libquixcc::ReturnStmtNode>(*this);
}

std::unique_ptr<libquixcc::StmtNode> libquixcc::RetifStmtNode::reduce() const
{
    auto stmt = std::make_shared<ReturnStmtNode>(m_return);
    return std::make_unique<IfStmtNode>(m_cond, stmt, nullptr);
}

std::unique_ptr<libquixcc::StmtNode> libquixcc::RetzStmtNode::reduce() const
{
    auto inv_expr = std::make_shared<UnaryExprNode>(Operator::Not, m_cond);
    auto stmt = std::make_shared<ReturnStmtNode>(m_return);
    return std::make_unique<IfStmtNode>(inv_expr, stmt, nullptr);
}

std::unique_ptr<libquixcc::StmtNode> libquixcc::RetvStmtNode::reduce() const
{
    auto stmt = std::make_shared<ReturnStmtNode>(nullptr);
    return std::make_unique<IfStmtNode>(m_cond, stmt, nullptr);
}

std::unique_ptr<libquixcc::StmtNode> libquixcc::IfStmtNode::reduce() const
{
    return std::make_unique<IfStmtNode>(*this);
}

std::unique_ptr<libquixcc::StmtNode> libquixcc::WhileStmtNode::reduce() const
{
    return std::make_unique<WhileStmtNode>(*this);
}

std::unique_ptr<libquixcc::StmtNode> libquixcc::ForStmtNode::reduce() const
{
    /*
    Any for loop of the form:
        for (init; cond; step) stmt;

    can be mapped to:
        {
            init;
            while (cond) {
                stmt;
                step;
            }
        }
    Note the scope block. the init is its own scope.
    */
    std::unique_ptr<BlockNode> block = std::make_unique<BlockNode>();

    auto group = std::make_shared<StmtGroupNode>();

    if (m_stmt)
        group->m_stmts.push_back(m_stmt->reduce());

    if (m_step)
        group->m_stmts.push_back(std::make_shared<ExprStmtNode>(m_step));

    auto while_loop = std::make_shared<WhileStmtNode>(m_cond, group);

    if (m_init)
        block->m_stmts.push_back(std::make_shared<ExprStmtNode>(m_init));

    block->m_stmts.push_back(while_loop);

    return block;
}