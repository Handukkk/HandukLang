#include "include/ast.h"
#include <stdlib.h>

ast_T* init_ast(AstType type)
{
	ast_T* ast = (struct AST_STRUCT*) malloc(sizeof(struct AST_STRUCT));
	ast->type = type;
	ast->var_def_var_name = (char*) 0;
	ast->var_def_value = (struct AST_STRUCT*) 0;
	
	// ast var
	ast->var_name_call = (char*) 0;
	
	// ast func call
	ast->func_call_name = (char*) 0;
	ast->func_call_args = (struct AST_STRUCT**) 0;
	ast->func_call_args_size = 0;
	
	// ast str
	ast->str_value = (char*) 0;
	
	// asat compound
	ast->compound_value = (struct AST_STRUCT**) 0;
	ast->compound_size = 0;
	
	return ast;
}


