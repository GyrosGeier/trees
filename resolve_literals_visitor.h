#ifndef trees_parse_resolve_literals_visitor_hpp_
#define trees_parse_resolve_literals_visitor_hpp_ 1

#include <parse_tree.hpp>

#include <map>
#include <list>

namespace trees {
namespace parse {

class resolve_literals_visitor :
        public component_visitor
{
public:
        resolve_literals_visitor(bool verbose) : verbose(verbose), num(0) { }
        virtual ~resolve_literals_visitor() throw() { }

        void operator()(root_ptr);

        virtual component_ptr visit(group_ptr);
        virtual component_ptr visit(regex_ptr);
        virtual component_ptr visit(string_literal_ptr);
        virtual component_ptr visit(unresolved_symbol_ptr);
        virtual component_ptr visit(terminal_ptr);
        virtual component_ptr visit(nonterminal_ptr);

private:
        bool verbose;
        unsigned int num;

        root_ptr rt;
        std::map<std::string, string_literal_ptr> literals;

        void visit(rule_ptr);
        void visit(alternative_ptr);
};

}
}

#endif
