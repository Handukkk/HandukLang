#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/stdutil.h"

visitor_T* init_visitor()
{
	visitor_T* visitor = (struct VISITOR_STRUCT*) malloc(sizeof(struct VISITOR_STRUCT));
	visitor->variable_definitions = (void*) 0;
	visitor->variable_definitions_size = 0;
	
	return visitor;
}

ast_T* visitor_visit(visitor_T* visitor, ast_T* node)
{
	switch(node->type)
	{
		case AST_VAR_DEF	: return visitor_visit_var_def(visitor, node); break;
		case AST_VAR_CALL	: return visitor_visit_var_call(visitor, node); break;
		case AST_FUNC_DEF	: return visitor_visit_func_def(visitor, node); break;
		case AST_FUNC_CALL	: return visitor_visit_func_call(visitor, node); break;
		case AST_STR		: return visitor_visit_string(visitor, node); break;
		case AST_COMPOUND	: return visitor_visit_compound(visitor, node); break;
	}
	
	printf("Uncaught statement type '%d'\n", node->type);
	exit(1);
	
	return init_ast(AST_NOOP);
}

ast_T* visitor_visit_var_def(visitor_T* visitor, ast_T* node)
{
	visitor->variable_definitions_size++;
	if(visitor->variable_definitions == (void*) 0)
	{
		visitor->variable_definitions = (struct AST_STRUCT**) malloc(sizeof(struct AST_STRUCT*));
		visitor->variable_definitions[0] = node;
	}
	else
	{
		visitor->variable_definitions = (struct AST_STRUCT**) realloc(visitor->variable_definitions, visitor->variable_definitions_size * sizeof(struct AST_STRUCT*));
		visitor->variable_definitions[visitor->variable_definitions_size-1] = node;
	}
	
	return node;
}

ast_T* visitor_visit_var_call(visitor_T* visitor, ast_T* node)
{
	int i;
	for(i = 0; i < visitor->variable_definitions_size; i++)
	{
		ast_T* var_defi = visitor->variable_definitions[i];
		if(strcmp(var_defi->var_def_var_name, node->var_name_call) == 0)
		{
			return visitor_visit(visitor, var_defi->var_def_value);
		}
	}
	
	printf("Undifined variable '%s'\n", node->var_name_call);
	exit(1);
	return (ast_T*) 0;
}

ast_T* visitor_visit_func_def(visitor_T* visitor, ast_T* node)
{
}

ast_T* visitor_visit_func_call(visitor_T* visitor, ast_T* node)
{
	if(strcmp(node->func_call_name, "println") == 0)
	{
		return println_builtin_func(visitor, node->func_call_args_size, node->func_call_args);
	}
	
	printf("Undefined function named '%s'\n", node->func_call_name);
	exit(1);
}

ast_T* visitor_visit_string(visitor_T* visitor, ast_T* node)
{
	return node;
}

ast_T* visitor_visit_compound(visitor_T* visitor, ast_T* node)
{
	int i;
	for(i = 0; i < node->compound_size; i++)
	{
		visitor_visit(visitor, node->compound_value[i]);
	}
	
	return init_ast(AST_NOOP);
}
