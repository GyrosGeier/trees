/* Copyright 2009 Simon Richter <Simon.Richter@hogyros.de>
 *
 * Released under the GNU General Public Licence version 3.
 */

#include "bison_to_ast_visitor.hpp"

#include <sstream>

namespace trees {
namespace tree {

bison_to_ast_visitor::bison_to_ast_visitor(void)
{
        ast = std::make_shared<root>();
        ast->global_namespace = std::make_shared<namespace_node>();
        ast->global_namespace->parent.reset();
        include_node_ptr nn = std::make_shared<include_node>();
        nn->name = "<string>";
        ast->includes.push_back(nn);
        current_namespace = ast->global_namespace;
        current_namespace->uses_lists = false;
}

void bison_to_ast_visitor::visit(bison::start const &s)
{
        /* rules */
        if(!current_namespace->group)
        {
                current_group = std::make_shared<group_node>();
                current_group->name = "node";
                current_group->ns = current_namespace;
                current_group->parent.reset();
                current_group->has_const_visitor = true;
                current_group->has_visitor = false;
                current_group->smartpointer = strict_ownership;
                current_namespace->group = current_group;
        }
        descend(s._1);
        for(std::list<basic_type_node_ptr>::iterator i = unresolved.begin();
                        i != unresolved.end(); ++i)
                (**i).name = "std::string";
}

void bison_to_ast_visitor::visit(bison::empty_rules const &)
{
        /* empty */
}

void bison_to_ast_visitor::visit(bison::chained_rules const &r)
{
        /* rules rule */
        descend(r._1);
        descend(r._2);
}

void bison_to_ast_visitor::visit(bison::rule const &r)
{
        /* IDENTIFIER_COLON alternatives */
        current_identifier = r._1;
        nonterminals.insert(r._1);
        for(std::list<basic_type_node_ptr>::iterator i = unresolved.begin();
                        i != unresolved.end();)
        {
                if((**i).name == r._1)
                        i = unresolved.erase(i);
                else
                        ++i;
        }
        current_count = 0;
        current_group = current_namespace->group;
        descend(r._2);
}

void bison_to_ast_visitor::visit(bison::unnamed_alternative const &a)
{
        /* components */
        current_node = std::make_shared<node_node>();
        current_node->ns = current_namespace;
        current_node->group = current_group;
        if(current_count == 0)
                current_node->name = current_identifier;
        else
        {
                std::ostringstream str;
                str << current_identifier;
                str << "_" << current_count++;
                current_node->name = str.str();
        }
        current_node->smartpointer = strict_ownership;
        current_group->nodes.push_back(current_node);
        descend(a._1);
}

void bison_to_ast_visitor::visit(bison::named_alternative const &a)
{
        /* NAME_HINT components */
        current_node = std::make_shared<node_node>();
        current_node->ns = current_namespace;
        current_node->group = current_group;
        current_node->name = a._1;
        current_node->smartpointer = strict_ownership;
        current_group->nodes.push_back(current_node);
        descend(a._2);
}

void bison_to_ast_visitor::visit(bison::single_alternative const &a)
{
        /* alternative */
        descend(a._1);
}

void bison_to_ast_visitor::visit(bison::chained_alternatives const &a)
{
        /* alternatives "|" alternative */
        if(current_count == 0)
        {
                current_count = 1;
                current_group = std::make_shared<group_node>();
                current_group->name = current_identifier;
                current_group->ns = current_namespace;
                current_group->parent = current_namespace->group;
                current_group->has_const_visitor = false;
                current_group->has_visitor = false;
                current_group->smartpointer = strict_ownership;
                current_namespace->group->groups.push_back(current_group);
        }
        descend(a._1);
        descend(a._2);
}

void bison_to_ast_visitor::visit(bison::terminated_alternatives const &a)
{
        /* alternatives ";" */
        descend(a._1);
}

void bison_to_ast_visitor::visit(bison::empty_components const &)
{
        /* empty */
}

void bison_to_ast_visitor::visit(bison::chained_components const &c)
{
        /* components component */
        descend(c._1);
        descend(c._2);
}

void bison_to_ast_visitor::visit(bison::symbol const &c)
{
        /* IDENTIFIER */
        data_member_node_ptr nn = std::make_shared<data_member_node>();
        std::ostringstream str;
        str << "_" << current_node->members.size() + 1;
        nn->name = str.str();
        nn->needs_init = true;
        basic_type_node_ptr nt = std::make_shared<basic_type_node>();
        nt->name = c._1;
        if(nonterminals.find(c._1) == nonterminals.end())
                unresolved.push_back(nt);
        nt->ns = current_namespace;
        nt->is_const = false;
        nt->is_volatile = false;
        nn->type = nt;
        current_node->members.push_back(nn);
} 

void bison_to_ast_visitor::visit(bison::literal const &)
{
        /* STRING */
        return;
}

void bison_to_ast_visitor::push_initial_namespace(std::string const &ns)
{
        namespace_node_ptr nn = std::make_shared<namespace_node>();
        nn->name = ns;
        nn->parent = current_namespace;
        current_namespace->namespaces.push_back(nn);
        current_namespace = nn;
        current_namespace->uses_lists = false;
}

}
}
