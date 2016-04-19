#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "resolve_symbols_visitor.h"

#include "errors.h"

#include <iostream>

namespace trees {
namespace parse {

component_ptr resolve_symbols_visitor::visit(group_ptr g)
{
        for(auto &i : g->components)
        {
                current_context = &i;
                descend(i);
        }
        return g;
}

component_ptr resolve_symbols_visitor::visit(regex_ptr r) { return r; }
component_ptr resolve_symbols_visitor::visit(string_literal_ptr s) { return s; }
component_ptr resolve_symbols_visitor::visit(unresolved_symbol_ptr s)
{
        auto ntref = nonterminals.find(s->name);
        if(ntref != nonterminals.end())
        {
                if(verbose)
                        std::cerr << "Immediately resolved nonterminal " << s->name << std::endl;
                *current_context = ntref->second;
        }
        else
        {
                unresolved_references[s->name].push_back(current_context);
                if(verbose)
                        std::cerr << "Queuing unresolved symbol " << s->name << std::endl;
        }
        return *current_context;
}

component_ptr resolve_symbols_visitor::visit(terminal_ptr t) { return t; }
component_ptr resolve_symbols_visitor::visit(nonterminal_ptr n) { return n; }

void resolve_symbols_visitor::operator()(root_ptr r)
{
        for(auto &i : r->rules)
                visit(i);

        if(verbose)
        {
                auto n = unresolved_references.size();
                if(n)
                {
                        std::cerr << n << " unresolved symbols remaining." << std::endl;
                        for(auto i : unresolved_references)
                        {
                                std::cerr << "Symbol " << i.first << ": " << i.second.size() << " references" << std::endl;
                        }
                        throw unknown_production();
                }
        }
}

void resolve_symbols_visitor::visit(rule_ptr r)
{
        nonterminal_ptr nt = std::make_shared<nonterminal>();
        nt->name = r->name;
        nt->rule = r;

        if(verbose)
                std::cerr << "Found rule " << r->name << std::endl;

        auto ntref = nonterminals.find(r->name);
        if(ntref != nonterminals.end())
                throw duplicate_rule(r->name);

        nonterminals[r->name] = nt;

        auto urref = unresolved_references.find(r->name);
        if(urref != unresolved_references.end())
        {
                if(verbose)
                        std::cerr << "Resolving " << urref->second.size() << " queued references." << std::endl;
                for(auto &i : urref->second)
                        *i = nt;
                unresolved_references.erase(urref);
        }

        for(auto &i : r->alternatives)
                visit(i);

}

void resolve_symbols_visitor::visit(alternative_ptr a)
{
        visit(a->group);
}

}
}
