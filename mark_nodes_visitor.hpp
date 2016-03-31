#ifndef trees_tree_mark_nodes_visitor_hpp_
#define trees_tree_mark_nodes_visitor_hpp_ 1

#include <tree_tree.hpp>

namespace trees {
namespace tree {

class mark_nodes_visitor :
        public node_visitor
{
public:
        virtual ~mark_nodes_visitor(void) throw() { }

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
        bool collecting;
};

}
}

#endif
