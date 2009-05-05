%{
#include "tree_bison_context.hpp"
#include "tree_bison_tree.hpp"
#include "tree_bison_parse.hpp"
%}

%option nostdinit
/*%option nodefault*/
%option nounput
%option noyywrap
%option reentrant
%option bison-bridge
%option bison-locations
%option prefix="tree_bison_"
%option header-file="tree_bison_lex.hpp"
%option extra-type="context *"

%x ccomment cfragment action rules

IDENT                   [[:alpha:]_][[:alnum:]_]*

%%

\%\{                    BEGIN(cfragment);
\%\%                    BEGIN(rules);

<INITIAL>{
  \n                    /* ignore */
  .                     /* ignore */
}

<cfragment>{
  \%\}                  BEGIN(INITIAL);
  \n                    /* ignore */
  .                     /* ignore */
}

<action>{
  \{                    ++yyextra->bracecount;
  \}                    if(!--yyextra->bracecount) BEGIN(rules); else return ACTION;
  \n                    /* ignore */
  .                     /* ignore */
}

<rules>{
  \r                    /* ignore */
  \                     /* ignore */
  \t                    /* ignore */
  \n                    /* ignore */

  ;                     return SEMICOLON;
  \|                    return BAR;
  \{                    yyextra->bracecount = 1; BEGIN(action);

  \/\*                  BEGIN(ccomment);

  \"([^"\\\n]|\\.|\\\n)*\"    yylval->string = yytext; return STRING;
  {IDENT}:              yylval->string = yytext; yytext[yyleng-1] = 0; return IDENTIFIER_COLON;
  {IDENT}               yylval->string = yytext; return IDENTIFIER;
}

<ccomment>{
  \*\/                  BEGIN(rules);
  \n                    /* ignore */
  .                     /* ignore */
}

%%

/*.                       return INVALID;*/
