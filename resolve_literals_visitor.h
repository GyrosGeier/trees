#ifndef trees_parse_resolve_literals_visitor_hpp_
#define trees_parse_resolve_literals_visitor_hpp_ 1

#include <parse_tree.hpp>

#include <map>
#include <list>

namespace trees {
namespace parse {

class resolve_literals_visitor :
        public node_visitor
{
public:
        resolve_literals_visitor(bool verbose) : verbose(verbose), num(0) { }
        virtual ~resolve_literals_visitor() throw() { }

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
        unsigned int num;

        root_ptr rt;
        std::map<std::string, string_literal_ptr> literals;

        component_ptr *current_context;
};

}
}

#endif
