#include "globals.h"

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

void assign(char* name,TreeNode* node)
{
    if(node->kind.exp==IdK)
    {
        strcpy(name,node->attr.name);
    }
    else
    {
        sprintf(name,"%d",node->attr.val);
    }
}

int memory(Midcode* code,int quad)
{
    Midcode* p=(Midcode*)malloc(sizeof(Midcode));
    p->next=NULL;
    code->next=p;
    code=p;
    code->type=0;
    code->quad=quad;
    quad++;
    return quad;
}

int Build(TreeNode* node,Midcode* code,int quad)
{
    int n;
    switch(node->nodekind)
    {
        case ExpK:
            switch(node->kind.exp)
            {
                case AssignK:
                    quad=memory(code,quad);
                    strcpy(code->op,":=");
                    strcpy(code->var3.res,node->attr.name);
                    strcpy(code->var2,"-"); 
                    code->type=0;
                    assign(code->var1,node->child[0]);
                    break;
                case OpK:
                    quad=memory(code,quad);
                    switch(node->attr.op)
                    {
                        assign(code->var1,node->child[0]);
                        assign(code->var2,node->child[1]);
                        case PLUS:
                            strcpy(code->var3.res,"T");
                            strcpy(code->op,"+");
                            quad=memory(code,quad);
                            strcpy(code->op,":=");
                            strcpy(code->var1,"T");
                            strcpy(code->var2,"-");
                            strcpy(code->var3.res,node->attr.name);
                            break;
                        case MINUS:
                            strcpy(code->var3.res,"T");
                            strcpy(code->op,"-");
                            quad=memory(code,quad);
                            strcpy(code->op,":=");
                            strcpy(code->var1,"T");
                            strcpy(code->var2,"-");
                            strcpy(code->var3.res,node->attr.name);
                            break;
                        case TIMES:
                            strcpy(code->var3.res,"T");
                            strcpy(code->op,"*");
                            quad=memory(code,quad);
                            strcpy(code->op,":=");
                            strcpy(code->var1,"T");
                            strcpy(code->var2,"-");
                            strcpy(code->var3.res,node->attr.name);
                            break;
                        case OVER:
                            strcpy(code->var3.res,"T");
                            strcpy(code->op,"/");
                            quad=memory(code,quad);
                            strcpy(code->op,":=");
                            strcpy(code->var1,"T");
                            strcpy(code->var2,"-");
                            strcpy(code->var3.res,node->attr.name);
                            break;
                        default:
                            break;
                    }
                    break;  
                default:
                    break;   
            }
            break;
        case StmtK:
            switch(node->kind.stmt)
            {
                case IfK:
                    switch(node->child[0]->kind.exp)
                    {
                        case OpK:
                            switch(node->child[0]->attr.op)
                            {
                                case LT:
                                    code->type=1;
                                    strcpy(code->op,"j<");
                                    code->var3.jump=quad+1;
                                    quad=memory(code,quad);
                                    code->type=1;
                                    strcpy(code->op,"j");
                                    strcpy(code->var1,"-");
                                    strcpy(code->var2,"-");
                                    for(int i=0;i<MAXCHILDREN;i++)
                                    {
                                        quad=Build(node->child[i],code,quad);
                                    }
                                    code->var3.jump=quad;
                                    break;
                                case LTEQ:
                                    code->type=1;
                                    strcpy(code->op,"j<=");
                                    code->var3.jump=quad+1;
                                    quad=memory(code,quad);
                                    code->type=1;
                                    strcpy(code->op,"j");
                                    strcpy(code->var1,"-");
                                    strcpy(code->var2,"-");
                                    for(int i=0;i<MAXCHILDREN;i++)
                                    {
                                        quad=Build(node->child[i],code,quad);
                                    }
                                    code->var3.jump=quad;
                                    break;
                                case GT:
                                    code->type=1;
                                    strcpy(code->op,"j>");
                                    code->var3.jump=quad+1;
                                    quad=memory(code,quad);
                                    code->type=1;
                                    strcpy(code->op,"j");
                                    strcpy(code->var1,"-");
                                    strcpy(code->var2,"-");
                                    for(int i=0;i<MAXCHILDREN;i++)
                                    {
                                        quad=Build(node->child[i],code,quad);
                                    }
                                    code->var3.jump=quad;
                                    break;
                                case GTEQ:
                                    code->type=1;
                                    strcpy(code->op,"j>=");
                                    code->var3.jump=quad+1;
                                    quad=memory(code,quad);
                                    code->type=1;
                                    strcpy(code->op,"j");
                                    strcpy(code->var1,"-");
                                    strcpy(code->var2,"-");
                                    for(int i=0;i<MAXCHILDREN;i++)
                                    {
                                        quad=Build(node->child[i],code,quad);
                                    }
                                    code->var3.jump=quad;
                                    break;
                                case EQ:
                                    code->type=1;
                                    strcpy(code->op,"je");
                                    code->var3.jump=quad+1;
                                    quad=memory(code,quad);
                                    code->type=1;
                                    strcpy(code->op,"j");
                                    strcpy(code->var1,"-");
                                    strcpy(code->var2,"-");
                                    for(int i=0;i<MAXCHILDREN;i++)
                                    {
                                        quad=Build(node->child[i],code,quad);
                                    }
                                    code->var3.jump=quad;
                                    break;
                                case NEQ:
                                    code->type=1;
                                    strcpy(code->op,"jne");
                                    code->var3.jump=quad+1;
                                    quad=memory(code,quad);
                                    code->type=1;
                                    strcpy(code->op,"j");
                                    strcpy(code->var1,"-");
                                    strcpy(code->var2,"-");
                                    for(int i=0;i<MAXCHILDREN;i++)
                                    {
                                        quad=Build(node->child[i],code,quad);
                                    }
                                    code->var3.jump=quad;
                                    break;
                                default:
                                    break;
                            }
                            break;
                        case IdK:
                            quad=memory(code,quad);
                            strcpy(code->type,"jnz");
                            assign(code->var1,node);
                            code->type=1;
                            strcpy(code->var2,"0");
                            code->var3.jump=quad+1;
                            quad=memory(code,quad);
                            code->type=1;
                            strcpy(code->op,"j");
                            strcpy(code->var1,"-");
                            strcpy(code->var2,"-");
                            for(int i=0;i<MAXCHILDREN;i++)
                            {
                                quad=Build(node->child[i],code,quad);
                            }
                            code->var3.jump=quad;   
                            break;
                        default:
                            break;
                    }
                    break;
                case IterK:
                    n=quad;
                    switch(node->child[0]->kind.exp)
                    {
                        case OpK:
                            switch(node->child[0]->attr.op)
                            {
                                case LT:
                                    code->type=1;
                                    strcpy(code->op,"j<");
                                    code->var3.jump=quad+1;
                                    quad=memory(code,quad);
                                    code->type=1;
                                    strcpy(code->op,"j");
                                    strcpy(code->var1,"-");
                                    strcpy(code->var2,"-");
                                    for(int i=0;i<MAXCHILDREN;i++)
                                    {
                                        quad=Build(node->child[i],code,quad);
                                    }
                                    code->var3.jump=quad;
                                    break;
                                case LTEQ:
                                    code->type=1;
                                    strcpy(code->op,"j<=");
                                    code->var3.jump=quad+1;
                                    quad=memory(code,quad);
                                    code->type=1;
                                    strcpy(code->op,"j");
                                    strcpy(code->var1,"-");
                                    strcpy(code->var2,"-");
                                    for(int i=0;i<MAXCHILDREN;i++)
                                    {
                                        quad=Build(node->child[i],code,quad);
                                    }
                                    code->var3.jump=quad;
                                    break;
                                case GT:
                                    code->type=1;
                                    strcpy(code->op,"j>");
                                    code->var3.jump=quad+1;
                                    quad=memory(code,quad);
                                    code->type=1;
                                    strcpy(code->op,"j");
                                    strcpy(code->var1,"-");
                                    strcpy(code->var2,"-");
                                    for(int i=0;i<MAXCHILDREN;i++)
                                    {
                                        quad=Build(node->child[i],code,quad);
                                    }
                                    code->var3.jump=quad;
                                    break;
                                case GTEQ:
                                    code->type=1;
                                    strcpy(code->op,"j>=");
                                    code->var3.jump=quad+1;
                                    quad=memory(code,quad);
                                    code->type=1;
                                    strcpy(code->op,"j");
                                    strcpy(code->var1,"-");
                                    strcpy(code->var2,"-");
                                    for(int i=0;i<MAXCHILDREN;i++)
                                    {
                                        quad=Build(node->child[i],code,quad);
                                    }
                                    code->var3.jump=quad;
                                    break;
                                case EQ:
                                    code->type=1;
                                    strcpy(code->op,"je");
                                    code->var3.jump=quad+1;
                                    quad=memory(code,quad);
                                    code->type=1;
                                    strcpy(code->op,"j");
                                    strcpy(code->var1,"-");
                                    strcpy(code->var2,"-");
                                    for(int i=0;i<MAXCHILDREN;i++)
                                    {
                                        quad=Build(node->child[i],code,quad);
                                    }
                                    code->var3.jump=quad;
                                    break;
                                case NEQ:
                                    code->type=1;
                                    strcpy(code->op,"jne");
                                    code->var3.jump=quad+1;
                                    quad=memory(code,quad);
                                    code->type=1;
                                    strcpy(code->op,"j");
                                    strcpy(code->var1,"-");
                                    strcpy(code->var2,"-");
                                    for(int i=0;i<MAXCHILDREN;i++)
                                    {
                                        quad=Build(node->child[i],code,quad);
                                    }
                                    code->var3.jump=quad;
                                    break;
                            }
                            break;
                        case IdK:
                            quad=memory(code,quad);
                            strcpy(code->op,"jnz");
                            assign(code->var1,node);
                            code->type=1;
                            strcpy(code->var2,"0");
                            code->var3.jump=quad+1;
                            quad=memory(code,quad);
                            code->type=1;
                            strcpy(code->op,"j");
                            strcpy(code->var1,"-");
                            strcpy(code->var2,"-");
                            for(int i=0;i<MAXCHILDREN;i++)
                            {
                                quad=Build(node->child[i],code,quad);
                            }
                            code->var3.jump=quad;   
                            break;
                    }
                    quad=memory(code,quad);
                    code->type=1;
                    strcpy(code->op,"j");
                    strcpy(code->var1,"-");
                    strcpy(code->var2,"-");
                    code->var3.jump=n;
                    break;
                case RetK:
                    quad=memory(code,quad);
                    strcpy(code->op,"ret");
                    strcpy(code->var1,"-");
                    strcpy(code->var2,"-");
                    strcpy(code->var3.res,"-");
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    Build(node->sibling,code,quad);
    return quad;
}



void Create(TreeNode* node)
{
    Midcode* head;
    head=(Midcode*)malloc(sizeof(Midcode));
    head->next=NULL;
    Build(node,head,100);
    Midcode *p;
    p=head->next;
    while(p)
    {
        if(p->type==1)
        {
            fprintf(code,"<%s,%s,%s,%d>",p->op,p->var1,p->var2,p->var3.jump);
        }
        else
        {
            fprintf(code,"<%s,%s,%s,%s>",p->op,p->var1,p->var2,p->var3.res);
        }
        p=p->next;
    }
}