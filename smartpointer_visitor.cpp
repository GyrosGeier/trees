/* Copyright 2009 Simon Richter <Simon.Richter@hogyros.de>
 *
 * Released under the GNU General Public Licence version 3.
 */

#include "smartpointer_visitor.hpp"

namespace trees {
namespace tree {

void smartpointer_visitor::operator()(root_ptr const &r)
{
        ast_root = r;
        handle(r->global_namespace);
}

void smartpointer_visitor::handle(namespace_node_ptr const &n)
{
        for(auto const &i : n->namespaces)
                handle(i);
        if(n->group)
                handle(n->group);
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

void smartpointer_visitor::handle(node_node_ptr const &n)
{
        for(auto const &i : n->members)
                handle(i);
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
