#include "include/parser.h"
#include "include/ast.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

parser_T* init_parser(lexer_T* lexer)
{
	parser_T* parser = (struct PARSER_STRUCT*) malloc(sizeof(struct PARSER_STRUCT));
	parser->lexer = lexer;
	parser->current_token = lexer_get_next_token(lexer);
	parser->prev_token = parser->current_token;
	
	return parser;
}

void parser_throw_error_illegal_token(token_T* token)
{
	printf("Illegal Token '%s'\n", token->value);
	exit(1);
}

void parser_check_advance(parser_T* parser, TokenType type)
{
	if(parser->current_token->type == type)
	{
		parser->prev_token = parser->current_token;
		parser->current_token = lexer_get_next_token(parser->lexer);
	}
	else 
	{ 
		printf("Unexcpected Token '%s' type %d\n", parser->current_token->value, parser->current_token->type); 
		exit(1); 
	}
}

ast_T* parser_parse_statement(parser_T* parser)
{
	switch(parser->current_token->type)
	{
		case TOKEN_ID		: return parser_parse_id(parser);
	}
	
	return init_ast(AST_NOOP);
}

ast_T* parser_parse_list_statements(parser_T* parser)
{
	ast_T* compound = init_ast(AST_COMPOUND);
	compound->compound_value = (struct AST_STRUCT**) malloc(sizeof(struct AST_STRUCT*));
	ast_T* ast = parser_parse_statement(parser);
	compound->compound_value[0] = ast;
	compound->compound_size++;
	
	while(parser->current_token->type == TOKEN_SEMICOLON)
	{
		parser_check_advance(parser, TOKEN_SEMICOLON);
		if(parser->current_token->type == TOKEN_EOF) return compound;
		
		ast_T* ast = parser_parse_statement(parser);
		compound->compound_size++;
		compound->compound_value = (struct AST_STRUCT**) realloc(compound->compound_value, compound->compound_size * sizeof(struct AST_STRUCT*));
		compound->compound_value[compound->compound_size-1] = ast;
	}
	
	return compound;
}

ast_T* parser_parse_expr(parser_T* parser)
{
	switch(parser->current_token->type)
	{
		case TOKEN_ID		: return parser_parse_id(parser);
		case TOKEN_STRING	: return parser_parse_string(parser);
	}
	
	return init_ast(AST_NOOP);
}

ast_T* parser_parse_factor(parser_T* parser)
{
	
}

ast_T* parser_parse_term(parser_T* parser)
{
	
}

ast_T* parser_parse_func_call(parser_T* parser)
{
	ast_T* func_call = init_ast(AST_FUNC_CALL);
	func_call->func_call_name = parser->prev_token->value;
	parser_check_advance(parser, TOKEN_LPAREN);
	
	func_call->func_call_args = (struct AST_STRUCT**) malloc(sizeof(ast_T*));
	ast_T* ast_expr = parser_parse_expr(parser);
	func_call->func_call_args[0] = ast_expr;
	func_call->func_call_args_size++;
	
	while(parser->current_token->type == TOKEN_COMMA)
	{
		parser_check_advance(parser, TOKEN_COMMA);
		if(parser->current_token->type != TOKEN_ID) parser_throw_error_illegal_token(parser->current_token);
		
		ast_T* ast_expr = parser_parse_expr(parser);
		func_call->func_call_args_size++;
		func_call->func_call_args = (struct AST_STRUCT**) realloc(func_call->func_call_args, func_call->func_call_args_size * sizeof(struct AST_STRUCT*));
		func_call->func_call_args[func_call->func_call_args_size-1] = ast_expr;
	}
	
	return func_call;
}

ast_T* parser_parse_variable_definition(parser_T* parser)
{
	parser_check_advance(parser, TOKEN_ID);
	char* var_name = parser->current_token->value;
	parser_check_advance(parser, TOKEN_ID);
	parser_check_advance(parser, TOKEN_EQUALS);
	ast_T* var_value = parser_parse_expr(parser);
	
	ast_T* var_defi = init_ast(AST_VAR_DEF);
	var_defi->var_def_var_name = var_name;
	var_defi->var_def_value = var_value;
	
	return var_defi;
}

ast_T* parser_parse_var(parser_T* parser)
{
	char* var_name = parser->current_token->value;
	parser_check_advance(parser, TOKEN_ID);
	
	if(parser->current_token->type == TOKEN_LPAREN) return parser_parse_func_call(parser);
	
	ast_T* ast_var_call = init_ast(AST_VAR_CALL);
	ast_var_call->var_name_call = var_name;
	
	return ast_var_call;
}

ast_T* parser_parse_string(parser_T* parser)
{
	ast_T* ast = init_ast(AST_STR);
	ast->str_value = parser->current_token->value;
	
	parser_check_advance(parser, TOKEN_STRING);
	return ast;
}

ast_T* parser_parse_id(parser_T* parser)
{
	if(!strcmp(parser->current_token->value, "var"))
	{
		return parser_parse_variable_definition(parser);
	} else return parser_parse_var(parser);
}

ast_T* parser_parse(parser_T* parser)
{
	return parser_parse_list_statements(parser);
}

