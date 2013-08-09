%{
#include "parse_cst_cst.hpp"
#include "parse_cst_parse.hpp"
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
%option prefix="parse_cst_"
IDENT           [[:alpha:]_][[:alnum:]_]*

%x COMMENT

%%

<INITIAL>\/\*   BEGIN(COMMENT);
<COMMENT>\*\/   BEGIN(INITIAL);
<COMMENT>.      /* ignore */

\               /* ignore */
\t              /* ignore */
\n              /* ignore */
:	return LITERAL_1;
\;	return LITERAL_2;
\|	return LITERAL_3;
-	return LITERAL_4;
\?	return LITERAL_5;
\+	return LITERAL_6;
\*	return LITERAL_7;
\(	return LITERAL_8;
\)	return LITERAL_9;
[a-zA-Z_][a-zA-Z0-9_]*	yylval->string = strdup(yytext); return REGEX_1;
\/(\/|(\\.|[^*])(\\.|[^\/])*)\/	yylval->string = strdup(yytext); return REGEX_2;
%[^\n]*	yylval->string = strdup(yytext); return REGEX_3;
\"(\\.|[^\"])*\"	yylval->string = strdup(yytext); return REGEX_4;
