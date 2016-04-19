#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "resolve_literals_visitor.h"

#include <sstream>

namespace trees {
namespace parse {

component_ptr resolve_literals_visitor::visit(group_ptr g)
{
        for(auto &i : g->components)
        {
                descend(i);
        }
        return g;
}

component_ptr resolve_literals_visitor::visit(regex_ptr r) { return r; }

component_ptr resolve_literals_visitor::visit(string_literal_ptr l)
{
        auto litref = literals.find(l->text);
        if(litref != literals.end())
        {
                return litref->second;
        }
        else
        {
                std::ostringstream os;
                os << "LITERAL_" << ++num;
                l->name = os.str();
                literals[l->text] = l;
                rt->literals.push_back(l);
        }
        return l;
}

component_ptr resolve_literals_visitor::visit(unresolved_symbol_ptr u) { return u; }

component_ptr resolve_literals_visitor::visit(terminal_ptr t) { return t; }
component_ptr resolve_literals_visitor::visit(nonterminal_ptr n) { return n; }

void resolve_literals_visitor::operator()(root_ptr r)
{
        rt = r;
        for(auto &i : r->rules)
                visit(i);
}

void resolve_literals_visitor::visit(rule_ptr r)
{
        for(auto &i : r->alternatives)
                visit(i);
}

void resolve_literals_visitor::visit(alternative_ptr a)
{
        visit(a->group);
}

}
}
