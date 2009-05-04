#ifndef foundry_tree_cst_to_ast_visitor_hpp_
#define foundry_tree_cst_to_ast_visitor_hpp_

#include <tree_description_tree.hpp>
#include <tree_tree.hpp>

#include <boost/intrusive_ptr.hpp>

namespace foundry {
namespace tree {

class cst_to_ast_visitor :
    public tree_description::const_visitor
{
public:
    virtual ~cst_to_ast_visitor(void) throw() { }

    root_ptr get_ast(void) { return ast_root; }

    virtual void visit(tree_description::start const &);
    virtual void visit(tree_description::declarations_1 const &);
    virtual void visit(tree_description::declarations_2 const &);
    virtual void visit(tree_description::declaration_1 const &);
    virtual void visit(tree_description::declaration_2 const &);
    virtual void visit(tree_description::namespace_member_declaration_1 const &);
    virtual void visit(tree_description::namespace_member_declaration_2 const &);
    virtual void visit(tree_description::namespace_member_declaration_3 const &);
    virtual void visit(tree_description::namespace_declaration const &);
    virtual void visit(tree_description::group_declaration const &);
    virtual void visit(tree_description::group_member_declarations_1 const &);
    virtual void visit(tree_description::group_member_declarations_2 const &);
    virtual void visit(tree_description::group_member_declaration_1 const &);
    virtual void visit(tree_description::group_member_declaration_2 const &);
    virtual void visit(tree_description::group_member_declaration_3 const &);
    virtual void visit(tree_description::node_declaration_1 const &);
    virtual void visit(tree_description::node_declaration_2 const &);
    virtual void visit(tree_description::visitor_declaration_1 const &);
    virtual void visit(tree_description::visitor_declaration_2 const &);
    virtual void visit(tree_description::member_declarations_1 const &);
    virtual void visit(tree_description::member_declarations_2 const &);
    virtual void visit(tree_description::member_declarations_3 const &);
    virtual void visit(tree_description::member_declaration_1 const &);
    virtual void visit(tree_description::member_declaration_2 const &);
    virtual void visit(tree_description::member_declaration_3 const &);
    virtual void visit(tree_description::member_directive_1 const &);
    virtual void visit(tree_description::member_directive_2 const &);
    virtual void visit(tree_description::member_directive_3 const &);
    virtual void visit(tree_description::member_directive_4 const &);
    virtual void visit(tree_description::member_directive_5 const &);
    virtual void visit(tree_description::member_directive_6 const &);
    virtual void visit(tree_description::member_directive_7 const &);
    virtual void visit(tree_description::data_member_declaration const &);
    virtual void visit(tree_description::constructor_declaration const &);
    virtual void visit(tree_description::parameter_list_1 const &);
    virtual void visit(tree_description::parameter_list_2 const &);
    virtual void visit(tree_description::parameter_list_3 const &);
    virtual void visit(tree_description::parameters_1 const &);
    virtual void visit(tree_description::parameters_2 const &);
    virtual void visit(tree_description::parameter_1 const &);
    virtual void visit(tree_description::parameter_2 const &);
    virtual void visit(tree_description::destructor_declaration const &);
    virtual void visit(tree_description::void_or_nothing_1 const &);
    virtual void visit(tree_description::void_or_nothing_2 const &);
    virtual void visit(tree_description::declarator_1 const &);
    virtual void visit(tree_description::declarator_2 const &);
    virtual void visit(tree_description::reference_1 const &);
    virtual void visit(tree_description::reference_2 const &);
    virtual void visit(tree_description::pointer_1 const &);
    virtual void visit(tree_description::pointer_2 const &);
    virtual void visit(tree_description::type_qualifiers_1 const &);
    virtual void visit(tree_description::type_qualifiers_2 const &);
    virtual void visit(tree_description::type_qualifier_1 const &);
    virtual void visit(tree_description::type_qualifier_2 const &);
    virtual void visit(tree_description::arrays_1 const &);
    virtual void visit(tree_description::arrays_2 const &);
    virtual void visit(tree_description::bounded_arrays_1 const &);
    virtual void visit(tree_description::bounded_arrays_2 const &);
    virtual void visit(tree_description::bounded_array const &);
    virtual void visit(tree_description::unbounded_array const &);
    virtual void visit(tree_description::type_1 const &);
    virtual void visit(tree_description::type_2 const &);
    virtual void visit(tree_description::type_3 const &);
    virtual void visit(tree_description::type_4 const &);
    virtual void visit(tree_description::template_name const &);
    virtual void visit(tree_description::template_argument_list_1 const &);
    virtual void visit(tree_description::template_argument_list_2 const &);
    virtual void visit(tree_description::template_arguments_1 const &);
    virtual void visit(tree_description::template_arguments_2 const &);
    virtual void visit(tree_description::template_argument_1 const &);
    virtual void visit(tree_description::template_argument_2 const &);
    virtual void visit(tree_description::template_argument_3 const &);
    virtual void visit(tree_description::template_argument_4 const &);
    virtual void visit(tree_description::scoped_name const &);
    virtual void visit(tree_description::scope_1 const &);
    virtual void visit(tree_description::scope_2 const &);
    virtual void visit(tree_description::literal_1 const &);
    virtual void visit(tree_description::literal_2 const &);
    virtual void visit(tree_description::boolean_literal_1 const &);
    virtual void visit(tree_description::boolean_literal_2 const &);
    virtual void visit(tree_description::integer_literal const &);

private:
    root_ptr ast_root;
    namespace_node_ptr current_namespace;
    node_node_ptr current_node;
    node_ptr current_type;
    basic_type_node_ptr current_basic_type;
    std::string current_identifier;
};

}
}

#endif
