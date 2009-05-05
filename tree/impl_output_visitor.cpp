#include "impl_output_visitor.hpp"

namespace foundry {
namespace tree {

impl_output_visitor::impl_output_visitor(std::ostream &out) :
    out(out)
{
    return;
}

void impl_output_visitor::visit(root const &r)
{
    visit(*r.global_namespace);
}

void impl_output_visitor::visit(include_node const &)
{
    return;
}

void impl_output_visitor::visit(node_node const &n)
{
    for(group_node_weak_ptr i = n.group; i; i = i->parent)
    {
        if(i->has_visitor)
            out << "void " << n.name << "::apply(" << i->name << "_visitor &v)" << std::endl
                << "{" << std::endl
                << "    v.visit(*this);" << std::endl
                << "}" << std::endl;
        if(i->has_const_visitor)
            out << "void " << n.name << "::apply(" << i->name << "_const_visitor &v) const" << std::endl
                << "{" << std::endl
                << "    v.visit(*this);" << std::endl
                << "}" << std::endl;
    }
}

void impl_output_visitor::visit(namespace_node const &n)
{
    if(!n.name.empty())
        out << "namespace " << n.name << " {" << std::endl;

    for(std::list<namespace_node_ptr>::const_iterator i = n.namespaces.begin();
            i != n.namespaces.end(); ++i)
        visit(**i);

    if(n.group)
        visit(*n.group);

    if(!n.name.empty())
        out <<  "}" << std::endl;
}

void impl_output_visitor::visit(group_node const &n)
{
    for(std::list<group_node_ptr>::const_iterator i = n.groups.begin();
            i != n.groups.end(); ++i)
        visit(**i);
    for(std::list<node_node_ptr>::const_iterator i = n.nodes.begin();
            i != n.nodes.end(); ++i)
        visit(**i);
}

void impl_output_visitor::visit(basic_type_node const &)
{
    return;
}

void impl_output_visitor::visit(reference_type_node const &)
{
    return;
}

void impl_output_visitor::visit(pointer_type_node const &)
{
    return;
}

void impl_output_visitor::visit(template_type_node const &)
{
    return;
}

void impl_output_visitor::visit(data_member_node const &)
{
    return;
}

void impl_output_visitor::visit(list_type_node const &)
{
    return;
}

}
}
