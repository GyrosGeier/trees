#ifndef tree_tree_hpp_
#define tree_tree_hpp_ 1

#include <string>
#include <string>
#include <string>
#include <tree.h>
#include <string>
#include <tree.h>
#include <string>
#include <string>
#include <string>
#include <string>
#include <boost/intrusive_ptr.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/intrusive_ptr.hpp>
#include <list>
namespace trees {
namespace tree {
struct node;
typedef boost::intrusive_ptr<node> node_ptr;
typedef node *node_weak_ptr;
struct node_const_visitor;
struct node_visitor;
struct type_node;
typedef boost::intrusive_ptr<type_node> type_node_ptr;
typedef type_node *type_node_weak_ptr;
struct type_node_visitor;
struct group_node;
typedef boost::intrusive_ptr<group_node> group_node_ptr;
typedef group_node *group_node_weak_ptr;
struct node_node;
typedef boost::intrusive_ptr<node_node> node_node_ptr;
typedef node_node *node_node_weak_ptr;
struct basic_type_node;
typedef boost::intrusive_ptr<basic_type_node> basic_type_node_ptr;
typedef basic_type_node *basic_type_node_weak_ptr;
struct reference_type_node;
typedef boost::intrusive_ptr<reference_type_node> reference_type_node_ptr;
typedef reference_type_node *reference_type_node_weak_ptr;
struct pointer_type_node;
typedef boost::intrusive_ptr<pointer_type_node> pointer_type_node_ptr;
typedef pointer_type_node *pointer_type_node_weak_ptr;
struct template_type_node;
typedef boost::intrusive_ptr<template_type_node> template_type_node_ptr;
typedef template_type_node *template_type_node_weak_ptr;
struct list_type_node;
typedef boost::intrusive_ptr<list_type_node> list_type_node_ptr;
typedef list_type_node *list_type_node_weak_ptr;
struct root;
typedef boost::intrusive_ptr<root> root_ptr;
typedef root *root_weak_ptr;
struct include_node;
typedef boost::intrusive_ptr<include_node> include_node_ptr;
typedef include_node *include_node_weak_ptr;
struct namespace_node;
typedef boost::intrusive_ptr<namespace_node> namespace_node_ptr;
typedef namespace_node *namespace_node_weak_ptr;
struct data_member_node;
typedef boost::intrusive_ptr<data_member_node> data_member_node_ptr;
typedef data_member_node *data_member_node_weak_ptr;
}
}
namespace trees {
namespace tree {
struct node {
        node(void) throw() : refcount(0) { }
        virtual ~node(void) throw() { }
        virtual node_ptr apply(node_visitor &) = 0;
        virtual void apply(node_const_visitor &) const = 0;
        unsigned int refcount;
};
inline void intrusive_ptr_add_ref(node *n) { ++n->refcount; }
inline void intrusive_ptr_release(node *n) { if(!--n->refcount) delete n; }
class node_visitor
{
public:
        virtual ~node_visitor(void) throw() { }
        template<typename T>
        inline void descend(boost::intrusive_ptr<T> const &p) { if(p) p->apply(*this); }
        template<typename T, typename Alloc>
        inline void descend(std::list<T, Alloc> &l)
        {
                for(typename std::list<T, Alloc>::iterator i = l.begin(); i != l.end(); ++i)
                        descend(*i);
        }
        virtual type_node_ptr visit(group_node &) = 0;
        inline void descend(boost::intrusive_ptr<group_node> const &p) { if(p) visit(*p); }
        virtual type_node_ptr visit(node_node &) = 0;
        inline void descend(boost::intrusive_ptr<node_node> const &p) { if(p) visit(*p); }
        virtual type_node_ptr visit(basic_type_node &) = 0;
        inline void descend(boost::intrusive_ptr<basic_type_node> const &p) { if(p) visit(*p); }
        virtual type_node_ptr visit(reference_type_node &) = 0;
        inline void descend(boost::intrusive_ptr<reference_type_node> const &p) { if(p) visit(*p); }
        virtual type_node_ptr visit(pointer_type_node &) = 0;
        inline void descend(boost::intrusive_ptr<pointer_type_node> const &p) { if(p) visit(*p); }
        virtual type_node_ptr visit(template_type_node &) = 0;
        inline void descend(boost::intrusive_ptr<template_type_node> const &p) { if(p) visit(*p); }
        virtual type_node_ptr visit(list_type_node &) = 0;
        inline void descend(boost::intrusive_ptr<list_type_node> const &p) { if(p) visit(*p); }
        virtual node_ptr visit(root &) = 0;
        inline void descend(boost::intrusive_ptr<root> const &p) { if(p) visit(*p); }
        virtual node_ptr visit(include_node &) = 0;
        inline void descend(boost::intrusive_ptr<include_node> const &p) { if(p) visit(*p); }
        virtual node_ptr visit(namespace_node &) = 0;
        inline void descend(boost::intrusive_ptr<namespace_node> const &p) { if(p) visit(*p); }
        virtual node_ptr visit(data_member_node &) = 0;
        inline void descend(boost::intrusive_ptr<data_member_node> const &p) { if(p) visit(*p); }
};
class node_const_visitor
{
public:
        virtual ~node_const_visitor(void) throw() { }
        template<typename T>
        inline void descend(boost::intrusive_ptr<T> const &p) { if(p) p->apply(*this); }
        template<typename T, typename Alloc>
        inline void descend(std::list<T, Alloc> const &l)
        {
                for(typename std::list<T, Alloc>::const_iterator i = l.begin(); i != l.end(); ++i)
                        descend(*i);
        }
        virtual void visit(group_node const &) = 0;
        inline void descend(boost::intrusive_ptr<group_node> const &p) { if(p) visit(*p); }
        virtual void visit(node_node const &) = 0;
        inline void descend(boost::intrusive_ptr<node_node> const &p) { if(p) visit(*p); }
        virtual void visit(basic_type_node const &) = 0;
        inline void descend(boost::intrusive_ptr<basic_type_node> const &p) { if(p) visit(*p); }
        virtual void visit(reference_type_node const &) = 0;
        inline void descend(boost::intrusive_ptr<reference_type_node> const &p) { if(p) visit(*p); }
        virtual void visit(pointer_type_node const &) = 0;
        inline void descend(boost::intrusive_ptr<pointer_type_node> const &p) { if(p) visit(*p); }
        virtual void visit(template_type_node const &) = 0;
        inline void descend(boost::intrusive_ptr<template_type_node> const &p) { if(p) visit(*p); }
        virtual void visit(list_type_node const &) = 0;
        inline void descend(boost::intrusive_ptr<list_type_node> const &p) { if(p) visit(*p); }
        virtual void visit(root const &) = 0;
        inline void descend(boost::intrusive_ptr<root> const &p) { if(p) visit(*p); }
        virtual void visit(include_node const &) = 0;
        inline void descend(boost::intrusive_ptr<include_node> const &p) { if(p) visit(*p); }
        virtual void visit(namespace_node const &) = 0;
        inline void descend(boost::intrusive_ptr<namespace_node> const &p) { if(p) visit(*p); }
        virtual void visit(data_member_node const &) = 0;
        inline void descend(boost::intrusive_ptr<data_member_node> const &p) { if(p) visit(*p); }
};
struct type_node : node {
        type_node(void) throw() { }
        virtual ~type_node(void) throw() { }
        virtual type_node_ptr apply(type_node_visitor &) = 0;
        using node::apply;
};
class type_node_visitor
{
public:
        virtual ~type_node_visitor(void) throw() { }
        template<typename T>
        inline void descend(boost::intrusive_ptr<T> const &p) { if(p) p->apply(*this); }
        template<typename T, typename Alloc>
        inline void descend(std::list<T, Alloc> &l)
        {
                for(typename std::list<T, Alloc>::iterator i = l.begin(); i != l.end(); ++i)
                        descend(*i);
        }
        virtual type_node_ptr visit(group_node &) = 0;
        inline void descend(boost::intrusive_ptr<group_node> const &p) { if(p) visit(*p); }
        virtual type_node_ptr visit(node_node &) = 0;
        inline void descend(boost::intrusive_ptr<node_node> const &p) { if(p) visit(*p); }
        virtual type_node_ptr visit(basic_type_node &) = 0;
        inline void descend(boost::intrusive_ptr<basic_type_node> const &p) { if(p) visit(*p); }
        virtual type_node_ptr visit(reference_type_node &) = 0;
        inline void descend(boost::intrusive_ptr<reference_type_node> const &p) { if(p) visit(*p); }
        virtual type_node_ptr visit(pointer_type_node &) = 0;
        inline void descend(boost::intrusive_ptr<pointer_type_node> const &p) { if(p) visit(*p); }
        virtual type_node_ptr visit(template_type_node &) = 0;
        inline void descend(boost::intrusive_ptr<template_type_node> const &p) { if(p) visit(*p); }
        virtual type_node_ptr visit(list_type_node &) = 0;
        inline void descend(boost::intrusive_ptr<list_type_node> const &p) { if(p) visit(*p); }
};
struct group_node : type_node
{
        group_node() throw() { }
        virtual ~group_node(void) throw() { }
        virtual type_node_ptr apply(type_node_visitor &);
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        namespace_node_weak_ptr ns;
        group_node_weak_ptr parent;
        std::string name;
        bool has_visitor;
        bool has_const_visitor;
        std::list<boost::intrusive_ptr< ::trees::tree::group_node> >  groups;
        std::list<boost::intrusive_ptr< ::trees::tree::node_node> >  nodes;
        std::list<boost::intrusive_ptr< ::trees::tree::data_member_node> >  default_members;
        smartpointer_type smartpointer;
};
struct node_node : type_node
{
        node_node() throw() { }
        virtual ~node_node(void) throw() { }
        virtual type_node_ptr apply(type_node_visitor &);
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        namespace_node_weak_ptr ns;
        group_node_weak_ptr group;
        std::string name;
        std::list<boost::intrusive_ptr< ::trees::tree::data_member_node> >  members;
        smartpointer_type smartpointer;
};
struct basic_type_node : type_node
{
        basic_type_node() throw() { }
        virtual ~basic_type_node(void) throw() { }
        virtual type_node_ptr apply(type_node_visitor &);
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        namespace_node_weak_ptr ns;
        std::string name;
        bool is_node;
        bool is_const;
        bool is_volatile;
};
struct reference_type_node : type_node
{
        reference_type_node() throw() { }
        virtual ~reference_type_node(void) throw() { }
        virtual type_node_ptr apply(type_node_visitor &);
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        boost::intrusive_ptr< ::trees::tree::type_node>  type;
};
struct pointer_type_node : type_node
{
        pointer_type_node() throw() { }
        virtual ~pointer_type_node(void) throw() { }
        virtual type_node_ptr apply(type_node_visitor &);
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        boost::intrusive_ptr< ::trees::tree::type_node>  type;
        bool is_const;
        bool is_volatile;
};
struct template_type_node : type_node
{
        template_type_node() throw() { }
        virtual ~template_type_node(void) throw() { }
        virtual type_node_ptr apply(type_node_visitor &);
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        namespace_node_weak_ptr ns;
        std::string name;
        std::list<boost::intrusive_ptr< ::trees::tree::type_node> >  template_args;
};
struct list_type_node : type_node
{
        list_type_node() throw() { }
        virtual ~list_type_node(void) throw() { }
        virtual type_node_ptr apply(type_node_visitor &);
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        boost::intrusive_ptr< ::trees::tree::type_node>  type;
};
struct root : node
{
        root() throw() { }
        virtual ~root(void) throw() { }
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        std::list<boost::intrusive_ptr< ::trees::tree::include_node> >  includes;
        boost::intrusive_ptr< ::trees::tree::namespace_node>  global_namespace;
};
struct include_node : node
{
        include_node() throw() { }
        virtual ~include_node(void) throw() { }
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        std::string name;
};
struct namespace_node : node
{
        namespace_node() throw() { }
        virtual ~namespace_node(void) throw() { }
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        namespace_node_weak_ptr parent;
        std::string name;
        std::list<boost::intrusive_ptr< ::trees::tree::namespace_node> >  namespaces;
        boost::intrusive_ptr< ::trees::tree::group_node>  group;
        bool uses_lists;
};
struct data_member_node : node
{
        data_member_node() throw() { }
        virtual ~data_member_node(void) throw() { }
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        boost::intrusive_ptr< ::trees::tree::type_node>  type;
        std::string name;
        bool needs_init;
};
}
}
#endif
