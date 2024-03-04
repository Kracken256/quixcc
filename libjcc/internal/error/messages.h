#ifndef __J_CC_MESSAGES_HPP__
#define __J_CC_MESSAGES_HPP__

#ifndef __cplusplus
#error "This header requires C++"
#endif

#include <map>

namespace libjcc
{
    enum Msg
    {
        PARSER_EXPECTED_KEYWORD,
        PARSER_EXPECTED_LEFT_BRACE,
        PARSER_EXPECTED_RIGHT_BRACE,
        PARSER_EXPECTED_SEMICOLON,

        TYPE_EXPECTED_IDENTIFIER_OR_BRACKET,

        LET_DECL_MISSING_IDENTIFIER,
        LET_DECL_MISSING_COLON,
        LET_DECL_TYPE_ERR,
        LET_DECL_INIT_ERR,
        LET_DECL_MISSING_PUNCTOR,

        VAR_DECL_MISSING_IDENTIFIER,
        VAR_DECL_MISSING_COLON,
        VAR_DECL_TYPE_ERR,
        VAR_DECL_INIT_ERR,
        VAR_DECL_MISSING_PUNCTOR,

        CONST_DECL_MISSING_IDENTIFIER,
        CONST_DECL_MISSING_COLON,
        CONST_DECL_TYPE_ERR,
        CONST_DECL_INIT_ERR,
        CONST_DECL_MISSING_PUNCTOR,

        STRUCT_DECL_MISSING_IDENTIFIER,
        STRUCT_FIELD_MISSING_IDENTIFIER,
        STRUCT_DEF_EXPECTED_OPEN_BRACE,
        STRUCT_DEF_EXPECTED_SEMICOLON,
        STRUCT_FIELD_MISSING_COLON,
        STRUCT_FIELD_TYPE_ERR,
        STRUCT_FIELD_INIT_ERR,
        STRUCT_FIELD_MISSING_PUNCTOR,

        UNION_DECL_MISSING_IDENTIFIER,
        UNION_DEF_EXPECTED_OPEN_BRACE,
        UNION_FIELD_MISSING_IDENTIFIER,
        UNION_DEF_EXPECTED_SEMICOLON,
        UNION_FIELD_MISSING_COLON,
        UNION_FIELD_TYPE_ERR,
        UNION_FIELD_MISSING_PUNCTOR,

        TYPE_EXPECTED_TYPE,
        TYPE_EXPECTED_SEMICOLON,
        TYPE_EXPECTED_CONST_EXPR,
        TYPE_EXPECTED_CLOSE_BRACKET,

        SUBSYSTEM_MISSING_IDENTIFIER,
        SUBSYSTEM_EXPECTED_IDENTIFIER,
        SUBSYSTEM_EXPECTED_SEMICOLON,

        ENUM_EXPECTED_IDENTIFIER,
        ENUM_EXPECTED_COLON,
        ENUM_EXPECTED_LEFT_BRACE,
        ENUM_DEF_EXPECTED_SEMICOLON,
        ENUM_FIELD_EXPECTED_IDENTIFIER,
        ENUM_FIELD_EXPECTED_CONST_EXPR,
        ENUM_FIELD_EXPECTED_SEMICOLON,

        PREP_DUPLICATE_IMPORT,

    };

    extern std::map<Msg, const char *> feedback;
};

#endif