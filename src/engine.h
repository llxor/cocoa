#pragma once
#include "engine.h"
#include "queue.h"

Queue convert_to_RPN(Token *tokens, int len);
int eval(Queue *tokens);
