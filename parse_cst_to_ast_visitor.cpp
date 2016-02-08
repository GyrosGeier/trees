#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "parse_cst_to_ast_visitor.h"

#include "errors.h"

#include <sstream>

namespace trees {
namespace parse {

cst_to_ast_visitor::cst_to_ast_visitor() :
        rt(new root)
{
        return;
}

cst_to_ast_visitor::~cst_to_ast_visitor() throw()
{
        return;
}

void cst_to_ast_visitor::visit(cst::start const &s)
{
        descend(s._1);
        descend(s._2);
}

void cst_to_ast_visitor::visit(cst::directives_chain const &d)
{
        std::string::size_type const space = d._1.find(' ');
        if(space != d._1.npos)
        {
                std::string const cmd(d._1, 1, space-1);
                std::string const arg(d._1, space +1);
                if(cmd == "namespace")
                        rt->ns = arg;
                else
                        throw unhandled_directive(d._1);
        }
        else
                throw unhandled_directive(d._1);
        descend(d._2);
}

void cst_to_ast_visitor::visit(cst::end_of_directives const &)
{
        return;
}

void cst_to_ast_visitor::visit(cst::rules_chain const &r)
{
        descend(r._1);
        descend(r._2);
}

void cst_to_ast_visitor::visit(cst::end_of_rules const &)
{
        return;
}

void cst_to_ast_visitor::visit(cst::rule const &r)
{
        current_rule = new rule;
        current_rule->name = r._1;
        descend(r._2);
        if(current_rule->alternatives.size() != 1)
        {
                unsigned int n = 1;
                for(auto i : current_rule->alternatives)
                {
                        if(i->name == r._1)
                        {
                                std::ostringstream os;
                                os << i->name << "_" << n;
                                i->name = os.str();
                        }
                        ++n;
                }
        }

        rt->rules.push_back(current_rule);
        current_rule = 0;
}

void cst_to_ast_visitor::visit(cst::alternatives const &a)
{
        current_alternative = new alternative;
        current_alternative->group = new group;
        current_group = current_alternative->group;
        current_group->rep = repeat_none;
        descend(a._1);
        descend(a._2);
}

void cst_to_ast_visitor::visit(cst::more_alternatives const &t)
{
        current_rule->alternatives.push_back(current_alternative);
        current_alternative = new alternative;
        current_alternative->group = new group;
        current_group = current_alternative->group;
        current_group->rep = repeat_none;
        descend(t._1);
}

void cst_to_ast_visitor::visit(cst::end_of_alternatives const &)
{
        current_rule->alternatives.push_back(current_alternative);
}

void cst_to_ast_visitor::visit(cst::unnamed_alternative const &a)
{
        current_alternative->name = current_rule->name;
        descend(a._1);
}

void cst_to_ast_visitor::visit(cst::named_alternative const &a)
{
        current_alternative->name = a._1;
        descend(a._2);
}

void cst_to_ast_visitor::visit(cst::components const &c)
{
        descend(c._1);
}

void cst_to_ast_visitor::visit(cst::components_1_chain const &c)
{
        descend(c._1);
        descend(c._2);
}

void cst_to_ast_visitor::visit(cst::end_of_components_1 const &)
{
        return;
}

void cst_to_ast_visitor::visit(cst::components_1_elem const &c)
{
        // Resolve repetition first
        descend(c._2);
        if(current_repeat != repeat_none)
        {
                group_ptr ng = new group;
                ng->rep = current_repeat;
                current_repeat = repeat_none;
                current_group->components.push_back(ng);

                group_ptr stack = current_group;
                current_group = ng;
                descend(c._1);
                current_group = stack;
        }
        else
        {
                descend(c._1);
        }
}

void cst_to_ast_visitor::visit(cst::no_repetition const &)
{
        current_repeat = repeat_none;
}

void cst_to_ast_visitor::visit(cst::zero_or_one const &)
{
        current_repeat = repeat_zero_or_one;
}

void cst_to_ast_visitor::visit(cst::one_or_more const &)
{
        current_repeat = repeat_one_or_more;
}

void cst_to_ast_visitor::visit(cst::zero_or_more const &)
{
        current_repeat = repeat_zero_or_more;
}

void cst_to_ast_visitor::visit(cst::symbol const &c)
{
        unresolved_symbol_ptr u = new unresolved_symbol;
        u->name = c._1;
        current_group->components.push_back(u);
}

void cst_to_ast_visitor::visit(cst::literal const &c)
{
        string_literal_ptr sl = new string_literal;
        sl->text = c._1;
        current_group->components.push_back(sl);
}

void cst_to_ast_visitor::visit(cst::regex const &c)
{
        regex_ptr rx = new regex;
        rx->text = c._1;
        current_group->components.push_back(rx);
}

void cst_to_ast_visitor::visit(cst::group const &g)
{
        group_ptr ng = new group;
        ng->rep = current_repeat;
        current_group->components.push_back(ng);

        group_ptr stack = current_group;
        current_group = ng;
        descend(g._1);
        current_group = stack;
}

}
}
