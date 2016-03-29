#ifndef trees_parse_resolve_regexes_visitor_h_
#define trees_parse_resolve_regexes_visitor_h_ 1

#include <parse_tree.hpp>

namespace trees {
namespace parse {

class resolve_regexes_visitor :
        public node_visitor
{
public:
        resolve_regexes_visitor(bool verbose) : verbose(verbose), num(0) { }
        virtual ~resolve_regexes_visitor() throw() { }

        virtual component_ptr visit(string_literal&);
        virtual component_ptr visit(unresolved_symbol&);
        virtual component_ptr visit(terminal&);
        virtual component_ptr visit(nonterminal&);
        virtual component_ptr visit(regex&);
        virtual component_ptr visit(group&);
        virtual node_ptr visit(root&);
        virtual node_ptr visit(rule&);
        virtual node_ptr visit(alternative&);

private:
        bool verbose;
        unsigned int num;
        root_ptr rt;
        component_ptr *current_context;
};

}
}

#endif
