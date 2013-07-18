#include "mark_nodes_visitor.hpp"

namespace foundry {
namespace tree {

void mark_nodes_visitor::visit(basic_type_node &n)
{
        n.is_node = (n.ns->node_types.find(n.name) != n.ns->node_types.end());
}

void mark_nodes_visitor::visit(reference_type_node &n)
{
        descend(n.type);
}

void mark_nodes_visitor::visit(pointer_type_node &n)
{
        descend(n.type);
}

void mark_nodes_visitor::visit(template_type_node &n)
{
        descend(n.template_args);
}

void mark_nodes_visitor::visit(list_type_node &n)
{
        descend(n.type);
}

void mark_nodes_visitor::visit(root &r)
{
        collecting = true;
        descend(r.global_namespace);
        collecting = false;
        descend(r.global_namespace);
}

void mark_nodes_visitor::visit(include_node&) { }
void mark_nodes_visitor::visit(namespace_node &n)
{
        descend(n.namespaces);
        descend(n.group);
}

void mark_nodes_visitor::visit(group_node &n)
{
        if(collecting)
                n.ns->node_types.insert(n.name);
        else
                descend(n.default_members);
        descend(n.groups);
        descend(n.nodes);
}

void mark_nodes_visitor::visit(node_node &n)
{
        if(collecting)
                n.ns->node_types.insert(n.name);
        else
                descend(n.members);
}

void mark_nodes_visitor::visit(data_member_node &n)
{
        descend(n.type);
}

}
}
