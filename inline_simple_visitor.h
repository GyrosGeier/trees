#ifndef trees_parse_inline_simple_visitor_h_
#define trees_parse_inline_simple_visitor_h_ 1

#include <parse_tree.hpp>

namespace trees {
namespace parse {

class inline_simple_visitor :
        public node_visitor
{
public:
        inline_simple_visitor(bool verbose) : verbose(verbose) { }
        virtual ~inline_simple_visitor() throw() { }

        virtual void visit(trees::parse::string_literal&);
        virtual void visit(trees::parse::unresolved_symbol&);
        virtual void visit(trees::parse::terminal&);
        virtual void visit(trees::parse::nonterminal&);
        virtual void visit(trees::parse::regex&);
        virtual void visit(trees::parse::group&);
        virtual void visit(trees::parse::root&);
        virtual void visit(trees::parse::rule&);
        virtual void visit(trees::parse::alternative&);

private:
        bool verbose;
        rule_ptr start;
        rule_ptr *current_rule_context;
        component_ptr *current_component_context;

        bool is_simple_rule(rule_ptr &);

        bool is_simple;
};

}
}

#endif
