#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "lex_output_visitor.h"

#include "errors.h"

#include <iostream>

namespace trees {
namespace parse {

lex_output_visitor::lex_output_visitor(std::string const &basename, std::ostream &out) :
        basename(basename),
        out(out)
{
        return;
}

void lex_output_visitor::visit(root const &r)
{
        out << "%{" << std::endl;
        out << "#include \"" << basename << "_cst.hpp\"" << std::endl;
        out << "#include \"" << basename << "_parse.hpp\"" << std::endl;
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
        out << "%option prefix=\"" << basename << "_\"" << std::endl;
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
        out << "\\               /* ignore */" << std::endl;
        out << "\\t              /* ignore */" << std::endl;
        out << "\\n              /* ignore */" << std::endl;
        descend(r.literals);
        descend(r.regexes);
}

void lex_output_visitor::visit(rule const &)
{
}

void lex_output_visitor::visit(alternative const &)
{
}

void lex_output_visitor::visit(group const &)
{
}

void lex_output_visitor::visit(regex const &r)
{
        std::string const text = r.text.substr(1, r.text.size() - 2);
        for(auto i : text)
        {
                switch(i)
                {
                case '"':
                        out << '\\' << i;
                        break;
                default:
                        out << i;
                        break;
                }
        }
        out << "\tyylval->string = strdup(yytext); return " << r.name << ";" << std::endl;
}
void lex_output_visitor::visit(string_literal const &l)
{
        std::string const text = l.text.substr(1, l.text.size() - 2);
        for(auto i : text)
        {
                switch(i)
                {
                case '.':
                case ';':
                case '|':
                case '?':
                case '^':
                case '*':
                case '+':
                case '/':
                case '\\':
                case '(': case ')':
                case '<': case '>':
                case '[': case ']':
                case '{': case '}':
                        out << '\\' << i;
                        break;
                default:
                        out << i;
                        break;
                }
        }
        out << "\treturn " << l.name << ";" << std::endl;
}

void lex_output_visitor::visit(terminal const &)
{
}

void lex_output_visitor::visit(nonterminal const &)
{
}

void lex_output_visitor::visit(unresolved_symbol const &)
{
        throw internal_error("unresolved symbol found during output");
}

}
}
