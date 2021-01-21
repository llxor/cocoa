CFLAGS = -O3 -s -lSDL2 -lSDL2main
default:; clang src/main.cc -o main $(CFLAGS)
format:; clang-format -i src/main.cc
