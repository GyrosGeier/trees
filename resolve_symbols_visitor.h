#ifndef trees_parse_resolve_symbols_visitor_hpp_
#define trees_parse_resolve_symbols_visitor_hpp_ 1

#include <parse_tree.hpp>

#include <map>
#include <list>

namespace trees {
namespace parse {

class resolve_symbols_visitor :
        public node_visitor
{
public:
        resolve_symbols_visitor(bool verbose) : verbose(verbose) { }
        virtual ~resolve_symbols_visitor() throw() { }

        virtual component_ptr visit(group &);
        virtual component_ptr visit(regex &);
        virtual component_ptr visit(string_literal &);
        virtual component_ptr visit(unresolved_symbol &);
        virtual component_ptr visit(terminal &);
        virtual component_ptr visit(nonterminal &);
        virtual node_ptr visit(root &);
        virtual node_ptr visit(rule &);
        virtual node_ptr visit(alternative &);

private:
        bool verbose;
        std::map<std::string, nonterminal_ptr> nonterminals;
        std::map<std::string, std::list<component_ptr *> > unresolved_references;

        component_ptr *current_context;
};

}
}

#endif
