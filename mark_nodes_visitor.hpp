#ifndef trees_tree_mark_nodes_visitor_hpp_
#define trees_tree_mark_nodes_visitor_hpp_ 1

#include <tree_tree.hpp>

#include <map>
#include <string>

namespace trees {
namespace tree {

class mark_nodes_visitor :
        public type_node_visitor
{
public:
        virtual ~mark_nodes_visitor(void) throw() { }

        void operator()(root_ptr);

        virtual type_node_ptr visit(group_type_node_ptr);
        virtual type_node_ptr visit(node_type_node_ptr);
        virtual type_node_ptr visit(basic_type_node_ptr);
        virtual type_node_ptr visit(rvalue_reference_type_node_ptr);
        virtual type_node_ptr visit(reference_type_node_ptr);
        virtual type_node_ptr visit(pointer_type_node_ptr);
        virtual type_node_ptr visit(template_type_node_ptr);
        virtual type_node_ptr visit(list_type_node_ptr);

private:
        bool collecting;

        std::map<namespace_node_ptr, std::map<std::string, type_node_ptr> > known_types;

        void traverse(namespace_node_ptr);
        void handle(group_node_ptr);
        void handle(node_node_ptr);
        void handle(data_member_node_ptr);
};

}
}

#endif
