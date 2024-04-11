#include "include/lexer.h"
#include "token.cpp"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

lexer_T* init_lexer(char* contents)
{
	lexer_T* lexer = (struct LEXER_STRUCT*) malloc(sizeof(struct LEXER_STRUCT));
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	
	return lexer;
}

void lexer_advance(lexer_T* lexer)
{
	if(lexer->c != '\0' && lexer->i < strlen(lexer->contents))
	{
		lexer->i++;
		lexer->c = lexer->contents[lexer->i];
	}
}

void lexer_ignore_whitespace(lexer_T* lexer)
{
	while(lexer->c == ' ' || lexer->c == 10)
	{
		lexer_advance(lexer);
	}
}

token_T* lexer_get_next_token(lexer_T* lexer)
{
	while(lexer->c != '\0' && lexer->i < strlen(lexer->contents))
	{
		if(lexer->c == ' ' || lexer->c == 10) lexer_advance(lexer);
	
		if(isalnum(lexer->c)) return lexer_get_token_id(lexer);
		
		if(lexer->c == '"') return lexer_get_string(lexer);
		
		switch(lexer->c)
		{
			case '=': return lexer_advance_get_token(lexer, init_token(TOKEN_EQUALS, lexer_get_char_as_string(lexer))); break;
			case ',': return lexer_advance_get_token(lexer, init_token(TOKEN_COMMA, lexer_get_char_as_string(lexer))); break;
			case ';': return lexer_advance_get_token(lexer, init_token(TOKEN_SEMICOLON, lexer_get_char_as_string(lexer))); break;
			case '(': return lexer_advance_get_token(lexer, init_token(TOKEN_LPAREN, lexer_get_char_as_string(lexer))); break;
			case ')': return lexer_advance_get_token(lexer, init_token(TOKEN_RPAREN, lexer_get_char_as_string(lexer))); break;
			default : return lexer_advance_get_token(lexer, init_token(TOKEN_ILLEGAL, lexer_get_char_as_string(lexer))); break;
		}
	}
	
	return init_token(TOKEN_EOF, (char*) 0);
}

token_T* lexer_get_string(lexer_T* lexer)
{
	lexer_advance(lexer);
	char* string = (char*) malloc(sizeof(char));
	string[0] = '\0';
	while(lexer->c != '"')
	{
		char* s = lexer_get_char_as_string(lexer);
		string = (char*) realloc(string, (strlen(string) + strlen(s) + 1) * sizeof(char));
		strcat(string, s);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	
	return init_token(TOKEN_STRING, string);
}

token_T* lexer_get_token_id(lexer_T* lexer)
{
	char* string = (char*) malloc(sizeof(char));
	string[0] = '\0';
	
	while(isalnum(lexer->c))
	{
		char* s = lexer_get_char_as_string(lexer);
		string = (char*) realloc(string, (strlen(string) + strlen(s) + 1) * sizeof(char));
		strcat(string, s);
		lexer_advance(lexer);
	}
	
	return init_token(TOKEN_ID, string);
}

token_T* lexer_advance_get_token(lexer_T* lexer, token_T* token)
{
	lexer_advance(lexer);
	return token;
}	

char* lexer_get_char_as_string(lexer_T* lexer)
{
	char* string = (char*) malloc(sizeof(char) * 2);
	string[0] = lexer->c;
	string[1] = '\0';
	
	return string;
}
