#include <tree_tree.hpp>

start::~start(void) throw()
{
    delete _1;
}

void start::apply(const_visitor &v) const
{
    v.visit(*this);
}

rules_1::~rules_1(void) throw()
{
}

void rules_1::apply(const_visitor &v) const
{
    v.visit(*this);
}

rules_2::~rules_2(void) throw()
{
    delete _1;
    delete _2;
}

void rules_2::apply(const_visitor &v) const
{
    v.visit(*this);
}

rule::~rule(void) throw()
{
    delete _2;
}

void rule::apply(const_visitor &v) const
{
    v.visit(*this);
}

alternatives_1::~alternatives_1(void) throw()
{
    delete _1;
}

void alternatives_1::apply(const_visitor &v) const
{
    v.visit(*this);
}

alternatives_2::~alternatives_2(void) throw()
{
    delete _1;
    delete _2;
}

void alternatives_2::apply(const_visitor &v) const
{
    v.visit(*this);
}

alternatives_3::~alternatives_3(void) throw()
{
    delete _1;
}

void alternatives_3::apply(const_visitor &v) const
{
    v.visit(*this);
}

components_1::~components_1(void) throw()
{
}

void components_1::apply(const_visitor &v) const
{
    v.visit(*this);
}

components_2::~components_2(void) throw()
{
    delete _1;
    delete _2;
}

void components_2::apply(const_visitor &v) const
{
    v.visit(*this);
}

component_1::~component_1(void) throw()
{
    delete _1;
}

void component_1::apply(const_visitor &v) const
{
    v.visit(*this);
}

component_2::~component_2(void) throw()
{
}

void component_2::apply(const_visitor &v) const
{
    v.visit(*this);
}

symbol_1::~symbol_1(void) throw()
{
}

void symbol_1::apply(const_visitor &v) const
{
    v.visit(*this);
}

symbol_2::~symbol_2(void) throw()
{
}

void symbol_2::apply(const_visitor &v) const
{
    v.visit(*this);
}

