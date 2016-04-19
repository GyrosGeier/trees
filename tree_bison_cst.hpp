#ifndef tree_bison_cst_hpp_
#define tree_bison_cst_hpp_ 1

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
#include <list>
namespace trees {
namespace tree {
namespace bison {
struct node;
typedef std::unique_ptr<node> node_ptr;
typedef node *node_weak_ptr;
struct node_const_visitor;
struct rules;
typedef std::unique_ptr<rules> rules_ptr;
typedef rules *rules_weak_ptr;
struct empty_rules;
typedef std::unique_ptr<empty_rules> empty_rules_ptr;
typedef empty_rules *empty_rules_weak_ptr;
struct chained_rules;
typedef std::unique_ptr<chained_rules> chained_rules_ptr;
typedef chained_rules *chained_rules_weak_ptr;
struct alternatives;
typedef std::unique_ptr<alternatives> alternatives_ptr;
typedef alternatives *alternatives_weak_ptr;
struct single_alternative;
typedef std::unique_ptr<single_alternative> single_alternative_ptr;
typedef single_alternative *single_alternative_weak_ptr;
struct chained_alternatives;
typedef std::unique_ptr<chained_alternatives> chained_alternatives_ptr;
typedef chained_alternatives *chained_alternatives_weak_ptr;
struct terminated_alternatives;
typedef std::unique_ptr<terminated_alternatives> terminated_alternatives_ptr;
typedef terminated_alternatives *terminated_alternatives_weak_ptr;
struct alternative;
typedef std::unique_ptr<alternative> alternative_ptr;
typedef alternative *alternative_weak_ptr;
struct unnamed_alternative;
typedef std::unique_ptr<unnamed_alternative> unnamed_alternative_ptr;
typedef unnamed_alternative *unnamed_alternative_weak_ptr;
struct named_alternative;
typedef std::unique_ptr<named_alternative> named_alternative_ptr;
typedef named_alternative *named_alternative_weak_ptr;
struct components;
typedef std::unique_ptr<components> components_ptr;
typedef components *components_weak_ptr;
struct empty_components;
typedef std::unique_ptr<empty_components> empty_components_ptr;
typedef empty_components *empty_components_weak_ptr;
struct chained_components;
typedef std::unique_ptr<chained_components> chained_components_ptr;
typedef chained_components *chained_components_weak_ptr;
struct component;
typedef std::unique_ptr<component> component_ptr;
typedef component *component_weak_ptr;
struct symbol;
typedef std::unique_ptr<symbol> symbol_ptr;
typedef symbol *symbol_weak_ptr;
struct literal;
typedef std::unique_ptr<literal> literal_ptr;
typedef literal *literal_weak_ptr;
struct start;
typedef std::unique_ptr<start> start_ptr;
typedef start *start_weak_ptr;
struct rule;
typedef std::unique_ptr<rule> rule_ptr;
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
class node_const_visitor
{
public:
        virtual ~node_const_visitor(void) throw() { }
        template<typename T>
        inline void descend(std::unique_ptr<T> const &p) { if(p) p->apply(*this); }
        virtual void visit(empty_rules const &) = 0;
        inline void descend(std::unique_ptr<empty_rules> const &p) { if(p) visit(*p); }
        virtual void visit(chained_rules const &) = 0;
        inline void descend(std::unique_ptr<chained_rules> const &p) { if(p) visit(*p); }
        virtual void visit(single_alternative const &) = 0;
        inline void descend(std::unique_ptr<single_alternative> const &p) { if(p) visit(*p); }
        virtual void visit(chained_alternatives const &) = 0;
        inline void descend(std::unique_ptr<chained_alternatives> const &p) { if(p) visit(*p); }
        virtual void visit(terminated_alternatives const &) = 0;
        inline void descend(std::unique_ptr<terminated_alternatives> const &p) { if(p) visit(*p); }
        virtual void visit(unnamed_alternative const &) = 0;
        inline void descend(std::unique_ptr<unnamed_alternative> const &p) { if(p) visit(*p); }
        virtual void visit(named_alternative const &) = 0;
        inline void descend(std::unique_ptr<named_alternative> const &p) { if(p) visit(*p); }
        virtual void visit(empty_components const &) = 0;
        inline void descend(std::unique_ptr<empty_components> const &p) { if(p) visit(*p); }
        virtual void visit(chained_components const &) = 0;
        inline void descend(std::unique_ptr<chained_components> const &p) { if(p) visit(*p); }
        virtual void visit(symbol const &) = 0;
        inline void descend(std::unique_ptr<symbol> const &p) { if(p) visit(*p); }
        virtual void visit(literal const &) = 0;
        inline void descend(std::unique_ptr<literal> const &p) { if(p) visit(*p); }
        virtual void visit(start const &) = 0;
        inline void descend(std::unique_ptr<start> const &p) { if(p) visit(*p); }
        virtual void visit(rule const &) = 0;
        inline void descend(std::unique_ptr<rule> const &p) { if(p) visit(*p); }
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
        chained_rules(std::unique_ptr< ::trees::tree::bison::rules>  _1, std::unique_ptr< ::trees::tree::bison::rule>  _2) throw() : 
                _1(std::move(_1)), _2(std::move(_2)) { }
        virtual ~chained_rules(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        std::unique_ptr< ::trees::tree::bison::rules>  _1;
        std::unique_ptr< ::trees::tree::bison::rule>  _2;
};
struct alternatives : node {
        alternatives(void) throw() { }
        virtual ~alternatives(void) throw() { }
};
struct single_alternative : alternatives
{
        single_alternative(std::unique_ptr< ::trees::tree::bison::alternative>  _1) throw() : 
                _1(std::move(_1)) { }
        virtual ~single_alternative(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        std::unique_ptr< ::trees::tree::bison::alternative>  _1;
};
struct chained_alternatives : alternatives
{
        chained_alternatives(std::unique_ptr< ::trees::tree::bison::alternatives>  _1, std::unique_ptr< ::trees::tree::bison::alternative>  _2) throw() : 
                _1(std::move(_1)), _2(std::move(_2)) { }
        virtual ~chained_alternatives(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        std::unique_ptr< ::trees::tree::bison::alternatives>  _1;
        std::unique_ptr< ::trees::tree::bison::alternative>  _2;
};
struct terminated_alternatives : alternatives
{
        terminated_alternatives(std::unique_ptr< ::trees::tree::bison::alternatives>  _1) throw() : 
                _1(std::move(_1)) { }
        virtual ~terminated_alternatives(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        std::unique_ptr< ::trees::tree::bison::alternatives>  _1;
};
struct alternative : node {
        alternative(void) throw() { }
        virtual ~alternative(void) throw() { }
};
struct unnamed_alternative : alternative
{
        unnamed_alternative(std::unique_ptr< ::trees::tree::bison::components>  _1) throw() : 
                _1(std::move(_1)) { }
        virtual ~unnamed_alternative(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        std::unique_ptr< ::trees::tree::bison::components>  _1;
};
struct named_alternative : alternative
{
        named_alternative(std::string _1, std::unique_ptr< ::trees::tree::bison::components>  _2) throw() : 
                _1(std::move(_1)), _2(std::move(_2)) { }
        virtual ~named_alternative(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        std::string _1;
        std::unique_ptr< ::trees::tree::bison::components>  _2;
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
        chained_components(std::unique_ptr< ::trees::tree::bison::components>  _1, std::unique_ptr< ::trees::tree::bison::component>  _2) throw() : 
                _1(std::move(_1)), _2(std::move(_2)) { }
        virtual ~chained_components(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        std::unique_ptr< ::trees::tree::bison::components>  _1;
        std::unique_ptr< ::trees::tree::bison::component>  _2;
};
struct component : node {
        component(void) throw() { }
        virtual ~component(void) throw() { }
};
struct symbol : component
{
        symbol(std::string _1) throw() : 
                _1(std::move(_1)) { }
        virtual ~symbol(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        std::string _1;
};
struct literal : component
{
        literal(std::string _1) throw() : 
                _1(std::move(_1)) { }
        virtual ~literal(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        std::string _1;
};
struct start : node
{
        start(std::unique_ptr< ::trees::tree::bison::rules>  _1) throw() : 
                _1(std::move(_1)) { }
        virtual ~start(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        std::unique_ptr< ::trees::tree::bison::rules>  _1;
};
struct rule : node
{
        rule(std::string _1, std::unique_ptr< ::trees::tree::bison::alternatives>  _2) throw() : 
                _1(std::move(_1)), _2(std::move(_2)) { }
        virtual ~rule(void) throw() { }
        virtual void apply(node_const_visitor &) const;
        std::string _1;
        std::unique_ptr< ::trees::tree::bison::alternatives>  _2;
};
}
}
}
#endif
