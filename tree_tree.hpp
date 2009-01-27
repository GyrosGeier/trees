#ifndef stage2_tree_tree_hpp_
#define stage2_tree_tree_hpp_ 1

#include <string>
class const_visitor;

struct node
{
    virtual ~node(void) throw() { }
    virtual void apply(const_visitor &v) const = 0;
};

struct start;
struct rules;
struct rule;
struct alternatives;
struct components;
struct component;
struct symbol;

struct start :
    public node
{
    start(rules *_1) : _1(_1) { }
    virtual ~start(void) throw();

    virtual void apply(const_visitor &) const;

    rules *_1;
};

struct rules : public node
{
    virtual ~rules(void) throw() { }
};

struct rules_1 :
    public rules
{
    virtual ~rules_1(void) throw();

    virtual void apply(const_visitor &) const;

};

struct rules_2 :
    public rules
{
    rules_2(rules *_1, rule *_2) : _1(_1), _2(_2) { }
    virtual ~rules_2(void) throw();

    virtual void apply(const_visitor &) const;

    rules *_1;
    rule *_2;
};

struct rule :
    public node
{
    rule(std::string const &_1, alternatives *_2) : _1(_1), _2(_2) { }
    virtual ~rule(void) throw();

    virtual void apply(const_visitor &) const;

    std::string _1;
    alternatives *_2;
};

struct alternatives : public node
{
    virtual ~alternatives(void) throw() { }
};

struct alternatives_1 :
    public alternatives
{
    alternatives_1(components *_1) : _1(_1) { }
    virtual ~alternatives_1(void) throw();

    virtual void apply(const_visitor &) const;

    components *_1;
};

struct alternatives_2 :
    public alternatives
{
    alternatives_2(alternatives *_1, components *_2) : _1(_1), _2(_2) { }
    virtual ~alternatives_2(void) throw();

    virtual void apply(const_visitor &) const;

    alternatives *_1;
    components *_2;
};

struct alternatives_3 :
    public alternatives
{
    alternatives_3(alternatives *_1) : _1(_1) { }
    virtual ~alternatives_3(void) throw();

    virtual void apply(const_visitor &) const;

    alternatives *_1;
};

struct components : public node
{
    virtual ~components(void) throw() { }
};

struct components_1 :
    public components
{
    virtual ~components_1(void) throw();

    virtual void apply(const_visitor &) const;

};

struct components_2 :
    public components
{
    components_2(components *_1, component *_2) : _1(_1), _2(_2) { }
    virtual ~components_2(void) throw();

    virtual void apply(const_visitor &) const;

    components *_1;
    component *_2;
};

struct component : public node
{
    virtual ~component(void) throw() { }
};

struct component_1 :
    public component
{
    component_1(symbol *_1) : _1(_1) { }
    virtual ~component_1(void) throw();

    virtual void apply(const_visitor &) const;

    symbol *_1;
};

struct component_2 :
    public component
{
    component_2(std::string const &_1) : _1(_1) { }
    virtual ~component_2(void) throw();

    virtual void apply(const_visitor &) const;

    std::string _1;
};

struct symbol : public node
{
    virtual ~symbol(void) throw() { }
};

struct symbol_1 :
    public symbol
{
    symbol_1(std::string const &_1) : _1(_1) { }
    virtual ~symbol_1(void) throw();

    virtual void apply(const_visitor &) const;

    std::string _1;
};

struct symbol_2 :
    public symbol
{
    symbol_2(std::string const &_1) : _1(_1) { }
    virtual ~symbol_2(void) throw();

    virtual void apply(const_visitor &) const;

    std::string _1;
};


class const_visitor
{
public:
    virtual ~const_visitor(void) throw() { }

    virtual void visit(start const &) = 0;
    virtual void visit(rules_1 const &) = 0;
    virtual void visit(rules_2 const &) = 0;
    virtual void visit(rule const &) = 0;
    virtual void visit(alternatives_1 const &) = 0;
    virtual void visit(alternatives_2 const &) = 0;
    virtual void visit(alternatives_3 const &) = 0;
    virtual void visit(components_1 const &) = 0;
    virtual void visit(components_2 const &) = 0;
    virtual void visit(component_1 const &) = 0;
    virtual void visit(component_2 const &) = 0;
    virtual void visit(symbol_1 const &) = 0;
    virtual void visit(symbol_2 const &) = 0;
};

#endif
