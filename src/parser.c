#include "parser.h"
#include<stdio.h>

AT_COMMAND_DATA data;

char* STR_NOT_READY = "NOT_READY";
char* STR_READY_OK = "READY_OK";
char* STR_READY_WITH_ERROR = "READY_WITH_ERROR";
char* STR_UNKNOWN = "UNKOWN_STATE_THIS_SHOULD_NOT_HAPPEN";

char* STR_OK = "OK";
char* STR_ERROR = "ERROR" ;

char* getReturnValueString(STATE_MACHINE_RETURN_VALUE val){
    if(val == STATE_MACHINE_NOT_READY)
        return STR_NOT_READY;
    else if(val == STATE_MACHINE_READY_OK)
        return STR_READY_OK;
    else if(val == STATE_MACHINE_READY_WITH_ERROR)
        return STR_READY_WITH_ERROR;
    return STR_UNKNOWN;
}

char* getOKorERROR(STATE_MACHINE_RETURN_VALUE val){
    if(val == STATE_MACHINE_NOT_READY)
        return STR_UNKNOWN;
    else if(val == STATE_MACHINE_READY_OK)
        return STR_OK;
    else if(val == STATE_MACHINE_READY_WITH_ERROR)
        return STR_ERROR;
    return STR_UNKNOWN;
}

//function definition
STATE_MACHINE_RETURN_VALUE at_command_parse(uint8_t crt_char)
{
    static uint8_t state = 0;
    static uint8_t col_cnt = 0;

    #ifdef ENABLE_LOG
        printf("#################################################\n");
        printf("Parsing char with value %i %c with state %i\n", crt_char, crt_char, state);
    #endif

    STATE_MACHINE_RETURN_VALUE ret = STATE_MACHINE_NOT_READY;;
    if(state == 0){
        data.ok = 1;
        data.line_count = 0;
        col_cnt = 0;
    }

    switch(state) //reset to state 0 after the transmission 
    {
        case 0:
            if(crt_char == CR) //CR
            {
                state = 1;
            }
            break;
        case 1: 
            if(crt_char == 10) //LF
            {
                state = 2;
            }
            else
            {
                ret = STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 2:
            if(crt_char == 'O') //o
            {
                state = 3;
            }
            else if(crt_char == 'E') // e
            {
                state = 6;
            }
            else if(crt_char == '+') // +
            {
                state = 12;
                data.line_count = 0;
                col_cnt = 0;
                data.data[data.line_count][col_cnt] = crt_char;
                col_cnt++;
            }
            else
            {
                ret = STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 3:
            if(crt_char == 'K')
            {
                state = 4;
            }
            else
            {
                ret = STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 4:
            if(crt_char ==  CR)
            {
                state = 5;
            }
            else
            {
                ret = STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 5:
            if(crt_char ==  LF)
            {
                state = DONE_OK;
                ret = STATE_MACHINE_READY_OK;
            }
            else
            {
                ret = STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 6:
            if(crt_char == 'R')
            {
                state = 7;
            }
            else
            {
                ret = STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 7:
            if(crt_char == 'R')
            {
                state = 8;
            }
            else
            {
                ret = STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 8:
            if(crt_char == 'O')
            {
                state = 9;
            }
            else
            {
                ret = STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 9:
            if(crt_char == 'R')
            {
                state = 10;
            }
            else
            {
                ret = STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 10:
            if(crt_char == CR)
            {
                state = 11;
            }
            else
            {
                ret = STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 11:
            if(crt_char == LF)
            {
                state = DONE_ERROR;
                ret = STATE_MACHINE_READY_WITH_ERROR;
            }
            else
            {
                ret = STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 12:
            if(crt_char >= 'A' && crt_char <= 'Z')
            {
                state = 13;
                data.data[data.line_count][col_cnt] = crt_char;
                col_cnt++;
            }
            else
            {
                ret = STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 13:
            if(crt_char >= 'A' && crt_char <= 'Z')
            {
                state = 13;
                data.data[data.line_count][col_cnt] = crt_char;
                col_cnt++;
            }
            else if(crt_char == ':')
            {
                state = 14;
                data.data[data.line_count][col_cnt] = crt_char;
                col_cnt++;
            }
            else
            {
                ret = STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 14:
            if(crt_char == ' ')
            {
                state = 15;
                data.data[data.line_count][col_cnt] = crt_char;
                col_cnt++;
            }
            else
            {
                ret = STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 15:
            if(crt_char >= 32 && crt_char <= 126)
            {
                state = 16;
                data.data[data.line_count][col_cnt] = crt_char;
                col_cnt++;
            }
            else
            {
                ret = STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 16:
            if(crt_char >= 32 && crt_char <= 126)
            {
                state = 16;
                data.data[data.line_count][col_cnt] = crt_char;
                col_cnt++;
            }
            else if(crt_char == CR)
            {
                state = 17;
            }
            else
            {
                ret = STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 17:
            if(crt_char == LF)
            {
                state = 18;
                data.data[data.line_count][col_cnt] = 0;
                col_cnt++;
            }
            else
            {
                ret = STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 18:
            if(crt_char == CR)
            {
                state = 19;
            }
            else if(crt_char == '+')
            {
                state = 12;
                data.line_count++;
                col_cnt = 0;
                data.data[data.line_count][col_cnt] = crt_char;
                col_cnt++;
            }
            else
            {
                ret = STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 19:
            if(crt_char == LF)
            {
                state = 20;
            }
            else
            {
                ret = STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
        case 20:
            if(crt_char == 'O')
            {
                state = 3;
            }
            else if(crt_char == 'E')
            {
                state = 6;
            }
            else
            {
                ret = STATE_MACHINE_READY_WITH_ERROR;
            }
            break;
    }

    #ifdef ENABLE_LOG
    printf("Exiting with state %i %s %s\n", state, data.data[data.line_count], getReturnValueString(ret));
    #endif

    if(ret == STATE_MACHINE_READY_WITH_ERROR){
        data.ok = 0;
        data.data[data.line_count][col_cnt] = 0;
        data.line_count++;
        state = 0;
    }
    if(ret == STATE_MACHINE_READY_OK){
        data.ok = 1;
        data.data[data.line_count][col_cnt] = 0;
        //data.line_count++;
        state = 0;
    }

    return ret;
}