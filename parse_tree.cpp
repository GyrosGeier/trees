#include <parse_tree.hpp>

namespace trees {
namespace parse {
component_ptr string_literal::apply(component_visitor &v)
{
        return v.visit(shared_from_this());
}
node_ptr string_literal::apply(node_visitor &v)
{
        return v.visit(shared_from_this());
}
void string_literal::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
component_ptr unresolved_symbol::apply(component_visitor &v)
{
        return v.visit(shared_from_this());
}
node_ptr unresolved_symbol::apply(node_visitor &v)
{
        return v.visit(shared_from_this());
}
void unresolved_symbol::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
component_ptr terminal::apply(component_visitor &v)
{
        return v.visit(shared_from_this());
}
node_ptr terminal::apply(node_visitor &v)
{
        return v.visit(shared_from_this());
}
void terminal::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
component_ptr nonterminal::apply(component_visitor &v)
{
        return v.visit(shared_from_this());
}
node_ptr nonterminal::apply(node_visitor &v)
{
        return v.visit(shared_from_this());
}
void nonterminal::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
component_ptr regex::apply(component_visitor &v)
{
        return v.visit(shared_from_this());
}
node_ptr regex::apply(node_visitor &v)
{
        return v.visit(shared_from_this());
}
void regex::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
component_ptr group::apply(component_visitor &v)
{
        return v.visit(shared_from_this());
}
node_ptr group::apply(node_visitor &v)
{
        return v.visit(shared_from_this());
}
void group::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
node_ptr root::apply(node_visitor &v)
{
        return v.visit(shared_from_this());
}
void root::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
node_ptr rule::apply(node_visitor &v)
{
        return v.visit(shared_from_this());
}
void rule::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
node_ptr alternative::apply(node_visitor &v)
{
        return v.visit(shared_from_this());
}
void alternative::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
}
}
