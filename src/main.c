#include<stdlib.h>
#include<stdio.h>
#include "parser.h"
#include<string.h>

static const int flag_lines[] = {10, 14, 1027, 2022};
static const num_flags = sizeof(flag_lines) / sizeof(int);
int line_counter = 1;

void isAtypical(){
    for(int i = 0; i < num_flags; i++){
        if(line_counter == flag_lines[i]){
            ATYPICAL_CMD_FLAG = 1;
            return;
        }
    }
    ATYPICAL_CMD_FLAG = 0;
}

int main(const int argc, const char **argv)
{
    printf("Merrydo how do you do\n");
    printf("Running AT command parser with %i arguments. They are:\n", argc);
    for(int i = 0; i < argc; i++)
    {
        printf("[%i] %s\n", i, argv[i]);
    }
    printf("\n");

    for(int file_idx = 1; file_idx < argc; file_idx++)
    {
        const char* input_filename = argv[file_idx];
        char output_filename[100];
        strcpy(output_filename, "output/output_");
        strcat(output_filename, input_filename);
        
        FILE *input = fopen(input_filename, "rb");
        if(input == NULL)
        {
            printf("FAILED TO OPEN %s\n", input_filename);
            return 1;
        }
        else
            printf("OPENED %s\n", input_filename);

        FILE *output = fopen(output_filename, "wb");
        if(output == NULL)
        {
            printf("FAILED TO OPEN %s\n", input_filename);
            return 2;
        }
        else
            printf("OPENED %s\n", output_filename);

        fseek(input, 0, SEEK_END);
        size_t filesize = ftell(input);
        rewind(input);

        data.ok = 1;
        data.line_count = 0;

        for(int i = 0; i < filesize; i++)
        {
            uint8_t buffer; 
            fread(&buffer, 1, 1, input);
            isAtypical();

            STATE_MACHINE_RETURN_VALUE res = at_command_parse(buffer);

            if(res == STATE_MACHINE_READY_OK)
            {
                fprintf(output, "%s, %i lines\n", getOKorERROR(data.ok), data.line_count);
                for(int j = 0; j < data.line_count; j++){
                    fprintf(output, "%s\n", data.data[j]);
                }
            }
            else if(res == STATE_MACHINE_READY_WITH_ERROR){
                fprintf(output, "%s, %i lines\n", "SYNTAX_ERROR", data.line_count);
                for(int j = 0; j < data.line_count; j++){
                    fprintf(output, "%s\n", data.data[j]);
                }
                //fprintf(output, "%s\n", getOKorERROR(res));
            }
            else
            {
                //printf("%s\n", getReturnValueString(res));
            }
            
            if(buffer == LF){
                line_counter++;
            }
        }
        printf("\n");
        
        fclose(input);
        fclose(output);
    }


    return 0;
}