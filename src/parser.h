#pragma once

enum Token_Type
{
	NUM_LITERAL,
	OPERATOR,
	LEFT_PAREN,
	RIGHT_PAREN,
};

struct Token
{
	int kind, value;
};

typedef struct Token Token;
typedef enum Token_Type Token_Type;

void trim(const char **src);
int parse_number(const char *src, const char **end);
Token parse_token(const char *src, const char **end);