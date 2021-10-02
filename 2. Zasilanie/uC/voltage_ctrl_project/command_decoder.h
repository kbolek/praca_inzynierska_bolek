#ifndef COMMAND_DECODER_H
#define COMMAND_DECODER_H

#define MAX_TOKEN_NR 2 
#define MAX_KEYWORD_STRING_LTH 3 
#define MAX_STRING_LTH 9
#define MAX_KEYWORD_NR 9
#define DELIMITER_CHAR 0x20

enum token_type { KEYWORD, NUMBER, STRING};
enum keyword_code {RS,RB,CC,CR,CRC,VC,VR,VRC,CD};
enum result { OK, FAIL };


union token_value {
    enum keyword_code as_keyword;
    unsigned int number;
    char *pc_str;
};

struct token {
    enum token_type as_type; 
    union token_value value;
};

struct keyword{
    enum keyword_code code;
    char as_string[MAX_KEYWORD_STRING_LTH + 1]; 
};


extern struct token as_token[MAX_TOKEN_NR];
extern unsigned char token_nr;

void decode_msg(char *pc_string);
       
#endif