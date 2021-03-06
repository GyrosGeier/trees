/* Copyright 2009 Simon Richter <Simon.Richter@hogyros.de>
 *
 * Released under the GNU General Public Licence version 3.
 */

#include "header_output_visitor.hpp"

namespace trees {
namespace tree {

header_output_visitor::header_output_visitor(std::ostream &out) :
        out(out), state(fwddecl)
{
        return;
}

void header_output_visitor::visit(root const &r)
{
        descend(r.includes);
        out << "#include <list>" << std::endl;
        state = fwddecl;
        descend(r.global_namespace);
        state = decl;
        descend(r.global_namespace);
}

void header_output_visitor::visit(include_node const &n)
{
        out << "#include " << n.name << std::endl;
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
        if(n.nodes.empty() && n.groups.empty())
                return;

        auto parent = n.parent.lock();
        auto ns = n.ns.lock();

        switch(state)
        {
        case fwddecl:
                out << "struct " << n.name << ";" << std::endl;
                switch(n.smartpointer)
                {
                case strict_ownership:
                        out << "typedef std::unique_ptr<" << n.name << "> " << n.name << "_ptr;" << std::endl
                                << "typedef " << n.name << " *" << n.name << "_weak_ptr;" << std::endl;
                        break;
                case shared_ownership:
                        out << "typedef std::shared_ptr<" << n.name << "> " << n.name << "_ptr;" << std::endl
                                << "typedef std::weak_ptr<" << n.name << "> " << n.name << "_weak_ptr;" << std::endl;
                        break;
                case intrusive:
                        out << "typedef boost::intrusive_ptr<" << n.name << "> " << n.name << "_ptr;" << std::endl
                                << "typedef " << n.name << " *" << n.name << "_weak_ptr;" << std::endl;
                        break;
                }
                if(n.has_const_visitor)
                        out << "struct " << n.name << "_const_visitor;" << std::endl;
                if(n.has_visitor)
                        out << "struct " << n.name << "_visitor;" << std::endl;
                break;
        case decl:
                out << "struct " << n.name;
                if(parent)
                        out << " : " << parent->name;
                out << " {" << std::endl
                        << "        " << n.name << "(void) throw()";
                if(!parent)
                        out << " : refcount(0)";
                out << " { }" << std::endl
                        << "        virtual ~" << n.name << "(void) throw() { }" << std::endl;
                if(n.has_visitor)
                        out << "        virtual " << n.name << "_ptr apply(" << n.name << "_visitor &) = 0;" << std::endl;
                if(n.has_const_visitor)
                        out << "        virtual void apply(" << n.name << "_const_visitor &) const = 0;" << std::endl;
                if(parent && (n.has_visitor || n.has_const_visitor))
                        out << "        using " << parent->name << "::apply;" << std::endl;
                if(!parent)
                        out << "        unsigned int refcount;" << std::endl;
                descend(n.default_members);
                out << "};" << std::endl;
                if(!parent && n.smartpointer == intrusive)
                        out << "inline void intrusive_ptr_add_ref(" << n.name << " *n) { ++n->refcount; }" << std::endl
                                << "inline void intrusive_ptr_release(" << n.name << " *n) { if(!--n->refcount) delete n; }" << std::endl;
                if(n.has_visitor)
                {
                        out << "class " << n.name << "_visitor" << std::endl
                                << "{" << std::endl
                                << "public:" << std::endl
                                << "        virtual ~" << n.name << "_visitor(void) throw() { }" << std::endl
                                << "        template<typename T>" << std::endl;
                        switch(n.smartpointer)
                        {
                        case strict_ownership:
                                out << "        inline void descend(std::unique_ptr<T> &p) { if(p) p = p->apply(*this); }" << std::endl;
                                break;
                        case shared_ownership:
                                out << "        inline void descend(std::shared_ptr<T> &p) { if(p) p = p->apply(*this); }" << std::endl;
                                break;
                        case intrusive:
                                out << "        inline void descend(boost::intrusive_ptr<T> &p) { if(p) p = p->apply(*this); }" << std::endl;
                                break;
                        }
                        if(ns->uses_lists)
                                out << "        template<typename T, typename Alloc>" << std::endl
                                        << "        inline void descend(std::list<T, Alloc> &l)" << std::endl
                                        << "        {" << std::endl
                                        << "                for(typename std::list<T, Alloc>::iterator i = l.begin(); i != l.end(); ++i)" << std::endl
                                        << "                        descend(*i);" << std::endl
                                        << "        }" << std::endl;
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
                                << "        virtual ~" << n.name << "_const_visitor(void) throw() { }" << std::endl
                                << "        template<typename T>" << std::endl;
                        switch(n.smartpointer)
                        {
                        case strict_ownership:
                                out << "        inline void descend(std::unique_ptr<T> const &p) { if(p) p->apply(*this); }" << std::endl;
                                break;
                        case shared_ownership:
                                out << "        inline void descend(std::shared_ptr<T> const &p) { if(p) p->apply(*this); }" << std::endl;
                                break;
                        case intrusive:
                                out << "        inline void descend(boost::intrusive_ptr<T> const &p) { if(p) p->apply(*this); }" << std::endl;
                                break;
                        }
                        if(ns->uses_lists)
                                out << "        template<typename T, typename Alloc>" << std::endl
                                        << "        inline void descend(std::list<T, Alloc> const &l)" << std::endl
                                        << "        {" << std::endl
                                        << "                for(typename std::list<T, Alloc>::const_iterator i = l.begin(); i != l.end(); ++i)" << std::endl
                                        << "                        descend(*i);" << std::endl
                                        << "        }" << std::endl;
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

        auto group = n.group.lock();

        switch(state)
        {
        case fwddecl:
                out << "struct " << n.name << ";" << std::endl;
                switch(n.smartpointer)
                {
                case strict_ownership:
                        out << "typedef std::unique_ptr<" << n.name << "> " << n.name << "_ptr;" << std::endl
                                << "typedef " << n.name << " *" << n.name << "_weak_ptr;" << std::endl;
                        break;
                case shared_ownership:
                        out << "typedef std::shared_ptr<" << n.name << "> " << n.name << "_ptr;" << std::endl
                                << "typedef std::weak_ptr<" << n.name << "> " << n.name << "_weak_ptr;" << std::endl;
                        break;
                case intrusive:
                        out << "typedef boost::intrusive_ptr<" << n.name << "> " << n.name << "_ptr;" << std::endl
                                << "typedef " << n.name << " *" << n.name << "_weak_ptr;" << std::endl;
                        break;
                }
                break;
        case decl:
                out << "struct " << n.name << " : " << group->name << std::endl;
                if(n.smartpointer == shared_ownership)
                        out << ", "
                                << "std::enable_shared_from_this<" << n.name << ">";
                out << "{" << std::endl
                        << "        " << n.name << "(";

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
                                << "                ";
                        first = true;
                        for(std::list<data_member_node_ptr>::const_iterator i = n.members.begin();
                                        i != n.members.end(); ++i)
                        {
                                if((**i).needs_init)
                                {
                                        if(!first)
                                                out << ", ";
                                        out << (**i).name << "(std::move(" << (**i).name << "))";
                                        first = false;
                                }
                        }
                }
                out << " { }" << std::endl;

                out << "        virtual ~" << n.name << "(void) throw() { }" << std::endl;

                for(group_node_ptr i = group; i; i = i->parent.lock())
                {
                        if(i->has_visitor)
                                out << "        virtual " << i->name << "_ptr apply(" << i->name << "_visitor &);" << std::endl;
                        if(i->has_const_visitor)
                                out << "        virtual void apply(" << i->name << "_const_visitor &) const;" << std::endl;
                }

                descend(n.members);

                out << "};" << std::endl;
                break;
        case visit_decl:
                out << "        virtual " << group->name << "_ptr visit(" << n.name << "_ptr) = 0;" << std::endl;
                break;
        case const_visit_decl:
                out << "        virtual void visit(" << n.name << " const &) = 0;" << std::endl;
                switch(n.smartpointer)
                {
                case strict_ownership:
                        out << "        inline void descend(std::unique_ptr<" << n.name << "> const &p) { if(p) visit(*p); }" << std::endl;
                        break;
                case shared_ownership:
                        out << "        inline void descend(std::shared_ptr<" << n.name << "> const &p) { if(p) visit(*p); }" << std::endl;
                        break;
                case intrusive:
                        out << "        inline void descend(boost::intrusive_ptr<" << n.name << "> const &p) { if(p) visit(*p); }" << std::endl;
                        break;
                }
        }
}

void header_output_visitor::visit(group_type_node const &n)
{
        auto node_ns = n.node->ns.lock();

        std::string ns;
        for(namespace_node_ptr i = node_ns; i; i = i->parent.lock())
                ns = i->name + "::" + ns;
        out << ns << n.node->name;
}

void header_output_visitor::visit(node_type_node const &n)
{
        auto node_ns = n.node->ns.lock();

        std::string ns;
        for(namespace_node_ptr i = node_ns; i; i = i->parent.lock())
                ns = i->name + "::" + ns;
        out << ns << n.node->name;
}

void header_output_visitor::visit(basic_type_node const &n)
{
        out << n.name;
        if(n.is_const)
                out << " const";
        if(n.is_volatile)
                out << " volatile";
}

void header_output_visitor::visit(rvalue_reference_type_node const &n)
{
        descend(n.type);
        out << "&&";
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
        out << n.name << "< ";
        bool first = true;
        for(std::list<type_node_ptr>::const_iterator i = n.template_args.begin();
                        i != n.template_args.end(); ++i)
        {
                if(!first)
                {
                        out << ", ";
                }
                (**i).apply(*this);
                first = false;
        }
        out << "> ";
}

void header_output_visitor::visit(data_member_node const &n)
{
        out << "        ";
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
