#pragma once
#include "parser.h"

struct Queue
{
	Token tokens[100];
	int len;
};

typedef struct Queue Queue;

void push(Queue *queue, Token token);
Token pop(Queue *queue);
Token peek(Queue *queue);

