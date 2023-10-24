clear &&
cd tests &&
gcc ../src/main.c ../src/parser.c -o main &&
./main \
at_simple_error_ok.txt \
test_file_csq_not_ok_1.txt \
test_file_csq_not_ok_3.txt \
test_file_csq_ok.txt \
multiple_commands.txt \
test_file_copn_ok.txt \
test_file_csq_not_ok_2.txt \
test_file_csq_not_ok_4_no_cr_present.txt \
test_file_simple_at_ok.txt