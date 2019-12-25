#ifndef _MIDCODE_H_
#define _MIDCODE_H_

typedef struct Midcode{
    int quad;
    int type;//1 -> jump
    char op[10];
    char var1[20];
    char var2[20];
    union{char res[20];
        int jump;}var3;
    struct Midcode* next;
}Midcode;

void Create(TreeNode* node,FILE* code);

#endif