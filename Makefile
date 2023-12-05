CC=gcc
TEST_SRC=test/unity.c

all: main.c data_structures/symtable.c scanner/scanner.c data_structures/tokens.c data_structures/str.c test/debug.c codeGenerator/compiler.c
	$(CC) -o main $^

foreign_test: 
	cd test/foreign_tests/ && ./test.sh
	cd ../..

foreign_test2: 
	cd test/foreign_tests2/ && ./test2.sh
	cd ../..

pepega_test: 
	cd test/pepega_tests/ifj23-tests-master && python3 compiler_tests.py
	cd ../../..


old_rus: main.c scanner/oldRusScanner.c data_structures/tokens.c data_structures/str.c test/debug.c codeGenerator/compiler.c
	$(CC) -o old_rus_script $^
	
symtable_test: test/symtable_test.c data_structures/symtable.c data_structures/str.c
	$(CC) -o $@ $^ $(TEST_SRC) -I. -lm

token_list_test: test/tokens_test.c data_structures/tokens.c
	$(CC) -o $@ $^ $(TEST_SRC) -I. -lm

scanner_test: test/scanner_test.c scanner/scanner.c data_structures/tokens.c
	$(CC) -o $@ $^ $(TEST_SRC) -I. -lm

parser_test: test/parser_test.c parser/parser.c scanner/scanner.c data_structures/tokens.c data_structures/symtable.c data_structures/str.c
	$(CC) -o $@ $^ $(TEST_SRC) -I. -lm