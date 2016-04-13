#ifndef parse_tree_hpp_
#define parse_tree_hpp_ 1

#include <parse.h>
#include <string>
#include <boost/intrusive_ptr.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/intrusive_ptr.hpp>
#include <list>
namespace trees {
namespace parse {
struct node;
typedef boost::intrusive_ptr<node> node_ptr;
typedef node *node_weak_ptr;
struct node_const_visitor;
struct node_visitor;
struct component;
typedef boost::intrusive_ptr<component> component_ptr;
typedef component *component_weak_ptr;
struct component_visitor;
struct string_literal;
typedef boost::intrusive_ptr<string_literal> string_literal_ptr;
typedef string_literal *string_literal_weak_ptr;
struct unresolved_symbol;
typedef boost::intrusive_ptr<unresolved_symbol> unresolved_symbol_ptr;
typedef unresolved_symbol *unresolved_symbol_weak_ptr;
struct terminal;
typedef boost::intrusive_ptr<terminal> terminal_ptr;
typedef terminal *terminal_weak_ptr;
struct nonterminal;
typedef boost::intrusive_ptr<nonterminal> nonterminal_ptr;
typedef nonterminal *nonterminal_weak_ptr;
struct regex;
typedef boost::intrusive_ptr<regex> regex_ptr;
typedef regex *regex_weak_ptr;
struct group;
typedef boost::intrusive_ptr<group> group_ptr;
typedef group *group_weak_ptr;
struct root;
typedef boost::intrusive_ptr<root> root_ptr;
typedef root *root_weak_ptr;
struct rule;
typedef boost::intrusive_ptr<rule> rule_ptr;
typedef rule *rule_weak_ptr;
struct alternative;
typedef boost::intrusive_ptr<alternative> alternative_ptr;
typedef alternative *alternative_weak_ptr;
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
        virtual component_ptr visit(string_literal &) = 0;
        virtual component_ptr visit(unresolved_symbol &) = 0;
        virtual component_ptr visit(terminal &) = 0;
        virtual component_ptr visit(nonterminal &) = 0;
        virtual component_ptr visit(regex &) = 0;
        virtual component_ptr visit(group &) = 0;
        virtual node_ptr visit(root &) = 0;
        virtual node_ptr visit(rule &) = 0;
        virtual node_ptr visit(alternative &) = 0;
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
        virtual void visit(string_literal const &) = 0;
        inline void descend(boost::intrusive_ptr<string_literal> const &p) { if(p) visit(*p); }
        virtual void visit(unresolved_symbol const &) = 0;
        inline void descend(boost::intrusive_ptr<unresolved_symbol> const &p) { if(p) visit(*p); }
        virtual void visit(terminal const &) = 0;
        inline void descend(boost::intrusive_ptr<terminal> const &p) { if(p) visit(*p); }
        virtual void visit(nonterminal const &) = 0;
        inline void descend(boost::intrusive_ptr<nonterminal> const &p) { if(p) visit(*p); }
        virtual void visit(regex const &) = 0;
        inline void descend(boost::intrusive_ptr<regex> const &p) { if(p) visit(*p); }
        virtual void visit(group const &) = 0;
        inline void descend(boost::intrusive_ptr<group> const &p) { if(p) visit(*p); }
        virtual void visit(root const &) = 0;
        inline void descend(boost::intrusive_ptr<root> const &p) { if(p) visit(*p); }
        virtual void visit(rule const &) = 0;
        inline void descend(boost::intrusive_ptr<rule> const &p) { if(p) visit(*p); }
        virtual void visit(alternative const &) = 0;
        inline void descend(boost::intrusive_ptr<alternative> const &p) { if(p) visit(*p); }
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
        inline void descend(boost::intrusive_ptr<T> const &p) { if(p) p->apply(*this); }
        template<typename T, typename Alloc>
        inline void descend(std::list<T, Alloc> &l)
        {
                for(typename std::list<T, Alloc>::iterator i = l.begin(); i != l.end(); ++i)
                        descend(*i);
        }
        virtual component_ptr visit(string_literal &) = 0;
        virtual component_ptr visit(unresolved_symbol &) = 0;
        virtual component_ptr visit(terminal &) = 0;
        virtual component_ptr visit(nonterminal &) = 0;
        virtual component_ptr visit(regex &) = 0;
        virtual component_ptr visit(group &) = 0;
};
struct string_literal : component
{
        string_literal() throw() { }
        virtual ~string_literal(void) throw() { }
        virtual component_ptr apply(component_visitor &);
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        std::string text;
};
struct unresolved_symbol : component
{
        unresolved_symbol() throw() { }
        virtual ~unresolved_symbol(void) throw() { }
        virtual component_ptr apply(component_visitor &);
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
};
struct terminal : component
{
        terminal() throw() { }
        virtual ~terminal(void) throw() { }
        virtual component_ptr apply(component_visitor &);
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
};
struct nonterminal : component
{
        nonterminal() throw() { }
        virtual ~nonterminal(void) throw() { }
        virtual component_ptr apply(component_visitor &);
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        boost::intrusive_ptr< ::trees::parse::rule>  rule;
};
struct regex : component
{
        regex() throw() { }
        virtual ~regex(void) throw() { }
        virtual component_ptr apply(component_visitor &);
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        std::string text;
};
struct group : component
{
        group() throw() { }
        virtual ~group(void) throw() { }
        virtual component_ptr apply(component_visitor &);
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        std::list<boost::intrusive_ptr< ::trees::parse::component> >  components;
        repetition rep;
};
struct root : node
{
        root() throw() { }
        virtual ~root(void) throw() { }
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        std::string ns;
        std::list<boost::intrusive_ptr< ::trees::parse::rule> >  rules;
        std::list<boost::intrusive_ptr< ::trees::parse::string_literal> >  literals;
        std::list<boost::intrusive_ptr< ::trees::parse::regex> >  regexes;
};
struct rule : node
{
        rule() throw() { }
        virtual ~rule(void) throw() { }
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        std::string name;
        std::list<boost::intrusive_ptr< ::trees::parse::alternative> >  alternatives;
};
struct alternative : node
{
        alternative() throw() { }
        virtual ~alternative(void) throw() { }
        virtual node_ptr apply(node_visitor &);
        virtual void apply(node_const_visitor &) const;
        std::string name;
        boost::intrusive_ptr< ::trees::parse::group>  group;
};
}
}
#endif
