#ifndef tree_bison_cst_hpp_
#define tree_bison_cst_hpp_ 1

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
#include <boost/intrusive_ptr.hpp>
#include <list>
namespace trees {
namespace tree {
namespace bison {
struct node;
typedef boost::intrusive_ptr<node> node_ptr;
typedef node *node_weak_ptr;
struct node_const_visitor;
struct rules;
typedef boost::intrusive_ptr<rules> rules_ptr;
typedef rules *rules_weak_ptr;
struct empty_rules;
typedef boost::intrusive_ptr<empty_rules> empty_rules_ptr;
typedef empty_rules *empty_rules_weak_ptr;
struct chained_rules;
typedef boost::intrusive_ptr<chained_rules> chained_rules_ptr;
typedef chained_rules *chained_rules_weak_ptr;
struct alternatives;
typedef boost::intrusive_ptr<alternatives> alternatives_ptr;
typedef alternatives *alternatives_weak_ptr;
struct single_alternative;
typedef boost::intrusive_ptr<single_alternative> single_alternative_ptr;
typedef single_alternative *single_alternative_weak_ptr;
struct chained_alternatives;
typedef boost::intrusive_ptr<chained_alternatives> chained_alternatives_ptr;
typedef chained_alternatives *chained_alternatives_weak_ptr;
struct terminated_alternatives;
typedef boost::intrusive_ptr<terminated_alternatives> terminated_alternatives_ptr;
typedef terminated_alternatives *terminated_alternatives_weak_ptr;
struct alternative;
typedef boost::intrusive_ptr<alternative> alternative_ptr;
typedef alternative *alternative_weak_ptr;
struct unnamed_alternative;
typedef boost::intrusive_ptr<unnamed_alternative> unnamed_alternative_ptr;
typedef unnamed_alternative *unnamed_alternative_weak_ptr;
struct named_alternative;
typedef boost::intrusive_ptr<named_alternative> named_alternative_ptr;
typedef named_alternative *named_alternative_weak_ptr;
struct components;
typedef boost::intrusive_ptr<components> components_ptr;
typedef components *components_weak_ptr;
struct empty_components;
typedef boost::intrusive_ptr<empty_components> empty_components_ptr;
typedef empty_components *empty_components_weak_ptr;
struct chained_components;
typedef boost::intrusive_ptr<chained_components> chained_components_ptr;
typedef chained_components *chained_components_weak_ptr;
struct component;
typedef boost::intrusive_ptr<component> component_ptr;
typedef component *component_weak_ptr;
struct symbol;
typedef boost::intrusive_ptr<symbol> symbol_ptr;
typedef symbol *symbol_weak_ptr;
struct literal;
typedef boost::intrusive_ptr<literal> literal_ptr;
typedef literal *literal_weak_ptr;
struct start;
typedef boost::intrusive_ptr<start> start_ptr;
typedef start *start_weak_ptr;
struct rule;
typedef boost::intrusive_ptr<rule> rule_ptr;
typedef rule *rule_weak_ptr;
}
}
}
namespace trees {
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
        virtual void visit(empty_rules const &) = 0;
        inline void descend(empty_rules const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<empty_rules> const &p) { if(p) descend(*p); }
        virtual void visit(chained_rules const &) = 0;
        inline void descend(chained_rules const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<chained_rules> const &p) { if(p) descend(*p); }
        virtual void visit(single_alternative const &) = 0;
        inline void descend(single_alternative const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<single_alternative> const &p) { if(p) descend(*p); }
        virtual void visit(chained_alternatives const &) = 0;
        inline void descend(chained_alternatives const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<chained_alternatives> const &p) { if(p) descend(*p); }
        virtual void visit(terminated_alternatives const &) = 0;
        inline void descend(terminated_alternatives const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<terminated_alternatives> const &p) { if(p) descend(*p); }
        virtual void visit(unnamed_alternative const &) = 0;
        inline void descend(unnamed_alternative const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<unnamed_alternative> const &p) { if(p) descend(*p); }
        virtual void visit(named_alternative const &) = 0;
        inline void descend(named_alternative const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<named_alternative> const &p) { if(p) descend(*p); }
        virtual void visit(empty_components const &) = 0;
        inline void descend(empty_components const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<empty_components> const &p) { if(p) descend(*p); }
        virtual void visit(chained_components const &) = 0;
        inline void descend(chained_components const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<chained_components> const &p) { if(p) descend(*p); }
        virtual void visit(symbol const &) = 0;
        inline void descend(symbol const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<symbol> const &p) { if(p) descend(*p); }
        virtual void visit(literal const &) = 0;
        inline void descend(literal const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<literal> const &p) { if(p) descend(*p); }
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
};
struct empty_rules : rules
{
        empty_rules() throw() { }
        virtual ~empty_rules(void) throw() { }
        virtual void apply(node_const_visitor &) const;
};
struct chained_rules : rules
{
        chained_rules(boost::intrusive_ptr< ::trees::tree::bison::rules>  _1, boost::intrusive_ptr< ::trees::tree::bison::rule>  _2) throw() : 
                _1(_1), _2(_2) { }
        virtual ~chained_rules(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        boost::intrusive_ptr< ::trees::tree::bison::rules>  _1;
        boost::intrusive_ptr< ::trees::tree::bison::rule>  _2;
};
struct alternatives : node {
        alternatives(void) throw() { }
        virtual ~alternatives(void) throw() { }
};
struct single_alternative : alternatives
{
        single_alternative(boost::intrusive_ptr< ::trees::tree::bison::alternative>  _1) throw() : 
                _1(_1) { }
        virtual ~single_alternative(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        boost::intrusive_ptr< ::trees::tree::bison::alternative>  _1;
};
struct chained_alternatives : alternatives
{
        chained_alternatives(boost::intrusive_ptr< ::trees::tree::bison::alternatives>  _1, boost::intrusive_ptr< ::trees::tree::bison::alternative>  _2) throw() : 
                _1(_1), _2(_2) { }
        virtual ~chained_alternatives(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        boost::intrusive_ptr< ::trees::tree::bison::alternatives>  _1;
        boost::intrusive_ptr< ::trees::tree::bison::alternative>  _2;
};
struct terminated_alternatives : alternatives
{
        terminated_alternatives(boost::intrusive_ptr< ::trees::tree::bison::alternatives>  _1) throw() : 
                _1(_1) { }
        virtual ~terminated_alternatives(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        boost::intrusive_ptr< ::trees::tree::bison::alternatives>  _1;
};
struct alternative : node {
        alternative(void) throw() { }
        virtual ~alternative(void) throw() { }
};
struct unnamed_alternative : alternative
{
        unnamed_alternative(boost::intrusive_ptr< ::trees::tree::bison::components>  _1) throw() : 
                _1(_1) { }
        virtual ~unnamed_alternative(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        boost::intrusive_ptr< ::trees::tree::bison::components>  _1;
};
struct named_alternative : alternative
{
        named_alternative(std::string _1, boost::intrusive_ptr< ::trees::tree::bison::components>  _2) throw() : 
                _1(_1), _2(_2) { }
        virtual ~named_alternative(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        std::string _1;
        boost::intrusive_ptr< ::trees::tree::bison::components>  _2;
};
struct components : node {
        components(void) throw() { }
        virtual ~components(void) throw() { }
};
struct empty_components : components
{
        empty_components() throw() { }
        virtual ~empty_components(void) throw() { }
        virtual void apply(node_const_visitor &) const;
};
struct chained_components : components
{
        chained_components(boost::intrusive_ptr< ::trees::tree::bison::components>  _1, boost::intrusive_ptr< ::trees::tree::bison::component>  _2) throw() : 
                _1(_1), _2(_2) { }
        virtual ~chained_components(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        boost::intrusive_ptr< ::trees::tree::bison::components>  _1;
        boost::intrusive_ptr< ::trees::tree::bison::component>  _2;
};
struct component : node {
        component(void) throw() { }
        virtual ~component(void) throw() { }
};
struct symbol : component
{
        symbol(std::string _1) throw() : 
                _1(_1) { }
        virtual ~symbol(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        std::string _1;
};
struct literal : component
{
        literal(std::string _1) throw() : 
                _1(_1) { }
        virtual ~literal(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        std::string _1;
};
struct start : node
{
        start(boost::intrusive_ptr< ::trees::tree::bison::rules>  _1) throw() : 
                _1(_1) { }
        virtual ~start(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        boost::intrusive_ptr< ::trees::tree::bison::rules>  _1;
};
struct rule : node
{
        rule(std::string _1, boost::intrusive_ptr< ::trees::tree::bison::alternatives>  _2) throw() : 
                _1(_1), _2(_2) { }
        virtual ~rule(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        std::string _1;
        boost::intrusive_ptr< ::trees::tree::bison::alternatives>  _2;
};
}
}
}
#endif
