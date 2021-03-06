#include "parser.h"

void trim(const char **src)
{
	while (**src == ' ')(*src)++;
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
	const char *ref = src;

	while (('0' <= *src && *src <= '9')
	    || ('a' <= *src && *src <= 'f')
	    || ('A' <= *src && *src <= 'F'))
	{
		char d = *src | 0x20;
		char r = d - diff[d >= 'a'];

		if (r >= base)
		{
			printf("[ERROR] invalid digit '%c' in base-%d integer\n", *src, base);
			for(;;);
		}

		res = res * base + r;
		src++;
	}

	if (src == ref)
	{
		printf("[ERROR] invalid char '%c'\n", *src);
		for(;;);
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

		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
		case '&':
		case '|':
		case '^':
		case '~':
		case '>':
		case '<':
			token.kind = OPERATOR;
			token.value = *src;

			if (*(src + 1) == *src)
			{
				if (*src++ == '*')
				{
					token.value = EXP;
				}
			}

			else if (*src == '>' || *src == '<')
			{
				printf("[ERROR] expected '%c' found '%c'", *src, *(src+1));
				for(;;);
			}

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

void scan_for_errors(Token *tokens, int len)
{
	if (len == 0)
	{
		puts("[ERROR] empty expression");
		for(;;);
	}

	int parens = 0;

	for (int i = 0; i<len; i++)
	{
		Token token = tokens[i];

		switch (token.kind)
		{
		case LEFT_PAREN:
			parens++;
			break;

		case RIGHT_PAREN:
			parens--;
			if (parens < 0)
			{
				puts("[ERROR] mismatched )");
				for(;;);
			}
			break;
		}
	}

	if (parens != 0)
	{
		puts("[ERROR] mismatched (");
		for(;;);
	}

	Token last = {.kind = OPERATOR};

	for (int i = 0; i < len; i++)
	{
		Token token = tokens[i];
		char valid = 0;

		switch (last.kind)
		{
		case NUM_LITERAL:
			valid = token.kind == OPERATOR
			     || token.kind == RIGHT_PAREN;
			break;

		case OPERATOR:
			valid = token.kind == NUM_LITERAL
			     || token.kind == LEFT_PAREN
			     || token.value == '-'
			     || token.value == '~';

			switch (token.value)
			{
			case '-':
				token.kind = tokens[i].kind = UNARY_OP;
				token.value = tokens[i].value = NEG;
				break;

			case '~':
				token.kind = tokens[i].kind = UNARY_OP;
				token.value = tokens[i].value = NOT;
				break;
			}

			break;

		case UNARY_OP:
			valid = token.kind == NUM_LITERAL
			     || token.kind == LEFT_PAREN;
			break;

		case LEFT_PAREN:
			valid = token.kind == NUM_LITERAL
			     || token.value == '-'
			     || token.value == '~';

			if (token.kind == OPERATOR)
			{
				switch (token.value)
				{
				case '-':
					token.kind = tokens[i].kind = UNARY_OP;
					token.value = tokens[i].value = NEG;
					break;

				case '~':
					token.kind = tokens[i].kind = UNARY_OP;
					token.value = tokens[i].value = NOT;
					break;
				}
			}

			break;

		case RIGHT_PAREN:
			valid = token.kind == OPERATOR;
			break;
		}

		last = token;
		if (!valid)
		{
			puts("[ERROR] unexpected symbol");
			printf("%d (%d)\n", token.kind, token.value);
			for(;;);
		}
	}

	if (tokens[len-1].kind == OPERATOR ||
	    tokens[len-1].kind == LEFT_PAREN)
	{
		char value = tokens[len-1].value ?: '(';
		printf("[ERROR] expression cannot end with '%c'\n", value);
		for(;;);
	}
}
