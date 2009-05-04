#include "smartpointer_visitor.hpp"

namespace foundry {
namespace tree {

void smartpointer_visitor::visit(root &r)
{
    ast_root = &r;
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

    for(std::list<node_node_ptr>::iterator i = n.nodes.begin();
            i != n.nodes.end(); ++i)
        visit(**i);
}

void smartpointer_visitor::visit(node_node &n)
{
    for(std::list<data_member_node_ptr>::iterator i = n.members.begin();
            i != n.members.end(); ++i)
        visit(**i);
}

void smartpointer_visitor::visit(data_member_node &n)
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

void smartpointer_visitor::visit(basic_type_node &n)
{
    is_node_type = false;

    if(n.name == "node")
        is_node_type = true;
    else
        for(std::list<node_node_ptr>::iterator i = n.ns->nodes.begin();
                i != n.ns->nodes.end(); ++i)
            if(n.name == (**i).name)
            {
                is_node_type = true;
                break;
            }
}

void smartpointer_visitor::visit(reference_type_node &n)
{
    is_node_type = false;
}

void smartpointer_visitor::visit(pointer_type_node &n)
{
    is_node_type = false;
}

void smartpointer_visitor::visit(template_type_node &n)
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
