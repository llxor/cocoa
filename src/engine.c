#include "engine.h"

static char prec[128] =
{
	[AND] = 1,
	[ OR] = 1,
	[XOR] = 1,

	[SHL] = 2,
	[SHR] = 2,

	[ADD] = 3,
	[SUB] = 3,
	[MUL] = 3,
	[DIV] = 4,
	[MOD] = 4,
	[EXP] = 5,

	[NEG] = 6,
	[NOT] = 6,
};

Queue convert_to_RPN(Token *tokens, int len)
{
	Queue output = {0}, ops = {0};	

	for (int i = 0; i < len; i++)
	{
		Token token = tokens[i],
		      unary_arg = {.kind = NUM_LITERAL};

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
			switch (token.value)
			{
			case NEG: unary_arg.value =  0; break;
			case NOT: unary_arg.value = -1; break;
			}

			push(&output, unary_arg);
			token.kind = OPERATOR;
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

inline int _exp(int a, int b)
{
	int v = 1;

	while (b)
	{
		v *= a * (b&1) + (~b&1);
		a *= a;
		b >>= 1;
	}

	return v;
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
		case MOD: return B % A;
		case EXP: return _exp(B,A);

		case AND: return B & A;
		case  OR: return B | A;
		case XOR: return B ^ A;

		case SHL: return B << A;
		case SHR: return B >> A;

		case NEG: return B - A; // (B =  0) - A; 
		case NOT: return B ^ A; // (B = -1) ^ A;
	}

	puts("[ERROR]");
	for(;;);
	return 0;
}
