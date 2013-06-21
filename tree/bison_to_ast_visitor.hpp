/* Copyright 2009 Simon Richter <Simon.Richter@hogyros.de>
 *
 * Released under the GNU General Public Licence version 3.
 */

#ifndef foundry_tree_bison_to_ast_visitor_hpp_
#define foundry_tree_bison_to_ast_visitor_hpp_ 1

#include <tree_bison_tree.hpp>
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
    virtual void visit(bison::rules_1 const &);
    virtual void visit(bison::rules_2 const &);
    virtual void visit(bison::rule const &);
    virtual void visit(bison::alternatives_1 const &);
    virtual void visit(bison::alternatives_2 const &);
    virtual void visit(bison::alternatives_3 const &);
    virtual void visit(bison::components_1 const &);
    virtual void visit(bison::components_2 const &);
    virtual void visit(bison::component_1 const &);
    virtual void visit(bison::component_2 const &);

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
