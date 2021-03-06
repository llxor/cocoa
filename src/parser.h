#pragma once
#include <stdio.h>

enum Token_Type
{
	NUM_LITERAL,
	OPERATOR,
	UNARY_OP,
	LEFT_PAREN,
	RIGHT_PAREN,
};

enum Operator
{
	// UNARY OPERATORS //
	NEG,
	NOT = '~',

	// BINARY OPERATORS //
	ADD = '+',
	SUB = '-',
	MUL = '*',
	DIV = '/',
	MOD = '%',
	EXP = 'e',

	// BITWISE OPERATORS //
	AND = '&',
	 OR = '|',
	XOR = '^',

	SHL = '<',
	SHR = '>',
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
void scan_for_errors(Token *tokens, int len);
