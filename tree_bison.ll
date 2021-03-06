%{
#include "tree_bison_context.hpp"
#include "tree_bison_cst.hpp"
#include "tree_bison_parse.hpp"
#define YY_USER_ACTION yylloc->first_line = yylloc->last_line = yylineno;
%}

%option nostdinit
/*%option nodefault*/
%option nounput
%option noyywrap
%option reentrant
%option bison-bridge
%option bison-locations
%option yylineno
%option prefix="tree_bison_"
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
  \}                    if(!--yyextra->bracecount) { BEGIN(rules); }
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

  \/\*-[^-]*-\*\/       yylval->string = strndup(yytext+3, yyleng-6); return NAME_HINT;
  \/\*                  BEGIN(ccomment);

  \"(\\.|[^"])*\"       yylval->string = strdup(yytext); return STRING;
  {IDENT}:              yylval->string = strdup(yytext); yylval->string[yyleng-1] = 0; return IDENTIFIER_COLON;
  {IDENT}               yylval->string = strdup(yytext); return IDENTIFIER;
}

<ccomment>{
  \*\/                  BEGIN(rules);
  \n                    /* ignore */
  .                     /* ignore */
}

%%

/*.                       return INVALID;*/
