%{
#include "tree_cst_cst.hpp"
#include "tree_cst_parse.hpp"
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
%option prefix="tree_cst_"
%option header-file="tree_cst_lex.hpp"

IDENT                       [[:alpha:]_][[:alnum:]_]*
INTEGER                     [[:digit:]]+

%%

\                           /* ignore */
\n                          /* ignore */
\t                          /* ignore */
\r                          /* ignore */

\(                          return LPAREN;
\)                          return RPAREN;
\{                          return LBRACE;
\}                          return RBRACE;
\[                          return LBRACKET;
\]                          return RBRACKET;
\<                          return LANGLE;
\>                          return RANGLE;
&                           return AMPERSAND;
,                           return COMMA;
;                           return SEMICOLON;
::                          return DOUBLECOLON;
\*                          return ASTERISK;
\.\.\.                      return ELLIPSIS;

visitor                     return VISITOR;
group                       return GROUP;
%multiparent                return MULTIPARENT;
%scoped_ptr                 return SCOPED_PTR;
%shared_ptr                 return SHARED_PTR;
%intrusive_ptr              return INTRUSIVE_PTR;
%smartpointer[^\n]*         return SMARTPOINTER;
%include\ [^\n]*            yylval->string.data = yytext; yylval->string.length = yyleng; return INCLUDE;

namespace                   return NAMESPACE;
const                       return CONST;
volatile                    return VOLATILE;
void                        return VOID;

node                        return NODE;
parent                      return PARENT;

true                        return TRUE;
false                       return FALSE;

{IDENT}                     yylval->string.data = yytext; yylval->string.length = yyleng; return IDENTIFIER;
{INTEGER}                   yylval->string.data = yytext; yylval->string.length = yyleng; return INTEGER;
\"([^"\\\n]|\\.|\\\n)*\"    yylval->string.data = yytext+1; yylval->string.length = yyleng-2; return QUOTED_NAME;
