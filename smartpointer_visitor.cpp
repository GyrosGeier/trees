/* Copyright 2009 Simon Richter <Simon.Richter@hogyros.de>
 *
 * Released under the GNU General Public Licence version 3.
 */

#include "smartpointer_visitor.hpp"

namespace trees {
namespace tree {

node_ptr smartpointer_visitor::visit(root &r)
{
        throw;
}

void smartpointer_visitor::operator()(root_ptr const &r)
{
        ast_root = r;
        handle(r->global_namespace);
}

node_ptr smartpointer_visitor::visit(include_node &i)
{
        return &i;
}

node_ptr smartpointer_visitor::visit(namespace_node &n)
{
        throw;
}

void smartpointer_visitor::handle(namespace_node_ptr const &n)
{
        for(auto const &i : n->namespaces)
                handle(i);
        if(n->group)
                handle(n->group);
}

node_ptr smartpointer_visitor::visit(group_node &n)
{
        throw;
}

void smartpointer_visitor::handle(group_node_ptr const &n)
{
        for(auto const &i : n->groups)
                handle(i);
        for(auto const &i : n->default_members)
                handle(i);
        for(auto const &i : n->nodes)
                handle(i);
}

node_ptr smartpointer_visitor::visit(node_node &n)
{
        throw;
}

void smartpointer_visitor::handle(node_node_ptr const &n)
{
        for(auto const &i : n->members)
                handle(i);
}

node_ptr smartpointer_visitor::visit(data_member_node &n)
{
        throw;
}

void smartpointer_visitor::handle(data_member_node_ptr const &n)
{
        descend(n->type);
}

type_node_ptr smartpointer_visitor::visit(group_type_node &n)
{
        return make_smartpointer(&n);
}

type_node_ptr smartpointer_visitor::visit(node_type_node &n)
{
        return make_smartpointer(&n);
}

type_node_ptr smartpointer_visitor::visit(basic_type_node &n)
{
        return &n;
}

type_node_ptr smartpointer_visitor::visit(reference_type_node &n)
{
        return &n;
}

type_node_ptr smartpointer_visitor::visit(pointer_type_node &n)
{
        return &n;
}

type_node_ptr smartpointer_visitor::visit(template_type_node &n)
{
        return &n;
}

type_node_ptr smartpointer_visitor::visit(list_type_node &n)
{
        descend(n.type);
        return &n;
}

type_node_ptr smartpointer_visitor::make_smartpointer(type_node_ptr const &n)
{
        template_type_node_ptr nn = new template_type_node;
        nn->name = "boost::intrusive_ptr";
        nn->template_args.push_back(n);
        include_node_ptr ni = new include_node;
        ni->name = "<boost/intrusive_ptr.hpp>";
        ast_root->includes.push_back(ni);
        return nn;
}

}
}
