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

#ifndef __QUIXCC_PREP_PREPROCESS_H__
#define __QUIXCC_PREP_PREPROCESS_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <bits/types/FILE.h>
#include <vector>
#include <string>
#include <optional>
#include <lexer/Lex.h>
#include <prep/AllMacros.h>
#include <quixcc.h>
#include <memory>
#include <set>
#include <stack>
#include <queue>

namespace libquixcc
{
    class PrepEngine : public libquixcc::Scanner
    {
    protected:
        struct Entry
        {
            StreamLexer lexer;
            std::string path;
            std::set<std::string> already_included;
            FILE *file;
            std::string *buffer;

            Entry(StreamLexer l, const std::string &p, FILE *f = nullptr, std::string *buf = nullptr) : lexer(l), path(p), file(f), buffer(buf) {}
            Entry() : lexer(), path(), file(nullptr) {}
        };
        std::set<std::string> m_include_dirs;
        std::vector<std::string> m_include_files; // for circular include detection
        std::stack<Entry> m_stack;
        quixcc_job_t *m_job;
        std::string include_path;
        std::optional<Token> m_tok;
        std::map<std::string, std::string> m_statics;
        std::queue<Token> m_buffer;
        MacroParser m_macro_parser;

        Token read_token();

        bool handle_import();
        bool handle_macro(const Token &tok);

        Entry build_statics_decl();

        void push(Token tok) override;

    public:
        PrepEngine(quixcc_job_t &job) : m_job(&job), m_macro_parser(job) {}

        // Install macro routines
        void setup();

        void addpath(const std::string &path);

        /// @brief Set the source file
        /// @param src C FILE pointer
        /// @return true if the source file is set successfully
        virtual bool set_source(FILE *src, const std::string &filename);

        /// @brief Get the next token
        /// @return The next token
        Token next() override;

        /// @brief Peek the next token
        /// @return The next token
        Token peek() override;

        void set_static(const std::string &name, const std::string &value) { m_statics[name] = value; }
        bool get_static(const std::string &name, std::string &value) const;
    };
}

#endif // __QUIXCC_PREP_PREPROCESS_H__