#ifndef trees_parse_inline_simple_visitor_h_
#define trees_parse_inline_simple_visitor_h_ 1

#include <parse_tree.hpp>

namespace trees {
namespace parse {

class inline_simple_visitor :
        public component_visitor
{
public:
        inline_simple_visitor(bool verbose) : verbose(verbose) { }
        virtual ~inline_simple_visitor() throw() { }

        void operator()(trees::parse::root_ptr);

        virtual component_ptr visit(trees::parse::string_literal_ptr);
        virtual component_ptr visit(trees::parse::unresolved_symbol_ptr);
        virtual component_ptr visit(trees::parse::terminal_ptr);
        virtual component_ptr visit(trees::parse::nonterminal_ptr);
        virtual component_ptr visit(trees::parse::regex_ptr);
        virtual component_ptr visit(trees::parse::group_ptr);

private:
        bool verbose;
        rule_ptr start;
        rule_ptr *current_rule_context;
        component_ptr *current_component_context;

        bool is_simple_rule(rule_ptr &);

        bool is_simple;

        void handle(trees::parse::rule_ptr);
        void handle(trees::parse::alternative_ptr);
};

}
}

#endif
