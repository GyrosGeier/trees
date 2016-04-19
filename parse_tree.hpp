#ifndef parse_tree_hpp_
#define parse_tree_hpp_ 1

#include <parse.h>
#include <string>
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
namespace parse {
struct node;
typedef std::shared_ptr<node> node_ptr;
typedef std::weak_ptr<node> node_weak_ptr;
struct node_const_visitor;
struct node_visitor;
struct component;
typedef std::shared_ptr<component> component_ptr;
typedef std::weak_ptr<component> component_weak_ptr;
struct component_visitor;
struct string_literal;
typedef std::shared_ptr<string_literal> string_literal_ptr;
typedef std::weak_ptr<string_literal> string_literal_weak_ptr;
struct unresolved_symbol;
typedef std::shared_ptr<unresolved_symbol> unresolved_symbol_ptr;
typedef std::weak_ptr<unresolved_symbol> unresolved_symbol_weak_ptr;
struct terminal;
typedef std::shared_ptr<terminal> terminal_ptr;
typedef std::weak_ptr<terminal> terminal_weak_ptr;
struct nonterminal;
typedef std::shared_ptr<nonterminal> nonterminal_ptr;
typedef std::weak_ptr<nonterminal> nonterminal_weak_ptr;
struct regex;
typedef std::shared_ptr<regex> regex_ptr;
typedef std::weak_ptr<regex> regex_weak_ptr;
struct group;
typedef std::shared_ptr<group> group_ptr;
typedef std::weak_ptr<group> group_weak_ptr;
struct root;
typedef std::shared_ptr<root> root_ptr;
typedef std::weak_ptr<root> root_weak_ptr;
struct rule;
typedef std::shared_ptr<rule> rule_ptr;
typedef std::weak_ptr<rule> rule_weak_ptr;
struct alternative;
typedef std::shared_ptr<alternative> alternative_ptr;
typedef std::weak_ptr<alternative> alternative_weak_ptr;
}
}
namespace trees {
namespace parse {
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
        virtual component_ptr visit(string_literal_ptr) = 0;
        virtual component_ptr visit(unresolved_symbol_ptr) = 0;
        virtual component_ptr visit(terminal_ptr) = 0;
        virtual component_ptr visit(nonterminal_ptr) = 0;
        virtual component_ptr visit(regex_ptr) = 0;
        virtual component_ptr visit(group_ptr) = 0;
        virtual node_ptr visit(root_ptr) = 0;
        virtual node_ptr visit(rule_ptr) = 0;
        virtual node_ptr visit(alternative_ptr) = 0;
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
        virtual void visit(string_literal const &) = 0;
        inline void descend(std::shared_ptr<string_literal> const &p) { if(p) visit(*p); }
        virtual void visit(unresolved_symbol const &) = 0;
        inline void descend(std::shared_ptr<unresolved_symbol> const &p) { if(p) visit(*p); }
        virtual void visit(terminal const &) = 0;
        inline void descend(std::shared_ptr<terminal> const &p) { if(p) visit(*p); }
        virtual void visit(nonterminal const &) = 0;
        inline void descend(std::shared_ptr<nonterminal> const &p) { if(p) visit(*p); }
        virtual void visit(regex const &) = 0;
        inline void descend(std::shared_ptr<regex> const &p) { if(p) visit(*p); }
        virtual void visit(group const &) = 0;
        inline void descend(std::shared_ptr<group> const &p) { if(p) visit(*p); }
        virtual void visit(root const &) = 0;
        inline void descend(std::shared_ptr<root> const &p) { if(p) visit(*p); }
        virtual void visit(rule const &) = 0;
        inline void descend(std::shared_ptr<rule> const &p) { if(p) visit(*p); }
        virtual void visit(alternative const &) = 0;
        inline void descend(std::shared_ptr<alternative> const &p) { if(p) visit(*p); }
};
struct component : node {
        component(void) throw() { }
        virtual ~component(void) throw() { }
        virtual component_ptr apply(component_visitor &) = 0;
        using node::apply;
        std::string name;
};
class component_visitor
{
public:
        virtual ~component_visitor(void) throw() { }
        template<typename T>
        inline void descend(std::shared_ptr<T> &p) { if(p) p = p->apply(*this); }
        template<typename T, typename Alloc>
        inline void descend(std::list<T, Alloc> &l)
        {
                for(typename std::list<T, Alloc>::iterator i = l.begin(); i != l.end(); ++i)
                        descend(*i);
        }
        virtual component_ptr visit(string_literal_ptr) = 0;
        virtual component_ptr visit(unresolved_symbol_ptr) = 0;
        virtual component_ptr visit(terminal_ptr) = 0;
        virtual component_ptr visit(nonterminal_ptr) = 0;
        virtual component_ptr visit(regex_ptr) = 0;
        virtual component_ptr visit(group_ptr) = 0;
};
struct string_literal : component
, std::enable_shared_from_this<string_literal>{
        string_literal() throw() { }
        virtual ~string_literal(void) throw() { }
        virtual component_ptr apply(component_visitor &);
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        std::string text;
};
struct unresolved_symbol : component
, std::enable_shared_from_this<unresolved_symbol>{
        unresolved_symbol() throw() { }
        virtual ~unresolved_symbol(void) throw() { }
        virtual component_ptr apply(component_visitor &);
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
};
struct terminal : component
, std::enable_shared_from_this<terminal>{
        terminal() throw() { }
        virtual ~terminal(void) throw() { }
        virtual component_ptr apply(component_visitor &);
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
};
struct nonterminal : component
, std::enable_shared_from_this<nonterminal>{
        nonterminal() throw() { }
        virtual ~nonterminal(void) throw() { }
        virtual component_ptr apply(component_visitor &);
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        std::shared_ptr< ::trees::parse::rule>  rule;
};
struct regex : component
, std::enable_shared_from_this<regex>{
        regex() throw() { }
        virtual ~regex(void) throw() { }
        virtual component_ptr apply(component_visitor &);
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        std::string text;
};
struct group : component
, std::enable_shared_from_this<group>{
        group() throw() { }
        virtual ~group(void) throw() { }
        virtual component_ptr apply(component_visitor &);
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        std::list<std::shared_ptr< ::trees::parse::component> >  components;
        repetition rep;
};
struct root : node
, std::enable_shared_from_this<root>{
        root() throw() { }
        virtual ~root(void) throw() { }
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        std::string ns;
        std::list<std::shared_ptr< ::trees::parse::rule> >  rules;
        std::list<std::shared_ptr< ::trees::parse::string_literal> >  literals;
        std::list<std::shared_ptr< ::trees::parse::regex> >  regexes;
};
struct rule : node
, std::enable_shared_from_this<rule>{
        rule() throw() { }
        virtual ~rule(void) throw() { }
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        std::string name;
        std::list<std::shared_ptr< ::trees::parse::alternative> >  alternatives;
};
struct alternative : node
, std::enable_shared_from_this<alternative>{
        alternative() throw() { }
        virtual ~alternative(void) throw() { }
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        std::string name;
        std::shared_ptr< ::trees::parse::group>  group;
};
}
}
#endif
