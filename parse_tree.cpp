#include <parse_tree.hpp>

namespace trees {
namespace parse {
node_ptr string_literal::apply(node_visitor &v)
{
        return v.visit(*this);
}
void string_literal::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
node_ptr unresolved_symbol::apply(node_visitor &v)
{
        return v.visit(*this);
}
void unresolved_symbol::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
node_ptr terminal::apply(node_visitor &v)
{
        return v.visit(*this);
}
void terminal::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
node_ptr nonterminal::apply(node_visitor &v)
{
        return v.visit(*this);
}
void nonterminal::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
node_ptr regex::apply(node_visitor &v)
{
        return v.visit(*this);
}
void regex::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
node_ptr group::apply(node_visitor &v)
{
        return v.visit(*this);
}
void group::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
node_ptr root::apply(node_visitor &v)
{
        return v.visit(*this);
}
void root::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
node_ptr rule::apply(node_visitor &v)
{
        return v.visit(*this);
}
void rule::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
node_ptr alternative::apply(node_visitor &v)
{
        return v.visit(*this);
}
void alternative::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
}
}
