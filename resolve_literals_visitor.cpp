#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "resolve_literals_visitor.h"

#include <sstream>

namespace foundry {
namespace parse {

void resolve_literals_visitor::visit(group &g)
{
        for(auto &i : g.components)
        {
                current_context = &i;
                descend(i);
        }
}

void resolve_literals_visitor::visit(regex &) { }
void resolve_literals_visitor::visit(string_literal &l)
{
        auto litref = literals.find(l.text);
        if(litref != literals.end())
        {
                *current_context = litref->second;
        }
        else
        {
                std::ostringstream os;
                os << "LITERAL_" << ++num;
                l.name = os.str();
                literals[l.text] = &l;
                rt->literals.push_back(&l);
        }
}
void resolve_literals_visitor::visit(unresolved_symbol &) { }
void resolve_literals_visitor::visit(terminal &) { }
void resolve_literals_visitor::visit(nonterminal &) { }
void resolve_literals_visitor::visit(root &r) { rt = &r; descend(r.rules); }
void resolve_literals_visitor::visit(rule &r) { descend(r.alternatives);  }
void resolve_literals_visitor::visit(alternative &a) { descend(a.group); }

}
}
