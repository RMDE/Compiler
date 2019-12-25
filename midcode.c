#include "globals.h"
#include "midcode.h"
#include "symtab.h"

void show(Midcode* p)
{
    if(p->type==1)
    {
        printf("\n%d:<%s,%s,%s,%d>\n",p->quad,p->op,p->var1,p->var2,p->var3.jump);////////////////
    }
    else
    {
        printf("\n%d:<%s,%s,%s,%s>\n",p->quad,p->op,p->var1,p->var2,p->var3.res);////////////////
    }
}


void assign(char* name,TreeNode* node)
{
    printf("in assign    **");
    if(node->kind.exp==IdK)
    {
        printf("ID  %s\n",node->attr.name);///////
        strcpy(name,node->attr.name);
    }
    else if(node->kind.exp==ConstK)
    {
        printf("num %d\n",node->attr.val);///////
        sprintf(name,"%d",node->attr.val);
    }
}

int memory(Midcode* code,int quad)
{
    printf("memory %d\n",quad);////////////////////
    Midcode* p=(Midcode*)malloc(sizeof(Midcode));
    p->next=NULL;
    code->next=p;
    code=p;
    code->type=0;
    printf("quad:%d\n",quad);/////////
    code->quad=quad;
    quad++;
    return quad;
}

int Build(TreeNode* node,Midcode* code,int quad)
{
    //printf("build %d\n",quad);////////////////////
    //printf("build %d\n",quad);
    int n;
    if(!node)
    {
        return quad;
    }
    printf("%d\n",node->nodekind);
    switch(node->nodekind)
    {
        case ExpK:
            switch(node->kind.exp)
            {
                case AssignK:
                    quad=memory(code,quad);
                    strcpy(code->op,":=");
                    strcpy(code->var3.res,node->child[0]->attr.name);
                    strcpy(code->var2,"-");
                    code->type=0;
                    if(node->child[1]->kind.exp==IdK||node->child[1]->kind.exp==ConstK)
                    {
                        assign(code->var1,node->child[1]);
                        show(code);////////
                    }
                    else
                    {
                        quad=Build(node->child[1],code,quad);
                        strcpy(code->var1,"T");
                    }
                    show(code);//////////
                    break;
                case OpK:
                    quad=memory(code,quad);
                    printf("opk\n");
                    switch(node->attr.op)
                    {
                        case PLUS:
                            strcpy(code->var3.res,"T");
                            strcpy(code->op,"+");
                            assign(code->var1,node->child[0]);
                            show(code);//////////
                            if(node->child[1]->kind.exp==IdK||node->child[1]->kind.exp==ConstK)
                            {
                                assign(code->var1,node->child[1]);
                            }
                            else
                            {
                                quad=Build(node->child[1],code,quad);
                                strcpy(code->var2,"T");
                            }
                            show(code);//////////
                            break;
                        case MINUS:
                            strcpy(code->var3.res,"T");
                            strcpy(code->op,"-");
                            assign(code->var1,node->child[0]);
                            show(code);//////////
                            if(node->child[1]->kind.exp==IdK||node->child[1]->kind.exp==ConstK)
                            {
                                assign(code->var1,node->child[1]);
                            }
                            else
                            {
                                quad=Build(node->child[1],code,quad);
                                strcpy(code->var2,"T");
                            }
                            show(code);//////////
                            break;
                        case TIMES:
                            strcpy(code->var3.res,"T");
                            strcpy(code->op,"*");
                            assign(code->var1,node->child[0]);
                            show(code);//////////
                            if(node->child[1]->kind.exp==IdK||node->child[1]->kind.exp==ConstK)
                            {
                                assign(code->var1,node->child[1]);
                            }
                            else
                            {
                                quad=Build(node->child[1],code,quad);
                                strcpy(code->var2,"T");
                            }
                            show(code);//////////
                            break;
                        case OVER:
                            strcpy(code->var3.res,"T");
                            strcpy(code->op,"/");
                            assign(code->var1,node->child[0]);
                            show(code);//////////
                            if(node->child[1]->kind.exp==IdK||node->child[1]->kind.exp==ConstK)
                            {
                                assign(code->var1,node->child[1]);
                            }
                            else
                            {
                                quad=Build(node->child[1],code,quad);
                                strcpy(code->var2,"T");
                            }
                            show(code);//////////
                            break;
                        default:
                            for(int i=0;i<MAXCHILDREN;i++)
                            {
                                quad=Build(node->child[i],code,quad);
                            }
                            break;
                    }
                    break;  
                default:
                    for(int i=0;i<MAXCHILDREN;i++)
                    {
                        quad=Build(node->child[i],code,quad);
                    }
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
                                    assign(code->var1,node->child[0]);
                                    assign(code->var2,node->child[1]);
                                    show(code);//////////
                                    quad=memory(code,quad);
                                    code->type=1;
                                    strcpy(code->op,"j");
                                    strcpy(code->var1,"-");
                                    strcpy(code->var2,"-");
                                    show(code);//////////
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
                                    assign(code->var1,node->child[0]);
                                    assign(code->var2,node->child[1]);
                                    show(code);//////////
                                    quad=memory(code,quad);
                                    code->type=1;
                                    strcpy(code->op,"j");
                                    strcpy(code->var1,"-");
                                    strcpy(code->var2,"-");
                                    show(code);//////////
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
                                    assign(code->var1,node->child[0]);
                                    assign(code->var2,node->child[1]);
                                    show(code);//////////
                                    quad=memory(code,quad);
                                    code->type=1;
                                    strcpy(code->op,"j");
                                    strcpy(code->var1,"-");
                                    strcpy(code->var2,"-");
                                    show(code);//////////
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
                                    assign(code->var1,node->child[0]);
                                    assign(code->var2,node->child[1]);
                                    show(code);//////////
                                    quad=memory(code,quad);
                                    code->type=1;
                                    strcpy(code->op,"j");
                                    strcpy(code->var1,"-");
                                    strcpy(code->var2,"-");
                                    show(code);//////////
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
                                    assign(code->var1,node->child[0]);
                                    assign(code->var2,node->child[1]);
                                    show(code);//////////
                                    quad=memory(code,quad);
                                    code->type=1;
                                    strcpy(code->op,"j");
                                    strcpy(code->var1,"-");
                                    strcpy(code->var2,"-");
                                    show(code);//////////
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
                                    assign(code->var1,node->child[0]);
                                    assign(code->var2,node->child[1]);
                                    show(code);//////////
                                    quad=memory(code,quad);
                                    code->type=1;
                                    strcpy(code->op,"j");
                                    strcpy(code->var1,"-");
                                    strcpy(code->var2,"-");
                                    show(code);//////////
                                    for(int i=0;i<MAXCHILDREN;i++)
                                    {
                                        quad=Build(node->child[i],code,quad);
                                    }
                                    code->var3.jump=quad;
                                    break;
                                default:
                                    for(int i=0;i<MAXCHILDREN;i++)
                                    {
                                        quad=Build(node->child[i],code,quad);
                                    }
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
                            show(code);//////////
                            quad=memory(code,quad);
                            code->type=1;
                            strcpy(code->op,"j");
                            strcpy(code->var1,"-");
                            strcpy(code->var2,"-");
                            show(code);//////////
                            for(int i=0;i<MAXCHILDREN;i++)
                            {
                                quad=Build(node->child[i],code,quad);
                            }
                            code->var3.jump=quad;   
                            break;
                        default:
                            for(int i=0;i<MAXCHILDREN;i++)
                            {
                                quad=Build(node->child[i],code,quad);
                            }
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
                                    show(code);//////////
                                    quad=memory(code,quad);
                                    code->type=1;
                                    strcpy(code->op,"j");
                                    strcpy(code->var1,"-");
                                    strcpy(code->var2,"-");
                                    show(code);//////////
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
                                    show(code);//////////
                                    quad=memory(code,quad);
                                    code->type=1;
                                    strcpy(code->op,"j");
                                    strcpy(code->var1,"-");
                                    strcpy(code->var2,"-");
                                    show(code);//////////
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
                                    show(code);//////////
                                    quad=memory(code,quad);
                                    code->type=1;
                                    strcpy(code->op,"j");
                                    strcpy(code->var1,"-");
                                    strcpy(code->var2,"-");
                                    show(code);//////////
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
                                    show(code);//////////
                                    quad=memory(code,quad);
                                    code->type=1;
                                    strcpy(code->op,"j");
                                    strcpy(code->var1,"-");
                                    strcpy(code->var2,"-");
                                    show(code);//////////
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
                                    show(code);//////////
                                    quad=memory(code,quad);
                                    code->type=1;
                                    strcpy(code->op,"j");
                                    strcpy(code->var1,"-");
                                    strcpy(code->var2,"-");
                                    show(code);//////////
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
                                    show(code);//////////
                                    quad=memory(code,quad);
                                    code->type=1;
                                    strcpy(code->op,"j");
                                    strcpy(code->var1,"-");
                                    strcpy(code->var2,"-");
                                    show(code);//////////
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
                            show(code);//////////
                            quad=memory(code,quad);
                            code->type=1;
                            strcpy(code->op,"j");
                            strcpy(code->var1,"-");
                            strcpy(code->var2,"-");
                            show(code);//////////
                            for(int i=0;i<MAXCHILDREN;i++)
                            {
                                quad=Build(node->child[i],code,quad);
                            }
                            code->var3.jump=quad;   
                            break;
                        default:
                            for(int i=0;i<MAXCHILDREN;i++)
                            {
                                quad=Build(node->child[i],code,quad);
                            }
                            break;
                    }
                    quad=memory(code,quad);
                    code->type=1;
                    strcpy(code->op,"j");
                    strcpy(code->var1,"-");
                    strcpy(code->var2,"-");
                    code->var3.jump=n;
                    show(code);//////////
                    break;
                case RetK:
                    quad=memory(code,quad);
                    strcpy(code->op,"ret");
                    strcpy(code->var1,"-");
                    strcpy(code->var2,"-");
                    strcpy(code->var3.res,"-");
                    show(code);//////////
                    break;
                default:
                    for(int i=0;i<MAXCHILDREN;i++)
                    {
                        quad=Build(node->child[i],code,quad);
                    }
                    break;
            }
            break;
        default:
            for(int i=0;i<MAXCHILDREN;i++)
            {
                quad=Build(node->child[i],code,quad);
            }
            break;
    }
    quad=Build(node->sibling,code,quad);
    return quad;
}



void Create(TreeNode* node,FILE* code)
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
            printf("<%s,%s,%s,%d>",p->op,p->var1,p->var2,p->var3.jump);////////////////
        }
        else
        {
            fprintf(code,"<%s,%s,%s,%s>",p->op,p->var1,p->var2,p->var3.res);
            printf("<%s,%s,%s,%s>",p->op,p->var1,p->var2,p->var3.res);////////////////
        }
        p=p->next;
    }
}