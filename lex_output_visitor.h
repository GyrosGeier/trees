#ifndef foundry_parse_lex_output_visitor_hpp_
#define foundry_parse_lex_output_visitor_hpp_ 1

#include "parse_tree.hpp"

namespace foundry {
namespace parse {

class lex_output_visitor :
        public node_const_visitor
{
public:
        lex_output_visitor(std::ostream &out);

        virtual void visit(root const &);
        virtual void visit(rule const &);
        virtual void visit(alternative const &);
        virtual void visit(unresolved_symbol const &);
        virtual void visit(regex const &);
        virtual void visit(string_literal const &);
        virtual void visit(terminal const &);
        virtual void visit(nonterminal const &);
        virtual void visit(group const &);

private:
        std::ostream &out;
};

}
}

#endif
