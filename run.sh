clear &&
gcc ./src/main.c ./src/parser.c -o main &&
cd tests &&
../main test_file_simple_at_ok.txt