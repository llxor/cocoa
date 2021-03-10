#include <stdio.h>
#include "engine.h"
#include "parser.h"

int main()
{
	char buffer[1000] = {0};

	do
	{
		printf("> ");
		if (fgets(buffer, sizeof buffer, stdin) == NULL)
		{
			break;
		}

		char *end = buffer;
		while (*end++) *end &= -(*end != '\n');

		Token tokens[100];
		int len = 0;

		const char *src = buffer;

		while (*src != 0)
		{
			tokens[len++] = parse_token(src, &src);
			trim(&src);
		}

		scan_for_errors(tokens, len);
		Queue RPN = convert_to_RPN(tokens, len);

		int value = eval(&RPN);
		printf("int: %10d\nhex: 0x%08X\n", value, value);
	}
	while(1);

	return 0;
}
