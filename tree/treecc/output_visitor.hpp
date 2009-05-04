#ifndef output_visitor_hpp_
#define output_visitor_hpp_ 1

#include <tree_tree.hpp>

#include <ostream>
#include <map>

namespace treecc {

class output_visitor :
    public const_visitor
{
public:
    enum desired_output
    {
        header,
        source
    };

    output_visitor(std::ostream &out, desired_output sel) : out(out), sel(sel) { }
    virtual ~output_visitor(void) throw() { }

    virtual void visit(start const &);
    virtual void visit(rules_1 const &);
    virtual void visit(rules_2 const &);
    virtual void visit(rule const &);
    virtual void visit(alternatives_1 const &);
    virtual void visit(alternatives_2 const &);
    virtual void visit(alternatives_3 const &);
    virtual void visit(components_1 const &);
    virtual void visit(components_2 const &);
    virtual void visit(component_1 const &);
    virtual void visit(component_2 const &);
    virtual void visit(symbol_1 const &);
    virtual void visit(symbol_2 const &);

private:
    std::ostream &out;
    desired_output const sel;

    rule const *current_rule;
    unsigned int alternative_count;
    unsigned int component_count;

    enum {
        scan_nonterminals,
        emit_fwddecl,
        emit_defn,
        emit_ctor,
        emit_members,
        emit_constvisitor,
        emit_visitor,
        emit_throwconstvisitor,
        emit_throwvisitor,
        emit_descendconstvisitor,
        emit_descendvisitor,
        emit_dtor,
        emit_constapply,
        emit_apply,
        emit_throwconstvisit,
        emit_throwvisit,
        emit_descendconstvisit,
        emit_descendvisit
    } action;

    std::map<std::string, bool> nonterminal_p;
};

}

#endif
