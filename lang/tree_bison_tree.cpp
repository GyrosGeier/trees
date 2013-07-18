#include <tree_bison_tree.hpp>

namespace foundry {
namespace tree {
namespace bison {
void empty_rules::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void chained_rules::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void single_alternative::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void chained_alternatives::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void terminated_alternatives::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void unnamed_alternative::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void named_alternative::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void empty_components::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void chained_components::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void symbol::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void literal::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void start::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void rule::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
}
}
}
