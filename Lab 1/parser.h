//header parser.h

//header guard
#ifndef __PARSER_AT__
#define __PARSER_AT__
#include <stdint.h>
//custom data types
#define AT_COMMAND_MAX_LINES 100
#define AT_COMMAND_MAX_LINE_SIZE 128

typedef struct 
{
    /* data */
    uint8_t ok;
    uint8_t data[AT_COMMAND_MAX_LINES][AT_COMMAND_MAX_LINE_SIZE];
    uint32_t line_count;
}AT_COMMAND_DATA;

extern AT_COMMAND_DATA data;

typedef enum
{
    STATE_MACHINE_NOT_READY; // in  state 1 for ex if i get an lf; i can put it like a default after the cases; is for intermediary states
    STATE_MACHINE_READY_OK; //i will return when i have complete transmission and everying ok
    STATE_MACHINE_READY_WITH_ERROR; //
}STATE_MACHINE_RETURN_VALUE;

//function declaration 
STATE_MACHINE_RETURN_VALUE at_command_parse(uint8_t crt_char);

#endif
