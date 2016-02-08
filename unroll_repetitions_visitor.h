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

        virtual void visit(regex &);
        virtual void visit(string_literal &);
        virtual void visit(unresolved_symbol &);
        virtual void visit(terminal &);
        virtual void visit(nonterminal &);
        virtual void visit(group &);
        virtual void visit(root &);
        virtual void visit(rule &);
        virtual void visit(alternative &);

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
