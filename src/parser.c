#include "parser.h"

AT_COMMAND_DATA data;

//function definition
STATE_MACHINE_RETURN_VALUE at_command_parse(uint8_t crt_char )
{
    
    static uint8_t state = 0;
    static uint8_t col_cnt = 0;
    switch(state) //reset to state 0 after the transmission 
    {
        case 0:
            if(crt_char == 13) //CR
            {
                state = 1;
                data.line_count = 0;
                col_cnt = 0;
            }
            break;
        case 1: 
           if(crt_char == 10) //LF
            {
                state = 2;
                return STATE_MACHINE_NOT_READY;
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 2:
            if(crt_char == 'O') //o
            {
                state = 3;
            }
            else if(crt_char == 'E') // e
            {
                
            }
            else if(crt_char == '+') // +
            {

            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
            
            break;
        //...
        //random number, will change 22 with nr from drawing
        case 22:
            if(crt_char >= 32 && crt_char <= 126) 
            {   //change -1 with value
                if(col_cnt < -1)
                {
                    data.data[data.line_count][col_cnt] = crt_char;
                    col_cnt++;
                }
            }
            else if(crt_char == 13) //CR
            {
                //increase line count or wait for +
                col_cnt = 0;
                //counter update with line width or set terminator
            }
            else
            {
                return STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
    }
}