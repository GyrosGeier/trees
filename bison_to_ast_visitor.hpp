/* Copyright 2009 Simon Richter <Simon.Richter@hogyros.de>
 *
 * Released under the GNU General Public Licence version 3.
 */

#ifndef foundry_tree_bison_to_ast_visitor_hpp_
#define foundry_tree_bison_to_ast_visitor_hpp_ 1

#include <tree_bison_cst.hpp>
#include <tree_tree.hpp>

#include <set>
#include <list>
#include <string>

namespace foundry {
namespace tree {

class bison_to_ast_visitor :
        public bison::node_const_visitor
{
public:
        bison_to_ast_visitor(void);
        virtual ~bison_to_ast_visitor(void) throw() { }

        root_ptr get_ast(void) { return ast; }

        virtual void visit(bison::start const &);
        virtual void visit(bison::empty_rules const &);
        virtual void visit(bison::chained_rules const &);
        virtual void visit(bison::rule const &);
        virtual void visit(bison::unnamed_alternative const &);
        virtual void visit(bison::named_alternative const &);
        virtual void visit(bison::single_alternative const &);
        virtual void visit(bison::chained_alternatives const &);
        virtual void visit(bison::terminated_alternatives const &);
        virtual void visit(bison::empty_components const &);
        virtual void visit(bison::chained_components const &);
        virtual void visit(bison::symbol const &);
        virtual void visit(bison::literal const &);

        void push_initial_namespace(std::string const &);

private:
        root_ptr ast;
        namespace_node_weak_ptr current_namespace;
        group_node_weak_ptr current_group;
        node_node_weak_ptr current_node;
        std::string current_identifier;
        unsigned int current_count;
        std::set<std::string> nonterminals;
        std::list<basic_type_node_weak_ptr> unresolved;
};

}
}

#endif
