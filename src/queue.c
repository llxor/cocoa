#include "queue.h"

void push(Queue *queue, Token token)
{
	queue->tokens[queue->len++] = token;
}

Token pop(Queue *queue)
{
	return queue->tokens[--queue->len];
}

Token peek(Queue *queue)
{
	return queue->tokens[queue->len-1];
}

