#ifndef foundry_tree_header_output_visitor_hpp_
#define foundry_tree_header_output_visitor_hpp_ 1

#include <tree_tree.hpp>

#include <ostream>

namespace foundry {
namespace tree {

class header_output_visitor :
    public const_visitor
{
public:
    header_output_visitor(std::ostream &out);

    virtual void visit(namespace_node const &);
    virtual void visit(node_node const &);
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
