clear &&
gcc ./src/main.c ./src/parser.c -o main &&
cd tests &&
../main multiple_commands.txt