#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/stdutil.h"

ast_T* println_builtin_func(visitor_T* visitor, int argc, ast_T** argv)
{
	int i;
	for(i = 0; i < argc; i++)
	{
		ast_T* visited_ast = visitor_visit(visitor, argv[i]);
		switch(visited_ast->type)
		{
			case AST_STR		: printf("%s\n", visited_ast->str_value); break;
			default				: printf("Unknown type %d, should be type %d\n", visited_ast->type, AST_STR); return init_ast(AST_NOOP);
		}
	}
}
