#include "smartpointer_visitor.hpp"

namespace foundry {
namespace tree {

void smartpointer_visitor::visit(root &r)
{
    ast_root = &r;
    state = collect;
    visit(*r.global_namespace);
    state = mark;
    visit(*r.global_namespace);
}

void smartpointer_visitor::visit(include_node &)
{
    return;
}

void smartpointer_visitor::visit(namespace_node &n)
{
    for(std::list<namespace_node_ptr>::iterator i = n.namespaces.begin();
            i != n.namespaces.end(); ++i)
        visit(**i);

    if(n.group)
        visit(*n.group);
}

void smartpointer_visitor::visit(group_node &n)
{
    if(state == collect)
        n.ns->node_types.insert(n.name);

    for(std::list<group_node_ptr>::iterator i = n.groups.begin();
            i != n.groups.end(); ++i)
        visit(**i);
    for(std::list<node_node_ptr>::iterator i = n.nodes.begin();
            i != n.nodes.end(); ++i)
        visit(**i);
}

void smartpointer_visitor::visit(node_node &n)
{
    if(state == collect)
        n.ns->node_types.insert(n.name);

    for(std::list<data_member_node_ptr>::iterator i = n.members.begin();
            i != n.members.end(); ++i)
        visit(**i);
}

void smartpointer_visitor::visit(data_member_node &n)
{
    if(state == mark)
    {
        n.type->apply(*this);
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
    n.type->apply(*this);
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
