CC=gcc
TEST_SRC=test/unity.c

all: main.c scanner/scanner.c data_structures/tokens.c test/debug.c
	$(CC) -o main $^

symtable_test: test/symtable_test.c data_structures/symtable.c
	$(CC) -o $@ $^ $(TEST_SRC) -I. -lm

token_list_test: test/tokens_test.c data_structures/tokens.c
	$(CC) -o $@ $^ $(TEST_SRC) -I. -lm

scanner_test: test/scanner_test.c scanner/scanner.c data_structures/tokens.c
	$(CC) -o $@ $^ $(TEST_SRC) -I. -lm