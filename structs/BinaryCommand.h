#ifndef ASSEMBLER_HW_BINARYCOMMAND_H
#define ASSEMBLER_HW_BINARYCOMMAND_H
enum CommandType{R, I, J, D, ASCII, E};

typedef struct BinaryCommand BinaryCommand;
struct  BinaryCommand{
    int command;
    int mask; /* indicates which bits are yet to be determined. 0 - not determined */
    enum CommandType type;
} ;

#endif /* ASSEMBLER_HW_BINARYCOMMAND_H */
