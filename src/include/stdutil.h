#ifndef STDUTIL_H
#define STDUTIL_H
#include "ast.h"
#include "visitor.h"

ast_T* println_builtin_func(visitor_T* visitor, int argc, ast_T** argv);

//ast_T* print_func(visitor_T* visitor, int argc, ast_T** argv);

#endif
