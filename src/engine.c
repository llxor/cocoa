#include "engine.h"
#include "stdio.h"

static char prec[128] =
{
	[ADD] = 1,
	[SUB] = 1,
	[MUL] = 2,
	[DIV] = 2,
	[NEG] = 3,
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

		case UNARY_OP:
			token.kind = NUM_LITERAL, token.value = 0;
			push(&output, token);
			token.kind = OPERATOR, token.value = NEG;
			// fallthrough;

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

	int A = eval(tokens);
	int B = eval(tokens);

	switch (token.value)
	{
		case ADD: return B + A;
		case SUB: return B - A;
		case MUL: return B * A;
		case DIV: return B / A;
		case NEG: return B - A; // multiply by -1
	}

	puts("[ERROR]");
	for(;;);
	return 0;
}
