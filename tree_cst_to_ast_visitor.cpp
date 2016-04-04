/* Copyright 2009 Simon Richter <Simon.Richter@hogyros.de>
 *
 * Released under the GNU General Public Licence version 3.
 */

#include "tree_cst_to_ast_visitor.hpp"

namespace trees {
namespace tree {

cst_to_ast_visitor::cst_to_ast_visitor(void)
{
        ast_root = new root;
        ast_root->global_namespace = current_namespace = new namespace_node;
        current_namespace->parent = 0;
        current_namespace->uses_lists = false;
}

void cst_to_ast_visitor::visit(cst::start const &s)
{
        /* declarations */
        descend(s._1);
}

void cst_to_ast_visitor::visit(cst::declarations_1 const &)
{
        /* empty */
}

void cst_to_ast_visitor::visit(cst::declarations_2 const &d)
{
        /* declarations declaration */
        descend(d._1);
        descend(d._2);
}

void cst_to_ast_visitor::visit(cst::declaration_1 const &d)
{
        /* namespace_declaration */
        descend(d._1);
}

void cst_to_ast_visitor::visit(cst::declaration_2 const &d)
{
        /* namespace_member_declaration */
        descend(d._1);
}

void cst_to_ast_visitor::visit(cst::namespace_member_declaration_1 const &md)
{
        /* group_declaration */
        descend(md._1);
}

void cst_to_ast_visitor::visit(cst::namespace_member_declaration_2 const &md)
{
        /* node_declaration */
        descend(md._1);
}

void cst_to_ast_visitor::visit(cst::namespace_member_declaration_3 const &md)
{
        /* namespace_member_declaration */
        descend(md._1);
}

void cst_to_ast_visitor::visit(cst::namespace_declaration const &n)
{
        /* "namespace" IDENTIFIER "{" declarations "}" */
        namespace_node_ptr tmp = current_namespace;
        namespace_node_ptr nn = new namespace_node;
        nn->name = n._1;
        nn->parent = current_namespace.get();
        current_namespace->namespaces.push_back(nn);
        current_namespace = nn.get();
        current_namespace->group = new group_node;
        current_namespace->group->smartpointer = intrusive;
        current_namespace->uses_lists = false;
        current_group = current_namespace->group.get();
        current_group->name = "node";
        current_group->ns = current_namespace.get();
        current_group->parent = 0;
        current_group->has_const_visitor = false;
        current_group->has_visitor = false;
        descend(n._2);
        current_namespace = tmp;
}

void cst_to_ast_visitor::visit(cst::group_declaration const &gd)
{
        /* "group" IDENTIFIER group_member_declarations */
        group_node_ptr nn = new group_node;
        nn->name = gd._1;
        nn->ns = current_namespace.get();
        nn->parent = current_group.get();
        nn->has_const_visitor = false;
        nn->has_visitor = false;
        nn->smartpointer = current_group->smartpointer;
        current_group->groups.push_back(nn);
        current_group = nn;
        descend(gd._2);
        current_group = current_group->parent;
}

void cst_to_ast_visitor::visit(cst::group_member_declarations_1 const &)
{
        /* empty */
}

void cst_to_ast_visitor::visit(cst::group_member_declarations_2 const &gmd)
{
        /* group_member_declarations group_member_declaration ";" */
        descend(gmd._1);
        descend(gmd._2);
}

void cst_to_ast_visitor::visit(cst::group_member_declaration_1 const &gmd)
{
        /* group_declaration */
        descend(gmd._1);
}

void cst_to_ast_visitor::visit(cst::group_member_declaration_2 const &gmd)
{
        /* node_declaration */
        descend(gmd._1);
}

void cst_to_ast_visitor::visit(cst::group_member_declaration_3 const &gmd)
{
        /* visitor_declaration */
        descend(gmd._1);
}

void cst_to_ast_visitor::visit(cst::node_declaration_1 const &n)
{
        /* "node" IDENTIFIER "{" member_declarations "}" */
        current_node = new node_node;
        current_node->name = n._1;
        current_node->ns = current_namespace.get();
        current_node->group = current_group.get();
        current_node->smartpointer = current_group->smartpointer;
        current_group->nodes.push_back(current_node);
        descend(n._2);
}

void cst_to_ast_visitor::visit(cst::node_declaration_2 const &n)
{
        /* "node" "group" "{" member_declarations "}" */
        current_node = new node_node;
        current_node->name = "group";
        current_node->ns = current_namespace.get();
        current_node->group = current_group.get();
        current_node->smartpointer = current_group->smartpointer;
        current_group->nodes.push_back(current_node);
        descend(n._1);
}

void cst_to_ast_visitor::visit(cst::node_declaration_3 const &n)
{
        /* "node" "{" member_declarations "}" */
        node_node_ptr fake_node = new node_node;
        fake_node->smartpointer = current_group->smartpointer;
        current_node = fake_node.get();
        descend(n._1);
        current_group->default_members.splice(current_group->default_members.end(), fake_node->members);
        current_group->smartpointer = fake_node->smartpointer;
}

void cst_to_ast_visitor::visit(cst::visitor_declaration_1 const &)
{
        /* "visitor" IDENTIFIER "{" member_declarations "}" */
        current_group->has_visitor = true;
        // TODO: Generate visitor
}

void cst_to_ast_visitor::visit(cst::visitor_declaration_2 const &)
{
        /* "const" "visitor" IDENTIFIER "{" member_declarations "}" */
        current_group->has_const_visitor = true;
        // TODO: Generate visitor
}

void cst_to_ast_visitor::visit(cst::visitor_declaration_3 const &)
{
        /* "visitor" IDENTIFIER */
        current_group->has_visitor = true;
        // TODO: Generate visitor
}

void cst_to_ast_visitor::visit(cst::visitor_declaration_4 const &)
{
        /* "const" "visitor" IDENTIFIER */
        current_group->has_const_visitor = true;
        // TODO: Generate visitor
}

void cst_to_ast_visitor::visit(cst::visitor_declaration_5 const &)
{
        /* "visitor" */
        current_group->has_visitor = true;
}

void cst_to_ast_visitor::visit(cst::visitor_declaration_6 const &)
{
        /* "const" "visitor" */
        current_group->has_const_visitor = true;
}

void cst_to_ast_visitor::visit(cst::member_declarations_1 const &)
{
        /* empty */
}

void cst_to_ast_visitor::visit(cst::member_declarations_2 const &md)
{
        /* member_declarations member_declaration */
        descend(md._1);
        descend(md._2);
}

void cst_to_ast_visitor::visit(cst::member_declarations_3 const &md)
{
        /* member_declarations member_directive */
        descend(md._1);
        descend(md._2);
}

void cst_to_ast_visitor::visit(cst::member_declaration_1 const &md)
{
        /* data_member_declaration */        
        current_type_needs_init = false;
        descend(md._1);
}

void cst_to_ast_visitor::visit(cst::member_declaration_2 const &){ }
void cst_to_ast_visitor::visit(cst::member_declaration_3 const&){ }
void cst_to_ast_visitor::visit(cst::member_directive_1 const&){ }
void cst_to_ast_visitor::visit(cst::member_directive_2 const&){ current_node->smartpointer = strict_ownership; }
void cst_to_ast_visitor::visit(cst::member_directive_3 const&){ current_node->smartpointer = shared_ownership; }
void cst_to_ast_visitor::visit(cst::member_directive_4 const&){ current_node->smartpointer = intrusive; }
void cst_to_ast_visitor::visit(cst::member_directive_5 const&){ }
void cst_to_ast_visitor::visit(cst::member_directive_6 const &md)
{
        include_node_ptr nn = new include_node;
        nn->name = md._1.substr(9);
        ast_root->includes.push_back(nn);
}

void cst_to_ast_visitor::visit(cst::data_member_declaration const &dm)
{
        /* type type_qualifiers declarator */
        descend(dm._1);
        descend(dm._2);
        descend(dm._3);
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
        descend(d._1);
        current_identifier = d._2;
        descend(d._3);
}

void cst_to_ast_visitor::visit(cst::declarator_2 const &d)
{
        /* reference "parent" arrays */
        descend(d._1);
        current_identifier = "parent";
        descend(d._2);
}

void cst_to_ast_visitor::visit(cst::declarator_3 const &d)
{
        /* reference "parent" arrays */
        descend(d._1);
        current_identifier = "group";
        descend(d._2);
}

void cst_to_ast_visitor::visit(cst::declarator_4 const &d)
{
        /* reference "node" arrays */
        descend(d._1);
        current_identifier = "node";
        descend(d._2);
}

void cst_to_ast_visitor::visit(cst::reference_1 const &r)
{
        /* pointer */
        descend(r._1);
}

void cst_to_ast_visitor::visit(cst::reference_2 const &r)
{
        /* pointer "&" */
        descend(r._1);
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
        descend(p._1);
        descend(p._2);
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
        descend(q._1);
        descend(q._2);
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
        descend(a._1);
}

void cst_to_ast_visitor::visit(cst::arrays_2 const &a)
{
        /* bounded_arrays unbounded_array */
        descend(a._1);
        descend(a._2);
}

void cst_to_ast_visitor::visit(cst::bounded_arrays_1 const &)
{
        /* empty */
}

void cst_to_ast_visitor::visit(cst::bounded_arrays_2 const&){ }
void cst_to_ast_visitor::visit(cst::bounded_array const&){ }
void cst_to_ast_visitor::visit(cst::unbounded_array const &)
{
        current_namespace->uses_lists = true;
        list_type_node_ptr nn = new list_type_node;
        nn->type = current_type;
        current_type = nn.get();
        current_type_needs_init = false;
}

void cst_to_ast_visitor::visit(cst::type_1 const &t)
{
        /* template_name */
        template_type_node_ptr nt = new template_type_node;
        nt->ns = current_namespace.get();
        std::string tmp1 = current_identifier;
        current_identifier.clear();
        std::list<type_node_ptr> *tmp2 = current_template_argument_list;
        current_template_argument_list = &nt->template_args;
        descend(t._1);
        nt->name = current_identifier;
        current_template_argument_list = tmp2;
        current_identifier = tmp1;
        current_type = nt;
}

void cst_to_ast_visitor::visit(cst::type_2 const &t)
{
        /* scoped_name */
        basic_type_node_ptr nt = new basic_type_node;
        nt->is_const = false;
        nt->is_volatile = false;
        nt->ns = current_namespace.get();
        current_type = nt;
        std::string tmp1 = current_identifier;
        current_identifier.clear();
        descend(t._1);
        nt->name = current_identifier;
        current_identifier = tmp1;
}

void cst_to_ast_visitor::visit(cst::type_3 const&)
{
        /* "node" */
        basic_type_node_ptr nt = new basic_type_node;
        nt->is_const = false;
        nt->is_volatile = false;
        nt->ns = current_namespace.get();
        nt->name = "node";
        current_type = nt;
        current_type_needs_init = false;
}

void cst_to_ast_visitor::visit(cst::type_4 const&)
{
        /* "group" */
        basic_type_node_ptr nt = new basic_type_node;
        nt->is_const = false;
        nt->is_volatile = false;
        nt->ns = current_namespace.get();
        nt->name = "group";
        current_type = nt;
        current_type_needs_init = false;
}

void cst_to_ast_visitor::visit(cst::type_5 const&)
{
        /* "parent" */
        basic_type_node_ptr nt = new basic_type_node;
        nt->is_const = false;
        nt->is_volatile = false;
        nt->ns = current_namespace.get();
        nt->name = "node";
        current_type = nt;
        current_type_needs_init = false;
}

void cst_to_ast_visitor::visit(cst::template_name const &tn)
{
        /* scoped_name "<" template_argument_list ">" */
        descend(tn._1);
        descend(tn._2);
}

void cst_to_ast_visitor::visit(cst::template_argument_list_1 const &)
{
        /* empty */
        return;
}

void cst_to_ast_visitor::visit(cst::template_argument_list_2 const &tal)
{
        /* template_arguments */
        descend(tal._1);
}

void cst_to_ast_visitor::visit(cst::template_arguments_1 const &tas)
{
        /* template_argument */
        descend(tas._1);
}

void cst_to_ast_visitor::visit(cst::template_arguments_2 const &tas)
{
        /* template_arguments "," template_argument */
        descend(tas._1);
        descend(tas._2);
}

void cst_to_ast_visitor::visit(cst::template_argument_1 const &ta)
{
        /* type */
        descend(ta._1);
        current_template_argument_list->push_back(current_type);
}

void cst_to_ast_visitor::visit(cst::template_argument_2 const&){ }
void cst_to_ast_visitor::visit(cst::template_argument_3 const&){ }
void cst_to_ast_visitor::visit(cst::template_argument_4 const&){ }
void cst_to_ast_visitor::visit(cst::scoped_name const &n)
{
        /* scope IDENTIFIER */
        descend(n._1);
        if(!current_identifier.empty())
                current_identifier += "::";
        current_identifier += n._2;
}

void cst_to_ast_visitor::visit(cst::scope_1 const &)
{
        /* empty */
}

void cst_to_ast_visitor::visit(cst::scope_2 const &s)
{
        /* scope "::" IDENTIFIER */
        descend(s._1);
        if(!current_identifier.empty())
                current_identifier += "::";
        current_identifier += s._2;
}

void cst_to_ast_visitor::visit(cst::literal_1 const&){ }
void cst_to_ast_visitor::visit(cst::literal_2 const&){ }
void cst_to_ast_visitor::visit(cst::boolean_literal_1 const&){ }
void cst_to_ast_visitor::visit(cst::boolean_literal_2 const&){ }

}
}
