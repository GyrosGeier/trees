#ifndef foundry_parse_inline_simple_visitor_h_
#define foundry_parse_inline_simple_visitor_h_ 1

#include <parse_tree.hpp>

namespace foundry {
namespace parse {

class inline_simple_visitor :
        public node_visitor
{
public:
        inline_simple_visitor(bool verbose) : verbose(verbose) { }
        virtual ~inline_simple_visitor() throw() { }

        virtual void visit(foundry::parse::string_literal&);
        virtual void visit(foundry::parse::unresolved_symbol&);
        virtual void visit(foundry::parse::terminal&);
        virtual void visit(foundry::parse::nonterminal&);
        virtual void visit(foundry::parse::regex&);
        virtual void visit(foundry::parse::group&);
        virtual void visit(foundry::parse::root&);
        virtual void visit(foundry::parse::rule&);
        virtual void visit(foundry::parse::alternative&);

private:
        bool verbose;
        rule_ptr *current_rule_context;
        component_ptr *current_component_context;

        bool is_simple_rule(rule_ptr &);

        bool is_simple;
};

}
}

#endif
