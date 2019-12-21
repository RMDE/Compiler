%{
#include "globals.h"
#include "util.h"
#include "scan.h"
/* lexeme of identifier or reserved word */
char tokenString[MAXTOKENLEN+1];
%}


digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  [a-zA-Z_][a-zA-Z_0-9]*
newline     \n
whitespace  [ \t]+

/*deleted:                                 */
/*"bool"                    {return BOOL;}*/
/*"char"                    {return CHAR;}*/
/*"short"                   {return SHORT;}*/
/*"float"                   {return FLOAT;}*/
/*"double"                  {return DOUBLE;}*/
/*"long long int"           {return LONG_INT;}*/
/*"unsigned int"            {return UINT;}*/
/*"enum"                    {return ENUM;}*/
/*"union"                   {return UNION;}*/
/*"struct"                  {return STRUCT;}*/
/* "class"                  {return CLASS;} */
/*"for"                     {return FOR;}*/
/*"break"                   {return BREAK;}*/
/*"continue"                {return CONTINUE;}*/
/*"case"                    {return CASE;}*/
/*"switch"                  {return SWITCH;}*/
/*"^"                       {return POW;}*/
/*("pi")|("PI")							{return PI;}*/
/*("mod")|("MOD")						{return MOD;}*/
%option noyywrap
%%


"void"                    {return VOID;} //variable's type
"int"                     {return INT;}
{identifier}"["{number}"]" {return ARRAY;}



"else"          {return ELSE;} //assign
"if"            {return IF;}
"while"         {return WHILE;}
"return"        {return RETURN;}

"output"        {return OUTPUT;}
"input"         {return INPUT;}



"+"             {return PLUS;}
"-"             {return MINUS;}
"*"             {return TIMES;}
"/"             {return OVER;}
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

TokenType getToken(void)
{ static int firstTime = TRUE;
  TokenType currentToken;
  if (firstTime)
  { firstTime = FALSE;
    lineno++;
    yyin = source;
    yyout = listing;
  }
  currentToken = yylex();
  strncpy(tokenString,yytext,MAXTOKENLEN);
  if (TraceScan) {
    fprintf(listing,"\t%d: ",lineno);
    printToken(currentToken,tokenString);
  }
  return currentToken;
}
