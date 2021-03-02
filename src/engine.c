#include "engine.h"
#include "stdio.h"

static char prec[128] =
{
	['+'] = 1,
	['-'] = 1,
	['*'] = 2,
	['/'] = 2,
};

Queue convert_to_RPN(Token *tokens, int len)
{
	Queue output = {0}, ops = {0};	

	for (int i = 0; i < len; i++)
	{
		Token token = tokens[i];

		switch (token.kind)
		{
		case NUM_LITERAL:
			push(&output, token);
			break;

		case LEFT_PAREN:
			push(&ops, token);
			break;

		case RIGHT_PAREN:
			while (peek(&ops).kind != LEFT_PAREN)
				push(&output, pop(&ops));
			pop(&ops);
			break;

		case OPERATOR:
			while (ops.len && peek(&ops).kind != LEFT_PAREN
				&& prec[peek(&ops).value] >= prec[token.value])
			{
				push(&output, pop(&ops));
			}
			push(&ops, token);
			break;
		}
	}

	while (ops.len)
		push(&output, pop(&ops));

	return output;
}

int eval(Queue *tokens)
{
	if (tokens->len == 0)
	{
		puts("[ERROR]");
		for(;;);
	}

	Token token = pop(tokens);

	if (token.kind == NUM_LITERAL)
		return token.value;

	int B = eval(tokens);
	int A = eval(tokens);

	switch (token.value)
	{
		case '+': return A + B;
		case '-': return A - B;
		case '*': return A * B;
		case '/': return A / B;
	}

	puts("[ERROR]");
	for(;;);
	return 0;
}
