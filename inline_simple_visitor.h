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

        virtual component_ptr visit(trees::parse::string_literal&);
        virtual component_ptr visit(trees::parse::unresolved_symbol&);
        virtual component_ptr visit(trees::parse::terminal&);
        virtual component_ptr visit(trees::parse::nonterminal&);
        virtual component_ptr visit(trees::parse::regex&);
        virtual component_ptr visit(trees::parse::group&);
        virtual node_ptr visit(trees::parse::root&);
        virtual node_ptr visit(trees::parse::rule&);
        virtual node_ptr visit(trees::parse::alternative&);

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
