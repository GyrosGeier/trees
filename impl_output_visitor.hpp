/* Copyright 2009 Simon Richter <Simon.Richter@hogyros.de>
 *
 * Released under the GNU General Public Licence version 3.
 */

#ifndef trees_tree_impl_output_visitor_hpp_
#define trees_tree_impl_output_visitor_hpp_ 1

#include <tree_tree.hpp>

#include <ostream>

namespace trees {
namespace tree {

class impl_output_visitor :
        public node_const_visitor
{
public:
        impl_output_visitor(std::ostream &out);
        virtual ~impl_output_visitor(void) throw() { }

        virtual void visit(root const &);
        virtual void visit(include_node const &);
        virtual void visit(node_node const &);
        virtual void visit(group_node const &);
        virtual void visit(namespace_node const &);
        virtual void visit(basic_type_node const &);
        virtual void visit(reference_type_node const &);
        virtual void visit(pointer_type_node const &);
        virtual void visit(template_type_node const &);
        virtual void visit(list_type_node const &);
        virtual void visit(data_member_node const &);

private:
        std::ostream &out;
};

}
}

#endif
