#ifndef output_visitor_hpp_
#define output_visitor_hpp_ 1

#include <tree_tree.hpp>

#include <ostream>
#include <map>

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
        emit_visitor,
        emit_constvisitor,
        emit_dtorapply
    } action;

    std::map<std::string, bool> nonterminal_p;
};

#endif
