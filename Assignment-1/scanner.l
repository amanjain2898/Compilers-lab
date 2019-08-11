%{
# include "parser.tab.h"
#include "storetokens.hh"
%}

digit [0-9]
operator [-+*/]
uminus [-]
name [a-zA-Z_][a-zA-Z_0-9]*
ws [ \t]+
double_num {digit}+\.{digit}+
misc [\(\){},;]
comment \/\/.*$


%%
{misc} {store_token_name("META CHAR",yytext,yylineno); return yytext[0]; }
return {store_token_name("RETURN",yytext,yylineno);  return RETURN; } 
void {store_token_name("VOID",yytext,yylineno);  return VOID; }
float {store_token_name("FLOAT",yytext,yylineno);  return FLOAT; }
int {store_token_name("INTEGER",yytext,yylineno);  return INTEGER; }
{digit}+  {store_token_name("NUM",yytext,yylineno); yylval.integer_value = atoi(yytext); return INTEGER_NUMBER; }
{double_num} {store_token_name("FNUM",yytext,yylineno); yylval.double_value = atof(yytext); return DOUBLE_NUMBER; } 
{name} {store_token_name("NAME",yytext,yylineno); yylval.string_value = new std::string(yytext); return NAME; }
= {store_token_name("ASSIGN_OP",yytext,yylineno);  return ASSIGN; }
{operator} {store_token_name("ARITHOP",yytext,yylineno); return yytext[0]; }
\n {yylineno++;};
{comment} ;
{ws} ;
. {printf("flex scanner internal error at line number %d\n",yylineno);};
