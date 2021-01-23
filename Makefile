CFLAGS = -O3 -s -Wall -Wextra -Werror

default:; clang $(CFLAGS) src/main.cc -o main
format:; clang-format -i src/main.cc
