#include <bits/stdc++.h>
#include "src/lexer.cpp"
#include "src/parser.cpp"
#include "src/ast.cpp"

int main(int argc, char* argv[])
{
	char input_test[] = "var x = \"hehe\";println(x, y)";
	lexer_T* lexer = init_lexer(input_test);

	parser_T* parser = init_parser(lexer);
	ast_T* root = parser_parse(parser);
	
//	printf("Root type: %d\n", root->type);
//	printf("Root size: %d\n", root->compound_size);

//	while(parser->current_token->type != TOKEN_EOF)
//	{
//		printf("%s type: %d\n", parser->current_token->value, parser->current_token->type);
//		parser->current_token = lexer_get_next_token(lexer);
//	}
	return 0;
}
