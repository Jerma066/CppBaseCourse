/* These three directives tell flex not to generate the functions input, yyunput and
 * yywrap, which are not used in this case. They are necessary for
 * suppress compiler warnings */

%option nounput
%option noinput
%option noyywrap

%{

#include <iostream>
#include <string>

#include "paracl-grammar.h"
struct Position_t {
  int line;
  int column;
};

static Position_t CurPos = {1, 1};

static bool GotError = false;

/* Automatic action when during lexeme reading */
#define YY_USER_ACTION {                              \
    yylloc.first_line   = CurPos.line;                \
    yylloc.last_line    = CurPos.line;                \
    yylloc.first_column = CurPos.column;              \
    yylloc.last_column  = CurPos.column + yyleng - 1; \
    CurPos.column += yyleng; }

static void printLexeme(const std::string& tokName) {
  std::cout << tokName << ", \"" << yytext << "\", {" << CurPos.line << ", "
            << CurPos.column - yyleng << "}\n";
}

%}

/* Here we describe the states that the lexical analyzer gets into */

/* Multiline comment state */
%x COMMENT

INTEGER [0-9]+
SPACE [ \t]*
IDENTIFIER [a-zA-Z_][a-zA-Z_0-9]*
NOT_AVIABLE [^a-zA-Z_0-9+\-*/><!;,=(){}\[\]&|'" \n\t]

%%

 /* Processing comments */

"/*"                    { BEGIN(COMMENT); } /* Enable comment analysis state */
<COMMENT>.              {} 		    /* Nothing to do inside the comment */
<COMMENT>"*/"           { BEGIN(INITIAL); } /* Return to the initial state */

 /* Keywords */
if                      { printLexeme("IF"); }
else                    { printLexeme("ELSE"); }
for                     { printLexeme("FOR"); }
while                   { printLexeme("WHILE"); }
break                   { printLexeme("BREAK"); }
continue                { printLexeme("CONTINUE"); }
true                    { return TOK_TRUE; }
false                   { return TOK_FALSE; }
print			              { printLexeme("PRINT"); }
"?"			                { printLexeme("STDIN"); }

 /* Single Characters */
[+\-*/><!;,=(){}\[\]]   { return yytext[0]; }

 /* Multi-character operations */
"&&"                    { printLexeme("LOGIC_AND"); }
"||"                    { printLexeme("LOGIC_OR"); }
"=="                    { printLexeme("IS_EQ"); }
"!="                    { printLexeme("IS_NEQ"); }
">="                    { printLexeme("IS_GEQ"); }
"<="                    { printLexeme("IS_LEQ"); }

 /* Program flow processing */
\'\\?.\'                { return TOK_CHAR; }
{INTEGER}               { return TOK_INT; }
{IDENTIFIER}            { return TOK_IDENT; }
{SPACE}                 {} /* Ignoring spaces */

 /* New line transition (at any state) */
<*>\n                   { CurPos.column = 1; CurPos.line += 1;}

 /* Illegal characters */
{NOT_AVIABLE}+          { printLexeme("ERROR"); GotError = true;}

 /* Here we catch what the previous rules could not catch */
.                       { printLexeme("UNKNOWN"); }

<<EOF>>                 { return GotError;}

%%

