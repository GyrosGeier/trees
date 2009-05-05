#include "cst_to_ast_visitor.hpp"

namespace foundry {
namespace tree {

cst_to_ast_visitor::cst_to_ast_visitor(void)
{
    ast_root = new root;
    ast_root->global_namespace = current_namespace = new namespace_node;
    current_namespace->has_nodes = false;
    current_namespace->has_visitor = false;
    current_namespace->has_const_visitor = false;
}

void cst_to_ast_visitor::visit(cst::start const &s)
{
    /* declarations */
    s._1->apply(*this);
}

void cst_to_ast_visitor::visit(cst::declarations_1 const &)
{
    /* empty */
}

void cst_to_ast_visitor::visit(cst::declarations_2 const &d)
{
    /* declarations declaration */
    d._1->apply(*this);
    d._2->apply(*this);
}

void cst_to_ast_visitor::visit(cst::declaration_1 const &d)
{
    /* namespace_declaration */
    d._1->apply(*this);
}

void cst_to_ast_visitor::visit(cst::declaration_2 const &d)
{
    /* namespace_member_declaration */
    d._1->apply(*this);
}

void cst_to_ast_visitor::visit(cst::namespace_member_declaration_1 const &md)
{
    /* group_declaration */
    md._1->apply(*this);
}

void cst_to_ast_visitor::visit(cst::namespace_member_declaration_2 const &md)
{
    /* node_declaration */
    md._1->apply(*this);
}

void cst_to_ast_visitor::visit(cst::namespace_member_declaration_3 const &md)
{
    /* namespace_member_declaration */
    md._1->apply(*this);
}

void cst_to_ast_visitor::visit(cst::namespace_declaration const &n)
{
    /* "namespace" IDENTIFIER "{" declarations "}" */
    namespace_node_weak_ptr tmp = current_namespace;
    namespace_node_ptr nn = new namespace_node;
    nn->name = n._1;
    nn->parent = current_namespace;
    nn->has_nodes = false;
    nn->has_visitor = false;
    nn->has_const_visitor = false;
    current_namespace->namespaces.push_back(nn);
    current_namespace = nn.get();
    n._2->apply(*this);
    current_namespace = tmp;
}

void cst_to_ast_visitor::visit(cst::group_declaration const&){ }
void cst_to_ast_visitor::visit(cst::group_member_declarations_1 const&){ }
void cst_to_ast_visitor::visit(cst::group_member_declarations_2 const&){ }
void cst_to_ast_visitor::visit(cst::group_member_declaration_1 const&){ }
void cst_to_ast_visitor::visit(cst::group_member_declaration_2 const&){ }
void cst_to_ast_visitor::visit(cst::group_member_declaration_3 const&){ }
void cst_to_ast_visitor::visit(cst::node_declaration_1 const &n)
{
    current_node = new node_node;
    current_node->name = n._1;
    current_node->ns = current_namespace;
    current_namespace->nodes.push_back(current_node);
    current_namespace->has_nodes = true;
    n._2->apply(*this);
}

void cst_to_ast_visitor::visit(cst::node_declaration_2 const&){ }
void cst_to_ast_visitor::visit(cst::visitor_declaration_1 const &vd)
{
    /* "visitor" IDENTIFIER "{" member_declarations "}" */
    current_namespace->has_visitor = true;
    // TODO: Generate visitor
}

void cst_to_ast_visitor::visit(cst::visitor_declaration_2 const &vd)
{
    /* "const" "visitor" IDENTIFIER "{" member_declarations "}" */
    current_namespace->has_const_visitor = true;
    // TODO: Generate visitor
}

void cst_to_ast_visitor::visit(cst::member_declarations_1 const &)
{
    /* empty */
}

void cst_to_ast_visitor::visit(cst::member_declarations_2 const &md)
{
    /* member_declarations member_declaration */
    md._1->apply(*this);
    md._2->apply(*this);
}

void cst_to_ast_visitor::visit(cst::member_declarations_3 const &md)
{
    /* member_declarations member_directive */
    md._1->apply(*this);
    md._2->apply(*this);
}

void cst_to_ast_visitor::visit(cst::member_declaration_1 const &md)
{
    /* data_member_declaration */    
    md._1->apply(*this);
}

void cst_to_ast_visitor::visit(cst::member_declaration_2 const &){ }
void cst_to_ast_visitor::visit(cst::member_declaration_3 const&){ }
void cst_to_ast_visitor::visit(cst::member_directive_1 const&){ }
void cst_to_ast_visitor::visit(cst::member_directive_2 const&){ }
void cst_to_ast_visitor::visit(cst::member_directive_3 const&){ }
void cst_to_ast_visitor::visit(cst::member_directive_4 const&){ }
void cst_to_ast_visitor::visit(cst::member_directive_5 const&){ }
void cst_to_ast_visitor::visit(cst::member_directive_6 const &md)
{
    include_node_ptr nn = new include_node;
    nn->name = md._1;
    ast_root->includes.push_back(nn);
}

void cst_to_ast_visitor::visit(cst::member_directive_7 const &md)
{
    include_node_ptr nn = new include_node;
    nn->name = md._1;
    ast_root->includes.push_back(nn);
}

void cst_to_ast_visitor::visit(cst::data_member_declaration const &dm)
{
    /* type type_qualifiers declarator */
    current_basic_type = new basic_type_node;
    current_basic_type->is_const = false;
    current_basic_type->is_volatile = false;
    current_basic_type->ns = current_namespace;
    current_type = current_basic_type;
    dm._1->apply(*this);
    dm._2->apply(*this);
    dm._3->apply(*this);
    data_member_node_ptr nn = new data_member_node;
    nn->type = current_type;
    nn->name = current_identifier;
    nn->needs_init = current_type_needs_init;
    current_node->members.push_back(nn);
}

void cst_to_ast_visitor::visit(cst::constructor_declaration const&){ }
void cst_to_ast_visitor::visit(cst::parameter_list_1 const&){ }
void cst_to_ast_visitor::visit(cst::parameter_list_2 const&){ }
void cst_to_ast_visitor::visit(cst::parameter_list_3 const&){ }
void cst_to_ast_visitor::visit(cst::parameters_1 const&){ }
void cst_to_ast_visitor::visit(cst::parameters_2 const&){ }
void cst_to_ast_visitor::visit(cst::parameter_1 const&){ }
void cst_to_ast_visitor::visit(cst::parameter_2 const&){ }
void cst_to_ast_visitor::visit(cst::destructor_declaration const&){ }
void cst_to_ast_visitor::visit(cst::void_or_nothing_1 const&){ }
void cst_to_ast_visitor::visit(cst::void_or_nothing_2 const&){ }
void cst_to_ast_visitor::visit(cst::declarator_1 const &d)
{
    /* reference IDENTIFIER arrays */
    d._1->apply(*this);
    current_identifier = d._2;
    d._3->apply(*this);
}

void cst_to_ast_visitor::visit(cst::declarator_2 const &d)
{
    /* reference "parent" arrays */
    d._1->apply(*this);
    current_identifier = "parent";
    d._2->apply(*this);
}

void cst_to_ast_visitor::visit(cst::declarator_3 const &d)
{
    /* reference "parent" arrays */
    d._1->apply(*this);
    current_identifier = "group";
    d._2->apply(*this);
}

void cst_to_ast_visitor::visit(cst::reference_1 const &r)
{
    /* pointer */
    r._1->apply(*this);
}

void cst_to_ast_visitor::visit(cst::reference_2 const &r)
{
    /* pointer "&" */
    r._1->apply(*this);
    reference_type_node_ptr nn = new reference_type_node;
    nn->type = current_type;
    current_type = nn.get();
    current_type_needs_init = true;
}

void cst_to_ast_visitor::visit(cst::pointer_1 const &)
{
    /* empty */
}

void cst_to_ast_visitor::visit(cst::pointer_2 const &p)
{
    /* pointer type_qualifiers "*" */
    p._1->apply(*this);
    p._2->apply(*this);
    pointer_type_node_ptr nn = new pointer_type_node;
    nn->type = current_type;
    nn->is_const = false;
    nn->is_volatile = false;
    current_type = nn.get();
    current_type_needs_init = true;
};

void cst_to_ast_visitor::visit(cst::type_qualifiers_1 const&)
{
    /* empty */
}

void cst_to_ast_visitor::visit(cst::type_qualifiers_2 const &q)
{
    /* type_qualifiers type_qualifier */
    q._1->apply(*this);
    q._2->apply(*this);
}

void cst_to_ast_visitor::visit(cst::type_qualifier_1 const &)
{
    /* "const" */
    current_type_needs_init = true;
    basic_type_node *bt = dynamic_cast<basic_type_node *>(current_type.get());
    if(bt)
    {
        bt->is_const = true;
        return;
    }
    pointer_type_node *pt = dynamic_cast<pointer_type_node *>(current_type.get());
    if(pt)
    {
        pt->is_const = true;
        return;
    }
    // TODO: proper error message
    throw;
}

void cst_to_ast_visitor::visit(cst::type_qualifier_2 const&)
{
    /* "volatile" */
    // TODO: current_type->is_volatile = true;
}

void cst_to_ast_visitor::visit(cst::arrays_1 const &a)
{
    /* bounded_arrays */
    a._1->apply(*this);
}

void cst_to_ast_visitor::visit(cst::arrays_2 const &a)
{
    /* bounded_arrays unbounded_array */
    a._1->apply(*this);
    a._2->apply(*this);
}

void cst_to_ast_visitor::visit(cst::bounded_arrays_1 const &)
{
    /* empty */
}

void cst_to_ast_visitor::visit(cst::bounded_arrays_2 const&){ }
void cst_to_ast_visitor::visit(cst::bounded_array const&){ }
void cst_to_ast_visitor::visit(cst::unbounded_array const &)
{
    list_type_node_ptr nn = new list_type_node;
    nn->type = current_type;
    current_type = nn.get();
    current_type_needs_init = false;
}

void cst_to_ast_visitor::visit(cst::type_1 const&){ }
void cst_to_ast_visitor::visit(cst::type_2 const &t)
{
    /* scoped_name */
    t._1->apply(*this);
}

void cst_to_ast_visitor::visit(cst::type_3 const&)
{
    /* "node" */
    current_basic_type->name = "node";
    current_type_needs_init = false;
}

void cst_to_ast_visitor::visit(cst::type_4 const&)
{
    /* "parent" */
    current_basic_type->name = "node";
    current_type_needs_init = false;
}

void cst_to_ast_visitor::visit(cst::template_name const&){ }
void cst_to_ast_visitor::visit(cst::template_argument_list_1 const&){ }
void cst_to_ast_visitor::visit(cst::template_argument_list_2 const&){ }
void cst_to_ast_visitor::visit(cst::template_arguments_1 const&){ }
void cst_to_ast_visitor::visit(cst::template_arguments_2 const&){ }
void cst_to_ast_visitor::visit(cst::template_argument_1 const&){ }
void cst_to_ast_visitor::visit(cst::template_argument_2 const&){ }
void cst_to_ast_visitor::visit(cst::template_argument_3 const&){ }
void cst_to_ast_visitor::visit(cst::template_argument_4 const&){ }
void cst_to_ast_visitor::visit(cst::scoped_name const &n)
{
    /* scope IDENTIFIER */
    n._1->apply(*this);
    if(!current_basic_type->name.empty())
        current_basic_type->name += "::";
    current_basic_type->name += n._2;
}

void cst_to_ast_visitor::visit(cst::scope_1 const &)
{
    /* empty */
}

void cst_to_ast_visitor::visit(cst::scope_2 const &s)
{
    /* scope "::" IDENTIFIER */
    s._1->apply(*this);
    if(!current_basic_type->name.empty())
        current_basic_type->name += "::";
    current_basic_type->name += s._2;
}

void cst_to_ast_visitor::visit(cst::literal_1 const&){ }
void cst_to_ast_visitor::visit(cst::literal_2 const&){ }
void cst_to_ast_visitor::visit(cst::boolean_literal_1 const&){ }
void cst_to_ast_visitor::visit(cst::boolean_literal_2 const&){ }
void cst_to_ast_visitor::visit(cst::integer_literal const&){ }

}
}
