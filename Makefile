CFLAGS = -O3 -s -Wall -Wextra -Werror

default:; gcc -o main src/main.c $(CFLAGS)
format:; indent src/*.c -linux && rm src/*.c~
