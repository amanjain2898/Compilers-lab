%{
# include "parser.tab.h"
#include "storetokens.hh"
int lineno=1;
%}

digit [0-9]
operator [-+*/]
uminus [-]
letter [a-zA-Z_]
ws [ \t]+
double_num ({digit}*\.{digit}+|{digit}+\.{digit}*)
misc [\(\){},;\?:]
comment "//"[^\n]*

%%
{comment} {};
">=" {store_token_name("GREATER_THAN_EQUAL",yytext,yylineno); return GTE; }
"<=" {store_token_name("LESS_THAN_EQUAL",yytext,yylineno); return LTE; }
">" {store_token_name("GREATER_THAN",yytext,yylineno); return GT; }
"<" {store_token_name("LESS_THAN",yytext,yylineno); return LT; }
"!=" {store_token_name("NOT_EQUAL",yytext,yylineno); return NEQ; }
"==" {store_token_name("EQUAL",yytext,yylineno); return EQ; }
do {store_token_name("DO",yytext,yylineno); return DO; }
while {store_token_name("WHILE",yytext,yylineno); return WHILE; }
if {store_token_name("IF",yytext,yylineno); return IF; }
else {store_token_name("ELSE",yytext,yylineno); return ELSE; }
"&&" {store_token_name("AND",yytext,yylineno); return AND; }
"||" {store_token_name("OR",yytext,yylineno); return OR; }
"!" {store_token_name("NOT",yytext,yylineno); return NOT; }

{misc} {store_token_name("META CHAR",yytext,yylineno); return yytext[0]; }
return {store_token_name("RETURN",yytext,yylineno);  return RETURN; } 
void {store_token_name("VOID",yytext,yylineno);  return VOID; }
float {store_token_name("FLOAT",yytext,yylineno);  return FLOAT; }
int {store_token_name("INTEGER",yytext,yylineno);  return INTEGER; }
{letter}({letter}|{digit})* {store_token_name("NAME",yytext,yylineno); yylval.string_value = new std::string(yytext); return NAME; }
{digit}+  {store_token_name("NUM",yytext,yylineno); yylval.integer_value = atoi(yytext); return INTEGER_NUMBER; }
{double_num} {store_token_name("FNUM",yytext,yylineno); yylval.double_value = atof(yytext); return DOUBLE_NUMBER; } 
= {store_token_name("ASSIGN_OP",yytext,yylineno);  return ASSIGN; }
{operator} {store_token_name("ARITHOP",yytext,yylineno); return yytext[0]; }
\n {lineno++;};
{ws} ;
. {printf("cs316: Error flex scanner internal Error at line number %d\n",yylineno);};
