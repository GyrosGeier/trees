#include <parse_cst_cst.hpp>

namespace foundry {
namespace parse {
namespace cst {
void directives_chain::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void end_of_directives::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void rules_chain::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void end_of_rules::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void more_alternatives::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void end_of_alternatives::apply(node_const_visitor &v) const
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
void no_repetition::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void zero_or_one::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void one_or_more::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void zero_or_more::apply(node_const_visitor &v) const
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
void group::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void regex::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void components_chain::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void end_of_components::apply(node_const_visitor &v) const
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
void alternatives::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void components::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
void components_elem::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
}
}
}
