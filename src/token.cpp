#include "include/token.h"
#include <stdlib.h>

token_T* init_token(TokenType type, char* value)
{
	token_T* token = (struct TOKEN_STRUCT*) malloc(sizeof(struct TOKEN_STRUCT));
	token->type = type;
	token->value = value;
	
	return token;
}
