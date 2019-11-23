%{

#include "compiler.tab.h"

void yyerror(char *s, ...);

%}

%%

"+"    { return ADD; }
"-"    { return NEG; }
"*"    { return MUL; }
"("    { return PAR_LEFT; }
")"    { return PAR_RIGHT; }
"^"    { return POW; }
[0-9]+ {
        yylval = atoi(yytext);
        return NUMBER;
}
\n     { yylineno++; return EOL; }
[ \t]  { /* ignore whitespace */ }
.      { yyerror("Mystery character %c\n", *yytext); }

%%

int yywrap()
{
    return (1) ;
}
