clear &&
gcc ./src/main.c ./src/parser.c -o main &&
cd new_tests &&
../main \
multiple_commands_2.txt