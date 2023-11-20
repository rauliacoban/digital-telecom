clear &&
gcc ./src/main.c ./src/parser.c -o main &&
cd new_tests &&
../main \
test_file_gmi_nok.txt  \
test_file_gmi_ok.txt