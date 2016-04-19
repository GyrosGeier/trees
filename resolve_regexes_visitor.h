#ifndef trees_parse_resolve_regexes_visitor_h_
#define trees_parse_resolve_regexes_visitor_h_ 1

#include <parse_tree.hpp>

namespace trees {
namespace parse {

class resolve_regexes_visitor :
        public component_visitor
{
public:
        resolve_regexes_visitor(bool verbose) : verbose(verbose), num(0) { }
        virtual ~resolve_regexes_visitor() throw() { }

        void operator()(root_ptr);

        virtual component_ptr visit(string_literal_ptr);
        virtual component_ptr visit(unresolved_symbol_ptr);
        virtual component_ptr visit(terminal_ptr);
        virtual component_ptr visit(nonterminal_ptr);
        virtual component_ptr visit(regex_ptr);
        virtual component_ptr visit(group_ptr);

private:
        bool verbose;
        unsigned int num;
        root_ptr rt;
        component_ptr *current_context;

        void visit(rule_ptr);
        void visit(alternative_ptr);
};

}
}

#endif
