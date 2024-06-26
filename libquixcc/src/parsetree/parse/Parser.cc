////////////////////////////////////////////////////////////////////////////////
///                                                                          ///
///  ░▒▓██████▓▒░░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░ ░▒▓██████▓▒░  ///
/// ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ ///
/// ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░        ///
/// ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓██████▓▒░░▒▓█▓▒░      ░▒▓█▓▒░        ///
/// ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░      ░▒▓█▓▒░        ///
/// ░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░ ///
///  ░▒▓██████▓▒░ ░▒▓██████▓▒░░▒▓█▓▒░▒▓█▓▒░░▒▓█▓▒░░▒▓██████▓▒░ ░▒▓██████▓▒░  ///
///    ░▒▓█▓▒░                                                               ///
///     ░▒▓██▓▒░                                                             ///
///                                                                          ///
///   * QUIX LANG COMPILER - The official compiler for the Quix language.    ///
///   * Copyright (C) 2024 Wesley C. Jones                                   ///
///                                                                          ///
///   The QUIX Compiler Suite is free software; you can redistribute it or   ///
///   modify it under the terms of the GNU Lesser General Public             ///
///   License as published by the Free Software Foundation; either           ///
///   version 2.1 of the License, or (at your option) any later version.     ///
///                                                                          ///
///   The QUIX Compiler Suite is distributed in the hope that it will be     ///
///   useful, but WITHOUT ANY WARRANTY; without even the implied warranty of ///
///   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      ///
///   Lesser General Public License for more details.                        ///
///                                                                          ///
///   You should have received a copy of the GNU Lesser General Public       ///
///   License along with the QUIX Compiler Suite; if not, see                ///
///   <https://www.gnu.org/licenses/>.                                       ///
///                                                                          ///
////////////////////////////////////////////////////////////////////////////////

#define QUIXCC_INTERNAL

#include <LibMacro.h>
#include <core/Logger.h>
#include <parsetree/Parser.h>

using namespace libquixcc;

bool libquixcc::parse(quixcc_job_t &job, libquixcc::Scanner *scanner,
                      std::shared_ptr<libquixcc::BlockNode> &group,
                      bool expect_braces, bool single_stmt) {
  Token tok;

  if (expect_braces) {
    tok = scanner->next();
    if (!tok.is<Punctor>(Punctor::OpenBrace)) {
      LOG(ERROR) << core::feedback[PARSER_EXPECTED_LEFT_BRACE] << tok.serialize()
                 << tok << std::endl;
      return false;
    }
  }

  group = std::make_shared<BlockNode>();

  while ((tok = scanner->peek()).type != TT::Eof) {
    if (single_stmt && group->m_stmts.size() > 0) break;

    if (expect_braces) {
      if (tok.is<Punctor>(Punctor::CloseBrace)) {
        scanner->next();
        return true;
      }
    }

    if (tok.is<Punctor>(Punctor::Semicolon)) /* Skip excessive semicolons */
    {
      scanner->next();
      continue;
    }

    if (tok.type != TT::Keyword) {
      std::shared_ptr<ExprNode> expr;
      if (!parse_expr(job, scanner, {Token(TT::Punctor, Punctor::Semicolon)},
                      expr)) {
        LOG(ERROR) << "Error parsing expression in block statement." << tok
                   << std::endl;
        return false;
      }

      if (!expr)
        LOG(ERROR) << "Null expressions are illegal in ExprStmtNode." << tok
                   << std::endl;

      tok = scanner->next();
      if (!tok.is<Punctor>(Punctor::Semicolon)) {
        LOG(ERROR) << core::feedback[PARSER_EXPECTED_SEMICOLON] << tok.serialize()
                   << tok << std::endl;
        return false;
      }

      group->m_stmts.push_back(std::make_shared<ExprStmtNode>(expr));
      continue;
    }

    scanner->next();

    std::shared_ptr<StmtNode> node;

    switch (tok.as<Keyword>()) {
      case Keyword::Var: {
        std::vector<std::shared_ptr<StmtNode>> decls;
        if (!parse_var(job, scanner, decls)) return false;
        for (auto &decl : decls) group->m_stmts.push_back(decl);
        break;
      }
      case Keyword::Let: {
        std::vector<std::shared_ptr<StmtNode>> decls;
        if (!parse_let(job, scanner, decls)) return false;
        for (auto &decl : decls) group->m_stmts.push_back(decl);
        break;
      }
      case Keyword::Const: {
        std::vector<std::shared_ptr<StmtNode>> decls;
        if (!parse_const(job, scanner, decls)) return false;
        for (auto &decl : decls) group->m_stmts.push_back(decl);
        break;
      }
      case Keyword::Enum:
        if (!parse_enum(job, scanner, node)) return false;
        break;
      case Keyword::Struct:
        if (!parse_struct(job, scanner, node)) return false;
        break;
      case Keyword::Region:
        if (!parse_region(job, scanner, node)) return false;
        break;
      case Keyword::Group:
        if (!parse_group(job, scanner, node)) return false;
        break;
      case Keyword::Union:
        if (!parse_union(job, scanner, node)) return false;
        break;
      case Keyword::Type:
        if (!parse_typedef(job, scanner, node)) return false;
        break;
      case Keyword::Subsystem:
        if (!parse_subsystem(job, scanner, node)) return false;
        break;
      case Keyword::Fn:
        if (!parse_function(job, scanner, node)) return false;
        break;
      case Keyword::Pub:
      case Keyword::Import:  // they both declare external functions
        if (!parse_pub(job, scanner, node)) return false;
        break;
      case Keyword::Return:
        if (!parse_return(job, scanner, node)) return false;
        break;
      case Keyword::Retif:
        if (!parse_retif(job, scanner, node)) return false;
        break;
      case Keyword::Retz:
        if (!parse_retz(job, scanner, node)) return false;
        break;
      case Keyword::Retv:
        if (!parse_retv(job, scanner, node)) return false;
        break;
      case Keyword::Break:
        node = std::make_shared<BreakStmtNode>();
        break;
      case Keyword::Continue:
        node = std::make_shared<ContinueStmtNode>();
        break;
      case Keyword::If:
        if (!parse_if(job, scanner, node)) return false;
        break;
      case Keyword::While:
        if (!parse_while(job, scanner, node)) return false;
        break;
      case Keyword::For:
        if (!parse_for(job, scanner, node)) return false;
        break;
      case Keyword::Form:
        if (!parse_form(job, scanner, node)) return false;
        break;
      case Keyword::Foreach:
        if (!parse_foreach(job, scanner, node)) return false;
        break;
      case Keyword::Switch:
        if (!parse_switch(job, scanner, node)) return false;
        break;
      case Keyword::__Asm__:
        if (!parse_inline_asm(job, scanner, node)) return false;
        break;
      case Keyword::Unsafe: {
        std::shared_ptr<BlockNode> block;
        Token tok = scanner->peek();
        if (tok.is<Punctor>(Punctor::OpenBrace)) {
          if (!parse(job, scanner, block)) return false;
        } else {
          if (!parse(job, scanner, block, false, true)) return false;
        }

        block->m_unsafe = true;
        group->m_stmts.push_back(block);
        break;
      }
      case Keyword::Safe: {
        std::shared_ptr<BlockNode> block;
        Token tok = scanner->peek();
        if (tok.is<Punctor>(Punctor::OpenBrace)) {
          if (!parse(job, scanner, block)) return false;
        } else {
          if (!parse(job, scanner, block, false, true)) return false;
        }
        block->m_unsafe = false;
        group->m_stmts.push_back(block);
        break;
      }
      default:
        LOG(ERROR) << core::feedback[PARSER_ILLEGAL_KEYWORD] << tok.serialize() << tok
                   << std::endl;
        return false;
    }

    if (node) group->m_stmts.push_back(node);
  }

  if (expect_braces) {
    LOG(ERROR) << core::feedback[PARSER_EXPECTED_RIGHT_BRACE] << tok.serialize()
               << tok << std::endl;
    return false;
  }

  return true;
}