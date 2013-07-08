#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "inline_simple_visitor.h"

namespace foundry {
namespace parse {

void inline_simple_visitor::visit(foundry::parse::string_literal&) { }
void inline_simple_visitor::visit(foundry::parse::unresolved_symbol&) { throw; }
void inline_simple_visitor::visit(foundry::parse::terminal&) { }

void inline_simple_visitor::visit(foundry::parse::nonterminal &nt)
{
        if(is_simple_rule(nt.rule))
                *current_component_context = nt.rule->alternatives.front()->group->components.front();
}

void inline_simple_visitor::visit(foundry::parse::regex&) { }
void inline_simple_visitor::visit(foundry::parse::group &)
{
        is_simple = false;
}

void inline_simple_visitor::visit(foundry::parse::root &r)
{
        for(auto &i : r.rules)
        {
                current_rule_context = &i;
                descend(i);
        }
        r.rules.remove_if(std::bind(std::mem_fun(&inline_simple_visitor::is_simple_rule), this, std::placeholders::_1));
}

void inline_simple_visitor::visit(foundry::parse::rule &r) { descend(r.alternatives); }
void inline_simple_visitor::visit(foundry::parse::alternative &a)
{
        for(auto &i : a.group->components)
        {
                current_component_context = &i;
                descend(i);
        }
}

bool inline_simple_visitor::is_simple_rule(rule_ptr &r)
{
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
