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

        virtual void visit(root &);
        virtual void visit(include_node &);
        virtual void visit(namespace_node &);
        virtual void visit(data_member_node &);
        virtual void visit(group_node &);
        virtual void visit(node_node &);
        virtual void visit(basic_type_node &);
        virtual void visit(reference_type_node &);
        virtual void visit(pointer_type_node &);
        virtual void visit(template_type_node &);
        virtual void visit(list_type_node &);

private:
        bool collecting;
};

}
}

#endif
