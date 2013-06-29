#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "cst_to_ast_visitor.h"

namespace foundry {
namespace parse {

cst_to_ast_visitor::cst_to_ast_visitor()
{
        return;
}

cst_to_ast_visitor::~cst_to_ast_visitor() throw()
{
        return;
}

void cst_to_ast_visitor::visit(cst::start const &s)
{
        if(!rt)
                rt = new root;
        descend(s._1);
        descend(s._2);
}

void cst_to_ast_visitor::visit(cst::directives_1 const &d)
{
        std::string::size_type const space = d._1.find(' ');
        if(space != d._1.npos)
        {
                std::string const cmd(d._1, 1, space-1);
                std::string const arg(d._1, space +1);
                if(cmd == "namespace")
                        rt->ns = arg;
                else
                        throw;
        }
        else
                throw;
        descend(d._2);
}

void cst_to_ast_visitor::visit(cst::directives_2 const &)
{
        return;
}

void cst_to_ast_visitor::visit(cst::rules_1 const &r)
{
        descend(r._1);
        descend(r._2);
}

void cst_to_ast_visitor::visit(cst::rules_2 const &)
{
        return;
}

void cst_to_ast_visitor::visit(cst::rule const &r)
{
        current_rule = new rule;
        current_rule->name = r._1;
        descend(r._2);
        rt->rules.push_back(current_rule);
        current_rule = 0;
}

void cst_to_ast_visitor::visit(cst::alternatives const &a)
{
        current_alternative = new alternative;
        descend(a._1);
        descend(a._2);
}

void cst_to_ast_visitor::visit(cst::alternatives_tail_1 const &t)
{
        current_rule->alternatives.push_back(current_alternative);
        current_alternative = new alternative;
        descend(t._1);
}

void cst_to_ast_visitor::visit(cst::alternatives_tail_2 const &)
{
        current_rule->alternatives.push_back(current_alternative);
}

void cst_to_ast_visitor::visit(cst::alternative_1 const &a)
{
        descend(a._1);
}

void cst_to_ast_visitor::visit(cst::alternative_2 const &a)
{
        descend(a._2);
}

void cst_to_ast_visitor::visit(cst::components_1 const &c)
{
        descend(c._1);
        descend(c._2);
}

void cst_to_ast_visitor::visit(cst::components_2 const &)
{
        return;
}

void cst_to_ast_visitor::visit(cst::component_1 const &c)
{
        unresolved_symbol_ptr u = new unresolved_symbol;
        u->name = c._1;
        current_alternative->components.push_back(u);
}

void cst_to_ast_visitor::visit(cst::component_2 const &c)
{
        string_literal_ptr sl = new string_literal;
        sl->text = c._1;
        current_alternative->components.push_back(sl);
}

}
}
