#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "resolve_literals_visitor.h"

#include <sstream>

namespace trees {
namespace parse {

component_ptr resolve_literals_visitor::visit(group &g)
{
        for(auto &i : g.components)
        {
                current_context = &i;
                descend(i);
        }
        return &g;
}

component_ptr resolve_literals_visitor::visit(regex &r) { return &r; }

component_ptr resolve_literals_visitor::visit(string_literal &l)
{
        auto litref = literals.find(l.text);
        if(litref != literals.end())
        {
                return *current_context = litref->second;
        }
        else
        {
                std::ostringstream os;
                os << "LITERAL_" << ++num;
                l.name = os.str();
                literals[l.text] = &l;
                rt->literals.push_back(&l);
        }
        return &l;
}

component_ptr resolve_literals_visitor::visit(unresolved_symbol &u) { return &u; }

component_ptr resolve_literals_visitor::visit(terminal &t) { return &t; }
component_ptr resolve_literals_visitor::visit(nonterminal &n) { return &n; }
node_ptr resolve_literals_visitor::visit(root &r) { rt = &r; descend(r.rules); return &r; }
node_ptr resolve_literals_visitor::visit(rule &r) { descend(r.alternatives); return &r; }
node_ptr resolve_literals_visitor::visit(alternative &a) { descend(a.group); return &a; }

}
}
