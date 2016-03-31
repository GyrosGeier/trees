#include "mark_nodes_visitor.hpp"

namespace trees {
namespace tree {

node_ptr mark_nodes_visitor::visit(root &r)
{
        throw;
}

void mark_nodes_visitor::operator()(root_ptr const &r)
{
        collecting = true;
        traverse(r->global_namespace);
        collecting = false;
        traverse(r->global_namespace);
}

node_ptr mark_nodes_visitor::visit(include_node &i)
{
        return &i;
}

node_ptr mark_nodes_visitor::visit(namespace_node &n)
{
        throw;
}

void mark_nodes_visitor::traverse(namespace_node_ptr const &n)
{
        for(auto const &i : n->namespaces)
                traverse(i);
        descend(n->group);
}

type_node_ptr mark_nodes_visitor::visit(group_node &n)
{
        if(collecting)
                n.ns->node_types.insert(n.name);
        else
                descend(n.default_members);
        descend(n.groups);
        descend(n.nodes);
        return &n;
}

type_node_ptr mark_nodes_visitor::visit(node_node &n)
{
        if(collecting)
                n.ns->node_types.insert(n.name);
        else
                descend(n.members);
        return &n;
}

node_ptr mark_nodes_visitor::visit(data_member_node &n)
{
        descend(n.type);
        return &n;
}

type_node_ptr mark_nodes_visitor::visit(basic_type_node &n)
{
        n.is_node = (n.ns->node_types.find(n.name) != n.ns->node_types.end());
        return &n;
}

type_node_ptr mark_nodes_visitor::visit(reference_type_node &n)
{
        descend(n.type);
        return &n;
}

type_node_ptr mark_nodes_visitor::visit(pointer_type_node &n)
{
        descend(n.type);
        return &n;
}

type_node_ptr mark_nodes_visitor::visit(template_type_node &n)
{
        descend(n.template_args);
        return &n;
}

type_node_ptr mark_nodes_visitor::visit(list_type_node &n)
{
        descend(n.type);
        return &n;
}

}
}
