#include "cst_to_ast_visitor.hpp"

namespace foundry {
namespace tree {

void cst_to_ast_visitor::visit(tree_description::start const &s)
{
    /* declarations */
    if(!current_namespace)
        current_namespace = new namespace_node;

    s._1->apply(*this);
}

void cst_to_ast_visitor::visit(tree_description::declarations_1 const &)
{
    /* empty */
}

void cst_to_ast_visitor::visit(tree_description::declarations_2 const &d)
{
    /* declarations declaration */
    d._1->apply(*this);
    d._2->apply(*this);
}

void cst_to_ast_visitor::visit(tree_description::declaration_1 const &d)
{
    /* namespace_declaration */
    d._1->apply(*this);
}

void cst_to_ast_visitor::visit(tree_description::declaration_2 const &d)
{
    /* namespace_member_declaration */
    d._1->apply(*this);
}

void cst_to_ast_visitor::visit(tree_description::namespace_member_declaration_1 const &md)
{
    /* root_declaration */
    md._1->apply(*this);
}

void cst_to_ast_visitor::visit(tree_description::namespace_member_declaration_2 const &md)
{
    /* group_declaration */
    md._1->apply(*this);
}

void cst_to_ast_visitor::visit(tree_description::namespace_member_declaration_3 const &md)
{
    /* node_declaration */
    md._1->apply(*this);
}

void cst_to_ast_visitor::visit(tree_description::namespace_member_declaration_4 const &md)
{
    /* namespace_member_declaration */
    md._1->apply(*this);
}

void cst_to_ast_visitor::visit(tree_description::namespace_declaration const &n)
{
    /* "namespace" IDENTIFIER "{" declarations "}" */
    namespace_node_ptr tmp = current_namespace;
    namespace_node_ptr nn = new namespace_node;
    nn->name = n._1;
    nn->parent = current_namespace.get();
    current_namespace->namespaces.push_back(nn);
    current_namespace = nn;
    n._2->apply(*this);
    current_namespace = tmp;
}

void cst_to_ast_visitor::visit(tree_description::root_declaration_1 const&){ }
void cst_to_ast_visitor::visit(tree_description::root_declaration_2 const&){ }
void cst_to_ast_visitor::visit(tree_description::root_declaration_3 const&){ }
void cst_to_ast_visitor::visit(tree_description::root_declaration_4 const&){ }
void cst_to_ast_visitor::visit(tree_description::group_declaration const&){ }
void cst_to_ast_visitor::visit(tree_description::group_member_declarations_1 const&){ }
void cst_to_ast_visitor::visit(tree_description::group_member_declarations_2 const&){ }
void cst_to_ast_visitor::visit(tree_description::group_member_declaration_1 const&){ }
void cst_to_ast_visitor::visit(tree_description::group_member_declaration_2 const&){ }
void cst_to_ast_visitor::visit(tree_description::group_member_declaration_3 const&){ }
void cst_to_ast_visitor::visit(tree_description::node_declaration_1 const &n)
{
    current_node = new node_node;
    current_node->name = n._1;
    current_node->ns = current_namespace.get();
    current_namespace->nodes.push_back(current_node);
    current_namespace->has_nodes = true;
    n._2->apply(*this);
}

void cst_to_ast_visitor::visit(tree_description::node_declaration_2 const&){ }
void cst_to_ast_visitor::visit(tree_description::visitor_declaration_1 const &vd)
{
    /* "visitor" IDENTIFIER "{" member_declarations "}" */
    current_namespace->has_visitor = true;
    // TODO: Generate visitor
}

void cst_to_ast_visitor::visit(tree_description::visitor_declaration_2 const &vd)
{
    /* "const" "visitor" IDENTIFIER "{" member_declarations "}" */
    current_namespace->has_const_visitor = true;
    // TODO: Generate visitor
}

void cst_to_ast_visitor::visit(tree_description::member_declarations_1 const &)
{
    /* empty */
}

void cst_to_ast_visitor::visit(tree_description::member_declarations_2 const &md)
{
    /* member_declarations member_declaration */
    md._1->apply(*this);
    md._2->apply(*this);
}

void cst_to_ast_visitor::visit(tree_description::member_declarations_3 const&){ }

void cst_to_ast_visitor::visit(tree_description::member_declaration_1 const &md)
{
    /* data_member_declaration */    
    md._1->apply(*this);
}

void cst_to_ast_visitor::visit(tree_description::member_declaration_2 const&){ }
void cst_to_ast_visitor::visit(tree_description::member_declaration_3 const&){ }
void cst_to_ast_visitor::visit(tree_description::member_directive_1 const&){ }
void cst_to_ast_visitor::visit(tree_description::member_directive_2 const&){ }
void cst_to_ast_visitor::visit(tree_description::member_directive_3 const&){ }
void cst_to_ast_visitor::visit(tree_description::member_directive_4 const&){ }
void cst_to_ast_visitor::visit(tree_description::member_directive_5 const&){ }

void cst_to_ast_visitor::visit(tree_description::data_member_declaration const &dm)
{
    /* type type_qualifiers declarator */
    current_basic_type = new basic_type_node;
    current_basic_type->ns = current_namespace.get();
    current_type = current_basic_type;
    dm._1->apply(*this);
    dm._2->apply(*this);
    dm._3->apply(*this);
    data_member_node_ptr nn = new data_member_node;
    nn->type = current_type;
    nn->name = current_identifier;
    current_node->members.push_back(nn);
}

void cst_to_ast_visitor::visit(tree_description::constructor_declaration const&){ }
void cst_to_ast_visitor::visit(tree_description::parameter_list_1 const&){ }
void cst_to_ast_visitor::visit(tree_description::parameter_list_2 const&){ }
void cst_to_ast_visitor::visit(tree_description::parameter_list_3 const&){ }
void cst_to_ast_visitor::visit(tree_description::parameters_1 const&){ }
void cst_to_ast_visitor::visit(tree_description::parameters_2 const&){ }
void cst_to_ast_visitor::visit(tree_description::parameter_1 const&){ }
void cst_to_ast_visitor::visit(tree_description::parameter_2 const&){ }
void cst_to_ast_visitor::visit(tree_description::destructor_declaration const&){ }
void cst_to_ast_visitor::visit(tree_description::void_or_nothing_1 const&){ }
void cst_to_ast_visitor::visit(tree_description::void_or_nothing_2 const&){ }
void cst_to_ast_visitor::visit(tree_description::declarator_1 const &d)
{
    /* reference IDENTIFIER arrays */
    d._1->apply(*this);
    current_identifier = d._2;
    d._3->apply(*this);
}

void cst_to_ast_visitor::visit(tree_description::declarator_2 const &d)
{
    /* reference "parent" arrays */
    d._1->apply(*this);
    current_identifier = "parent";
    d._2->apply(*this);
}

void cst_to_ast_visitor::visit(tree_description::reference_1 const &r)
{
    /* pointer */
    r._1->apply(*this);
}

void cst_to_ast_visitor::visit(tree_description::reference_2 const &r)
{
    /* pointer "&" */
    r._1->apply(*this);
    reference_type_node_ptr nn = new reference_type_node;
    nn->type = current_type;
    current_type = nn;
}

void cst_to_ast_visitor::visit(tree_description::pointer_1 const &)
{
    /* empty */
}

void cst_to_ast_visitor::visit(tree_description::pointer_2 const &p)
{
    /* pointer type_qualifiers "*" */
    p._1->apply(*this);
    p._2->apply(*this);
    pointer_type_node_ptr nn = new pointer_type_node;
    nn->type = current_type;
    current_type = nn;
};

void cst_to_ast_visitor::visit(tree_description::type_qualifiers_1 const&)
{
    /* empty */
}

void cst_to_ast_visitor::visit(tree_description::type_qualifiers_2 const &q)
{
    /* type_qualifiers type_qualifier */
    q._1->apply(*this);
    q._2->apply(*this);
}

void cst_to_ast_visitor::visit(tree_description::type_qualifier_1 const &)
{
    /* "const" */
    // TODO: current_type->is_const = true;
}

void cst_to_ast_visitor::visit(tree_description::type_qualifier_2 const&)
{
    /* "volatile" */
    // TODO: current_type->is_volatile = true;
}

void cst_to_ast_visitor::visit(tree_description::arrays_1 const &a)
{
    /* bounded_arrays */
    a._1->apply(*this);
}

void cst_to_ast_visitor::visit(tree_description::arrays_2 const &a)
{
    /* bounded_arrays unbounded_array */
    a._1->apply(*this);
    a._2->apply(*this);
}

void cst_to_ast_visitor::visit(tree_description::bounded_arrays_1 const &)
{
    /* empty */
}

void cst_to_ast_visitor::visit(tree_description::bounded_arrays_2 const&){ }
void cst_to_ast_visitor::visit(tree_description::bounded_array const&){ }
void cst_to_ast_visitor::visit(tree_description::unbounded_array const &)
{
    list_type_node_ptr nn = new list_type_node;
    nn->type = current_type;
    current_type = nn;
}

void cst_to_ast_visitor::visit(tree_description::type_1 const&){ }
void cst_to_ast_visitor::visit(tree_description::type_2 const &t)
{
    /* scoped_name */
    t._1->apply(*this);
}

void cst_to_ast_visitor::visit(tree_description::type_3 const&)
{
    /* "node" */
    current_basic_type->name = "node";
}

void cst_to_ast_visitor::visit(tree_description::type_4 const&)
{
    /* "parent" */
    current_basic_type->name = "node";
}

void cst_to_ast_visitor::visit(tree_description::template_name const&){ }
void cst_to_ast_visitor::visit(tree_description::template_argument_list_1 const&){ }
void cst_to_ast_visitor::visit(tree_description::template_argument_list_2 const&){ }
void cst_to_ast_visitor::visit(tree_description::template_arguments_1 const&){ }
void cst_to_ast_visitor::visit(tree_description::template_arguments_2 const&){ }
void cst_to_ast_visitor::visit(tree_description::template_argument_1 const&){ }
void cst_to_ast_visitor::visit(tree_description::template_argument_2 const&){ }
void cst_to_ast_visitor::visit(tree_description::template_argument_3 const&){ }
void cst_to_ast_visitor::visit(tree_description::template_argument_4 const&){ }
void cst_to_ast_visitor::visit(tree_description::scoped_name const &n)
{
    /* scope IDENTIFIER */
    n._1->apply(*this);
    if(!current_basic_type->name.empty())
        current_basic_type->name += "::";
    current_basic_type->name += n._2;
}

void cst_to_ast_visitor::visit(tree_description::scope_1 const &)
{
    /* empty */
}

void cst_to_ast_visitor::visit(tree_description::scope_2 const &s)
{
    /* scope "::" IDENTIFIER */
    s._1->apply(*this);
    if(!current_basic_type->name.empty())
        current_basic_type->name += "::";
    current_basic_type->name += s._2;
}

void cst_to_ast_visitor::visit(tree_description::literal_1 const&){ }
void cst_to_ast_visitor::visit(tree_description::literal_2 const&){ }
void cst_to_ast_visitor::visit(tree_description::boolean_literal_1 const&){ }
void cst_to_ast_visitor::visit(tree_description::boolean_literal_2 const&){ }
void cst_to_ast_visitor::visit(tree_description::integer_literal const&){ }

}
}
