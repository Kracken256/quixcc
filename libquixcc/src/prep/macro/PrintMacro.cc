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

#include <prep/macro/PrintMacro.h>
#include <lexer/Lex.h>
#include <error/Message.h>
#include <iostream>

bool libquixcc::macro::ParsePrint(quixcc_job_t *job, const Token &tok, const std::string &directive, const std::string &parameter, std::vector<libquixcc::Token> &exp)
{
    // print [mode] <message>
    (void)directive;
    (void)exp;

    std::vector<libquixcc::Token> tokens;
    if (!libquixcc::StringLexer::QuixkLex(parameter, tokens))
    {
        libquixcc::message(*job, libquixcc::Err::ERROR, "Failed to lex print message");
        return false;
    }

    if (tokens.empty())
    {
        libquixcc::message(*job, libquixcc::Err::ERROR, "Empty print message");
        return false;
    }

    Err level = Err::INFO;

    Token t = tokens[0];
    if (t.type() == TokenType::Identifier && tokens.size() == 2)
    {
        std::string id = std::get<std::string>(t.val());
        if (id == "debug")
            level = Err::DEBUG;
        else if (id == "ok" || id == "good" || id == "success")
            level = Err::SUCCESS;
        else if (id == "info")
            level = Err::INFO;
        else if (id == "warning" || id == "warn")
            level = Err::WARN;
        else if (id == "error")
            level = Err::ERROR;
        else if (id == "raw")
            level = Err::RAW;
        else
        {
            libquixcc::message(*job, libquixcc::Err::ERROR, "Invalid print level");
            return false;
        }

        switch (level)
        {
        case Err::DEBUG:
            prepmsg(*job, tok, libquixcc::Err::DEBUG, std::get<std::string>(tokens[1].val()));
            break;
        case Err::SUCCESS:
            prepmsg(*job, tok, libquixcc::Err::SUCCESS, std::get<std::string>(tokens[1].val()));
            break;
        case Err::INFO:
            prepmsg(*job, tok, libquixcc::Err::INFO, std::get<std::string>(tokens[1].val()));
            break;
        case Err::WARN:
            prepmsg(*job, tok, libquixcc::Err::WARN, std::get<std::string>(tokens[1].val()));
            break;
        case Err::ERROR:
            prepmsg(*job, tok, libquixcc::Err::ERROR, std::get<std::string>(tokens[1].val()));
            break;
        case Err::RAW:
            std::cout << std::get<std::string>(tokens[1].val());
            break;
        default:
            break;
        }
    }
    else
    {
        prepmsg(*job, tok, libquixcc::Err::INFO, std::get<std::string>(t.val()));
    }

    return true;
}