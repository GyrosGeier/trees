#include <parse_tree.hpp>

namespace foundry {
namespace parse {
void string_literal::apply(node_visitor &v)
{
        v.visit(*this);
}
void string_literal::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void unresolved_symbol::apply(node_visitor &v)
{
        v.visit(*this);
}
void unresolved_symbol::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void terminal::apply(node_visitor &v)
{
        v.visit(*this);
}
void terminal::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void nonterminal::apply(node_visitor &v)
{
        v.visit(*this);
}
void nonterminal::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void regex::apply(node_visitor &v)
{
        v.visit(*this);
}
void regex::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void group::apply(node_visitor &v)
{
        v.visit(*this);
}
void group::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void root::apply(node_visitor &v)
{
        v.visit(*this);
}
void root::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void rule::apply(node_visitor &v)
{
        v.visit(*this);
}
void rule::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void alternative::apply(node_visitor &v)
{
        v.visit(*this);
}
void alternative::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
}
}
