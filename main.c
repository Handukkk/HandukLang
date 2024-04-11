#include "src/lexer.c"
#include "src/parser.c"
#include "src/ast.c"
#include "src/visitor.c"
#include "src/stdutil.c"

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		puts("Usage: main.exe <input.hk>");
		exit(1);
	}
	
	char name_check[100];
	strcpy(name_check, argv[1]);
	char* ext = NULL;
	char* token = strtok(name_check, ".");
	while(token)
	{
		ext = token;
		token = strtok(NULL, ".");
	}
	
	if(strcmp(ext, "hk") != 0)
	{
		puts("Unknown file type!");
		exit(1);
	}
	
	char* filepath = argv[1];
	FILE* fp = fopen(filepath, "r");
	if(!fp)
	{
		puts("File not found!");
		exit(1);
	}
	
	char* buffer;
	long len;
	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	
	buffer = calloc(len, len);
	
	if(buffer)
	{
		fread(buffer, 1, len, fp);
	}
	fclose(fp);
	
	lexer_T* lexer = init_lexer(buffer);

	parser_T* parser = init_parser(lexer);
	ast_T* root = parser_parse(parser);
	visitor_T* visitor = init_visitor();
	
	visitor_visit(visitor, root);
	
	return 0;
}
