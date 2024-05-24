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
///     * Copyright (C) 2024 Wesley C. Jones                                     ///
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
///     License along with the QUIX Compiler Suite; if not, see                  ///
///     <https://www.gnu.org/licenses/>.                                         ///
///                                                                              ///
////////////////////////////////////////////////////////////////////////////////////

#ifndef __QUIXCC_LEX_TOKEN_H__
#define __QUIXCC_LEX_TOKEN_H__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <string>
#include <variant>
#include <cstdint>

namespace libquixcc
{
    enum class Keyword
    {
        Subsystem,
        Import,
        Type,
        Let,
        Var,
        Const,
        Static,
        Struct,
        Region,
        Group,
        Union,
        Opaque,
        Fn,
        Nothrow,
        Foreign,
        Impure,
        Tsafe,
        Enum,
        Pub,
        If,
        Else,
        For,
        While,
        Do,
        Switch,
        Case,
        Default,
        Break,
        Continue,
        Return,
        Retif,
        Retz,
        Retv,
        __Asm__,
        Void,
        Undef,
        Null,
        True,
        False,
    };

    enum class Punctor
    {
        OpenParen,
        CloseParen,
        OpenBrace,
        CloseBrace,
        OpenBracket,
        CloseBracket,
        Dot,
        Comma,
        Colon,
        Semicolon,
    };

    enum class Operator
    {
        At = 1,
        Question = 2,
        Arrow = 3,

        Plus = 10,
        Minus = 11,
        Multiply = 12,
        Divide = 13,
        Modulo = 14,

        BitwiseAnd = 20,
        BitwiseOr = 21,
        BitwiseXor = 22,
        BitwiseNot = 23,
        LeftShift = 24,
        RightShift = 25,

        Increment = 30,
        Decrement = 31,
        Assign = 32,
        PlusAssign = 33,
        MinusAssign = 34,
        MultiplyAssign = 35,
        DivideAssign = 36,
        ModuloAssign = 37,
        BitwiseOrAssign = 38,
        BitwiseAndAssign = 39,
        BitwiseXorAssign = 40,
        XorAssign = 41,
        OrAssign = 42,
        AndAssign = 43,
        LeftShiftAssign = 44,
        RightShiftAssign = 45,

        LogicalNot = 50,
        LogicalAnd = 51,
        LogicalOr = 52,
        LogicalXor = 53,

        LessThan = 60,
        GreaterThan = 61,
        LessThanEqual = 62,
        GreaterThanEqual = 63,
        Equal = 64,
        NotEqual = 65,
    };

    enum class TT
    {
        Eof = 0,
        Unknown = 1,
        Identifier = 2,
        Keyword = 3,
        Operator = 4,
        Punctor = 5,
        Integer = 6,
        Float = 7,
        String = 8,
        Char = 9,
        MacroBlock = 10,
        MacroSingleLine = 11,
        Comment = 12,
    };

    struct Loc
    {
        std::string_view file;
        int_fast32_t line;
        int_fast32_t col;

        Loc() : file(""), line(1), col(1) {}
        Loc(int_fast32_t line, int_fast32_t col, std::string_view file = "") : file(file), line(line), col(col) {}

        Loc operator-(int_fast32_t rhs) const;
    };

#if !defined(NDEBUG)
    typedef std::variant<std::string, Punctor, Keyword, Operator> TokVal;
#else
    struct TokVal
    {
        std::string str;
        int val;

        TokVal() : val(0) {}
        TokVal(std::string str) : str(str) {}
        TokVal(const char *str) : str(str) {}
        TokVal(Punctor punctor) : val(static_cast<int>(punctor)) {}
        TokVal(Keyword keyword) : val(static_cast<int>(keyword)) {}
        TokVal(Operator op) : val(static_cast<int>(op)) {}
    };
#endif

    class Token
    {
        TokVal m_value;
        Loc m_loc;

    public:
        TT type;

        Token() : type(TT::Unknown) {}
        Token(TT type, TokVal value, Loc loc = Loc());

        inline bool is(TT val) const { return type == val; }

        template <typename T, typename V = T>
        bool is(V val) const
        {
            if constexpr (std::is_same_v<T, std::string>)
                return type == TT::Identifier && as<std::string>() == val;
            else if constexpr (std::is_same_v<T, Keyword>)
                return type == TT::Keyword && as<Keyword>() == val;
            else if constexpr (std::is_same_v<T, Punctor>)
                return type == TT::Punctor && as<Punctor>() == val;
            else if constexpr (std::is_same_v<T, Operator>)
                return type == TT::Operator && as<Operator>() == val;
            else
                return false;
        }

        template <typename T>
        const T &as() const
        {
#if !defined(NDEBUG)
            return std::get<T>(m_value);
#else
            if constexpr (std::is_same_v<T, std::string>)
            {
                return m_value.str;
            }
            else if constexpr (std::is_same_v<T, Punctor>)
            {
                static_assert(sizeof(m_value.val) == sizeof(Punctor));
                return *reinterpret_cast<const Punctor *>(&m_value.val);
            }
            else if constexpr (std::is_same_v<T, Keyword>)
            {
                static_assert(sizeof(m_value.val) == sizeof(Keyword));
                return *reinterpret_cast<const Keyword *>(&m_value.val);
            }
            else if constexpr (std::is_same_v<T, Operator>)
            {
                static_assert(sizeof(m_value.val) == sizeof(Operator));
                return *reinterpret_cast<const Operator *>(&m_value.val);
            }
            else
            {
                static_assert(false, "Invalid type");
            }
#endif
        }

        const Loc &loc() const { return m_loc; }

        std::string serialize(bool human_readable = true) const;

        inline bool operator==(const Token &rhs) const
        {
            if (type != rhs.type)
                return false;

            switch (type)
            {
            case TT::Identifier:
            case TT::String:
            case TT::Char:
            case TT::Integer:
                return as<std::string>() == rhs.as<std::string>();
            case TT::Keyword:
                return as<Keyword>() == rhs.as<Keyword>();
            case TT::Operator:
                return as<Operator>() == rhs.as<Operator>();
            case TT::Punctor:
                return as<Punctor>() == rhs.as<Punctor>();
            default:
                return true;
            }
        }

        inline bool operator<(const Token &rhs) const
        {
            if (type != rhs.type)
                return type < rhs.type;
            switch (type)
            {
            case TT::Identifier:
            case TT::String:
            case TT::Char:
            case TT::Integer:
                return as<std::string>() < rhs.as<std::string>();
            case TT::Keyword:
                return as<Keyword>() < rhs.as<Keyword>();
            case TT::Operator:
                return as<Operator>() < rhs.as<Operator>();
            case TT::Punctor:
                return as<Punctor>() < rhs.as<Punctor>();
            default:
                return false;
            }
        }
    };
};

#endif // __QUIXCC_LEX_TOKEN_H__