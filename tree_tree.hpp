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
#include <memory>
#include <memory>
#include <memory>
#include <memory>
#include <memory>
#include <memory>
#include <memory>
#include <memory>
#include <memory>
#include <memory>
#include <memory>
#include <memory>
#include <memory>
#include <memory>
#include <memory>
#include <memory>
#include <boost/intrusive_ptr.hpp>
#include <list>
namespace trees {
namespace tree {
struct node;
typedef std::shared_ptr<node> node_ptr;
typedef std::weak_ptr<node> node_weak_ptr;
struct node_const_visitor;
struct node_visitor;
struct type_node;
typedef std::shared_ptr<type_node> type_node_ptr;
typedef std::weak_ptr<type_node> type_node_weak_ptr;
struct type_node_visitor;
struct group_type_node;
typedef std::shared_ptr<group_type_node> group_type_node_ptr;
typedef std::weak_ptr<group_type_node> group_type_node_weak_ptr;
struct node_type_node;
typedef std::shared_ptr<node_type_node> node_type_node_ptr;
typedef std::weak_ptr<node_type_node> node_type_node_weak_ptr;
struct basic_type_node;
typedef std::shared_ptr<basic_type_node> basic_type_node_ptr;
typedef std::weak_ptr<basic_type_node> basic_type_node_weak_ptr;
struct rvalue_reference_type_node;
typedef std::shared_ptr<rvalue_reference_type_node> rvalue_reference_type_node_ptr;
typedef std::weak_ptr<rvalue_reference_type_node> rvalue_reference_type_node_weak_ptr;
struct reference_type_node;
typedef std::shared_ptr<reference_type_node> reference_type_node_ptr;
typedef std::weak_ptr<reference_type_node> reference_type_node_weak_ptr;
struct pointer_type_node;
typedef std::shared_ptr<pointer_type_node> pointer_type_node_ptr;
typedef std::weak_ptr<pointer_type_node> pointer_type_node_weak_ptr;
struct template_type_node;
typedef std::shared_ptr<template_type_node> template_type_node_ptr;
typedef std::weak_ptr<template_type_node> template_type_node_weak_ptr;
struct list_type_node;
typedef std::shared_ptr<list_type_node> list_type_node_ptr;
typedef std::weak_ptr<list_type_node> list_type_node_weak_ptr;
struct root;
typedef std::shared_ptr<root> root_ptr;
typedef std::weak_ptr<root> root_weak_ptr;
struct include_node;
typedef std::shared_ptr<include_node> include_node_ptr;
typedef std::weak_ptr<include_node> include_node_weak_ptr;
struct namespace_node;
typedef std::shared_ptr<namespace_node> namespace_node_ptr;
typedef std::weak_ptr<namespace_node> namespace_node_weak_ptr;
struct group_node;
typedef std::shared_ptr<group_node> group_node_ptr;
typedef std::weak_ptr<group_node> group_node_weak_ptr;
struct node_node;
typedef std::shared_ptr<node_node> node_node_ptr;
typedef std::weak_ptr<node_node> node_node_weak_ptr;
struct data_member_node;
typedef std::shared_ptr<data_member_node> data_member_node_ptr;
typedef std::weak_ptr<data_member_node> data_member_node_weak_ptr;
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
class node_visitor
{
public:
        virtual ~node_visitor(void) throw() { }
        template<typename T>
        inline void descend(std::shared_ptr<T> &p) { if(p) p = p->apply(*this); }
        template<typename T, typename Alloc>
        inline void descend(std::list<T, Alloc> &l)
        {
                for(typename std::list<T, Alloc>::iterator i = l.begin(); i != l.end(); ++i)
                        descend(*i);
        }
        virtual type_node_ptr visit(group_type_node &) = 0;
        virtual type_node_ptr visit(node_type_node &) = 0;
        virtual type_node_ptr visit(basic_type_node &) = 0;
        virtual type_node_ptr visit(rvalue_reference_type_node &) = 0;
        virtual type_node_ptr visit(reference_type_node &) = 0;
        virtual type_node_ptr visit(pointer_type_node &) = 0;
        virtual type_node_ptr visit(template_type_node &) = 0;
        virtual type_node_ptr visit(list_type_node &) = 0;
        virtual node_ptr visit(root &) = 0;
        virtual node_ptr visit(include_node &) = 0;
        virtual node_ptr visit(namespace_node &) = 0;
        virtual node_ptr visit(group_node &) = 0;
        virtual node_ptr visit(node_node &) = 0;
        virtual node_ptr visit(data_member_node &) = 0;
};
class node_const_visitor
{
public:
        virtual ~node_const_visitor(void) throw() { }
        template<typename T>
        inline void descend(std::shared_ptr<T> const &p) { if(p) p->apply(*this); }
        template<typename T, typename Alloc>
        inline void descend(std::list<T, Alloc> const &l)
        {
                for(typename std::list<T, Alloc>::const_iterator i = l.begin(); i != l.end(); ++i)
                        descend(*i);
        }
        virtual void visit(group_type_node const &) = 0;
        inline void descend(std::shared_ptr<group_type_node> const &p) { if(p) visit(*p); }
        virtual void visit(node_type_node const &) = 0;
        inline void descend(std::shared_ptr<node_type_node> const &p) { if(p) visit(*p); }
        virtual void visit(basic_type_node const &) = 0;
        inline void descend(std::shared_ptr<basic_type_node> const &p) { if(p) visit(*p); }
        virtual void visit(rvalue_reference_type_node const &) = 0;
        inline void descend(std::shared_ptr<rvalue_reference_type_node> const &p) { if(p) visit(*p); }
        virtual void visit(reference_type_node const &) = 0;
        inline void descend(std::shared_ptr<reference_type_node> const &p) { if(p) visit(*p); }
        virtual void visit(pointer_type_node const &) = 0;
        inline void descend(std::shared_ptr<pointer_type_node> const &p) { if(p) visit(*p); }
        virtual void visit(template_type_node const &) = 0;
        inline void descend(std::shared_ptr<template_type_node> const &p) { if(p) visit(*p); }
        virtual void visit(list_type_node const &) = 0;
        inline void descend(std::shared_ptr<list_type_node> const &p) { if(p) visit(*p); }
        virtual void visit(root const &) = 0;
        inline void descend(std::shared_ptr<root> const &p) { if(p) visit(*p); }
        virtual void visit(include_node const &) = 0;
        inline void descend(std::shared_ptr<include_node> const &p) { if(p) visit(*p); }
        virtual void visit(namespace_node const &) = 0;
        inline void descend(std::shared_ptr<namespace_node> const &p) { if(p) visit(*p); }
        virtual void visit(group_node const &) = 0;
        inline void descend(std::shared_ptr<group_node> const &p) { if(p) visit(*p); }
        virtual void visit(node_node const &) = 0;
        inline void descend(std::shared_ptr<node_node> const &p) { if(p) visit(*p); }
        virtual void visit(data_member_node const &) = 0;
        inline void descend(std::shared_ptr<data_member_node> const &p) { if(p) visit(*p); }
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
        inline void descend(std::shared_ptr<T> &p) { if(p) p = p->apply(*this); }
        template<typename T, typename Alloc>
        inline void descend(std::list<T, Alloc> &l)
        {
                for(typename std::list<T, Alloc>::iterator i = l.begin(); i != l.end(); ++i)
                        descend(*i);
        }
        virtual type_node_ptr visit(group_type_node &) = 0;
        virtual type_node_ptr visit(node_type_node &) = 0;
        virtual type_node_ptr visit(basic_type_node &) = 0;
        virtual type_node_ptr visit(rvalue_reference_type_node &) = 0;
        virtual type_node_ptr visit(reference_type_node &) = 0;
        virtual type_node_ptr visit(pointer_type_node &) = 0;
        virtual type_node_ptr visit(template_type_node &) = 0;
        virtual type_node_ptr visit(list_type_node &) = 0;
};
struct group_type_node : type_node
, std::enable_shared_from_this<group_type_node>{
        group_type_node() throw() { }
        virtual ~group_type_node(void) throw() { }
        virtual type_node_ptr apply(type_node_visitor &);
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        std::shared_ptr< ::trees::tree::group_node>  node;
};
struct node_type_node : type_node
, std::enable_shared_from_this<node_type_node>{
        node_type_node() throw() { }
        virtual ~node_type_node(void) throw() { }
        virtual type_node_ptr apply(type_node_visitor &);
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        std::shared_ptr< ::trees::tree::node_node>  node;
};
struct basic_type_node : type_node
, std::enable_shared_from_this<basic_type_node>{
        basic_type_node() throw() { }
        virtual ~basic_type_node(void) throw() { }
        virtual type_node_ptr apply(type_node_visitor &);
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        namespace_node_weak_ptr ns;
        std::string name;
        bool is_const;
        bool is_volatile;
};
struct rvalue_reference_type_node : type_node
, std::enable_shared_from_this<rvalue_reference_type_node>{
        rvalue_reference_type_node() throw() { }
        virtual ~rvalue_reference_type_node(void) throw() { }
        virtual type_node_ptr apply(type_node_visitor &);
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        std::shared_ptr< ::trees::tree::type_node>  type;
};
struct reference_type_node : type_node
, std::enable_shared_from_this<reference_type_node>{
        reference_type_node() throw() { }
        virtual ~reference_type_node(void) throw() { }
        virtual type_node_ptr apply(type_node_visitor &);
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        std::shared_ptr< ::trees::tree::type_node>  type;
};
struct pointer_type_node : type_node
, std::enable_shared_from_this<pointer_type_node>{
        pointer_type_node() throw() { }
        virtual ~pointer_type_node(void) throw() { }
        virtual type_node_ptr apply(type_node_visitor &);
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        std::shared_ptr< ::trees::tree::type_node>  type;
        bool is_const;
        bool is_volatile;
};
struct template_type_node : type_node
, std::enable_shared_from_this<template_type_node>{
        template_type_node() throw() { }
        virtual ~template_type_node(void) throw() { }
        virtual type_node_ptr apply(type_node_visitor &);
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        namespace_node_weak_ptr ns;
        std::string name;
        std::list<std::shared_ptr< ::trees::tree::type_node> >  template_args;
};
struct list_type_node : type_node
, std::enable_shared_from_this<list_type_node>{
        list_type_node() throw() { }
        virtual ~list_type_node(void) throw() { }
        virtual type_node_ptr apply(type_node_visitor &);
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        std::shared_ptr< ::trees::tree::type_node>  type;
};
struct root : node
, std::enable_shared_from_this<root>{
        root() throw() { }
        virtual ~root(void) throw() { }
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        std::list<std::shared_ptr< ::trees::tree::include_node> >  includes;
        std::shared_ptr< ::trees::tree::namespace_node>  global_namespace;
};
struct include_node : node
, std::enable_shared_from_this<include_node>{
        include_node() throw() { }
        virtual ~include_node(void) throw() { }
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        std::string name;
};
struct namespace_node : node
, std::enable_shared_from_this<namespace_node>{
        namespace_node() throw() { }
        virtual ~namespace_node(void) throw() { }
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        namespace_node_weak_ptr parent;
        std::string name;
        std::list<std::shared_ptr< ::trees::tree::namespace_node> >  namespaces;
        std::shared_ptr< ::trees::tree::group_node>  group;
        bool uses_lists;
};
struct group_node : node
, std::enable_shared_from_this<group_node>{
        group_node() throw() { }
        virtual ~group_node(void) throw() { }
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        namespace_node_weak_ptr ns;
        group_node_weak_ptr parent;
        std::string name;
        bool has_visitor;
        bool has_const_visitor;
        std::list<std::shared_ptr< ::trees::tree::group_node> >  groups;
        std::list<std::shared_ptr< ::trees::tree::node_node> >  nodes;
        std::list<std::shared_ptr< ::trees::tree::data_member_node> >  default_members;
        smartpointer_type smartpointer;
};
struct node_node : node
, std::enable_shared_from_this<node_node>{
        node_node() throw() { }
        virtual ~node_node(void) throw() { }
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        namespace_node_weak_ptr ns;
        group_node_weak_ptr group;
        std::string name;
        std::list<std::shared_ptr< ::trees::tree::data_member_node> >  members;
        smartpointer_type smartpointer;
};
struct data_member_node : node
, std::enable_shared_from_this<data_member_node>{
        data_member_node() throw() { }
        virtual ~data_member_node(void) throw() { }
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        std::shared_ptr< ::trees::tree::type_node>  type;
        std::string name;
        bool needs_init;
};
}
}
#endif
