#ifndef PARSER_h //start header guard
#define PARSER_h

#include <stdint.h>

#define CR 13
#define LF 10
#define DONE_OK 21
#define DONE_ERROR 22
#define AT_COMMAND_MAX_LINES 1000
#define AT_COMMAND_MAX_LINE_SIZE 128

//#define ENABLE_LOG

extern char* STR_NOT_READY;
extern char* STR_READY_OK;
extern char* STR_READY_WITH_ERROR;
extern char* STR_UNKNOWN;
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
    STATE_MACHINE_NOT_READY,// in  state 1 for ex if i get an lf; i can put it like a default after the cases; is for intermediary states
    STATE_MACHINE_READY_OK, //i will return when i have complete transmission and everying ok
    STATE_MACHINE_READY_WITH_ERROR //
}STATE_MACHINE_RETURN_VALUE;

//function declaration 
STATE_MACHINE_RETURN_VALUE at_command_parse(uint8_t crt_char);

char* getReturnValueString(STATE_MACHINE_RETURN_VALUE val);

char* getOKorERROR(uint8_t ok);

#endif //end header guard
