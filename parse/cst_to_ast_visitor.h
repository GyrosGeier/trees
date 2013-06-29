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

        virtual void visit(cst::directives_1 const &);
        virtual void visit(cst::directives_2 const &);
        virtual void visit(cst::rules_1 const &);
        virtual void visit(cst::rules_2 const &);
        virtual void visit(cst::alternatives_tail_1 const &);
        virtual void visit(cst::alternatives_tail_2 const &);
        virtual void visit(cst::components_1 const &);
        virtual void visit(cst::components_2 const &);
        virtual void visit(cst::component_1 const &);
        virtual void visit(cst::component_2 const &);
        virtual void visit(cst::start const &);
        virtual void visit(cst::rule const &);
        virtual void visit(cst::alternatives const &);

        root_ptr get_root() { return rt; }

private:
        root_ptr rt;
        rule_ptr current_rule;
        alternative_ptr current_alternative;
};

}
}

#endif
