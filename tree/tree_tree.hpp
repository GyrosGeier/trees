#ifndef tree_tree_hpp_
#define tree_tree_hpp_ 1

#include <string>
#include <string>
#include <set>
#include <string>
#include <string>
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
namespace foundry {
namespace tree {
struct node;
typedef boost::intrusive_ptr<node> node_ptr;
typedef node *node_weak_ptr;
struct node_const_visitor;
struct node_visitor;
struct type_node;
typedef boost::intrusive_ptr<type_node> type_node_ptr;
typedef type_node *type_node_weak_ptr;
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
namespace foundry {
namespace tree {
struct node {
    node(void) throw() : refcount(0) { }
    virtual ~node(void) throw() { }
    virtual void apply(node_visitor &) = 0;
    virtual void apply(node_const_visitor &) const = 0;
    unsigned int refcount;
};
inline void intrusive_ptr_add_ref(node *n) { ++n->refcount; }
inline void intrusive_ptr_release(node *n) { if(!--n->refcount) delete n; }
class node_visitor
{
public:
    virtual ~node_visitor(void) throw() { }
    inline void descend(node &n) { n.apply(*this); }
    template<typename T>
    inline void descend(boost::intrusive_ptr<T> const &p) { if(p) descend(*p); }
    template<typename T, typename Alloc>
    inline void descend(std::list<T, Alloc> &l)
    {
        for(typename std::list<T, Alloc>::iterator i = l.begin(); i != l.end(); ++i)
            descend(*i);
    }
    virtual void visit(group_node &) = 0;
    inline void descend(group_node &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<group_node> &p) { if(p) descend(*p); }
    virtual void visit(node_node &) = 0;
    inline void descend(node_node &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<node_node> &p) { if(p) descend(*p); }
    virtual void visit(basic_type_node &) = 0;
    inline void descend(basic_type_node &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<basic_type_node> &p) { if(p) descend(*p); }
    virtual void visit(reference_type_node &) = 0;
    inline void descend(reference_type_node &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<reference_type_node> &p) { if(p) descend(*p); }
    virtual void visit(pointer_type_node &) = 0;
    inline void descend(pointer_type_node &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<pointer_type_node> &p) { if(p) descend(*p); }
    virtual void visit(template_type_node &) = 0;
    inline void descend(template_type_node &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<template_type_node> &p) { if(p) descend(*p); }
    virtual void visit(list_type_node &) = 0;
    inline void descend(list_type_node &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<list_type_node> &p) { if(p) descend(*p); }
    virtual void visit(root &) = 0;
    inline void descend(root &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<root> &p) { if(p) descend(*p); }
    virtual void visit(include_node &) = 0;
    inline void descend(include_node &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<include_node> &p) { if(p) descend(*p); }
    virtual void visit(namespace_node &) = 0;
    inline void descend(namespace_node &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<namespace_node> &p) { if(p) descend(*p); }
    virtual void visit(data_member_node &) = 0;
    inline void descend(data_member_node &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<data_member_node> &p) { if(p) descend(*p); }
};
class node_const_visitor
{
public:
    virtual ~node_const_visitor(void) throw() { }
    inline void descend(node const &n) { n.apply(*this); }
    template<typename T>
    inline void descend(boost::intrusive_ptr<T> const &p) { if(p) descend(*p); }
    template<typename T, typename Alloc>
    inline void descend(std::list<T, Alloc> const &l)
    {
        for(typename std::list<T, Alloc>::const_iterator i = l.begin(); i != l.end(); ++i)
            descend(*i);
    }
    virtual void visit(group_node const &) = 0;
    inline void descend(group_node const &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<group_node> const &p) { if(p) descend(*p); }
    virtual void visit(node_node const &) = 0;
    inline void descend(node_node const &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<node_node> const &p) { if(p) descend(*p); }
    virtual void visit(basic_type_node const &) = 0;
    inline void descend(basic_type_node const &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<basic_type_node> const &p) { if(p) descend(*p); }
    virtual void visit(reference_type_node const &) = 0;
    inline void descend(reference_type_node const &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<reference_type_node> const &p) { if(p) descend(*p); }
    virtual void visit(pointer_type_node const &) = 0;
    inline void descend(pointer_type_node const &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<pointer_type_node> const &p) { if(p) descend(*p); }
    virtual void visit(template_type_node const &) = 0;
    inline void descend(template_type_node const &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<template_type_node> const &p) { if(p) descend(*p); }
    virtual void visit(list_type_node const &) = 0;
    inline void descend(list_type_node const &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<list_type_node> const &p) { if(p) descend(*p); }
    virtual void visit(root const &) = 0;
    inline void descend(root const &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<root> const &p) { if(p) descend(*p); }
    virtual void visit(include_node const &) = 0;
    inline void descend(include_node const &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<include_node> const &p) { if(p) descend(*p); }
    virtual void visit(namespace_node const &) = 0;
    inline void descend(namespace_node const &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<namespace_node> const &p) { if(p) descend(*p); }
    virtual void visit(data_member_node const &) = 0;
    inline void descend(data_member_node const &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<data_member_node> const &p) { if(p) descend(*p); }
};
struct type_node : node {
    type_node(void) throw() { }
    virtual ~type_node(void) throw() { }
    using node::apply;
};
struct group_node : type_node
{
    group_node() throw() { }
    virtual ~group_node(void) throw() { }
    virtual void apply(node_visitor &);
    virtual void apply(node_const_visitor &) const;
    namespace_node_weak_ptr ns;
    group_node_weak_ptr parent;
    std::string name;
    bool has_visitor;
    bool has_const_visitor;
    std::list<boost::intrusive_ptr< ::foundry::tree::group_node> >  groups;
    std::list<boost::intrusive_ptr< ::foundry::tree::node_node> >  nodes;
    std::list<boost::intrusive_ptr< ::foundry::tree::data_member_node> >  default_members;
};
struct node_node : type_node
{
    node_node() throw() { }
    virtual ~node_node(void) throw() { }
    virtual void apply(node_visitor &);
    virtual void apply(node_const_visitor &) const;
    namespace_node_weak_ptr ns;
    group_node_weak_ptr group;
    std::string name;
    std::list<boost::intrusive_ptr< ::foundry::tree::data_member_node> >  members;
};
struct basic_type_node : type_node
{
    basic_type_node() throw() { }
    virtual ~basic_type_node(void) throw() { }
    virtual void apply(node_visitor &);
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
    virtual void apply(node_visitor &);
    virtual void apply(node_const_visitor &) const;
    boost::intrusive_ptr< ::foundry::tree::type_node>  type;
};
struct pointer_type_node : type_node
{
    pointer_type_node() throw() { }
    virtual ~pointer_type_node(void) throw() { }
    virtual void apply(node_visitor &);
    virtual void apply(node_const_visitor &) const;
    boost::intrusive_ptr< ::foundry::tree::type_node>  type;
    bool is_const;
    bool is_volatile;
};
struct template_type_node : type_node
{
    template_type_node() throw() { }
    virtual ~template_type_node(void) throw() { }
    virtual void apply(node_visitor &);
    virtual void apply(node_const_visitor &) const;
    namespace_node_weak_ptr ns;
    std::string name;
    std::list<boost::intrusive_ptr< ::foundry::tree::type_node> >  template_args;
};
struct list_type_node : type_node
{
    list_type_node() throw() { }
    virtual ~list_type_node(void) throw() { }
    virtual void apply(node_visitor &);
    virtual void apply(node_const_visitor &) const;
    boost::intrusive_ptr< ::foundry::tree::type_node>  type;
};
struct root : node
{
    root() throw() { }
    virtual ~root(void) throw() { }
    virtual void apply(node_visitor &);
    virtual void apply(node_const_visitor &) const;
    std::list<boost::intrusive_ptr< ::foundry::tree::include_node> >  includes;
    boost::intrusive_ptr< ::foundry::tree::namespace_node>  global_namespace;
};
struct include_node : node
{
    include_node() throw() { }
    virtual ~include_node(void) throw() { }
    virtual void apply(node_visitor &);
    virtual void apply(node_const_visitor &) const;
    std::string name;
    bool is_local;
};
struct namespace_node : node
{
    namespace_node() throw() { }
    virtual ~namespace_node(void) throw() { }
    virtual void apply(node_visitor &);
    virtual void apply(node_const_visitor &) const;
    namespace_node_weak_ptr parent;
    std::string name;
    std::list<boost::intrusive_ptr< ::foundry::tree::namespace_node> >  namespaces;
    boost::intrusive_ptr< ::foundry::tree::group_node>  group;
    bool uses_lists;
    std::set< std::string>  node_types;
};
struct data_member_node : node
{
    data_member_node() throw() { }
    virtual ~data_member_node(void) throw() { }
    virtual void apply(node_visitor &);
    virtual void apply(node_const_visitor &) const;
    boost::intrusive_ptr< ::foundry::tree::type_node>  type;
    std::string name;
    bool needs_init;
};
}
}
#endif
