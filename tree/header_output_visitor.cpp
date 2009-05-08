#include "header_output_visitor.hpp"

namespace foundry {
namespace tree {

header_output_visitor::header_output_visitor(std::ostream &out) :
    out(out), state(fwddecl)
{
    return;
}

void header_output_visitor::visit(root const &r)
{
    descend(r.includes);
    out << "#include <boost/intrusive_ptr.hpp>" << std::endl
        << "#include <list>" << std::endl;
    state = fwddecl;
    descend(r.global_namespace);
    state = decl;
    descend(r.global_namespace);
}

void header_output_visitor::visit(include_node const &n)
{
    out << "#include <" << n.name << ">" << std::endl;
}

void header_output_visitor::visit(namespace_node const &n)
{
    if(!n.name.empty())
        out << "namespace " << n.name << " {" << std::endl;

    descend(n.namespaces);

    descend(n.group);
    if(!n.name.empty())
        out << "}" << std::endl;
}

void header_output_visitor::visit(group_node const &n)
{
    switch(state)
    {
    case fwddecl:
        out << "struct " << n.name << ";" << std::endl
            << "typedef boost::intrusive_ptr<" << n.name << "> " << n.name << "_ptr;" << std::endl
            << "typedef " << n.name << " *" << n.name << "_weak_ptr;" << std::endl;
        if(n.has_const_visitor)
            out << "struct " << n.name << "_const_visitor;" << std::endl;
        if(n.has_visitor)
            out << "struct " << n.name << "_visitor;" << std::endl;
        break;
    case decl:
        out << "struct " << n.name;
        if(n.parent)
            out << " : " << n.parent->name;
        out << " {" << std::endl
            << "    " << n.name << "(void) throw()";
        if(!n.parent)
            out << " : refcount(0)";
        out << " { }" << std::endl
            << "    virtual ~" << n.name << "(void) throw() { }" << std::endl;
        if(n.has_visitor)
            out << "    virtual void apply(" << n.name << "_visitor &) = 0;" << std::endl;
        if(n.has_const_visitor)
            out << "    virtual void apply(" << n.name << "_const_visitor &) const = 0;" << std::endl;
        if(!n.parent)
            out << "    unsigned int refcount;" << std::endl;
        descend(n.default_members);
        out << "};" << std::endl;
        if(!n.parent)
            out << "inline void intrusive_ptr_add_ref(" << n.name << " *n) { ++n->refcount; }" << std::endl
                << "inline void intrusive_ptr_release(" << n.name << " *n) { if(!--n->refcount) delete n; }" << std::endl;
        if(n.has_visitor)
        {
            out << "class " << n.name << "_visitor" << std::endl
                << "{" << std::endl
                << "public:" << std::endl
                << "    virtual ~" << n.name << "_visitor(void) throw() { }" << std::endl
                << "    inline void descend(" << n.name << " &n) { n.apply(*this); }" << std::endl
                << "    template<typename T>" << std::endl
                << "    inline void descend(boost::intrusive_ptr<T> const &p) { if(p) descend(*p); }" << std::endl;
            if(n.ns->uses_lists)
                out << "    template<typename T, typename Alloc>" << std::endl
                    << "    inline void descend(std::list<T, Alloc> &l)" << std::endl
                    << "    {" << std::endl
                    << "        for(typename std::list<T, Alloc>::iterator i = l.begin(); i != l.end(); ++i)" << std::endl
                    << "            descend(*i);" << std::endl
                    << "    }" << std::endl;
            state = visit_decl;
            descend(n.groups);
            descend(n.nodes);
            state = decl;
            out << "};" << std::endl;
        }

        if(n.has_const_visitor)
        {
            out << "class " << n.name << "_const_visitor" << std::endl
                << "{" << std::endl
                << "public:" << std::endl
                << "    virtual ~" << n.name << "_const_visitor(void) throw() { }" << std::endl
                << "    inline void descend(" << n.name << " const &n) { n.apply(*this); }" << std::endl
                << "    template<typename T>" << std::endl
                << "    inline void descend(boost::intrusive_ptr<T> const &p) { if(p) descend(*p); }" << std::endl;
            if(n.ns->uses_lists)
                out << "    template<typename T, typename Alloc>" << std::endl
                    << "    inline void descend(std::list<T, Alloc> const &l)" << std::endl
                    << "    {" << std::endl
                    << "        for(typename std::list<T, Alloc>::const_iterator i = l.begin(); i != l.end(); ++i)" << std::endl
                    << "            descend(*i);" << std::endl
                    << "    }" << std::endl;
            state = const_visit_decl;
            descend(n.groups);
            descend(n.nodes);
            state = decl;
            out << "};" << std::endl;
        }
        break;
    case visit_decl:
    case const_visit_decl:
        break;
    }

    descend(n.groups);
    descend(n.nodes);
}

void header_output_visitor::visit(node_node const &n)
{
    bool first;

    switch(state)
    {
    case fwddecl:
        out << "struct " << n.name << ";" << std::endl
            << "typedef boost::intrusive_ptr<" << n.name << "> " << n.name << "_ptr;" << std::endl
            << "typedef " << n.name << " *" << n.name << "_weak_ptr;" << std::endl;
        break;
    case decl:
        out << "struct " << n.name << " : " << n.group->name << std::endl
            << "{" << std::endl
            << "    " << n.name << "(";

        first = true;
        for(std::list<data_member_node_ptr>::const_iterator i = n.members.begin();
                i != n.members.end(); ++i)
        {
            if((**i).needs_init)
            {
                if(!first)
                    out << ", ";
                (**i).type->apply(*this);
                out << " " << (**i).name;
                first = false;
            }
        }
        out << ") throw()";
        if(!first)
        {
            out << " : " << std::endl
                << "        ";
            first = true;
            for(std::list<data_member_node_ptr>::const_iterator i = n.members.begin();
                    i != n.members.end(); ++i)
            {
                if((**i).needs_init)
                {
                    if(!first)
                        out << ", ";
                    out << (**i).name << "(" << (**i).name << ")";
                    first = false;
                }
            }
        }
        out << " { }" << std::endl;

        out << "    virtual ~" << n.name << "(void) throw() { }" << std::endl;

        for(group_node_weak_ptr i = n.group; i; i = i->parent)
        {
            if(i->has_visitor)
                out << "    virtual void apply(" << i->name << "_visitor &);" << std::endl;
            if(i->has_const_visitor)
                out << "    virtual void apply(" << i->name << "_const_visitor &) const;" << std::endl;
        }

        descend(n.members);

        out << "};" << std::endl;
        break;
    case visit_decl:
        out << "    virtual void visit(" << n.name << " &) = 0;" << std::endl
            << "    inline void descend(" << n.name << " &n) { visit(n); }" << std::endl
            << "    inline void descend(boost::intrusive_ptr<" << n.name << "> &p) { if(p) descend(*p); }" << std::endl;
        break;
    case const_visit_decl:
        out << "    virtual void visit(" << n.name << " const &) = 0;" << std::endl
            << "    inline void descend(" << n.name << " const &n) { visit(n); }" << std::endl
            << "    inline void descend(boost::intrusive_ptr<" << n.name << "> const &p) { if(p) descend(*p); }" << std::endl;
    }
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
    descend(n.type);
    out << "&";
}

void header_output_visitor::visit(pointer_type_node const &n)
{
    descend(n.type);
    out << "*";
    if(n.is_const)
        out << " const";
    if(n.is_volatile)
        out << " volatile";
}

void header_output_visitor::visit(template_type_node const &n)
{
    out << n.name << "<";
    descend(n.template_args);
    out << "> ";
}

void header_output_visitor::visit(data_member_node const &n)
{
    out << "    ";
    descend(n.type);
    out << " " << n.name << ";" << std::endl;
}

void header_output_visitor::visit(list_type_node const &n)
{
    out << "std::list<";
    descend(n.type);
    out << "> ";
}

}
}
