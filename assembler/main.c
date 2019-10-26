#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

typedef enum {
    MOV,
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
    HLT
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
    if(!strncmp(mnemonic, "MOV", 3))
        return MOV;
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
    if(!strncmp(mnemonic, "HLT", 3))
        return HLT;
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
            return -1;
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
        if(i > 10) return -1;
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
            return -1;
    }
    
    p = code + 8;
    while(*p != '\n') {
        if(i > 10) return -1;
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
            return -1;
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
            return -1;
    }

    return r1 << 8 | r2 << 5;
}

int
main(void)
{
    char buf[256], inst[4];
    int count = 0;
    FILE *fp;

    printf("FIle name: ");
    scanf("%s", buf);

    if((fp = fopen(buf, "r")) == NULL) {
        puts("file open error!");
        return -1;
    }

    while(fgets(buf, 256, fp) != NULL) {
        strncpy(inst, buf, 3);
        printf("%d %d: %s", op_code(inst), count, buf);
        count++;

        switch(op_code(inst)) {
            case MOV:
                printf("%4x\n", MOV << 11 | regreg(buf));
                break;
            case ADD:
                printf("%04x\n", ADD << 11 | regreg(buf));
                break;
            case SUB:
                printf("%04x\n", SUB << 11 | regreg(buf));
                break;
            case AND:
                printf("%04x\n", AND << 11 | regreg(buf));
                break;
            case OR:
                printf("%04x\n", OR << 11 | regreg(buf));
                break;
            case SL:
                printf("%04x\n", SL << 11 | reg(buf));
                break;
            case SR:
                printf("%04x\n", SR << 11 | reg(buf));
                break;
            case SRA:
                printf("%04x\n", SRA << 11 | reg(buf));
                break;
            case LDL:
                printf("%04x\n", LDL << 11 | regimm(buf));
                break;
            case LDH:
                printf("%04x\n", LDH << 11 | regimm(buf));
                break;
            case CMP:
                printf("%04x\n", CMP << 11 | regreg(buf));
                break;
            case JE:
                printf("%04x\n", JE << 11 | imm(buf));
                break;
            case JMP:
                printf("%04x\n", JMP << 11 | imm(buf));
                break;
            case LD:
                printf("%04x\n", LD << 11 | regimm(buf));
                break;
            case ST:
                printf("%04x\n", ST << 11 | regimm(buf));
                break;
            case HLT:
                printf("%04x\n", HLT << 11);
                break;
        }
    }

    return 0;
}