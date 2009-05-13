#ifndef tree_bison_tree_hpp_
#define tree_bison_tree_hpp_ 1

#include <string>
#include <boost/intrusive_ptr.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/intrusive_ptr.hpp>
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
namespace bison {
struct node;
typedef boost::intrusive_ptr<node> node_ptr;
typedef node *node_weak_ptr;
struct node_const_visitor;
struct rules;
typedef boost::intrusive_ptr<rules> rules_ptr;
typedef rules *rules_weak_ptr;
struct rules_1;
typedef boost::intrusive_ptr<rules_1> rules_1_ptr;
typedef rules_1 *rules_1_weak_ptr;
struct rules_2;
typedef boost::intrusive_ptr<rules_2> rules_2_ptr;
typedef rules_2 *rules_2_weak_ptr;
struct alternatives;
typedef boost::intrusive_ptr<alternatives> alternatives_ptr;
typedef alternatives *alternatives_weak_ptr;
struct alternatives_1;
typedef boost::intrusive_ptr<alternatives_1> alternatives_1_ptr;
typedef alternatives_1 *alternatives_1_weak_ptr;
struct alternatives_2;
typedef boost::intrusive_ptr<alternatives_2> alternatives_2_ptr;
typedef alternatives_2 *alternatives_2_weak_ptr;
struct alternatives_3;
typedef boost::intrusive_ptr<alternatives_3> alternatives_3_ptr;
typedef alternatives_3 *alternatives_3_weak_ptr;
struct components;
typedef boost::intrusive_ptr<components> components_ptr;
typedef components *components_weak_ptr;
struct components_1;
typedef boost::intrusive_ptr<components_1> components_1_ptr;
typedef components_1 *components_1_weak_ptr;
struct components_2;
typedef boost::intrusive_ptr<components_2> components_2_ptr;
typedef components_2 *components_2_weak_ptr;
struct component;
typedef boost::intrusive_ptr<component> component_ptr;
typedef component *component_weak_ptr;
struct component_1;
typedef boost::intrusive_ptr<component_1> component_1_ptr;
typedef component_1 *component_1_weak_ptr;
struct component_2;
typedef boost::intrusive_ptr<component_2> component_2_ptr;
typedef component_2 *component_2_weak_ptr;
struct symbol;
typedef boost::intrusive_ptr<symbol> symbol_ptr;
typedef symbol *symbol_weak_ptr;
struct symbol_1;
typedef boost::intrusive_ptr<symbol_1> symbol_1_ptr;
typedef symbol_1 *symbol_1_weak_ptr;
struct symbol_2;
typedef boost::intrusive_ptr<symbol_2> symbol_2_ptr;
typedef symbol_2 *symbol_2_weak_ptr;
struct start;
typedef boost::intrusive_ptr<start> start_ptr;
typedef start *start_weak_ptr;
struct rule;
typedef boost::intrusive_ptr<rule> rule_ptr;
typedef rule *rule_weak_ptr;
}
}
}
namespace foundry {
namespace tree {
namespace bison {
struct node {
    node(void) throw() : refcount(0) { }
    virtual ~node(void) throw() { }
    virtual void apply(node_const_visitor &) const = 0;
    unsigned int refcount;
};
inline void intrusive_ptr_add_ref(node *n) { ++n->refcount; }
inline void intrusive_ptr_release(node *n) { if(!--n->refcount) delete n; }
class node_const_visitor
{
public:
    virtual ~node_const_visitor(void) throw() { }
    inline void descend(node const &n) { n.apply(*this); }
    template<typename T>
    inline void descend(boost::intrusive_ptr<T> const &p) { if(p) descend(*p); }
    virtual void visit(rules_1 const &) = 0;
    inline void descend(rules_1 const &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<rules_1> const &p) { if(p) descend(*p); }
    virtual void visit(rules_2 const &) = 0;
    inline void descend(rules_2 const &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<rules_2> const &p) { if(p) descend(*p); }
    virtual void visit(alternatives_1 const &) = 0;
    inline void descend(alternatives_1 const &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<alternatives_1> const &p) { if(p) descend(*p); }
    virtual void visit(alternatives_2 const &) = 0;
    inline void descend(alternatives_2 const &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<alternatives_2> const &p) { if(p) descend(*p); }
    virtual void visit(alternatives_3 const &) = 0;
    inline void descend(alternatives_3 const &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<alternatives_3> const &p) { if(p) descend(*p); }
    virtual void visit(components_1 const &) = 0;
    inline void descend(components_1 const &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<components_1> const &p) { if(p) descend(*p); }
    virtual void visit(components_2 const &) = 0;
    inline void descend(components_2 const &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<components_2> const &p) { if(p) descend(*p); }
    virtual void visit(component_1 const &) = 0;
    inline void descend(component_1 const &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<component_1> const &p) { if(p) descend(*p); }
    virtual void visit(component_2 const &) = 0;
    inline void descend(component_2 const &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<component_2> const &p) { if(p) descend(*p); }
    virtual void visit(symbol_1 const &) = 0;
    inline void descend(symbol_1 const &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<symbol_1> const &p) { if(p) descend(*p); }
    virtual void visit(symbol_2 const &) = 0;
    inline void descend(symbol_2 const &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<symbol_2> const &p) { if(p) descend(*p); }
    virtual void visit(start const &) = 0;
    inline void descend(start const &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<start> const &p) { if(p) descend(*p); }
    virtual void visit(rule const &) = 0;
    inline void descend(rule const &n) { visit(n); }
    inline void descend(boost::intrusive_ptr<rule> const &p) { if(p) descend(*p); }
};
struct rules : node {
    rules(void) throw() { }
    virtual ~rules(void) throw() { }
    using node::apply;
};
struct rules_1 : rules
{
    rules_1() throw() { }
    virtual ~rules_1(void) throw() { }
    virtual void apply(node_const_visitor &) const;
};
struct rules_2 : rules
{
    rules_2(boost::intrusive_ptr< ::foundry::tree::bison::rules>  _1, boost::intrusive_ptr< ::foundry::tree::bison::rule>  _2) throw() : 
        _1(_1), _2(_2) { }
    virtual ~rules_2(void) throw() { }
    virtual void apply(node_const_visitor &) const;
    boost::intrusive_ptr< ::foundry::tree::bison::rules>  _1;
    boost::intrusive_ptr< ::foundry::tree::bison::rule>  _2;
};
struct alternatives : node {
    alternatives(void) throw() { }
    virtual ~alternatives(void) throw() { }
    using node::apply;
};
struct alternatives_1 : alternatives
{
    alternatives_1(boost::intrusive_ptr< ::foundry::tree::bison::components>  _1) throw() : 
        _1(_1) { }
    virtual ~alternatives_1(void) throw() { }
    virtual void apply(node_const_visitor &) const;
    boost::intrusive_ptr< ::foundry::tree::bison::components>  _1;
};
struct alternatives_2 : alternatives
{
    alternatives_2(boost::intrusive_ptr< ::foundry::tree::bison::alternatives>  _1, boost::intrusive_ptr< ::foundry::tree::bison::components>  _2) throw() : 
        _1(_1), _2(_2) { }
    virtual ~alternatives_2(void) throw() { }
    virtual void apply(node_const_visitor &) const;
    boost::intrusive_ptr< ::foundry::tree::bison::alternatives>  _1;
    boost::intrusive_ptr< ::foundry::tree::bison::components>  _2;
};
struct alternatives_3 : alternatives
{
    alternatives_3(boost::intrusive_ptr< ::foundry::tree::bison::alternatives>  _1) throw() : 
        _1(_1) { }
    virtual ~alternatives_3(void) throw() { }
    virtual void apply(node_const_visitor &) const;
    boost::intrusive_ptr< ::foundry::tree::bison::alternatives>  _1;
};
struct components : node {
    components(void) throw() { }
    virtual ~components(void) throw() { }
    using node::apply;
};
struct components_1 : components
{
    components_1() throw() { }
    virtual ~components_1(void) throw() { }
    virtual void apply(node_const_visitor &) const;
};
struct components_2 : components
{
    components_2(boost::intrusive_ptr< ::foundry::tree::bison::components>  _1, boost::intrusive_ptr< ::foundry::tree::bison::component>  _2) throw() : 
        _1(_1), _2(_2) { }
    virtual ~components_2(void) throw() { }
    virtual void apply(node_const_visitor &) const;
    boost::intrusive_ptr< ::foundry::tree::bison::components>  _1;
    boost::intrusive_ptr< ::foundry::tree::bison::component>  _2;
};
struct component : node {
    component(void) throw() { }
    virtual ~component(void) throw() { }
    using node::apply;
};
struct component_1 : component
{
    component_1(boost::intrusive_ptr< ::foundry::tree::bison::symbol>  _1) throw() : 
        _1(_1) { }
    virtual ~component_1(void) throw() { }
    virtual void apply(node_const_visitor &) const;
    boost::intrusive_ptr< ::foundry::tree::bison::symbol>  _1;
};
struct component_2 : component
{
    component_2(std::string _1) throw() : 
        _1(_1) { }
    virtual ~component_2(void) throw() { }
    virtual void apply(node_const_visitor &) const;
    std::string _1;
};
struct symbol : node {
    symbol(void) throw() { }
    virtual ~symbol(void) throw() { }
    using node::apply;
};
struct symbol_1 : symbol
{
    symbol_1(std::string _1) throw() : 
        _1(_1) { }
    virtual ~symbol_1(void) throw() { }
    virtual void apply(node_const_visitor &) const;
    std::string _1;
};
struct symbol_2 : symbol
{
    symbol_2(std::string _1) throw() : 
        _1(_1) { }
    virtual ~symbol_2(void) throw() { }
    virtual void apply(node_const_visitor &) const;
    std::string _1;
};
struct start : node
{
    start(boost::intrusive_ptr< ::foundry::tree::bison::rules>  _1) throw() : 
        _1(_1) { }
    virtual ~start(void) throw() { }
    virtual void apply(node_const_visitor &) const;
    boost::intrusive_ptr< ::foundry::tree::bison::rules>  _1;
};
struct rule : node
{
    rule(std::string _1, boost::intrusive_ptr< ::foundry::tree::bison::alternatives>  _2) throw() : 
        _1(_1), _2(_2) { }
    virtual ~rule(void) throw() { }
    virtual void apply(node_const_visitor &) const;
    std::string _1;
    boost::intrusive_ptr< ::foundry::tree::bison::alternatives>  _2;
};
}
}
}
#endif
