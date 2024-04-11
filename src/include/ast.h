#ifndef AST_H
#define AST_H
#include <stddef.h>

typedef enum AST_TYPE
{
	AST_VAR_DEF,
	AST_VAR_CALL,
	AST_FUNC_DEF,
	AST_FUNC_CALL,
	AST_STR,
	AST_COMPOUND,
	AST_NOOP
} AstType;

typedef struct AST_STRUCT
{
	AstType type;
	
	// ast var def
	char* var_def_var_name;
	struct AST_STRUCT* var_def_value;
	
	// ast var
	char* var_name_call;
	
	// ast func call
	char* func_call_name;
	struct AST_STRUCT** func_call_args;
	size_t func_call_args_size;
	
	// ast str
	char* str_value;
	
	// ast compound
	struct AST_STRUCT** compound_value;
	size_t compound_size;
} ast_T;

ast_T* init_ast(AstType type);

#endif
