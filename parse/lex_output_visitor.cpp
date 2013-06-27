#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "lex_output_visitor.h"

namespace foundry {
namespace parse {

lex_output_visitor::lex_output_visitor(std::ostream &out) :
        out(out)
{
        return;
}

void lex_output_visitor::visit(root const &)
{
        out << "%{" << std::endl;
        out << "#include \"parse_cst.hpp\"" << std::endl;
        out << "#include \"parse_parse.hpp\"" << std::endl;
        out << "#define YY_USER_ACTION yylloc->first_line = yylloc->last_line = yylineno;" << std::endl;
        out << "%}" << std::endl;
        out << "" << std::endl;
        out << "%option nostdinit" << std::endl;
        out << "/*%option nodefault*/" << std::endl;
        out << "%option nounput" << std::endl;
        out << "%option noyywrap" << std::endl;
        out << "%option reentrant" << std::endl;
        out << "%option bison-bridge" << std::endl;
        out << "%option bison-locations" << std::endl;
        out << "%option yylineno" << std::endl;
        out << "%option prefix=\"parse_\"" << std::endl;
        out << "IDENT           [[:alpha:]_][[:alnum:]_]*" << std::endl;
        out << "" << std::endl;
        out << "%x COMMENT" << std::endl;
        out << "" << std::endl;
        out << "%%" << std::endl;
        out << "" << std::endl;
        out << "<INITIAL>\\/\\*   BEGIN(COMMENT);" << std::endl;
        out << "<COMMENT>\\*\\/   BEGIN(INITIAL);" << std::endl;
        out << "<COMMENT>.      /* ignore */" << std::endl;
        out << "" << std::endl;
        out << "\\;              return SEMICOLON;" << std::endl;
        out << ":               return COLON;" << std::endl;
        out << "\\|              return PIPE;" << std::endl;
        out << "\\               /* ignore */" << std::endl;
        out << "\\n              /* ignore */" << std::endl;
        out << "" << std::endl;
        out << "{IDENT}         yylval->string = strdup(yytext); return IDENTIFIER;" << std::endl;
        out << "\\\"(\\\\.|[^\"])*\\\" yylval->string = strdup(yytext); return STRING_LITERAL;" << std::endl;
}

void lex_output_visitor::visit(rule const &)
{
}

void lex_output_visitor::visit(alternative const &)
{
}

void lex_output_visitor::visit(string_literal const &)
{
}

void lex_output_visitor::visit(terminal const &)
{
}

void lex_output_visitor::visit(nonterminal const &)
{
}

}
}
