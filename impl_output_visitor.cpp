/* Copyright 2009 Simon Richter <Simon.Richter@hogyros.de>
 *
 * Released under the GNU General Public Licence version 3.
 */

#include "impl_output_visitor.hpp"

namespace trees {
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
        auto group = n.group.lock();

        for(group_node_ptr i = group; i; i = i->parent.lock())
        {
                if(i->has_visitor)
                {
                        out << i->name << "_ptr " << n.name << "::apply(" << i->name << "_visitor &v)" << std::endl
                                << "{" << std::endl;
                        switch(i->smartpointer)
                        {
                        case strict_ownership:
                        case intrusive:
                                out << "        return v.visit(this);" << std::endl;
                                break;
                        case shared_ownership:
                                out << "        return v.visit(shared_from_this());" << std::endl;
                                break;
                        }
                        out << "}" << std::endl;
                }
                if(i->has_const_visitor)
                        out << "void " << n.name << "::apply(" << i->name << "_const_visitor &v) const" << std::endl
                                << "{" << std::endl
                                << "        v.visit(*this);" << std::endl
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

void impl_output_visitor::visit(group_type_node const &)
{
        return;
}

void impl_output_visitor::visit(node_type_node const &)
{
        return;
}

void impl_output_visitor::visit(basic_type_node const &)
{
        return;
}

void impl_output_visitor::visit(rvalue_reference_type_node const &)
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
