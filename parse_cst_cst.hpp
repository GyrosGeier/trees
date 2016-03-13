#ifndef parse_cst_cst_hpp_
#define parse_cst_cst_hpp_ 1

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
#include <boost/intrusive_ptr.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/intrusive_ptr.hpp>
#include <list>
namespace trees {
namespace parse {
namespace cst {
struct node;
typedef boost::intrusive_ptr<node> node_ptr;
typedef node *node_weak_ptr;
struct node_const_visitor;
struct directives;
typedef boost::intrusive_ptr<directives> directives_ptr;
typedef directives *directives_weak_ptr;
struct directives_chain;
typedef boost::intrusive_ptr<directives_chain> directives_chain_ptr;
typedef directives_chain *directives_chain_weak_ptr;
struct end_of_directives;
typedef boost::intrusive_ptr<end_of_directives> end_of_directives_ptr;
typedef end_of_directives *end_of_directives_weak_ptr;
struct rules;
typedef boost::intrusive_ptr<rules> rules_ptr;
typedef rules *rules_weak_ptr;
struct rules_chain;
typedef boost::intrusive_ptr<rules_chain> rules_chain_ptr;
typedef rules_chain *rules_chain_weak_ptr;
struct end_of_rules;
typedef boost::intrusive_ptr<end_of_rules> end_of_rules_ptr;
typedef end_of_rules *end_of_rules_weak_ptr;
struct alternatives_tail;
typedef boost::intrusive_ptr<alternatives_tail> alternatives_tail_ptr;
typedef alternatives_tail *alternatives_tail_weak_ptr;
struct more_alternatives;
typedef boost::intrusive_ptr<more_alternatives> more_alternatives_ptr;
typedef more_alternatives *more_alternatives_weak_ptr;
struct end_of_alternatives;
typedef boost::intrusive_ptr<end_of_alternatives> end_of_alternatives_ptr;
typedef end_of_alternatives *end_of_alternatives_weak_ptr;
struct alternative;
typedef boost::intrusive_ptr<alternative> alternative_ptr;
typedef alternative *alternative_weak_ptr;
struct unnamed_alternative;
typedef boost::intrusive_ptr<unnamed_alternative> unnamed_alternative_ptr;
typedef unnamed_alternative *unnamed_alternative_weak_ptr;
struct named_alternative;
typedef boost::intrusive_ptr<named_alternative> named_alternative_ptr;
typedef named_alternative *named_alternative_weak_ptr;
struct repetition_qualifier;
typedef boost::intrusive_ptr<repetition_qualifier> repetition_qualifier_ptr;
typedef repetition_qualifier *repetition_qualifier_weak_ptr;
struct no_repetition;
typedef boost::intrusive_ptr<no_repetition> no_repetition_ptr;
typedef no_repetition *no_repetition_weak_ptr;
struct zero_or_one;
typedef boost::intrusive_ptr<zero_or_one> zero_or_one_ptr;
typedef zero_or_one *zero_or_one_weak_ptr;
struct one_or_more;
typedef boost::intrusive_ptr<one_or_more> one_or_more_ptr;
typedef one_or_more *one_or_more_weak_ptr;
struct zero_or_more;
typedef boost::intrusive_ptr<zero_or_more> zero_or_more_ptr;
typedef zero_or_more *zero_or_more_weak_ptr;
struct component;
typedef boost::intrusive_ptr<component> component_ptr;
typedef component *component_weak_ptr;
struct symbol;
typedef boost::intrusive_ptr<symbol> symbol_ptr;
typedef symbol *symbol_weak_ptr;
struct literal;
typedef boost::intrusive_ptr<literal> literal_ptr;
typedef literal *literal_weak_ptr;
struct group;
typedef boost::intrusive_ptr<group> group_ptr;
typedef group *group_weak_ptr;
struct regex;
typedef boost::intrusive_ptr<regex> regex_ptr;
typedef regex *regex_weak_ptr;
struct components_1_list;
typedef boost::intrusive_ptr<components_1_list> components_1_list_ptr;
typedef components_1_list *components_1_list_weak_ptr;
struct components_1_chain;
typedef boost::intrusive_ptr<components_1_chain> components_1_chain_ptr;
typedef components_1_chain *components_1_chain_weak_ptr;
struct end_of_components_1;
typedef boost::intrusive_ptr<end_of_components_1> end_of_components_1_ptr;
typedef end_of_components_1 *end_of_components_1_weak_ptr;
struct start;
typedef boost::intrusive_ptr<start> start_ptr;
typedef start *start_weak_ptr;
struct rule;
typedef boost::intrusive_ptr<rule> rule_ptr;
typedef rule *rule_weak_ptr;
struct alternatives;
typedef boost::intrusive_ptr<alternatives> alternatives_ptr;
typedef alternatives *alternatives_weak_ptr;
struct components;
typedef boost::intrusive_ptr<components> components_ptr;
typedef components *components_weak_ptr;
struct components_1_elem;
typedef boost::intrusive_ptr<components_1_elem> components_1_elem_ptr;
typedef components_1_elem *components_1_elem_weak_ptr;
}
}
}
namespace trees {
namespace parse {
namespace cst {
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
        virtual void visit(directives_chain const &) = 0;
        inline void descend(directives_chain const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<directives_chain> const &p) { if(p) descend(*p); }
        virtual void visit(end_of_directives const &) = 0;
        inline void descend(end_of_directives const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<end_of_directives> const &p) { if(p) descend(*p); }
        virtual void visit(rules_chain const &) = 0;
        inline void descend(rules_chain const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<rules_chain> const &p) { if(p) descend(*p); }
        virtual void visit(end_of_rules const &) = 0;
        inline void descend(end_of_rules const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<end_of_rules> const &p) { if(p) descend(*p); }
        virtual void visit(more_alternatives const &) = 0;
        inline void descend(more_alternatives const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<more_alternatives> const &p) { if(p) descend(*p); }
        virtual void visit(end_of_alternatives const &) = 0;
        inline void descend(end_of_alternatives const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<end_of_alternatives> const &p) { if(p) descend(*p); }
        virtual void visit(unnamed_alternative const &) = 0;
        inline void descend(unnamed_alternative const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<unnamed_alternative> const &p) { if(p) descend(*p); }
        virtual void visit(named_alternative const &) = 0;
        inline void descend(named_alternative const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<named_alternative> const &p) { if(p) descend(*p); }
        virtual void visit(no_repetition const &) = 0;
        inline void descend(no_repetition const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<no_repetition> const &p) { if(p) descend(*p); }
        virtual void visit(zero_or_one const &) = 0;
        inline void descend(zero_or_one const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<zero_or_one> const &p) { if(p) descend(*p); }
        virtual void visit(one_or_more const &) = 0;
        inline void descend(one_or_more const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<one_or_more> const &p) { if(p) descend(*p); }
        virtual void visit(zero_or_more const &) = 0;
        inline void descend(zero_or_more const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<zero_or_more> const &p) { if(p) descend(*p); }
        virtual void visit(symbol const &) = 0;
        inline void descend(symbol const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<symbol> const &p) { if(p) descend(*p); }
        virtual void visit(literal const &) = 0;
        inline void descend(literal const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<literal> const &p) { if(p) descend(*p); }
        virtual void visit(group const &) = 0;
        inline void descend(group const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<group> const &p) { if(p) descend(*p); }
        virtual void visit(regex const &) = 0;
        inline void descend(regex const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<regex> const &p) { if(p) descend(*p); }
        virtual void visit(components_1_chain const &) = 0;
        inline void descend(components_1_chain const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<components_1_chain> const &p) { if(p) descend(*p); }
        virtual void visit(end_of_components_1 const &) = 0;
        inline void descend(end_of_components_1 const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<end_of_components_1> const &p) { if(p) descend(*p); }
        virtual void visit(start const &) = 0;
        inline void descend(start const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<start> const &p) { if(p) descend(*p); }
        virtual void visit(rule const &) = 0;
        inline void descend(rule const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<rule> const &p) { if(p) descend(*p); }
        virtual void visit(alternatives const &) = 0;
        inline void descend(alternatives const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<alternatives> const &p) { if(p) descend(*p); }
        virtual void visit(components const &) = 0;
        inline void descend(components const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<components> const &p) { if(p) descend(*p); }
        virtual void visit(components_1_elem const &) = 0;
        inline void descend(components_1_elem const &n) { visit(n); }
        inline void descend(boost::intrusive_ptr<components_1_elem> const &p) { if(p) descend(*p); }
};
struct directives : node {
        directives(void) throw() { }
        virtual ~directives(void) throw() { }
};
struct directives_chain : directives
{
        directives_chain(std::string _1, boost::intrusive_ptr< ::trees::parse::cst::directives>  _2) throw() : 
                _1(_1), _2(_2) { }
        virtual ~directives_chain(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        std::string _1;
        boost::intrusive_ptr< ::trees::parse::cst::directives>  _2;
};
struct end_of_directives : directives
{
        end_of_directives() throw() { }
        virtual ~end_of_directives(void) throw() { }
        virtual void apply(node_const_visitor &) const;
};
struct rules : node {
        rules(void) throw() { }
        virtual ~rules(void) throw() { }
};
struct rules_chain : rules
{
        rules_chain(boost::intrusive_ptr< ::trees::parse::cst::rule>  _1, boost::intrusive_ptr< ::trees::parse::cst::rules>  _2) throw() : 
                _1(_1), _2(_2) { }
        virtual ~rules_chain(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        boost::intrusive_ptr< ::trees::parse::cst::rule>  _1;
        boost::intrusive_ptr< ::trees::parse::cst::rules>  _2;
};
struct end_of_rules : rules
{
        end_of_rules() throw() { }
        virtual ~end_of_rules(void) throw() { }
        virtual void apply(node_const_visitor &) const;
};
struct alternatives_tail : node {
        alternatives_tail(void) throw() { }
        virtual ~alternatives_tail(void) throw() { }
};
struct more_alternatives : alternatives_tail
{
        more_alternatives(boost::intrusive_ptr< ::trees::parse::cst::alternatives>  _1) throw() : 
                _1(_1) { }
        virtual ~more_alternatives(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        boost::intrusive_ptr< ::trees::parse::cst::alternatives>  _1;
};
struct end_of_alternatives : alternatives_tail
{
        end_of_alternatives() throw() { }
        virtual ~end_of_alternatives(void) throw() { }
        virtual void apply(node_const_visitor &) const;
};
struct alternative : node {
        alternative(void) throw() { }
        virtual ~alternative(void) throw() { }
};
struct unnamed_alternative : alternative
{
        unnamed_alternative(boost::intrusive_ptr< ::trees::parse::cst::components>  _1) throw() : 
                _1(_1) { }
        virtual ~unnamed_alternative(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        boost::intrusive_ptr< ::trees::parse::cst::components>  _1;
};
struct named_alternative : alternative
{
        named_alternative(std::string _1, boost::intrusive_ptr< ::trees::parse::cst::components>  _2) throw() : 
                _1(_1), _2(_2) { }
        virtual ~named_alternative(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        std::string _1;
        boost::intrusive_ptr< ::trees::parse::cst::components>  _2;
};
struct repetition_qualifier : node {
        repetition_qualifier(void) throw() { }
        virtual ~repetition_qualifier(void) throw() { }
};
struct no_repetition : repetition_qualifier
{
        no_repetition() throw() { }
        virtual ~no_repetition(void) throw() { }
        virtual void apply(node_const_visitor &) const;
};
struct zero_or_one : repetition_qualifier
{
        zero_or_one() throw() { }
        virtual ~zero_or_one(void) throw() { }
        virtual void apply(node_const_visitor &) const;
};
struct one_or_more : repetition_qualifier
{
        one_or_more() throw() { }
        virtual ~one_or_more(void) throw() { }
        virtual void apply(node_const_visitor &) const;
};
struct zero_or_more : repetition_qualifier
{
        zero_or_more() throw() { }
        virtual ~zero_or_more(void) throw() { }
        virtual void apply(node_const_visitor &) const;
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
struct group : component
{
        group(boost::intrusive_ptr< ::trees::parse::cst::components>  _1) throw() : 
                _1(_1) { }
        virtual ~group(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        boost::intrusive_ptr< ::trees::parse::cst::components>  _1;
};
struct regex : component
{
        regex(std::string _1) throw() : 
                _1(_1) { }
        virtual ~regex(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        std::string _1;
};
struct components_1_list : node {
        components_1_list(void) throw() { }
        virtual ~components_1_list(void) throw() { }
};
struct components_1_chain : components_1_list
{
        components_1_chain(boost::intrusive_ptr< ::trees::parse::cst::components_1_elem>  _1, boost::intrusive_ptr< ::trees::parse::cst::components_1_list>  _2) throw() : 
                _1(_1), _2(_2) { }
        virtual ~components_1_chain(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        boost::intrusive_ptr< ::trees::parse::cst::components_1_elem>  _1;
        boost::intrusive_ptr< ::trees::parse::cst::components_1_list>  _2;
};
struct end_of_components_1 : components_1_list
{
        end_of_components_1() throw() { }
        virtual ~end_of_components_1(void) throw() { }
        virtual void apply(node_const_visitor &) const;
};
struct start : node
{
        start(boost::intrusive_ptr< ::trees::parse::cst::directives>  _1, boost::intrusive_ptr< ::trees::parse::cst::rules>  _2) throw() : 
                _1(_1), _2(_2) { }
        virtual ~start(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        boost::intrusive_ptr< ::trees::parse::cst::directives>  _1;
        boost::intrusive_ptr< ::trees::parse::cst::rules>  _2;
};
struct rule : node
{
        rule(std::string _1, boost::intrusive_ptr< ::trees::parse::cst::alternatives>  _2) throw() : 
                _1(_1), _2(_2) { }
        virtual ~rule(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        std::string _1;
        boost::intrusive_ptr< ::trees::parse::cst::alternatives>  _2;
};
struct alternatives : node
{
        alternatives(boost::intrusive_ptr< ::trees::parse::cst::alternative>  _1, boost::intrusive_ptr< ::trees::parse::cst::alternatives_tail>  _2) throw() : 
                _1(_1), _2(_2) { }
        virtual ~alternatives(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        boost::intrusive_ptr< ::trees::parse::cst::alternative>  _1;
        boost::intrusive_ptr< ::trees::parse::cst::alternatives_tail>  _2;
};
struct components : node
{
        components(boost::intrusive_ptr< ::trees::parse::cst::components_1_list>  _1) throw() : 
                _1(_1) { }
        virtual ~components(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        boost::intrusive_ptr< ::trees::parse::cst::components_1_list>  _1;
};
struct components_1_elem : node
{
        components_1_elem(boost::intrusive_ptr< ::trees::parse::cst::component>  _1, boost::intrusive_ptr< ::trees::parse::cst::repetition_qualifier>  _2) throw() : 
                _1(_1), _2(_2) { }
        virtual ~components_1_elem(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        boost::intrusive_ptr< ::trees::parse::cst::component>  _1;
        boost::intrusive_ptr< ::trees::parse::cst::repetition_qualifier>  _2;
};
}
}
}
#endif
