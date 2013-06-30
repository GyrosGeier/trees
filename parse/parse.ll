%{
#include "parse_cst.hpp"
#include "parse_parse.hpp"
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
%option prefix="parse_"
IDENT           [[:alpha:]_][[:alnum:]_]*

%x COMMENT

%%

<INITIAL>\/\*   BEGIN(COMMENT);
<COMMENT>\*\/   BEGIN(INITIAL);
<COMMENT>.      /* ignore */

%[^\n]*          yylval->string = strdup(yytext); return DIRECTIVE;
:	return LITERAL_1;
\;	return LITERAL_2;
\|	return LITERAL_3;
-	return LITERAL_4;
\?	return LITERAL_5;
\+	return LITERAL_6;
\*	return LITERAL_7;
\(	return LITERAL_8;
\)	return LITERAL_9;
\               /* ignore */
\n              /* ignore */

{IDENT}         yylval->string = strdup(yytext); return IDENTIFIER;
\"(\\.|[^"])*\" yylval->string = strdup(yytext); return STRING_LITERAL;
