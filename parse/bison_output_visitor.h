#ifndef foundry_parse_bison_output_visitor_h_
#define foundry_parse_bison_output_visitor_h_ 1

#include "parse_tree.hpp"

namespace foundry {
namespace parse {

class bison_output_visitor :
        public node_const_visitor
{
public:
        bison_output_visitor(std::ostream &out);
        ~bison_output_visitor() throw() { }

        virtual void visit(root const &);
        virtual void visit(rule const &);
        virtual void visit(alternative const &);
        virtual void visit(unresolved_symbol const &) { throw; }
        virtual void visit(string_literal const &);
        virtual void visit(terminal const &);
        virtual void visit(nonterminal const &);

private:
        std::ostream &out;
        rule const *current_rule;
        bool first_alternative, first_component;
        bool multiple_alternatives;
        unsigned int current_alternative, current_component;

        enum
        {
                write_union_members,
                write_type_decls,
                write_rules,
                write_components,
                write_action
        } state;
};

}
}

#endif
