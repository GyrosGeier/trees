#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "resolve_regexes_visitor.h"

#include <sstream>

namespace foundry {
namespace parse {

void resolve_regexes_visitor::visit(string_literal&) { }
void resolve_regexes_visitor::visit(unresolved_symbol&) { }
void resolve_regexes_visitor::visit(terminal&) { }
void resolve_regexes_visitor::visit(nonterminal&) { }

void resolve_regexes_visitor::visit(regex &rx)
{
        std::ostringstream ss;
        ss << "REGEX_" << ++num;
        rx.name = ss.str();

        rt->regexes.push_back(&rx);

        terminal_ptr t = new terminal;
        t->name = rx.name;
        *current_context = t;
}

void resolve_regexes_visitor::visit(group &g)
{
        for(auto &i : g.components)
        {
                current_context = &i;
                descend(i);
        }
}

void resolve_regexes_visitor::visit(root &r)
{
        rt = &r;
        descend(r.rules);
}

void resolve_regexes_visitor::visit(rule &r)
{
        descend(r.alternatives);
}

void resolve_regexes_visitor::visit(alternative &a)
{
        descend(a.group);
}

}
}
