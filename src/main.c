#include<stdlib.h>
#include<stdio.h>
#include "parser.h"

int main()
{
    printf("Merrydo how do you do\n");

    uint8_t test_char;

    STATE_MACHINE_RETURN_VALUE res;

    char* input_filename = "tests/test_file_csq_ok.txt";
    FILE *input = fopen(input_filename, "rb");
    if(input == NULL)
        printf("COULD NOT OPEN %s\n", input_filename);
    else
        printf("OPENED %s\n", input_filename);

    fseek(input, 0, SEEK_END);          
    size_t filesize = ftell(input);            
    rewind(input);  

    uint8_t buffer; 
    for(int i = 0; i < filesize; i++) 
    {
        fread(&buffer, 1, 1, input); 
        //printf("|%c|", buffer);

        res = at_command_parse(buffer);

        if(res == STATE_MACHINE_READY_OK){
            printf("%s\n", getReturnValueString(res));
            for(int j = 0; j < data.line_count; j++){
                printf("|%s|\n", data.data[j]);
            }
        }
        //printf("%s\n", getReturnValueString(res));
    }
    printf("\n");

    /*
    open file
    while(!EOF)
    {
        read char   
        parser(char)
        if( ready==ok)
            print data
        if(ready = error)
            stop and print error message
            "expected %c and got %c"
    
    }*/
    
    fclose(input);
    return 0;
}