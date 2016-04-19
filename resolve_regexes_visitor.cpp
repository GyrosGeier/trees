#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "resolve_regexes_visitor.h"

#include <sstream>

namespace trees {
namespace parse {

component_ptr resolve_regexes_visitor::visit(string_literal_ptr s) { return s; }
component_ptr resolve_regexes_visitor::visit(unresolved_symbol_ptr u) { return u; }
component_ptr resolve_regexes_visitor::visit(terminal_ptr t) { return t; }
component_ptr resolve_regexes_visitor::visit(nonterminal_ptr n) { return n; }

component_ptr resolve_regexes_visitor::visit(regex_ptr rx)
{
        std::ostringstream ss;
        ss << "REGEX_" << ++num;
        rx->name = ss.str();

        rt->regexes.push_back(rx);

        terminal_ptr t = std::make_shared<terminal>();
        t->name = rx->name;
        *current_context = t;
        return *current_context;
}

component_ptr resolve_regexes_visitor::visit(group_ptr g)
{
        for(auto &i : g->components)
        {
                current_context = &i;
                descend(i);
        }
        return g;
}

void resolve_regexes_visitor::operator()(root_ptr r)
{
        rt = r;
        for(auto &i : r->rules)
                visit(i);
}

void resolve_regexes_visitor::visit(rule_ptr r)
{
        for(auto &i : r->alternatives)
                visit(i);
}

void resolve_regexes_visitor::visit(alternative_ptr a)
{
        visit(a->group);
}

}
}
