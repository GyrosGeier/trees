/* Copyright 2009 Simon Richter <Simon.Richter@hogyros.de>
 *
 * Released under the GNU General Public Licence version 3.
 */

#include "smartpointer_visitor.hpp"

namespace foundry {
namespace tree {

void smartpointer_visitor::visit(root &r)
{
    ast_root = &r;
    state = collect;
    descend(r.global_namespace);
    state = mark;
    descend(r.global_namespace);
}

void smartpointer_visitor::visit(include_node &)
{
    return;
}

void smartpointer_visitor::visit(namespace_node &n)
{
    descend(n.namespaces);
    descend(n.group);
}

void smartpointer_visitor::visit(group_node &n)
{
    if(state == collect)
        n.ns->node_types.insert(n.name);

    descend(n.groups);
    descend(n.default_members);
    descend(n.nodes);
}

void smartpointer_visitor::visit(node_node &n)
{
    if(state == collect)
        n.ns->node_types.insert(n.name);

    descend(n.members);
}

void smartpointer_visitor::visit(data_member_node &n)
{
    if(state == mark)
    {
        descend(n.type);
        if(is_node_type)
        {
            template_type_node_ptr nn = new template_type_node;
            nn->name = "boost::intrusive_ptr";
            nn->template_args.push_back(n.type);
            n.type = nn;
            include_node_ptr ni = new include_node;
            ni->name = "boost/intrusive_ptr.hpp";
            ast_root->includes.push_back(ni);
        }
    }
}

void smartpointer_visitor::visit(basic_type_node &n)
{
    is_node_type = (n.ns->node_types.find(n.name) != n.ns->node_types.end());
    if(is_node_type)
    {
        std::string ns;
        for(namespace_node_weak_ptr i = n.ns; i; i = i->parent)
            ns = i->name + "::" + ns;
        n.name = ns + n.name;
    }
}

void smartpointer_visitor::visit(reference_type_node &)
{
    is_node_type = false;
}

void smartpointer_visitor::visit(pointer_type_node &)
{
    is_node_type = false;
}

void smartpointer_visitor::visit(template_type_node &)
{
    is_node_type = false;
}

void smartpointer_visitor::visit(list_type_node &n)
{
    descend(n.type);
    if(is_node_type)
    {
        template_type_node_ptr nn = new template_type_node;
        nn->name = "boost::intrusive_ptr";
        nn->template_args.push_back(n.type);
        n.type = nn;
    }
    is_node_type = false;
}

}
}
