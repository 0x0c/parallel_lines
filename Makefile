CC = clang++ -std=c++11

all:
	$(CC) -g parallel_lines.cpp main.cpp

test:

clean:
	rm -r ./a.out
