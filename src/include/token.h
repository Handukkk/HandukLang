#ifndef TOKEN_H
#define TOKEN_H

typedef enum TOKEN_TYPE
{
	TOKEN_ID,
	TOKEN_EQUALS,
	TOKEN_STRING,
	TOKEN_COMMA,
	TOKEN_SEMICOLON,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_EOF,
	TOKEN_ILLEGAL	
} TokenType;

typedef struct TOKEN_STRUCT
{
	TokenType type;
	char* value;
} token_T;

token_T* init_token(TokenType type, char* value);

#endif
