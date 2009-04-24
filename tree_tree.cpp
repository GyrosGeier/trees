#include <tree_tree.hpp>

namespace treecc {

start::~start(void) throw()
{
    delete _1;
}

rules_1::~rules_1(void) throw()
{
}

rules_2::~rules_2(void) throw()
{
    delete _1;
    delete _2;
}

rule::~rule(void) throw()
{
    delete _2;
}

alternatives_1::~alternatives_1(void) throw()
{
    delete _1;
}

alternatives_2::~alternatives_2(void) throw()
{
    delete _1;
    delete _2;
}

alternatives_3::~alternatives_3(void) throw()
{
    delete _1;
}

components_1::~components_1(void) throw()
{
}

components_2::~components_2(void) throw()
{
    delete _1;
    delete _2;
}

component_1::~component_1(void) throw()
{
    delete _1;
}

component_2::~component_2(void) throw()
{
}

symbol_1::~symbol_1(void) throw()
{
}

symbol_2::~symbol_2(void) throw()
{
}

void start::apply(const_visitor &v) const
{
    v.visit(*this);
}

void rules_1::apply(const_visitor &v) const
{
    v.visit(*this);
}

void rules_2::apply(const_visitor &v) const
{
    v.visit(*this);
}

void rule::apply(const_visitor &v) const
{
    v.visit(*this);
}

void alternatives_1::apply(const_visitor &v) const
{
    v.visit(*this);
}

void alternatives_2::apply(const_visitor &v) const
{
    v.visit(*this);
}

void alternatives_3::apply(const_visitor &v) const
{
    v.visit(*this);
}

void components_1::apply(const_visitor &v) const
{
    v.visit(*this);
}

void components_2::apply(const_visitor &v) const
{
    v.visit(*this);
}

void component_1::apply(const_visitor &v) const
{
    v.visit(*this);
}

void component_2::apply(const_visitor &v) const
{
    v.visit(*this);
}

void symbol_1::apply(const_visitor &v) const
{
    v.visit(*this);
}

void symbol_2::apply(const_visitor &v) const
{
    v.visit(*this);
}

void start::apply(visitor &v)
{
    v.visit(*this);
}

void rules_1::apply(visitor &v)
{
    v.visit(*this);
}

void rules_2::apply(visitor &v)
{
    v.visit(*this);
}

void rule::apply(visitor &v)
{
    v.visit(*this);
}

void alternatives_1::apply(visitor &v)
{
    v.visit(*this);
}

void alternatives_2::apply(visitor &v)
{
    v.visit(*this);
}

void alternatives_3::apply(visitor &v)
{
    v.visit(*this);
}

void components_1::apply(visitor &v)
{
    v.visit(*this);
}

void components_2::apply(visitor &v)
{
    v.visit(*this);
}

void component_1::apply(visitor &v)
{
    v.visit(*this);
}

void component_2::apply(visitor &v)
{
    v.visit(*this);
}

void symbol_1::apply(visitor &v)
{
    v.visit(*this);
}

void symbol_2::apply(visitor &v)
{
    v.visit(*this);
}

void throw_const_visitor::visit(start const &)
{
    throw invalid_state("start", typeid(*this));
}

void throw_const_visitor::visit(rules_1 const &)
{
    throw invalid_state("rules_1", typeid(*this));
}

void throw_const_visitor::visit(rules_2 const &)
{
    throw invalid_state("rules_2", typeid(*this));
}

void throw_const_visitor::visit(rule const &)
{
    throw invalid_state("rule", typeid(*this));
}

void throw_const_visitor::visit(alternatives_1 const &)
{
    throw invalid_state("alternatives_1", typeid(*this));
}

void throw_const_visitor::visit(alternatives_2 const &)
{
    throw invalid_state("alternatives_2", typeid(*this));
}

void throw_const_visitor::visit(alternatives_3 const &)
{
    throw invalid_state("alternatives_3", typeid(*this));
}

void throw_const_visitor::visit(components_1 const &)
{
    throw invalid_state("components_1", typeid(*this));
}

void throw_const_visitor::visit(components_2 const &)
{
    throw invalid_state("components_2", typeid(*this));
}

void throw_const_visitor::visit(component_1 const &)
{
    throw invalid_state("component_1", typeid(*this));
}

void throw_const_visitor::visit(component_2 const &)
{
    throw invalid_state("component_2", typeid(*this));
}

void throw_const_visitor::visit(symbol_1 const &)
{
    throw invalid_state("symbol_1", typeid(*this));
}

void throw_const_visitor::visit(symbol_2 const &)
{
    throw invalid_state("symbol_2", typeid(*this));
}

void throw_visitor::visit(start &)
{
    throw invalid_state("start", typeid(*this));
}

void throw_visitor::visit(rules_1 &)
{
    throw invalid_state("rules_1", typeid(*this));
}

void throw_visitor::visit(rules_2 &)
{
    throw invalid_state("rules_2", typeid(*this));
}

void throw_visitor::visit(rule &)
{
    throw invalid_state("rule", typeid(*this));
}

void throw_visitor::visit(alternatives_1 &)
{
    throw invalid_state("alternatives_1", typeid(*this));
}

void throw_visitor::visit(alternatives_2 &)
{
    throw invalid_state("alternatives_2", typeid(*this));
}

void throw_visitor::visit(alternatives_3 &)
{
    throw invalid_state("alternatives_3", typeid(*this));
}

void throw_visitor::visit(components_1 &)
{
    throw invalid_state("components_1", typeid(*this));
}

void throw_visitor::visit(components_2 &)
{
    throw invalid_state("components_2", typeid(*this));
}

void throw_visitor::visit(component_1 &)
{
    throw invalid_state("component_1", typeid(*this));
}

void throw_visitor::visit(component_2 &)
{
    throw invalid_state("component_2", typeid(*this));
}

void throw_visitor::visit(symbol_1 &)
{
    throw invalid_state("symbol_1", typeid(*this));
}

void throw_visitor::visit(symbol_2 &)
{
    throw invalid_state("symbol_2", typeid(*this));
}

void descend_const_visitor::visit(start const &node)
{
    node._1->apply(*this);
}

void descend_const_visitor::visit(rules_1 const &)
{
}

void descend_const_visitor::visit(rules_2 const &node)
{
    node._1->apply(*this);
    node._2->apply(*this);
}

void descend_const_visitor::visit(rule const &node)
{
    node._2->apply(*this);
}

void descend_const_visitor::visit(alternatives_1 const &node)
{
    node._1->apply(*this);
}

void descend_const_visitor::visit(alternatives_2 const &node)
{
    node._1->apply(*this);
    node._2->apply(*this);
}

void descend_const_visitor::visit(alternatives_3 const &node)
{
    node._1->apply(*this);
}

void descend_const_visitor::visit(components_1 const &)
{
}

void descend_const_visitor::visit(components_2 const &node)
{
    node._1->apply(*this);
    node._2->apply(*this);
}

void descend_const_visitor::visit(component_1 const &node)
{
    node._1->apply(*this);
}

void descend_const_visitor::visit(component_2 const &node)
{
}

void descend_const_visitor::visit(symbol_1 const &node)
{
}

void descend_const_visitor::visit(symbol_2 const &node)
{
}

void descend_visitor::visit(start &node)
{
    node._1->apply(*this);
}

void descend_visitor::visit(rules_1 &)
{
}

void descend_visitor::visit(rules_2 &node)
{
    node._1->apply(*this);
    node._2->apply(*this);
}

void descend_visitor::visit(rule &node)
{
    node._2->apply(*this);
}

void descend_visitor::visit(alternatives_1 &node)
{
    node._1->apply(*this);
}

void descend_visitor::visit(alternatives_2 &node)
{
    node._1->apply(*this);
    node._2->apply(*this);
}

void descend_visitor::visit(alternatives_3 &node)
{
    node._1->apply(*this);
}

void descend_visitor::visit(components_1 &)
{
}

void descend_visitor::visit(components_2 &node)
{
    node._1->apply(*this);
    node._2->apply(*this);
}

void descend_visitor::visit(component_1 &node)
{
    node._1->apply(*this);
}

void descend_visitor::visit(component_2 &node)
{
}

void descend_visitor::visit(symbol_1 &node)
{
}

void descend_visitor::visit(symbol_2 &node)
{
}


}
