#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "bison_output_visitor.h"

namespace foundry {
namespace parse {

bison_output_visitor::bison_output_visitor(std::ostream &out) :
        out(out)
{
        return;
}

void bison_output_visitor::visit(root const &r)
{
        if(!r.rules.empty())
                (*r.rules.begin())->is_start = true;

        out << "%{" << std::endl;
        out << "#include \"parse_cst.hpp\"" << std::endl;
        out << "#include \"parse_parse.hpp\"" << std::endl;
        out << "#include \"parse_lex.hpp\"" << std::endl;
        out << "using namespace foundry::parse::cst;" << std::endl;
        out << "%}" << std::endl;
        out << "" << std::endl;
        out << "%debug" << std::endl;
        out << "%pure-parser" << std::endl;
        out << "%defines" << std::endl;
        out << "%error-verbose" << std::endl;
        out << "%locations" << std::endl;
        out << "" << std::endl;
        out << "%expect 0" << std::endl;
        out << "" << std::endl;
        out << "%parse-param {void *scanner}" << std::endl;
        out << "%parse-param {::foundry::parse::cst::start *&ret}" << std::endl;
        out << "%lex-param {void *scanner}" << std::endl;
        out << "" << std::endl;
        out << "%name-prefix=\"parse_\"" << std::endl;
        out << "" << std::endl;
        out << "%{" << std::endl;
        out << "void parse_error(YYLTYPE *loc, void *, ::foundry::parse::cst::start *&, char const *msg)" << std::endl;
        out << "{" << std::endl;
        out << "        std::cerr << loc->first_line << \":\" << msg << std::endl;" << std::endl;
        out << "}" << std::endl;
        out << "%}" << std::endl;
        state = write_terminals;
        descend(r.terminals);
        out << "%token SEMICOLON \";\"" << std::endl;
        out << "%token COLON \":\"" << std::endl;
        out << "%token PIPE \"|\"" << std::endl;
        out << "%union {" << std::endl;
        out << "        char const *string;" << std::endl;
        state = write_union_members;
        descend(r.rules);
        out << "}" << std::endl;
        state = write_type_decls;
        descend(r.rules);
        out << "%type<string> IDENTIFIER;" << std::endl;
        out << "%type<string> STRING_LITERAL;" << std::endl;
        out << "%%" << std::endl;
        state = write_rules;
        descend(r.rules);
}

void bison_output_visitor::visit(rule const &r)
{
        switch(state)
        {
        case write_union_members:
                out << "        ::foundry::parse::cst::" << r.name << " *" << r.name <<";" << std::endl;
                break;
        case write_type_decls:
                out << "%type<" << r.name << "> " << r.name << ";" << std::endl;
                break;
        case write_rules:
                current_rule = &r;
                out << r.name << ':';
                first_alternative = true;
                current_alternative = 0;
                multiple_alternatives = (r.alternatives.size() > 1);
                descend(r.alternatives);
                out << ';' << std::endl;
                break;
        default:
                throw;
        }
}

void bison_output_visitor::visit(alternative const &a)
{
        ++current_alternative;
        if(!first_alternative)
                out << " |";
        else
                first_alternative = false;
        state = write_components;
        first_component = true;
        current_component = 0;
        descend(a.components);
        state = write_action;
        out << " { ";
        if(current_rule->is_start)
                out << "ret";
        else
                out << "$$";
        out << " = new " << current_rule->name;
        if(multiple_alternatives)
                out << '_' << current_alternative;
        out << '(';
        first_component = true;
        current_component = 0;
        descend(a.components);
        out << "); }";
        state = write_rules;
}

void bison_output_visitor::visit(string_literal const &c)
{
        ++current_component;
        switch(state)
        {
        case write_components:
                out << ' ' << c.text;
                break;
        case write_action:
                break;
        default:
                throw;
        }
}

void bison_output_visitor::visit(terminal const &c)
{
        ++current_component;
        switch(state)
        {
        case write_terminals:
                out << "%token " << c.name << ";" << std::endl;
                break;
        case write_components:
                out << ' ' << c.name;
                break;
        case write_action:
                if(!first_component)
                        out << ", ";
                else
                        first_component = false;
                out << '$' << current_component;
                break;
        default:
                throw;
        }
}

void bison_output_visitor::visit(nonterminal const &c)
{
        ++current_component;
        switch(state)
        {
        case write_components:
                out << ' ' << c.name;
                break;
        case write_action:
                if(!first_component)
                        out << ", ";
                else
                        first_component = false;
                out << '$' << current_component;
                break;
        default:
                throw;
        }
}

}
}
