#ifndef PARSER_H
#define PARSER_H
#include "token.h"
#include "lexer.h"
#include "ast.h"

typedef struct PARSER_STRUCT
{
	lexer_T* lexer;
	token_T* current_token;
	token_T* prev_token;
} parser_T;

parser_T* init_parser(lexer_T* lexer);

void parser_throw_error_illegal_token(token_T* token);

void parser_check(parser_T* parser, TokenType type);

ast_T* parser_parse(parser_T* parser);

ast_T* parser_parse_statement(parser_T* parser);

ast_T* parser_parse_list_statements(parser_T* parser);

ast_T* parser_parse_expr(parser_T* parser);

ast_T* parser_parse_factor(parser_T* parser);

ast_T* parser_parse_term(parser_T* parser);

ast_T* parser_parse_func_call(parser_T* parser);

ast_T* parser_parse_variable_definition(parser_T* parser);

ast_T* parser_parse_var(parser_T* parser);

ast_T* parser_parse_string(parser_T* parser);

ast_T* parser_parse_id(parser_T* parser);

#endif
