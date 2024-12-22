%{
  #include "paracl-lexer.h"

  #include <string>

  void yyerror (const std::string &msg);
%}

%%

program:;

%%

void yyerror(const std::string &msg) {}
