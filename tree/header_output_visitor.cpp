#include "header_output_visitor.hpp"

namespace foundry {
namespace tree {

header_output_visitor::header_output_visitor(std::ostream &out) :
    out(out)
{
    return;
}

void header_output_visitor::visit(root const &r)
{
    for(std::list<include_node_ptr>::const_iterator i = r.includes.begin();
            i != r.includes.end(); ++i)
        visit(**i);
    visit(*r.global_namespace);
}

void header_output_visitor::visit(include_node const &n)
{
    out << "#include <" << n.name << ">" << std::endl;
}

void header_output_visitor::visit(namespace_node const &n)
{
    if(n.name.empty())
        out << "#include <boost/intrusive_ptr.hpp>" << std::endl
            << "#include <list>" << std::endl;
    else
        out << "namespace " << n.name << " {" << std::endl;

    for(std::list<namespace_node_ptr>::const_iterator i = n.namespaces.begin(); i != n.namespaces.end(); ++i)
        visit(**i);

    for(std::list<node_node_ptr>::const_iterator i = n.nodes.begin(); i != n.nodes.end(); ++i)
        out << "struct " << (**i).name << ";" << std::endl
            << "typedef boost::intrusive_ptr<" << (**i).name << "> " << (**i).name << "_ptr;" << std::endl
            << "typedef " << (**i).name << " *" << (**i).name << "_weak_ptr;" << std::endl;

    if(n.has_nodes)
    {
        if(n.has_visitor)
            out << "class visitor;" << std::endl;
        if(n.has_const_visitor)
            out << "class const_visitor;" << std::endl;
        out << "struct node {" << std::endl
            << "    node(void) throw() : refcount(0) { }" << std::endl
            << "    virtual ~node(void) throw() { }" << std::endl;
        if(n.has_visitor)
            out << "    virtual void apply(visitor &) = 0;" << std::endl;
        if(n.has_const_visitor)
            out << "    virtual void apply(const_visitor &) const = 0;" << std::endl;
        out << "    unsigned int refcount;" << std::endl
            << "};" << std::endl
            << "typedef boost::intrusive_ptr<node> node_ptr;" << std::endl
            << "typedef node *node_weak_ptr;" << std::endl
            << "inline void intrusive_ptr_add_ref(node *n) { ++n->refcount; }" << std::endl
            << "inline void intrusive_ptr_release(node *n) { if(!--n->refcount) delete n; }" << std::endl;
    }

    for(std::list<node_node_ptr>::const_iterator i = n.nodes.begin(); i != n.nodes.end(); ++i)
        visit(**i);

    if(n.has_visitor)
    {
        out << "class visitor" << std::endl
            << "{" << std::endl
            << "public:" << std::endl
            << "    virtual ~visitor(void) throw() { }" << std::endl;
        for(std::list<node_node_ptr>::const_iterator i = n.nodes.begin(); i != n.nodes.end(); ++i)
            out << "    virtual void visit(" << (**i).name << " &) = 0;" << std::endl;
        out << "};" << std::endl;
    }

    if(n.has_const_visitor)
    {
        out << "class const_visitor" << std::endl
            << "{" << std::endl
            << "public:" << std::endl
            << "    virtual ~const_visitor(void) throw() { }" << std::endl;
        for(std::list<node_node_ptr>::const_iterator i = n.nodes.begin(); i != n.nodes.end(); ++i)
            out << "    virtual void visit(" << (**i).name << " const &) = 0;" << std::endl;
        out << "};" << std::endl;
    }

    if(!n.name.empty())
        out << "}" << std::endl;
}

void header_output_visitor::visit(node_node const &n)
{
    out << "struct " << n.name << " : node" << std::endl
        << "{" << std::endl
        << "    " << n.name << "(void) throw() :" << std::endl
        << "        ";
    for(std::list<data_member_node_ptr>::const_iterator i = n.members.begin();
            i != n.members.end();)
    {
        out << (**i).name << "()";
        ++i;
        if(i == n.members.end())
            break;
        out << ", ";
    }
    out << " { }" << std::endl;

    out << "    virtual ~" << n.name << "(void) throw() { }" << std::endl;

    if(n.ns->has_visitor)
        out << "    virtual void apply(visitor &);" << std::endl;
    if(n.ns->has_const_visitor)
        out << "    virtual void apply(const_visitor &) const;" << std::endl;

    for(std::list<data_member_node_ptr>::const_iterator i = n.members.begin(); i!= n.members.end(); ++i)
        (**i).apply(*this);

    out << "};" << std::endl;
}

void header_output_visitor::visit(basic_type_node const &n)
{
    out << n.name;
    if(n.is_const)
        out << " const";
    if(n.is_volatile)
        out << " volatile";
}

void header_output_visitor::visit(reference_type_node const &n)
{
    n.type->apply(*this);
    out << "&";
}

void header_output_visitor::visit(pointer_type_node const &n)
{
    n.type->apply(*this);
    out << "*";
    if(n.is_const)
        out << " const";
    if(n.is_volatile)
        out << " volatile";
}

void header_output_visitor::visit(template_type_node const &n)
{
    out << n.name << "<";
    for(std::list<node_ptr>::const_iterator i = n.template_args.begin(); i!= n.template_args.end(); ++i)
        (**i).apply(*this);
    out << "> ";
}

void header_output_visitor::visit(data_member_node const &n)
{
    out << "    ";
    n.type->apply(*this);
    out << " " << n.name << ";" << std::endl;
}

void header_output_visitor::visit(list_type_node const &n)
{
    out << "std::list<";
    n.type->apply(*this);
    out << "> ";
}

}
}
