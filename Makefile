FLAGS = -lm -O3 -Wall -Wextra -Wpedantic

examples:
	gcc examples.c -o examples $(FLAGS)

tests:
	gcc tests.c -g3 -o tests $(FLAGS)
	./tests
	rm tests

.PHONY: tests examples
