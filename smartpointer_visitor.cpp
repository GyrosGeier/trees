/* Copyright 2009 Simon Richter <Simon.Richter@hogyros.de>
 *
 * Released under the GNU General Public Licence version 3.
 */

#include "smartpointer_visitor.hpp"

namespace trees {
namespace tree {

node_ptr smartpointer_visitor::visit(root &r)
{
        throw;
}

void smartpointer_visitor::operator()(root_ptr const &r)
{
        ast_root = r;
        descend(r->global_namespace);
}

node_ptr smartpointer_visitor::visit(include_node &i)
{
        return &i;
}

node_ptr smartpointer_visitor::visit(namespace_node &n)
{
        descend(n.namespaces);
        descend(n.group);
        return &n;
}

type_node_ptr smartpointer_visitor::visit(group_node &n)
{
        descend(n.groups);
        descend(n.default_members);
        descend(n.nodes);
        return &n;
}

type_node_ptr smartpointer_visitor::visit(node_node &n)
{
        descend(n.members);
        return &n;
}

node_ptr smartpointer_visitor::visit(data_member_node &n)
{
        descend(n.type);
        if(is_node_type)
        {
                template_type_node_ptr nn = new template_type_node;
                nn->name = "boost::intrusive_ptr";
                nn->template_args.push_back(n.type);
                n.type = nn;
                include_node_ptr ni = new include_node;
                ni->name = "<boost/intrusive_ptr.hpp>";
                ast_root->includes.push_back(ni);
        }
        return &n;
}

type_node_ptr smartpointer_visitor::visit(basic_type_node &n)
{
        is_node_type = n.is_node;
        if(is_node_type)
        {
                std::string ns;
                for(namespace_node_ptr i = n.ns; i; i = i->parent)
                        ns = i->name + "::" + ns;
                n.name = ns + n.name;
        }
        return &n;
}

type_node_ptr smartpointer_visitor::visit(reference_type_node &n)
{
        is_node_type = false;
        return &n;
}

type_node_ptr smartpointer_visitor::visit(pointer_type_node &n)
{
        is_node_type = false;
        return &n;
}

type_node_ptr smartpointer_visitor::visit(template_type_node &n)
{
        is_node_type = false;
        return &n;
}

type_node_ptr smartpointer_visitor::visit(list_type_node &n)
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
        return &n;
}

}
}
