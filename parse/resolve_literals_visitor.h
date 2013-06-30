#ifndef foundry_parse_resolve_literals_visitor_hpp_
#define foundry_parse_resolve_literals_visitor_hpp_ 1

#include "parse_tree.hpp"

#include <map>
#include <list>

namespace foundry {
namespace parse {

class resolve_literals_visitor :
        public node_visitor
{
public:
        resolve_literals_visitor(bool verbose) : verbose(verbose), num(0) { }
        virtual ~resolve_literals_visitor() throw() { }

        virtual void visit(group &);
        virtual void visit(string_literal &);
        virtual void visit(unresolved_symbol &);
        virtual void visit(terminal &);
        virtual void visit(nonterminal &);
        virtual void visit(root &);
        virtual void visit(rule &);
        virtual void visit(alternative &);

private:
        bool verbose;
        unsigned int num;

        root_weak_ptr rt;
        std::map<std::string, string_literal_ptr> literals;

        component_ptr *current_context;
};

}
}

#endif
