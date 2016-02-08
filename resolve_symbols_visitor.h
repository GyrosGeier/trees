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

        virtual void visit(group &);
        virtual void visit(regex &);
        virtual void visit(string_literal &);
        virtual void visit(unresolved_symbol &);
        virtual void visit(terminal &);
        virtual void visit(nonterminal &);
        virtual void visit(root &);
        virtual void visit(rule &);
        virtual void visit(alternative &);

private:
        bool verbose;
        std::map<std::string, nonterminal_ptr> nonterminals;
        std::map<std::string, std::list<component_ptr *> > unresolved_references;

        component_ptr *current_context;
};

}
}

#endif
