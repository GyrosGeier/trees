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
IDENT           [[:alpha:]_][[:alnum:]_]*

%x COMMENT

%%

<INITIAL>\/\*   BEGIN(COMMENT);
<COMMENT>\*\/   BEGIN(INITIAL);
<COMMENT>.      /* ignore */

\               /* ignore */
\t              /* ignore */
\n              /* ignore */
\;	return LITERAL_1;
namespace	return LITERAL_2;
\{	return LITERAL_3;
\}	return LITERAL_4;
group	return LITERAL_5;
node	return LITERAL_6;
visitor	return LITERAL_7;
const	return LITERAL_8;
%multiparent	return LITERAL_9;
%scoped_ptr	return LITERAL_10;
%shared_ptr	return LITERAL_11;
%intrusive_ptr	return LITERAL_12;
%smartpointer	return LITERAL_13;
\(	return LITERAL_14;
\)	return LITERAL_15;
void	return LITERAL_16;
,	return LITERAL_17;
~	return LITERAL_18;
parent	return LITERAL_19;
&	return LITERAL_20;
\*	return LITERAL_21;
volatile	return LITERAL_22;
\[	return LITERAL_23;
\]	return LITERAL_24;
\<	return LITERAL_25;
\>	return LITERAL_26;
\.\.\.	return LITERAL_27;
::	return LITERAL_28;
true	return LITERAL_29;
false	return LITERAL_30;
[[:alpha:]_][[:alnum:]_]*	yylval->string = strdup(yytext); return REGEX_1;
[[:digit:]]+	yylval->string = strdup(yytext); return REGEX_2;
%include\ [^\n]*	yylval->string = strdup(yytext); return REGEX_3;
\\"([^\"\\\n]|\\.|\\\n)*\\"	yylval->string = strdup(yytext); return REGEX_4;
