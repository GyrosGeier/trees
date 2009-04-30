#ifndef foundry_tree_smartpointer_visitor_hpp_
#define foundry_tree_smartpointer_visitor_hpp_ 1

#include <tree_tree.hpp>

namespace foundry {
namespace tree {

class smartpointer_visitor :
    public visitor
{
public:
    virtual ~smartpointer_visitor(void) throw() { }

    virtual void visit(data_member_node &);
    virtual void visit(node_node &);
    virtual void visit(namespace_node &);
    virtual void visit(basic_type_node &);
    virtual void visit(reference_type_node &);
    virtual void visit(pointer_type_node &);
    virtual void visit(list_type_node &);
    virtual void visit(template_type_node &);

private:
    bool is_node_type;
};

}
}

#endif
