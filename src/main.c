#include<stdlib.h>
#include<stdio.h>
#include "parser.h"

int main()
{
    printf("Merrydo how do you do\n");

    uint8_t test_char;

    STATE_MACHINE_RETURN_VALUE res = at_command_parse(test_char);

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
    return 0;
}