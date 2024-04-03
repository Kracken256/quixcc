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

#ifndef __QUIXCC_LOGGER_H__
#define __QUIXCC_LOGGER_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <string>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <functional>
#include <stack>
#include <lexer/Token.h>
#include <error/Messages.h>
#include <quixcc.h>

namespace libquixcc
{
    enum E
    {
        RAW,
        DEBUG,
        SUCCESS,
        INFO,
        WARN,
        ERROR,
        FATAL
    };

    typedef std::function<void(const std::string &, E type)> LogDispatchFunc;
    typedef std::function<std::string(const std::string &, E type, const Token &)> LogFormatFunc;

    class Logger
    {
        std::stringstream m_buf;
        std::stack<size_t> m_replacement_idx;
        std::vector<std::string> m_parts;
        Token m_tok;
        LogDispatchFunc m_dispatch;
        LogFormatFunc m_fmt;
        E m_level;

    public:
        inline Logger(E level) : m_dispatch(nullptr), m_fmt(nullptr), m_level(level) {}

        template <class T>
        Logger &operator+=(const T &msg)
        {
            if (!m_replacement_idx.empty())
            {
                m_parts[m_replacement_idx.top()] = msg;
                m_replacement_idx.pop();
                if (m_replacement_idx.empty())
                {
                    for (auto &part : m_parts)
                        m_buf << part;
                    m_parts = {};
                }
                return *this;
            }

            std::stringstream ss;
            ss << msg;
            auto s = ss.str();

            // Split the msg into parts by dilimiter '{}'
            size_t start = 0, end = 0, idx = 0;
            while ((end = s.find("{}", start)) != std::string::npos)
            {
                m_parts.push_back(s.substr(start, end - start));
                m_parts.push_back(""); // placeholder for replacement
                m_replacement_idx.push(idx + 1);
                idx += 2;
                start = end + 2;
            }

            if (start < s.length())
                m_parts.push_back(s.substr(start));

            if (!idx)
                m_buf << s;

            return *this;
        }

        inline Logger &log(const std::string &message, const Token &tok = Token())
        {
            m_buf << message;
            m_tok = tok;
            flush();
            return *this;
        }

        inline void flush()
        {
            if (!m_dispatch || !m_fmt)
                throw std::runtime_error("Logger dispatch function not set");

            m_dispatch(m_fmt(m_buf.str(), m_level, m_tok), m_level);
            m_buf.str("");
            m_parts = {};
            m_replacement_idx = {};
            m_tok = Token();
        }

        inline void base(const Token &tok) { m_tok = tok; }

        inline E level() { return m_level; }

        inline void conf(LogDispatchFunc func, LogFormatFunc fmt)
        {
            m_dispatch = func;
            m_fmt = fmt;
        }
    };

    class LoggerGroup
    {
        std::unordered_map<E, Logger *> m_loggers;
        Logger *m_hole;
        quixcc_job_t *m_job;

        static void push_message_to_job(quixcc_job_t &job, E type, const std::string &message)
        {
            job.m_result.m_messages = (quixcc_msg_t **)realloc(job.m_result.m_messages, (job.m_result.m_count + 1) * sizeof(quixcc_msg_t *));
            quixcc_msg_t *msg = (quixcc_msg_t *)malloc(sizeof(quixcc_msg_t));
            msg->line = 0;
            msg->column = 0;
            msg->message = strdup(message.c_str());
            msg->m_level = (quixcc_msg_level_t)type;
            job.m_result.m_messages[job.m_result.m_count] = msg;
            job.m_result.m_count++;
        }

        static bool is_color_enabled();
        static std::string format_message_ansi(const std::string &message, E type, const Token &tok);
        static std::string format_message_nocolor(const std::string &message, E type, const Token &tok);

        static inline std::string format_message(const std::string &message, E type, const Token &tok)
        {
            return is_color_enabled() ? format_message_ansi(message, type, tok) : format_message_nocolor(message, type, tok);
        }

    public:
        inline LoggerGroup()
        {
            m_loggers[DEBUG] = new Logger(DEBUG);
            m_loggers[SUCCESS] = new Logger(SUCCESS);
            m_loggers[INFO] = new Logger(INFO);
            m_loggers[WARN] = new Logger(WARN);
            m_loggers[ERROR] = new Logger(ERROR);
            m_loggers[FATAL] = new Logger(FATAL);
            m_hole = new Logger(DEBUG);
        }

        ~LoggerGroup()
        {
            for (auto &logger : m_loggers)
                delete logger.second;
            delete m_hole;
        }

        inline void setup(quixcc_job_t &job)
        {
            m_job = &job;

            for (auto &logger : m_loggers)
            {
                logger.second->conf([&job](const std::string &message, E type)
                                    { push_message_to_job(job, type, message); },
                                    format_message);
            }

            m_hole->conf([](const std::string &message, E type)
                         { (void)message; (void)type; },
                         [](const std::string &message, E type, const Token &tok)
                         { (void)message; (void)type; (void)tok; return ""; });
        }

        inline Logger &operator[](E level)
        {
            if (!m_job->m_debug && level == E::DEBUG)
                return *m_hole;
            return *m_loggers[level];
        }
    };

    template <class T>
    Logger &operator<<(Logger &logger, const T &msg)
    {
        return logger += msg;
    }

    static inline void operator<<(Logger &log, std::ostream &(*var)(std::ostream &)) { log.flush(); }
    static inline Logger &operator<<(Logger &log, const Token& tok)
    {
        log.base(tok);
        return log;
    }

    extern thread_local LoggerGroup __G_loggerGrp;

#define LOG(lvl) __G_loggerGrp[lvl]
#define LOGGER_SETUP() thread_local libquixcc::LoggerGroup libquixcc::__G_loggerGrp;

    static inline void LoggerConfigure(quixcc_job_t &job)
    {
        __G_loggerGrp.setup(job);
    }
};

#endif // __QUIXCC_LOGGER_H__