clear &&
gcc src/main.c src/parser.c -o main &&
./main \
tests/at_simple_error_ok.txt \
tests/test_file_csq_not_ok_1.txt \
tests/test_file_csq_not_ok_3.txt \
tests/test_file_csq_ok.txt \
tests/multiple_commands.txt \
tests/test_file_copn_ok.txt \
tests/test_file_csq_not_ok_2.txt \
tests/test_file_csq_not_ok_4_no_cr_present.txt \
tests/test_file_simple_at_ok.txt