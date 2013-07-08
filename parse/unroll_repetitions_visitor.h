#ifndef foundry_parse_unroll_repetitions_visitor_h_
#define foundry_parse_unroll_repetitions_visitor_h_ 1

#include "parse_tree.hpp"

namespace foundry {
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

        void unroll_common(component &);

        std::list<rule_ptr> generated_rules;

        group_weak_ptr current_group;
        alternative_weak_ptr current_alternative;
        component_ptr *current_context;
};

}
}

#endif
