#include <tree_tree.hpp>

namespace foundry {
namespace tree {
void basic_type_node::apply(node_visitor &v)
{
    v.visit(*this);
}
void basic_type_node::apply(node_const_visitor &v) const
{
    v.visit(*this);
}
void reference_type_node::apply(node_visitor &v)
{
    v.visit(*this);
}
void reference_type_node::apply(node_const_visitor &v) const
{
    v.visit(*this);
}
void pointer_type_node::apply(node_visitor &v)
{
    v.visit(*this);
}
void pointer_type_node::apply(node_const_visitor &v) const
{
    v.visit(*this);
}
void template_type_node::apply(node_visitor &v)
{
    v.visit(*this);
}
void template_type_node::apply(node_const_visitor &v) const
{
    v.visit(*this);
}
void list_type_node::apply(node_visitor &v)
{
    v.visit(*this);
}
void list_type_node::apply(node_const_visitor &v) const
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
void include_node::apply(node_visitor &v)
{
    v.visit(*this);
}
void include_node::apply(node_const_visitor &v) const
{
    v.visit(*this);
}
void namespace_node::apply(node_visitor &v)
{
    v.visit(*this);
}
void namespace_node::apply(node_const_visitor &v) const
{
    v.visit(*this);
}
void group_node::apply(node_visitor &v)
{
    v.visit(*this);
}
void group_node::apply(node_const_visitor &v) const
{
    v.visit(*this);
}
void node_node::apply(node_visitor &v)
{
    v.visit(*this);
}
void node_node::apply(node_const_visitor &v) const
{
    v.visit(*this);
}
void data_member_node::apply(node_visitor &v)
{
    v.visit(*this);
}
void data_member_node::apply(node_const_visitor &v) const
{
    v.visit(*this);
}
}
}
