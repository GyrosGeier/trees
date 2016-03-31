#include "mark_nodes_visitor.hpp"

namespace trees {
namespace tree {

void mark_nodes_visitor::operator()(root_ptr const &r)
{
        collecting = true;
        traverse(r->global_namespace);
        collecting = false;
        traverse(r->global_namespace);
}

void mark_nodes_visitor::traverse(namespace_node_ptr const &n)
{
        for(auto const &i : n->namespaces)
                traverse(i);
        if(n->group)
                handle(n->group);
}

type_node_ptr mark_nodes_visitor::visit(group_node &n)
{
        throw;
}

void mark_nodes_visitor::handle(group_node_ptr const &n)
{
        if(collecting)
                known_types[n->ns][n->name] = n;
        else
                for(auto const &i : n->default_members)
                        handle(i);

        for(auto const &i : n->groups)
                handle(i);
        for(auto const &i : n->nodes)
                handle(i);
}

type_node_ptr mark_nodes_visitor::visit(node_node &n)
{
        throw;
}

void mark_nodes_visitor::handle(node_node_ptr const &n)
{
        if(collecting)
                known_types[n->ns][n->name] = n;
        else
                for(auto const &i : n->members)
                        handle(i);
}

void mark_nodes_visitor::handle(data_member_node_ptr const &n)
{
        descend(n->type);
}

type_node_ptr mark_nodes_visitor::visit(basic_type_node &n)
{
        auto i = known_types.find(n.ns);
        if(i == known_types.end())
        {
                n.is_node = false;
                return &n;
        }
        auto j = i->second.find(n.name);
        if(j == i->second.end())
        {
                n.is_node = false;
                return &n;
        }
        n.is_node = true;
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
