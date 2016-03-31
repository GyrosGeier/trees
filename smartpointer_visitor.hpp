/* Copyright 2009 Simon Richter <Simon.Richter@hogyros.de>
 *
 * Released under the GNU General Public Licence version 3.
 */

#ifndef trees_tree_smartpointer_visitor_hpp_
#define trees_tree_smartpointer_visitor_hpp_ 1

#include <tree_tree.hpp>

namespace trees {
namespace tree {

class smartpointer_visitor :
        public node_visitor, public type_node_visitor
{
public:
        virtual ~smartpointer_visitor(void) throw() { }

        using type_node_visitor::descend;

        void operator()(root_ptr const &);

        virtual node_ptr visit(root &);
        virtual node_ptr visit(include_node &);
        virtual node_ptr visit(namespace_node &);
        virtual node_ptr visit(data_member_node &);
        virtual type_node_ptr visit(group_node &);
        virtual type_node_ptr visit(node_node &);
        virtual type_node_ptr visit(basic_type_node &);
        virtual type_node_ptr visit(reference_type_node &);
        virtual type_node_ptr visit(pointer_type_node &);
        virtual type_node_ptr visit(template_type_node &);
        virtual type_node_ptr visit(list_type_node &);

private:
        bool is_node_type;
        root_ptr ast_root;

        void handle(namespace_node_ptr const &);
        void handle(group_node_ptr const &);
        void handle(node_node_ptr const &);
        void handle(data_member_node_ptr const &);
};

}
}

#endif
