#include<stdlib.h>
#include<stdio.h>
#include "parser.h"

int main(const int argc, const char **argv)
{
    printf("Merrydo how do you do\n");
    printf("Running AT command parser with %i arguments. They are:\n", argc);
    for(int i = 0; i < argc; i++){
        printf("[%i] %s\n", i, argv[i]);
    }

    for(int file_idx = 1; file_idx < argc; file_idx++){
        const char* input_filename = argv[file_idx];
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

            STATE_MACHINE_RETURN_VALUE res = at_command_parse(buffer);

            if(res == STATE_MACHINE_READY_OK){
                printf("%s\n", getReturnValueString(res));
                for(int j = 0; j < data.line_count; j++){
                    printf("|%s|\n", data.data[j]);
                }
            }
            //printf("%s\n", getReturnValueString(res));
        }
        printf("\n");
        
        fclose(input);
    }

    

    return 0;
}