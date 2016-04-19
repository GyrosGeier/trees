#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "inline_simple_visitor.h"

#include "errors.h"

#include <iostream>

namespace trees {
namespace parse {

component_ptr inline_simple_visitor::visit(trees::parse::string_literal_ptr l) { return l; }

component_ptr inline_simple_visitor::visit(trees::parse::unresolved_symbol_ptr )
{
        throw internal_error("Unresolved symbol found during inlining");
}

component_ptr inline_simple_visitor::visit(trees::parse::terminal_ptr t) { return t; }

component_ptr inline_simple_visitor::visit(trees::parse::nonterminal_ptr nt)
{
        if(is_simple_rule(nt->rule))
        {
                if(verbose)
                        std::cerr << "Inlining " << nt->rule->name << std::endl;
                *current_component_context = nt->rule->alternatives.front()->group->components.front();
                descend(*current_component_context);
                return *current_component_context;
        }
        return nt;
}

component_ptr inline_simple_visitor::visit(trees::parse::regex_ptr r) { return r; }

component_ptr inline_simple_visitor::visit(trees::parse::group_ptr g)
{
        is_simple = false;
        for(auto &i : g->components)
        {
                current_component_context = &i;
                descend(i);
        }
        return g;
}

void inline_simple_visitor::operator()(trees::parse::root_ptr r)
{
        if(r->rules.empty())
                return;

        start = r->rules.front();

        for(auto &i : r->rules)
        {
                current_rule_context = &i;
                handle(i);
        }
        r->rules.remove_if(std::bind(std::mem_fun(&inline_simple_visitor::is_simple_rule), this, std::placeholders::_1));
}

void inline_simple_visitor::handle(trees::parse::rule_ptr r)
{
        for(auto &i : r->alternatives)
                handle(i);
}

void inline_simple_visitor::handle(trees::parse::alternative_ptr a)
{
        visit(a->group);
}

bool inline_simple_visitor::is_simple_rule(rule_ptr &r)
{
        if(r == start)
                return false;

        if(r->alternatives.size() == 1 &&
                r->alternatives.front()->group->rep == repeat_none &&
                r->alternatives.front()->group->components.size() == 1)
        {
                is_simple = true;
                descend(r->alternatives.front()->group->components.front());
                return is_simple;
        }
        return false;
}

}
}
