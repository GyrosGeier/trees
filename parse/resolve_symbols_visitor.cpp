#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "resolve_symbols_visitor.h"

#include "errors.h"

#include <iostream>

namespace foundry {
namespace parse {

void resolve_symbols_visitor::visit(group &g)
{
        for(auto &i : g.components)
        {
                current_context = &i;
                descend(i);
        }
}

void resolve_symbols_visitor::visit(regex &) { }
void resolve_symbols_visitor::visit(string_literal &) { }
void resolve_symbols_visitor::visit(unresolved_symbol &s)
{
        auto ntref = nonterminals.find(s.name);
        if(ntref != nonterminals.end())
        {
                *current_context = ntref->second;
                if(verbose)
                        std::cerr << "Immediately resolved nonterminal " << s.name << std::endl;
        }
        else
        {
                unresolved_references[s.name].push_back(current_context);
                if(verbose)
                        std::cerr << "Queuing unresolved symbol " << s.name << std::endl;
        }
}

void resolve_symbols_visitor::visit(terminal &) { }
void resolve_symbols_visitor::visit(nonterminal &) { }

void resolve_symbols_visitor::visit(root &r)
{
        descend(r.rules);

        if(verbose)
        {
                std::cerr << unresolved_references.size() << " unresolved symbols remaining." << std::endl;
                for(auto i : unresolved_references)
                {
                        std::cerr << "Symbol " << i.first << ": " << i.second.size() << " references" << std::endl;
                }
                throw unknown_production();
        }
}

void resolve_symbols_visitor::visit(rule &r)
{
        nonterminal_ptr nt = new nonterminal;
        nt->name = r.name;
        nt->rule = &r;

        if(verbose)
                std::cerr << "Found rule " << r.name << std::endl;

        auto ntref = nonterminals.find(r.name);
        if(ntref != nonterminals.end())
                throw duplicate_rule(r.name);

        nonterminals[r.name] = nt;

        auto urref = unresolved_references.find(r.name);
        if(urref != unresolved_references.end())
        {
                if(verbose)
                        std::cerr << "Resolving " << urref->second.size() << " queued references." << std::endl;
                for(auto &i : urref->second)
                        *i = nt;
                unresolved_references.erase(urref);
        }

        descend(r.alternatives);
}

void resolve_symbols_visitor::visit(alternative &a)
{
        descend(a.group);
}

}
}
