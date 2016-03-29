#ifndef trees_parse_unroll_repetitions_visitor_h_
#define trees_parse_unroll_repetitions_visitor_h_ 1

#include <parse_tree.hpp>

namespace trees {
namespace parse {

class unroll_repetitions_visitor :
        public node_visitor
{
public:
        unroll_repetitions_visitor(bool verbose) : verbose(verbose) { }
        virtual ~unroll_repetitions_visitor() throw() { }

        virtual component_ptr visit(regex &);
        virtual component_ptr visit(string_literal &);
        virtual component_ptr visit(unresolved_symbol &);
        virtual component_ptr visit(terminal &);
        virtual component_ptr visit(nonterminal &);
        virtual component_ptr visit(group &);
        virtual node_ptr visit(root &);
        virtual node_ptr visit(rule &);
        virtual node_ptr visit(alternative &);

private:
        bool verbose;

        std::list<rule_ptr> generated_rules;

        group_ptr current_group;
        std::string current_name;
        alternative_ptr current_alternative;
        component_ptr *current_context;
};

}
}

#endif
