#ifndef foundry_tree_cst_to_ast_visitor_hpp_
#define foundry_tree_cst_to_ast_visitor_hpp_

#include <tree_cst_tree.hpp>
#include <tree_tree.hpp>

#include <boost/intrusive_ptr.hpp>

namespace foundry {
namespace tree {

class cst_to_ast_visitor :
    public cst::node_const_visitor
{
public:
    cst_to_ast_visitor(void);
    virtual ~cst_to_ast_visitor(void) throw() { }

    root_ptr get_ast(void) { return ast_root; }

    virtual void visit(cst::start const &);
    virtual void visit(cst::declarations_1 const &);
    virtual void visit(cst::declarations_2 const &);
    virtual void visit(cst::declaration_1 const &);
    virtual void visit(cst::declaration_2 const &);
    virtual void visit(cst::namespace_member_declaration_1 const &);
    virtual void visit(cst::namespace_member_declaration_2 const &);
    virtual void visit(cst::namespace_member_declaration_3 const &);
    virtual void visit(cst::namespace_declaration const &);
    virtual void visit(cst::group_declaration const &);
    virtual void visit(cst::group_member_declarations_1 const &);
    virtual void visit(cst::group_member_declarations_2 const &);
    virtual void visit(cst::group_member_declaration_1 const &);
    virtual void visit(cst::group_member_declaration_2 const &);
    virtual void visit(cst::group_member_declaration_3 const &);
    virtual void visit(cst::node_declaration_1 const &);
    virtual void visit(cst::node_declaration_2 const &);
    virtual void visit(cst::visitor_declaration_1 const &);
    virtual void visit(cst::visitor_declaration_2 const &);
    virtual void visit(cst::member_declarations_1 const &);
    virtual void visit(cst::member_declarations_2 const &);
    virtual void visit(cst::member_declarations_3 const &);
    virtual void visit(cst::member_declaration_1 const &);
    virtual void visit(cst::member_declaration_2 const &);
    virtual void visit(cst::member_declaration_3 const &);
    virtual void visit(cst::member_directive_1 const &);
    virtual void visit(cst::member_directive_2 const &);
    virtual void visit(cst::member_directive_3 const &);
    virtual void visit(cst::member_directive_4 const &);
    virtual void visit(cst::member_directive_5 const &);
    virtual void visit(cst::member_directive_6 const &);
    virtual void visit(cst::member_directive_7 const &);
    virtual void visit(cst::data_member_declaration const &);
    virtual void visit(cst::constructor_declaration const &);
    virtual void visit(cst::parameter_list_1 const &);
    virtual void visit(cst::parameter_list_2 const &);
    virtual void visit(cst::parameter_list_3 const &);
    virtual void visit(cst::parameters_1 const &);
    virtual void visit(cst::parameters_2 const &);
    virtual void visit(cst::parameter_1 const &);
    virtual void visit(cst::parameter_2 const &);
    virtual void visit(cst::destructor_declaration const &);
    virtual void visit(cst::void_or_nothing_1 const &);
    virtual void visit(cst::void_or_nothing_2 const &);
    virtual void visit(cst::declarator_1 const &);
    virtual void visit(cst::declarator_2 const &);
    virtual void visit(cst::declarator_3 const &);
    virtual void visit(cst::reference_1 const &);
    virtual void visit(cst::reference_2 const &);
    virtual void visit(cst::pointer_1 const &);
    virtual void visit(cst::pointer_2 const &);
    virtual void visit(cst::type_qualifiers_1 const &);
    virtual void visit(cst::type_qualifiers_2 const &);
    virtual void visit(cst::type_qualifier_1 const &);
    virtual void visit(cst::type_qualifier_2 const &);
    virtual void visit(cst::arrays_1 const &);
    virtual void visit(cst::arrays_2 const &);
    virtual void visit(cst::bounded_arrays_1 const &);
    virtual void visit(cst::bounded_arrays_2 const &);
    virtual void visit(cst::bounded_array const &);
    virtual void visit(cst::unbounded_array const &);
    virtual void visit(cst::type_1 const &);
    virtual void visit(cst::type_2 const &);
    virtual void visit(cst::type_3 const &);
    virtual void visit(cst::type_4 const &);
    virtual void visit(cst::template_name const &);
    virtual void visit(cst::template_argument_list_1 const &);
    virtual void visit(cst::template_argument_list_2 const &);
    virtual void visit(cst::template_arguments_1 const &);
    virtual void visit(cst::template_arguments_2 const &);
    virtual void visit(cst::template_argument_1 const &);
    virtual void visit(cst::template_argument_2 const &);
    virtual void visit(cst::template_argument_3 const &);
    virtual void visit(cst::template_argument_4 const &);
    virtual void visit(cst::scoped_name const &);
    virtual void visit(cst::scope_1 const &);
    virtual void visit(cst::scope_2 const &);
    virtual void visit(cst::literal_1 const &);
    virtual void visit(cst::literal_2 const &);
    virtual void visit(cst::boolean_literal_1 const &);
    virtual void visit(cst::boolean_literal_2 const &);
    virtual void visit(cst::integer_literal const &);

private:
    root_ptr ast_root;
    namespace_node_weak_ptr current_namespace;
    group_node_weak_ptr current_group;
    node_node_weak_ptr current_node;
    node_ptr current_type;
    bool current_type_needs_init;
    std::string current_identifier;
    std::list<node_ptr> *current_template_argument_list;
};

}
}

#endif
