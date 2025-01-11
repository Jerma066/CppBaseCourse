%locations /* required for yylloc usage */

%{
  /*
   * This is the first section of the bison file. You can put C/C++ code
   * necessary for the analyzer to operate here.
   * Functions signatures and include directives are usually located here
   */

  /* Library headers */
  #include "paracl-lexer.h"

  #include <iostream>
  #include <string>

  /* Declarations of functions required by bison */
  void yyerror (const std::string &msg);

  /* Custom functions declarations */
  static void printTerminal(const std::string &tokName);
  static void printNonTerminal(const std::string &tokName);
%}

%token TOK_IDENT
%token TOK_CHAR TOK_INT TOK_TRUE TOK_FALSE

/*
 * In addition to the %token directive, the following directives can be used:
 * %left, %right, %nonassoc, %precedence;
 * The first two set left and right associativity. For example:
 *   specifying %left TOK, the expression x TOK y TOK z will be treated as
 *   (x TOK y) TOK z
 *
 * %noassoc disassociates the token:
 *   the expression x TOK y TOK z will cause an error
 *
 * %precedence is used to set priority to terminal characters
 */
%left '-' '+'
%left '*' '/'
%left TOK_LOGIC_AND TOK_LOGIC_OR TOK_IS_GEQ TOK_IS_LEQ '<' '>'
%left TOK_IS_EQ TOK_IS_NOT_EQ
%precedence TOK_UMIN    /* Unary minus for negative numbers */
%precedence TOK_NOT     /* Negation for boolean values */

/*
 * The %start directive specifies the grammar starting symbol
 */
%start program

%%

/*
 * Grammar rules Section.
 * It contains a description of the grammar in BNF (Backus–Naur form).
 *
 * The rules are described with the following syntax:
 *
 *   result: rule_1 {actions}
 *           | rule_2 {actions}
 *           ...
 *           ;
 */

/* Axiom of grammar */
program:
  func_body {printNonTerminal("input");}
;

/* Function body */
func_body:
  func_body statement   { printNonTerminal("func_body statement"); }
| %empty                {}
;

/* Expressions allowed in the function body */
statement:
  single_statement ';'  { printNonTerminal("single_statement ';'"); }
;

/* Expression ending with ; */
single_statement:
  assign_expr       { printNonTerminal("assign_expr"); }
;

/* Assignment expression */
assign_expr:
  ident_token '=' expr  { printNonTerminal("ident_token '=' expr"); }
;

/* Valid expressions. Only rvalues are allowed here (i.e. direct calculations) */
expr:
  const_token                                 { printNonTerminal("const_token"); }
| ident_token                                 { printNonTerminal("ident_token"); }
| '(' expr ')'                                { printNonTerminal("'(' expr ')'"); }
| expr '+' expr                               { printNonTerminal("expr '+' expr"); }
| expr '-' expr                               { printNonTerminal("expr '-' expr"); }
| expr '*' expr                               { printNonTerminal("expr '*' expr"); }
| expr '/' expr                               { printNonTerminal("expr '/' expr"); }
| expr '<' expr                               { printNonTerminal("expr '<' expr"); }
| expr '>' expr                               { printNonTerminal("expr '>' expr"); }
| expr TOK_LOGIC_AND expr                     { printNonTerminal("expr TOK_LOGIC_AND expr"); }
| expr TOK_LOGIC_OR expr                      { printNonTerminal("expr TOK_LOGIC_OR expr"); }
| expr TOK_IS_EQ expr                         { printNonTerminal("expr TOK_IS_EQ expr"); }
| expr TOK_IS_NOT_EQ expr                     { printNonTerminal("expr TOK_IS_NOT_EQ expr"); }
| expr TOK_IS_GEQ expr                        { printNonTerminal("expr TOK_IS_GEQ expr"); }
| expr TOK_IS_LEQ expr                        { printNonTerminal("expr TOK_IS_LEQ expr"); }
| '-' expr  %prec TOK_UMIN                    { printNonTerminal("'-' expr  %prec TOK_UMIN"); }
| '!' expr  %prec TOK_NOT                     { printNonTerminal("'!' expr  %prec TOK_NOT"); }
;

/* Constant values processing */
const_token:
  TOK_INT       { printTerminal("TOK_INT"); }
| TOK_TRUE      { printTerminal("TOK_TRUE"); }
| TOK_FALSE     { printTerminal("TOK_FALSE"); }
| TOK_CHAR      { printTerminal("TOK_CHAR"); }
;

/* Identifier token processing */
ident_token:
  TOK_IDENT { printTerminal("TOK_IDENT"); }
;

%%

/* Function defenitions */
void yyerror(const std::string &msg) {
  std::cout << msg << std::endl;
}

static void printTerminal(const std::string& tokName) {
  std::cout << '<' << tokName << ", \"" << yytext << "\", "
            << yylloc.first_line << ": " << yylloc.first_column << ", "
            << yylloc.last_line << ": " << yylloc.last_column << '>'
            << std::endl;
}

static void printNonTerminal(const std::string& tokName) {
  std::cout << '<' << tokName << '>' << std::endl;
}
