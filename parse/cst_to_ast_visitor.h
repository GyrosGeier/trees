#ifndef foundry_parse_cst_to_ast_visitor_h_
#define foundry_parse_cst_to_ast_visitor_h_ 1

#include "parse_cst.hpp"
#include "parse_tree.hpp"

namespace foundry {
namespace parse {

class cst_to_ast_visitor :
        public cst::node_const_visitor
{
public:
        cst_to_ast_visitor();
        ~cst_to_ast_visitor() throw();

        virtual void visit(cst::directives_chain const &);
        virtual void visit(cst::end_of_directives const &);
        virtual void visit(cst::rules_chain const &);
        virtual void visit(cst::end_of_rules const &);
        virtual void visit(cst::alternatives const &);
        virtual void visit(cst::more_alternatives const &);
        virtual void visit(cst::end_of_alternatives const &);
        virtual void visit(cst::unnamed_alternative const &);
        virtual void visit(cst::named_alternative const &);
        virtual void visit(cst::components_chain const &);
        virtual void visit(cst::end_of_components const &);
        virtual void visit(cst::symbol const &);
        virtual void visit(cst::literal const &);
        virtual void visit(cst::group const &);
        virtual void visit(cst::start const &);
        virtual void visit(cst::rule const &);

        root_ptr get_root() { return rt; }

private:
        root_ptr rt;
        rule_ptr current_rule;
        alternative_ptr current_alternative;
        group_ptr current_group;
};

}
}

#endif
