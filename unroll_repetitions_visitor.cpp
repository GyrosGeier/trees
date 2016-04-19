#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "unroll_repetitions_visitor.h"

#include "errors.h"

#include <iostream>
#include <sstream>

namespace trees {
namespace parse {

component_ptr unroll_repetitions_visitor::visit(regex_ptr r) { return r; }
component_ptr unroll_repetitions_visitor::visit(string_literal_ptr s) { return s; }

component_ptr unroll_repetitions_visitor::visit(unresolved_symbol_ptr )
{
        throw internal_error("Unresolved symbol found during unrolling");
}

component_ptr unroll_repetitions_visitor::visit(terminal_ptr t) { return t; }
component_ptr unroll_repetitions_visitor::visit(nonterminal_ptr n) { return n; }
component_ptr unroll_repetitions_visitor::visit(group_ptr g)
{
        if(!current_group)
        {
                // toplevel group in alternative
                if(verbose)
                        std::cerr << "Handling toplevel of alternative " << current_alternative->name << std::endl;
                if(g->rep != repeat_none)
                        throw;
                group_ptr group_stack = current_group;
                current_group = g;
                unsigned int count = 0;
                for(auto &i : g->components)
                {
                        ++count;
                        std::ostringstream os;
                        os << current_alternative->name << "_" << count;
                        current_name = os.str();
                        current_context = &i;
                        i->apply(*this);
                }
                current_group = group_stack;
                return g;
        }

        std::string generated_rule = current_name;

        switch(g->rep)
        {
        case repeat_none:
                {
                        // simple grouping, do nothing
                        group_ptr group_stack = current_group;
                        current_group = g;
                        unsigned int count = 0;
                        for(auto &i : g->components)
                        {
                                ++count;
                                std::ostringstream os;
                                os << current_alternative->name << "__" << count;
                                current_name = os.str();
                                current_context = &i;
                                descend(i);
                        }
                        current_group = group_stack;
                }
                break;

        case repeat_zero_or_one:
                {
                        rule_ptr nr = new rule;
                        nr->name = generated_rule;
                        generated_rules.push_back(nr);
                        
                        alternative_ptr alt_present = new alternative;
                        nr->alternatives.push_back(alt_present);
                        alt_present->name = generated_rule + "_present";
                        alt_present->group = g;
                        alt_present->group->rep = repeat_none;

                        alternative_ptr alt_absent = new alternative;
                        nr->alternatives.push_back(alt_absent);
                        alt_absent->name = generated_rule + "_absent";
                        alt_absent->group = new group;
                        alt_absent->group->rep = repeat_none;

                        nonterminal_ptr nt = new nonterminal;
                        nt->name = nr->name;
                        nt->rule = nr;

                        *current_context = nt;
                }
                break;

        case repeat_one_or_more:
        case repeat_zero_or_more:
                {
                        rule_ptr nr_elem = new rule;
                        nr_elem->name = generated_rule + "_elem";
                        generated_rules.push_back(nr_elem);

                        alternative_ptr elem_alt = new alternative;
                        nr_elem->alternatives.push_back(elem_alt);
                        elem_alt->name = nr_elem->name;
                        elem_alt->group = g;
                        elem_alt->group->rep = repeat_none;

                        rule_ptr nr_list = new rule;
                        generated_rules.push_back(nr_list);
                        nr_list->name = generated_rule + "_list";

                        alternative_ptr alt_chain = new alternative;
                        nr_list->alternatives.push_back(alt_chain);
                        alt_chain->name = generated_rule + "_chain";
                        alt_chain->group = new group;
                        alt_chain->group->rep = repeat_none;

                        alternative_ptr alt_end = new alternative;
                        nr_list->alternatives.push_back(alt_end);
                        alt_end->name = "end_of_" + generated_rule;
                        alt_end->group = new group;
                        alt_end->group->rep = repeat_none;

                        nonterminal_ptr nt_elem = new nonterminal;
                        alt_chain->group->components.push_back(nt_elem);
                        if(g->rep == repeat_one_or_more)
                                alt_end->group->components.push_back(nt_elem);
                        nt_elem->name = nr_elem->name;
                        nt_elem->rule = nr_elem;

                        nonterminal_ptr nt_chain = new nonterminal;
                        alt_chain->group->components.push_back(nt_chain);
                        nt_chain->name = nr_list->name;
                        nt_chain->rule = nr_list;

                        *current_context = nt_chain;
                }
                break;
        }
        return *current_context;
}

void unroll_repetitions_visitor::operator()(root_ptr r)
{
        do
        {
                r->rules.splice(r->rules.end(), generated_rules);
                for(auto &i : r->rules)
                        visit(i);
        }
        while(generated_rules.size());
}

void unroll_repetitions_visitor::visit(rule_ptr r)
{
        for(auto &i : r->alternatives)
                visit(i);
}

void unroll_repetitions_visitor::visit(alternative_ptr a)
{
        current_alternative = a;
        current_group = 0;
        visit(a->group);
}

}
}
