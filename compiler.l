%{

#include "compiler.tab.h"

void yyerror(char *s, ...);

%}


digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  [a-zA-Z_][a-zA-Z_0-9]*
newline     \n
whitespace  [ \t]+

%option noyywrap
%%


"void"                    {return VOID;}
"char"                    {return CHAR;}
"short"                   {return SHORT;}
"int"                     {return INT;}
"float"                   {return FLOAT;}
"double"                  {return DOUBLE;}
"long long int"           {return LONG_INT;}
"unsigned int"            {return UINT;}
"enum"                    {return ENUM;}
"union"                   {return UNION;}
"struct"                  {return STRUCT;}
"class"                   {return CLASS;}
{identifier}"["{number}"]" {return ARRAY;}



"else"          {return ELSE;}
"if"            {return IF;}
"while"         {return WHILE;}
"for"           {return FOR;}
"break"         {return BREAK;}
"continue"      {return CONTINUE;}
"case"          {return CASE;}
"switch"        {return SWITCH;}
"return"        {return RETURN;}

"output"        {return OUTPUT;}
"input"         {return INPUT;}



"+"             {return PLUS;}
"-"             {return MINUS;}
"*"             {return TIMES;}
"/"             {return OVER;}
"^"             {return POW;}
"<"             {return LT;}
"<="            {return LTEQ;}
">"             {return GT;}
">="            {return GTEQ;}
"=="            {return EQ;}
"!="            {return NEQ;}
"="             {return ASSIGN;}
";"             {return SEMI;}
","             {return COMMA;}
"("             {return LPAREN;}
")"             {return RPAREN;}
"["             {return LBRACK;}
"]"             {return RBRACK;}
"{"             {return LBRACE;}
"}"             {return RBRACE;}
{number}        {return NUM;}
{identifier}    {return ID;}
{newline}       {lineno++;}
{whitespace}    {/* skip whitespace */}
("pi")|("PI")													{return PI;}
("mod")|("MOD")												{return MOD;}


"/*"             { char c;
                  char p='\0';
                  do
                  { c = input();
                    if (c == EOF) break;
                    if (c == '\n') lineno++;
                    if (p == '*' && c == '/') break;
                    p = c;
                  } while (1);
                }
.               {return ERROR;}


%%

int yywrap()
{
    return (1) ;
}
