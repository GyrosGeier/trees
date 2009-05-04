%{
#include "tree_cst_tree.hpp"
#include "tree_cst_parse.hpp"
%}

%option nostdinit
/*%option nodefault*/
%option nounput
%option noyywrap
%option reentrant
%option bison-bridge
%option bison-locations
%option prefix="tree_cst_"
%option header-file="tree_cst_lex.hpp"

%s DIRECTIVE

IDENT                       [[:alpha:]_][[:alnum:]_]*
INTEGER                     [[:digit:]]+

%%

<INITIAL>%                  BEGIN(DIRECTIVE); return PERCENT;
<DIRECTIVE>(%|\n)           BEGIN(INITIAL); return PERCENT;

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

<INITIAL>visitor            return VISITOR;
<INITIAL>group              return GROUP;
<DIRECTIVE>multiparent      return MULTIPARENT;
<DIRECTIVE>scoped_ptr       return SCOPED_PTR;
<DIRECTIVE>shared_ptr       return SHARED_PTR;
<DIRECTIVE>intrusive_ptr    return INTRUSIVE_PTR;
<DIRECTIVE>smartpointer     return SMARTPOINTER;
<DIRECTIVE>include          return INCLUDE;

namespace                   return NAMESPACE;
const                       return CONST;
volatile                    return VOLATILE;
void                        return VOID;

node                        return NODE;
<INITIAL>parent             return PARENT;

true                        return TRUE;
false                       return FALSE;

{IDENT}                     yylval->string.data = yytext; yylval->string.length = yyleng; return IDENTIFIER;
{INTEGER}                   yylval->string.data = yytext; yylval->string.length = yyleng; return INTEGER;
\"([^"\\\n]|\\.|\\\n)*\"    yylval->string.data = yytext+1; yylval->string.length = yyleng-2; return QUOTED_NAME;
\<[^\>]*\>                  yylval->string.data = yytext+1; yylval->string.length = yyleng-2; return HEADER_NAME;
