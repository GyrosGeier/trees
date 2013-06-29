#ifndef foundry_parse_resolve_symbols_visitor_hpp_
#define foundry_parse_resolve_symbols_visitor_hpp_ 1

#include "parse_tree.hpp"

#include <map>
#include <list>

namespace foundry {
namespace parse {

class resolve_symbols_visitor :
        public node_visitor
{
public:
        virtual ~resolve_symbols_visitor() throw() { }

        virtual void visit(string_literal &);
        virtual void visit(unresolved_symbol &);
        virtual void visit(terminal &);
        virtual void visit(nonterminal &);
        virtual void visit(root &);
        virtual void visit(rule &);
        virtual void visit(alternative &);

private:
        std::map<std::string, nonterminal_ptr> nonterminals;
        std::map<std::string, std::list<component_ptr *> > unresolved_references;

        component_ptr *current_context;
};

}
}

#endif
