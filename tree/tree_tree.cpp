#include <tree_tree.hpp>

namespace foundry {
namespace tree {
void root::apply(visitor &v)
{
    v.visit(*this);
}
void root::apply(const_visitor &v) const
{
    v.visit(*this);
}
void include_node::apply(visitor &v)
{
    v.visit(*this);
}
void include_node::apply(const_visitor &v) const
{
    v.visit(*this);
}
void data_member_node::apply(visitor &v)
{
    v.visit(*this);
}
void data_member_node::apply(const_visitor &v) const
{
    v.visit(*this);
}
void node_node::apply(visitor &v)
{
    v.visit(*this);
}
void node_node::apply(const_visitor &v) const
{
    v.visit(*this);
}
void namespace_node::apply(visitor &v)
{
    v.visit(*this);
}
void namespace_node::apply(const_visitor &v) const
{
    v.visit(*this);
}
void basic_type_node::apply(visitor &v)
{
    v.visit(*this);
}
void basic_type_node::apply(const_visitor &v) const
{
    v.visit(*this);
}
void reference_type_node::apply(visitor &v)
{
    v.visit(*this);
}
void reference_type_node::apply(const_visitor &v) const
{
    v.visit(*this);
}
void pointer_type_node::apply(visitor &v)
{
    v.visit(*this);
}
void pointer_type_node::apply(const_visitor &v) const
{
    v.visit(*this);
}
void template_type_node::apply(visitor &v)
{
    v.visit(*this);
}
void template_type_node::apply(const_visitor &v) const
{
    v.visit(*this);
}
void list_type_node::apply(visitor &v)
{
    v.visit(*this);
}
void list_type_node::apply(const_visitor &v) const
{
    v.visit(*this);
}
}
}
