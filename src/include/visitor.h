#ifndef VISITOR_H
#define VISITOR_H
#include "ast.h"

typedef struct VISITOR_STRUCT
{
	ast_T** variable_definitions;
	size_t variable_definitions_size;
} visitor_T;

visitor_T* init_visitor();

ast_T* visitor_visit(visitor_T* visitor, ast_T* node);

ast_T* visitor_visit_var_def(visitor_T* visitor, ast_T* node);

ast_T* visitor_visit_var_call(visitor_T* visitor, ast_T* node);

ast_T* visitor_visit_func_def(visitor_T* visitor, ast_T* node);

ast_T* visitor_visit_func_call(visitor_T* visitor, ast_T* node);

ast_T* visitor_visit_string(visitor_T* visitor, ast_T* node);

ast_T* visitor_visit_compound(visitor_T* visitor, ast_T* node);

#endif
