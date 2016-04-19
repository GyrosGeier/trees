#ifndef trees_parse_resolve_symbols_visitor_hpp_
#define trees_parse_resolve_symbols_visitor_hpp_ 1

#include <parse_tree.hpp>

#include <map>
#include <list>

namespace trees {
namespace parse {

class resolve_symbols_visitor :
        public component_visitor
{
public:
        resolve_symbols_visitor(bool verbose) : verbose(verbose) { }
        virtual ~resolve_symbols_visitor() throw() { }

        void operator()(root_ptr);

        virtual component_ptr visit(group_ptr);
        virtual component_ptr visit(regex_ptr);
        virtual component_ptr visit(string_literal_ptr);
        virtual component_ptr visit(unresolved_symbol_ptr);
        virtual component_ptr visit(terminal_ptr);
        virtual component_ptr visit(nonterminal_ptr);

private:
        bool verbose;
        std::map<std::string, nonterminal_ptr> nonterminals;
        std::map<std::string, std::list<component_ptr *> > unresolved_references;

        component_ptr *current_context;

        void visit(rule_ptr);
        void visit(alternative_ptr);
};

}
}

#endif
