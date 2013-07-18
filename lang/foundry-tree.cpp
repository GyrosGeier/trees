/* Copyright 2009 Simon Richter <Simon.Richter@hogyros.de>
 *
 * Released under the GNU General Public Licence version 3.
 */

#include "tree_cst_to_ast_visitor.hpp"
#include "bison_to_ast_visitor.hpp"

#include "mark_nodes_visitor.hpp"
#include "smartpointer_visitor.hpp"
#include "header_output_visitor.hpp"
#include "impl_output_visitor.hpp"

#include "tree_bison_context.hpp"
#include "tree_bison_tree.hpp"
#include "tree_bison_parse.hpp"
#include "tree_bison_lex.hpp"

#include "tree_cst_tree.hpp"
#include "tree_cst_parse.hpp"
#include "tree_cst_lex.hpp"

#include <exception>
#include <iostream>
#include <fstream>
#include <list>

extern int tree_bison_parse(void *scanner, foundry::tree::bison::start *&ret);
extern int tree_cst_parse(void *scanner, foundry::tree::cst::start *&ret);

std::string extension(std::string const &s)
{
        std::string::size_type const dot = s.rfind('.');
        if(dot == std::string::npos)
                return "";
        return s.substr(dot);
}

int go(int argc, char **argv);

int main(int argc, char **argv)
{
        try
        {
                return go(argc, argv);
        }
        catch(std::exception &e)
        {
                std::cerr << "E: " << e.what() << std::endl;
                return 1;
        }
}

int go(int argc, char **argv)
{
        using namespace foundry::tree;

        typedef char const *const *arg_iterator;

        arg_iterator const args_begin = &argv[1];
        arg_iterator const args_end = &argv[argc];

        enum
        {
                header,
                source
        } output_format = header;

        std::list<std::string> outns;

        enum
        {
                initial,
                expect_ns,
                expect_output
        } state = initial;

        typedef std::string file;
        typedef std::list<file> file_list;

        file_list inputs;
        file output;

        for(arg_iterator i = args_begin; i != args_end; ++i)
        {
                std::string const arg(*i);

                switch(state)
                {
                case initial:
                        if(arg == "-o")
                                state = expect_output;
                        else if(arg == "-n")
                                state = expect_ns;
                        else if(arg == "-c")
                                output_format = source;
                        else
                                inputs.push_back(arg);
                        break;

                case expect_ns:
                        outns.push_back(arg);
                        state = initial;
                        break;

                case expect_output:
                        output = arg;
                        state = initial;
                        break;
                }
        }

        switch(state)
        {
        case initial:
                break;
        case expect_ns:
                std::cerr << "E: Option -n requires an argument" << std::endl;
                return 1;
        case expect_output:
                std::cerr << "E: Option -o requires an argument" << std::endl;
                return 1;
        }

        if(output.empty())
        {
                std::cerr << "E: No output file given" << std::endl;
                return 1;
        }

        yyscan_t bison_scanner;
        yyscan_t cst_scanner;

        context bison_context;
        tree_bison_lex_init_extra(&bison_context, &bison_scanner);
        tree_cst_lex_init(&cst_scanner);

        cst_to_ast_visitor cst_to_ast;
        bison_to_ast_visitor bison_to_ast;
        for(std::list<std::string>::const_iterator i = outns.begin();
                        i != outns.end(); ++i)
                bison_to_ast.push_initial_namespace(*i);

        for(file_list::const_iterator i = inputs.begin(); i != inputs.end(); ++i)
        {
                FILE *f = fopen(i->c_str(), "r");
                if(!f)
                {
                        std::cerr << "E: file not found: " << *i << std::endl;
                        return 1;
                }

                if(extension(*i) == ".yy")
                {
                        tree_bison_restart(f, bison_scanner);
                        bison::start *tree = 0;
                        if(tree_bison_parse(bison_scanner, tree) == 0)
                        {
                                tree->apply(bison_to_ast);
                        }
                        delete tree;
                }
                else
                {
                        tree_cst_restart(f, cst_scanner);
                        cst::start *tree = 0;
                        if(tree_cst_parse(cst_scanner, tree) == 0)
                        {
                                tree->apply(cst_to_ast);
                        }
                        delete tree;
                }

                fclose(f);
        }

        tree_cst_lex_destroy(cst_scanner);
        tree_bison_lex_destroy(bison_scanner);

        boost::intrusive_ptr<root> ast, ast2;

        ast = cst_to_ast.get_ast();
        ast2 = bison_to_ast.get_ast();
        ast->includes.splice(ast->includes.end(), ast2->includes);
        if(ast->global_namespace)
        {
                ast->global_namespace->namespaces.splice(ast->global_namespace->namespaces.end(), ast2->global_namespace->namespaces);
                if(ast->global_namespace->group)
                {
                        if(ast2->global_namespace && ast2->global_namespace->group)
                        {
                                ast->global_namespace->group->groups.splice(ast->global_namespace->group->groups.end(), ast2->global_namespace->group->groups);
                                ast->global_namespace->group->nodes.splice(ast->global_namespace->group->nodes.end(), ast2->global_namespace->group->nodes);
                        }
                }
                else
                        ast->global_namespace->group = ast2->global_namespace->group;
        }

        mark_nodes_visitor mark_nodes;
        ast->apply(mark_nodes);

        smartpointer_visitor smartptr;
        ast->apply(smartptr);

        std::ofstream out(output.c_str());

        switch(output_format)
        {
        case header:
                {
                        std::string::size_type slash = output.rfind('/');
                        if(slash == std::string::npos)
                                slash = 0;
                        else
                                ++slash;

                        std::string cppsymbol(output, slash);
                        for(unsigned int i = 0; i < cppsymbol.size(); ++i)
                        {
                                char c = cppsymbol[i];
                                if(c < '0' || (c > '9' && c < 'A') || (c > 'Z' && c < 'a') || c > 'z')
                                        cppsymbol[i] = '_';
                        }
                        out << "#ifndef " << cppsymbol << "_" << std::endl
                                << "#define " << cppsymbol << "_ 1" << std::endl
                                << std::endl;
                        header_output_visitor write_header(out);
                        ast->apply(write_header);
                        out << "#endif" << std::endl;
                }
                break;
        case source:
                {
                        std::string::size_type dot = output.rfind('.');
                        if(dot == std::string::npos)
                                break;
                        std::string ext = output.substr(dot);
                        if(ext == ".cpp")
                                ext = ".hpp";
                        else if(ext == ".cc")
                                ext = ".hh";
                        else
                                break;
                        std::string::size_type slash = output.rfind('/');
                        if(slash == std::string::npos)
                                slash = 0;
                        else
                                ++slash;
                        std::string basename = output.substr(slash, dot - slash);
                        out << "#include <" << basename << ext << ">" << std::endl
                                << std::endl;
                        impl_output_visitor write_impl(out);
                        ast->apply(write_impl);
                }
                break;
        }

        return 0;
}
