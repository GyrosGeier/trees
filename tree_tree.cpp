#include <tree_tree.hpp>

namespace trees {
namespace tree {
type_node_ptr group_node::apply(type_node_visitor &v)
{
        return v.visit(*this);
}
node_ptr group_node::apply(node_visitor &v)
{
        return v.visit(*this);
}
void group_node::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
type_node_ptr node_node::apply(type_node_visitor &v)
{
        return v.visit(*this);
}
node_ptr node_node::apply(node_visitor &v)
{
        return v.visit(*this);
}
void node_node::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
type_node_ptr basic_type_node::apply(type_node_visitor &v)
{
        return v.visit(*this);
}
node_ptr basic_type_node::apply(node_visitor &v)
{
        return v.visit(*this);
}
void basic_type_node::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
type_node_ptr reference_type_node::apply(type_node_visitor &v)
{
        return v.visit(*this);
}
node_ptr reference_type_node::apply(node_visitor &v)
{
        return v.visit(*this);
}
void reference_type_node::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
type_node_ptr pointer_type_node::apply(type_node_visitor &v)
{
        return v.visit(*this);
}
node_ptr pointer_type_node::apply(node_visitor &v)
{
        return v.visit(*this);
}
void pointer_type_node::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
type_node_ptr template_type_node::apply(type_node_visitor &v)
{
        return v.visit(*this);
}
node_ptr template_type_node::apply(node_visitor &v)
{
        return v.visit(*this);
}
void template_type_node::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
type_node_ptr list_type_node::apply(type_node_visitor &v)
{
        return v.visit(*this);
}
node_ptr list_type_node::apply(node_visitor &v)
{
        return v.visit(*this);
}
void list_type_node::apply(node_const_visitor &v) const
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
node_ptr include_node::apply(node_visitor &v)
{
        return v.visit(*this);
}
void include_node::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
node_ptr namespace_node::apply(node_visitor &v)
{
        return v.visit(*this);
}
void namespace_node::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
node_ptr data_member_node::apply(node_visitor &v)
{
        return v.visit(*this);
}
void data_member_node::apply(node_const_visitor &v) const
{
        v.visit(*this);
}
}
}
