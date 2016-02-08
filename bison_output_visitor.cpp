#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "bison_output_visitor.h"

#include "errors.h"

#include <iostream>

namespace trees {
namespace parse {

bison_output_visitor::bison_output_visitor(std::string const &basename, std::ostream &out) :
        basename(basename),
        out(out)
{
        return;
}

void bison_output_visitor::visit(root const &r)
{
        if(r.rules.empty())
                return;

        if(r.ns.empty())
                ns = "::";
        else
                ns = "::" + r.ns + "::";

        start = r.rules.front().get();

        out << "%{" << std::endl;
        out << "#include \"" << basename << "_cst.hpp\"" << std::endl;
        out << "#include \"" << basename << "_parse.hpp\"" << std::endl;
        out << "#include \"" << basename << "_lex.hpp\"" << std::endl;
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
        out << "%parse-param {" << ns << start->name << " *&ret}" << std::endl;
        out << "%lex-param {void *scanner}" << std::endl;
        out << "" << std::endl;
        out << "%name-prefix \"" << basename << "_\"" << std::endl;
        out << "" << std::endl;
        out << "%{" << std::endl;
        out << "void " << basename << "_error(YYLTYPE *loc, void *, " << ns << start->name << " *&, char const *msg)" << std::endl;
        out << "{" << std::endl;
        out << "        std::cerr << loc->first_line << \":\" << msg << std::endl;" << std::endl;
        out << "}" << std::endl;
        out << "%}" << std::endl;
        state = write_terminals;
        descend(r.regexes);
        descend(r.literals);
        out << "%union {" << std::endl;
        out << "        char *string;" << std::endl;
        state = write_union_members;
        descend(r.rules);
        out << "}" << std::endl;
        state = write_type_decls;
        descend(r.rules);
        out << "%%" << std::endl;
        state = write_rules;
        descend(r.rules);
}

void bison_output_visitor::visit(rule const &r)
{
        switch(state)
        {
        case write_union_members:
                out << "        " << ns << r.name << " *" << r.name <<";" << std::endl;
                break;
        case write_type_decls:
                out << "%type<" << r.name << "> " << r.name << ";" << std::endl;
                break;
        case write_rules:
                current_rule = &r;
                out << r.name << ':';
                first_alternative = true;
                descend(r.alternatives);
                out << ';' << std::endl;
                break;
        default:
                throw internal_error("Illegal output generator state");
        }
}

void bison_output_visitor::visit(alternative const &a)
{
        if(!first_alternative)
                out << " |";
        else
                first_alternative = false;
        out << " /*-" << a.name << "-*/";
        state = write_components;
        first_component = true;
        current_component = 0;
        descend(a.group);
        state = write_action;
        out << " { ";
        if(current_rule == start)
                out << "ret";
        else
                out << "$$";
        out << " = new " << ns << a.name;
        out << '(';
        first_component = true;
        current_component = 0;
        descend(a.group);
        out << "); ";
        state = write_cleanup;
        current_component = 0;
        descend(a.group);
        out << "}";
        state = write_rules;
}

void bison_output_visitor::visit(group const &g)
{
        descend(g.components);
}

void bison_output_visitor::visit(regex const &c)
{
        ++current_component;
        switch(state)
        {
        case write_terminals:
                out << "%token " << c.name << std::endl;
                out << "%type<string> " << c.name << ";" << std::endl;
                break;
        case write_components:
                out << ' ' << c.name;
                break;
        case write_action:
        case write_cleanup:
                break;
        default:
                throw internal_error("Illegal output generator state");
        }
}

void bison_output_visitor::visit(string_literal const &c)
{
        ++current_component;
        switch(state)
        {
        case write_terminals:
                out << "%token " << c.name << ' ' << c.text << std::endl;
                break;
        case write_components:
                out << ' ' << c.text;
                break;
        case write_action:
        case write_cleanup:
                break;
        default:
                throw internal_error("Illegal output generator state");
        }
}

void bison_output_visitor::visit(terminal const &c)
{
        ++current_component;
        switch(state)
        {
        case write_terminals:
                out << "%token " << c.name << ";" << std::endl;
                out << "%type<string> " << c.name << ";" << std::endl;
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
        case write_cleanup:
                out << "free($" << current_component << "); ";
                break;
        default:
                throw internal_error("Illegal output generator state");
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
        case write_cleanup:
                break;
        default:
                throw internal_error("Illegal output generator state");
        }
}

void bison_output_visitor::visit(unresolved_symbol const &)
{
        throw internal_error("unresolved symbol found during output");
}

}
}
