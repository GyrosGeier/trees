/* Copyright 2009 Simon Richter <Simon.Richter@hogyros.de>
 *
 * Released under the GNU General Public Licence version 3.
 */

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
    descend(r.global_namespace);
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

    descend(n.namespaces);
    descend(n.group);

    if(!n.name.empty())
        out <<  "}" << std::endl;
}

void impl_output_visitor::visit(group_node const &n)
{
    descend(n.groups);
    descend(n.nodes);
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
