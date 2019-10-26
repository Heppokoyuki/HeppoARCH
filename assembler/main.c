#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

typedef enum {
    NOP,
    ADD,
    SUB,
    AND,
    OR,
    SL,
    SR,
    SRA,
    LDL,
    LDH,
    CMP,
    JE,
    JMP,
    LD,
    ST,
    MOV
} inst_t;

typedef enum {
    R0,
    R1,
    R2,
    R3
} reg_t;

int
op_code(char *mnemonic)
{
    if(!strncmp(mnemonic, "NOP", 3))
        return NOP;
    if(!strncmp(mnemonic, "ADD", 3))
        return ADD;
    if(!strncmp(mnemonic, "SUB", 3))
        return SUB;
    if(!strncmp(mnemonic, "AND", 3))
        return AND;
    if(!strncmp(mnemonic, "OR ", 3))
        return OR;
    if(!strncmp(mnemonic, "SL ", 3))
        return SL;
    if(!strncmp(mnemonic, "SR ", 3))
        return SR;
    if(!strncmp(mnemonic, "SRA", 3))
        return SRA;
    if(!strncmp(mnemonic, "LDL", 3))
        return LDL;
    if(!strncmp(mnemonic, "LDH", 3))
        return LDH;
    if(!strncmp(mnemonic, "CMP", 3))
        return CMP;
    if(!strncmp(mnemonic, "JE ", 3))
        return JE;
    if(!strncmp(mnemonic, "JMP", 3))
        return JMP;
    if(!strncmp(mnemonic, "LD ", 3))
        return LD;
    if(!strncmp(mnemonic, "ST ", 3))
        return ST;
    if(!strncmp(mnemonic, "MOV", 3))
        return MOV;
    return -1;
}

uint64_t
reg(char *code)
{
    uint64_t r1;

    switch(code[5]) {
        case '0':
            r1 = R0;
            break;
        case '1':
            r1 = R1;
            break;
        case '2':
            r1 = R2;
            break;
        case '3':
            r1 = R3;
            break;
        default:
            printf("invalid instruction: %s\n", code);
            exit(-1);
    }

    return r1 << 8;
}

uint64_t
imm(char *code)
{
    uint64_t r1;
    int i = 0;
    char buf[10], *p;

    p = code + 4;
    while(*p != '\n') {
        if(i > 10) {
            printf("invalid instruction: %s\n", code);
            exit(-1);
        }
        buf[i] = *p;
        ++i, ++p;
    }
    r1 = atoi(buf);

    return r1;
}

uint64_t
regimm(char *code)
{
    uint64_t r1, r2;
    int i = 0;
    char buf[10], *p;

    switch(code[5]) {
        case '0':
            r1 = R0;
            break;
        case '1':
            r1 = R1;
            break;
        case '2':
            r1 = R2;
            break;
        case '3':
            r1 = R3;
            break;
        default:
            printf("invalid instruction: %s\n", code);
            exit(-1);
    }
    
    p = code + 8;
    while(*p != '\n') {
        if(i > 10) {
            printf("invalid instruction: %s\n", code);
            exit(-1);
        }
        buf[i] = *p;
        ++i, ++p;
    }
    r2 = atoi(buf);
    return r1 << 8 | r2;
}

uint64_t
regreg(char *code)
{
    uint64_t r1, r2;

    switch(code[5]) {
        case '0':
            r1 = R0;
            break;
        case '1':
            r1 = R1;
            break;
        case '2':
            r1 = R2;
            break;
        case '3':
            r1 = R3;
            break;
        default:
            printf("invalid instruction: %s\n", code);
            exit(-1);
    }

    switch(code[9]) {
        case '0':
            r2 = R0;
            break;
        case '1':
            r2 = R1;
            break;
        case '2':
            r2 = R2;
            break;
        case '3':
            r2 = R3;
            break;
        default:
            printf("invalid instruction: %s\n", code);
            exit(-1);
    }

    return r1 << 8 | r2 << 5;
}

int
main(void)
{
    char buf[256], inst[4];
    int count = 0;
    FILE *in, *out;

    printf("FIle name: ");
    scanf("%s", buf);

    if((in = fopen(buf, "r")) == NULL) {
        puts("file open error!");
        return -1;
    }

    if((out = fopen("rom_init.mif", "w")) == NULL) {
        puts("file open error!");
        return -1;
    }

    fprintf(out, "WIDTH=15;\n");
    fprintf(out, "DEPTH=256;\n");
    fprintf(out, "ADDRESS_RADIX=HEX;\n");
    fprintf(out, "DATA_RADIX=HEX;\n");
    fprintf(out, "CONTENT BEGIN\n");

    while(fgets(buf, 256, in) != NULL) {
        strncpy(inst, buf, 3);

        switch(op_code(inst)) {
            case NOP:
                fprintf(out, "\t%03X   :   %04X;\n", count, NOP << 11);
                break;
            case ADD:
                fprintf(out, "\t%03X   :   %04X;\n", count, ADD << 11 | regreg(buf));
                break;
            case SUB:
                fprintf(out, "\t%03X   :   %04X;\n", count, SUB << 11 | regreg(buf));
                break;
            case AND:
                fprintf(out, "\t%03X   :   %04X;\n", count, AND << 11 | regreg(buf));
                break;
            case OR:
                fprintf(out, "\t%03X   :   %04X;\n", count, OR << 11 | regreg(buf));
                break;
            case SL:
                fprintf(out, "\t%03X   :   %04X;\n", count, SL << 11 | reg(buf));
                break;
            case SR:
                fprintf(out, "\t%03X   :   %04X;\n", count, SR << 11 | reg(buf));
                break;
            case SRA:
                fprintf(out, "\t%03X   :   %04X;\n", count, SRA << 11 | reg(buf));
                break;
            case LDL:
                fprintf(out, "\t%03X   :   %04X;\n", count, LDL << 11 | regimm(buf));
                break;
            case LDH:
                fprintf(out, "\t%03X   :   %04X;\n", count, LDH << 11 | regimm(buf));
                break;
            case CMP:
                fprintf(out, "\t%03X   :   %04X;\n", count, CMP << 11 | regreg(buf));
                break;
            case JE:
                fprintf(out, "\t%03X   :   %04X;\n", count, JE << 11 | imm(buf));
                break;
            case JMP:
                fprintf(out, "\t%03X   :   %04X;\n", count, JMP << 11 | imm(buf));
                break;
            case LD:
                fprintf(out, "\t%03X   :   %04X;\n", count, LD << 11 | regimm(buf));
                break;
            case ST:
                fprintf(out, "\t%03X   :   %04X;\n", count, ST << 11 | regimm(buf));
                break;
            case MOV:
                fprintf(out, "\t%03X   :   %04X;\n", count, MOV << 11 | regreg(buf));
                break;
            default:
                printf("invalid instruction: %s\n", buf);
                return -1;
        }
        count++;
    }

    fprintf(out, "\t[%03X..0FF]   :   0000;\n", count);
    fprintf(out, "END;\n");

    fclose(in);
    fclose(out);

    return 0;
}