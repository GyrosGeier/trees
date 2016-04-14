#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "resolve_regexes_visitor.h"

#include <sstream>

namespace trees {
namespace parse {

component_ptr resolve_regexes_visitor::visit(string_literal &s) { return &s; }
component_ptr resolve_regexes_visitor::visit(unresolved_symbol &u) { return &u; }
component_ptr resolve_regexes_visitor::visit(terminal &t) { return &t; }
component_ptr resolve_regexes_visitor::visit(nonterminal &n) { return &n; }

component_ptr resolve_regexes_visitor::visit(regex &rx)
{
        std::ostringstream ss;
        ss << "REGEX_" << ++num;
        rx.name = ss.str();

        rt->regexes.push_back(&rx);

        terminal_ptr t = new terminal;
        t->name = rx.name;
        *current_context = t;
        return *current_context;
}

component_ptr resolve_regexes_visitor::visit(group &g)
{
        for(auto &i : g.components)
        {
                current_context = &i;
                descend(i);
        }
        return &g;
}

void resolve_regexes_visitor::operator()(root &r)
{
        rt = &r;
        for(auto &i : r.rules)
                visit(*i);
}

void resolve_regexes_visitor::visit(rule &r)
{
        for(auto &i : r.alternatives)
                visit(*i);
}

void resolve_regexes_visitor::visit(alternative &a)
{
        visit(*a.group);
}

}
}
