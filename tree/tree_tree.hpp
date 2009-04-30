#ifndef tree_tree_hpp_
#define tree_tree_hpp_ 1

#pragma once
#include <boost/intrusive_ptr.hpp>
#include <list>
#include <string>
namespace foundry {
namespace tree {
struct data_member_node;
typedef boost::intrusive_ptr<data_member_node> data_member_node_ptr;
typedef data_member_node *data_member_node_weak_ptr;
struct node_node;
typedef boost::intrusive_ptr<node_node> node_node_ptr;
typedef node_node *node_node_weak_ptr;
struct namespace_node;
typedef boost::intrusive_ptr<namespace_node> namespace_node_ptr;
typedef namespace_node *namespace_node_weak_ptr;
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
class visitor;
class const_visitor;
struct node {
    node(void) throw() : refcount(0) { }
    virtual ~node(void) throw() { }
    virtual void apply(visitor &) = 0;
    virtual void apply(const_visitor &) const = 0;
    unsigned int refcount;
};
typedef boost::intrusive_ptr<node> node_ptr;
typedef node *node_weak_ptr;
inline void intrusive_ptr_add_ref(node *n) { ++n->refcount; }
inline void intrusive_ptr_release(node *n) { if(!--n->refcount) delete n; }
struct data_member_node : node
{
    data_member_node(void) throw() :
        type(), name() { }
    virtual ~data_member_node(void) throw() { }
    virtual void apply(visitor &);
    virtual void apply(const_visitor &) const;
    boost::intrusive_ptr<node>  type;
    std::string name;
};
struct node_node : node
{
    node_node(void) throw() :
        ns(), name(), members() { }
    virtual ~node_node(void) throw() { }
    virtual void apply(visitor &);
    virtual void apply(const_visitor &) const;
    namespace_node_weak_ptr ns;
    std::string name;
    std::list<boost::intrusive_ptr<data_member_node> >  members;
};
struct namespace_node : node
{
    namespace_node(void) throw() :
        parent(), name(), has_nodes(), has_visitor(), has_const_visitor(), namespaces(), nodes() { }
    virtual ~namespace_node(void) throw() { }
    virtual void apply(visitor &);
    virtual void apply(const_visitor &) const;
    namespace_node_weak_ptr parent;
    std::string name;
    bool has_nodes;
    bool has_visitor;
    bool has_const_visitor;
    std::list<boost::intrusive_ptr<namespace_node> >  namespaces;
    std::list<boost::intrusive_ptr<node_node> >  nodes;
};
struct basic_type_node : node
{
    basic_type_node(void) throw() :
        ns(), name(), is_const(), is_volatile() { }
    virtual ~basic_type_node(void) throw() { }
    virtual void apply(visitor &);
    virtual void apply(const_visitor &) const;
    namespace_node_weak_ptr ns;
    std::string name;
    bool is_const;
    bool is_volatile;
};
struct reference_type_node : node
{
    reference_type_node(void) throw() :
        type() { }
    virtual ~reference_type_node(void) throw() { }
    virtual void apply(visitor &);
    virtual void apply(const_visitor &) const;
    boost::intrusive_ptr<node>  type;
};
struct pointer_type_node : node
{
    pointer_type_node(void) throw() :
        type() { }
    virtual ~pointer_type_node(void) throw() { }
    virtual void apply(visitor &);
    virtual void apply(const_visitor &) const;
    boost::intrusive_ptr<node>  type;
};
struct template_type_node : node
{
    template_type_node(void) throw() :
        name(), template_args() { }
    virtual ~template_type_node(void) throw() { }
    virtual void apply(visitor &);
    virtual void apply(const_visitor &) const;
    std::string name;
    std::list<boost::intrusive_ptr<node> >  template_args;
};
struct list_type_node : node
{
    list_type_node(void) throw() :
        type() { }
    virtual ~list_type_node(void) throw() { }
    virtual void apply(visitor &);
    virtual void apply(const_visitor &) const;
    boost::intrusive_ptr<node>  type;
};
class visitor
{
public:
    virtual ~visitor(void) throw() { }
    virtual void visit(data_member_node &) = 0;
    virtual void visit(node_node &) = 0;
    virtual void visit(namespace_node &) = 0;
    virtual void visit(basic_type_node &) = 0;
    virtual void visit(reference_type_node &) = 0;
    virtual void visit(pointer_type_node &) = 0;
    virtual void visit(template_type_node &) = 0;
    virtual void visit(list_type_node &) = 0;
};
class const_visitor
{
public:
    virtual ~const_visitor(void) throw() { }
    virtual void visit(data_member_node const &) = 0;
    virtual void visit(node_node const &) = 0;
    virtual void visit(namespace_node const &) = 0;
    virtual void visit(basic_type_node const &) = 0;
    virtual void visit(reference_type_node const &) = 0;
    virtual void visit(pointer_type_node const &) = 0;
    virtual void visit(template_type_node const &) = 0;
    virtual void visit(list_type_node const &) = 0;
};
}
}
#endif
