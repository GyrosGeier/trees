#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "resolve_symbols_visitor.h"

#include <iostream>

namespace foundry {
namespace parse {

void resolve_symbols_visitor::visit(string_literal &) { }
void resolve_symbols_visitor::visit(unresolved_symbol &s)
{
        auto ntref = nonterminals.find(s.name);
        if(ntref != nonterminals.end())
                *current_context = ntref->second;
        else
                unresolved_references[s.name].push_back(current_context);
}

void resolve_symbols_visitor::visit(terminal &) { }
void resolve_symbols_visitor::visit(nonterminal &) { }

void resolve_symbols_visitor::visit(root &r)
{
        descend(r.rules);

        // assume remaining unresolved references are terminals
        for(auto i : unresolved_references)
        {
                terminal_ptr t = new terminal;
                t->name = i.first;

                for(auto j : i.second)
                        *j = t;
        }
}

void resolve_symbols_visitor::visit(rule &r)
{
        nonterminal_ptr nt = new nonterminal;
        nt->name = r.name;
        nt->rule = &r;

        auto ntref = nonterminals.find(r.name);
        if(ntref != nonterminals.end())
                throw;

        nonterminals[r.name] = nt;

        auto urref = unresolved_references.find(r.name);
        if(urref != unresolved_references.end())
        {
                for(auto &i : urref->second)
                        *i = nt;
                unresolved_references.erase(urref);
        }

        descend(r.alternatives);
}

void resolve_symbols_visitor::visit(alternative &a)
{
        for(auto &i : a.components)
        {
                current_context = &i;
                descend(i);
        }
}

}
}
