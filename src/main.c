#include <stdio.h>
#include "parser.h"
#include "engine.h"

int main()
{
	const char *src = "(~4 + -5 * (6 + 4) / -(2 & 3) * 0xff) % 71";
	const char *original = src;

	Token tokens[100];
	int len = 0;

	while (*src != 0)
	{
		tokens[len++] = parse_token(src, &src);
		trim(&src);
	}

	scan_for_errors(tokens, len);
	Queue RPN = convert_to_RPN(tokens, len);
	printf("%s = %d\n", original, eval(&RPN));

	return 0;
}
