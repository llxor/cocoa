#include "parser.h"

void trim(const char **src)
{
	for (; **src == ' '; (*src)++);
}

int parse_number(const char *src, const char **end)
{
	int base = 10;
	int res = 0;

	if (*src == '0')
	{
		src++;
		switch (*src | 0x20)
		{
		case ' ': return (*end = src), 0;
		case 'b': base =  2; break;
		case 'x': base = 16; break;
		default:  base =  8; break;
		}
		src++;
	}

	const char *diff = "0W";

	while (('0' <= *src && *src <= '9')
	    || ('a' <= *src && *src <= 'f')
	    || ('A' <= *src && *src <= 'F'))
	{
		char d = *src | 0x20;
		res = res * base + d - diff[d >= 'a'];
		src++;
	}

	*end = src;
	return res;
}

Token parse_token(const char *src, const char **end)
{
	Token token = {0};
	
	switch (*src)
	{
		case '(': token.kind = LEFT_PAREN;  break;
		case ')': token.kind = RIGHT_PAREN; break;

		case '+': case '-': case '*': case '/':
			token.kind = OPERATOR;
			token.value = *src;
			break;

		default:
			token.kind = NUM_LITERAL; 
			token.value = parse_number(src, &src);
			break;
	}

	src += (token.kind != NUM_LITERAL);
	*end = src;

	return token;
}
