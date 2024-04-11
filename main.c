#include <stdio.h>
#include "src/lexer.c"
#include "src/parser.c"
#include "src/ast.c"
#include "src/visitor.c"
#include "src/stdutil.c"

int main(int argc, char* argv[])
{
	char input_test[] = "var x = \"hehe\";println(x);";
	lexer_T* lexer = init_lexer(input_test);

	parser_T* parser = init_parser(lexer);
	ast_T* root = parser_parse(parser);
	visitor_T* visitor = init_visitor();
	
	visitor_visit(visitor, root);
	
	return 0;
}
