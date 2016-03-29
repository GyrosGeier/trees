#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "inline_simple_visitor.h"

#include "errors.h"

namespace trees {
namespace parse {

component_ptr inline_simple_visitor::visit(trees::parse::string_literal &l) { return &l; }

component_ptr inline_simple_visitor::visit(trees::parse::unresolved_symbol &)
{
        throw internal_error("Unresolved symbol found during inlining");
}

component_ptr inline_simple_visitor::visit(trees::parse::terminal &t) { return &t; }

component_ptr inline_simple_visitor::visit(trees::parse::nonterminal &nt)
{
        if(is_simple_rule(nt.rule))
        {
                if(verbose)
                        std::cerr << "Inlining " << nt.rule->name << std::endl;
                *current_component_context = nt.rule->alternatives.front()->group->components.front();
                descend(*current_component_context);
        }
        return *current_component_context;
}

component_ptr inline_simple_visitor::visit(trees::parse::regex &r) { return &r; }

component_ptr inline_simple_visitor::visit(trees::parse::group &g)
{
        is_simple = false;
        for(auto &i : g.components)
        {
                current_component_context = &i;
                descend(i);
        }
        return &g;
}

node_ptr inline_simple_visitor::visit(trees::parse::root &r)
{
        if(r.rules.empty())
                return &r;

        start = r.rules.front();

        for(auto &i : r.rules)
        {
                current_rule_context = &i;
                descend(i);
        }
        r.rules.remove_if(std::bind(std::mem_fun(&inline_simple_visitor::is_simple_rule), this, std::placeholders::_1));
        return &r;
}

node_ptr inline_simple_visitor::visit(trees::parse::rule &r) { descend(r.alternatives); return &r; }
node_ptr inline_simple_visitor::visit(trees::parse::alternative &a)
{
        descend(a.group);
        return &a;
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
