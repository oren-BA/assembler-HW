//
// Created by orenb on 13/08/2021.
//

#ifndef ASSEMBLER_HW_TOKEN_H
#define ASSEMBLER_HW_TOKEN_H
enum TokenType{
    LabelDefinition, //
    Label,
    Command,
    Register,
    Number,
    String,
};

typedef struct Token Token;
struct Token{
    enum TokenType type;
    char* content;
} ;
#endif //ASSEMBLER_HW_TOKEN_H
