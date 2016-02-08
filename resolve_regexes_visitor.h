#ifndef foundry_parse_resolve_regexes_visitor_h_
#define foundry_parse_resolve_regexes_visitor_h_ 1

#include <parse_tree.hpp>

namespace foundry {
namespace parse {

class resolve_regexes_visitor :
        public node_visitor
{
public:
        resolve_regexes_visitor(bool verbose) : verbose(verbose), num(0) { }
        virtual ~resolve_regexes_visitor() throw() { }

        virtual void visit(string_literal&);
        virtual void visit(unresolved_symbol&);
        virtual void visit(terminal&);
        virtual void visit(nonterminal&);
        virtual void visit(regex&);
        virtual void visit(group&);
        virtual void visit(root&);
        virtual void visit(rule&);
        virtual void visit(alternative&);

private:
        bool verbose;
        unsigned int num;
        root_ptr rt;
        component_ptr *current_context;
};

}
}

#endif
