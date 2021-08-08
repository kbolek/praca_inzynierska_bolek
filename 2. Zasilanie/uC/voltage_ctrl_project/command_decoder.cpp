#include "command_decoder.h"
#include <string.h>
#include <stdio.h>

struct keyword as_keyword_list[MAX_KEYWORD_NR]=
    {
        {RVR, "rvr"},
        {RCR,"rcr"},
        {CC, "cc"},
        {CV, "cv"},
        {RC, "rc"},
        {RV, "rv"},
        {RCC, "rcc"},
        {RVC, "rvc"}
    };
struct token as_token[MAX_TOKEN_NR];
enum state{TOKEN,DELIMITER};
unsigned char token_nr = 0;

unsigned char find_tokens_in_string(char *pc_str){
    char * current_token;
    unsigned char token_counter = 0;
    
    current_token = strtok(pc_str, " ");
    while(NULL != current_token && token_counter < MAX_TOKEN_NR){
        as_token[token_counter].value.pc_str = current_token;
        token_counter++;
        current_token = strtok(NULL, " ");
    }    
    return token_counter;
}

enum result string_to_keyword(char pc_str[],enum keyword_code *ptr_keyword_code){
    unsigned char keyword_counter;
    for(keyword_counter=0;keyword_counter<MAX_KEYWORD_NR;keyword_counter++)
    {
        if (strcmp(pc_str,as_keyword_list[keyword_counter].as_string) == 0)
        {
            *ptr_keyword_code = as_keyword_list[keyword_counter].code;
            return OK;
        }
    }
    return FAIL;
};


enum result decode_tokens(){
    
   unsigned int number;
   unsigned char token_index;
   enum keyword_code as_keyword;
    
    for(token_index=0; token_index < token_nr; token_index++){
        if((string_to_keyword (as_token[token_index].value.pc_str, &as_keyword))== OK){
            as_token[token_index].as_type = KEYWORD;
            as_token[token_index].value.as_keyword=as_keyword;
        }
        else if(sscanf(as_token[token_index].value.pc_str,"%d",&number) == 1){ 
            as_token[token_index].as_type = NUMBER;
            as_token[token_index].value.number = number;       
        }
        else{
            as_token[token_index].as_type = STRING;
        }
    }
    return OK;
}

void replace_characters_in_string(char pc_str[], char old_char,char new_char){
    char *ptr_string = pc_str;
    while((ptr_string = strchr(ptr_string,old_char)) != NULL){
        *ptr_string++ = new_char;
    }      
}

void decode_msg(char *pc_str){

    token_nr = find_tokens_in_string(pc_str);
    replace_characters_in_string(pc_str, ' ', '\0');
    decode_tokens();
}