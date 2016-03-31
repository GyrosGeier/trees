/* Copyright 2009 Simon Richter <Simon.Richter@hogyros.de>
 *
 * Released under the GNU General Public Licence version 3.
 */

#include "tree_cst_to_ast_visitor.hpp"
#include "bison_to_ast_visitor.hpp"
#include "parse_cst_to_ast_visitor.h"

#include "mark_nodes_visitor.hpp"
#include "smartpointer_visitor.hpp"

#include "resolve_symbols_visitor.h"
#include "resolve_literals_visitor.h"
#include "resolve_regexes_visitor.h"
#include "inline_simple_visitor.h"

#include "unroll_repetitions_visitor.h"

#include "header_output_visitor.hpp"
#include "impl_output_visitor.hpp"
#include "bison_output_visitor.h"
#include "lex_output_visitor.h"

#include <tree_bison_context.hpp>
#include <tree_bison_cst.hpp>
#include <tree_bison_parse.hpp>
#include <tree_bison_lex.hpp>

#include <tree_cst_cst.hpp>
#include <tree_cst_parse.hpp>
#include <tree_cst_lex.hpp>

#include <parse_cst_parse.hpp>
#include <parse_cst_lex.hpp>

#include "errors.h"

#include <exception>

#include <iostream>
#include <fstream>
#include <list>
#include <string>

extern int tree_bison_parse(void *scanner, trees::tree::bison::start *&ret);
extern int tree_cst_parse(void *scanner, trees::tree::cst::start *&ret);
extern int parse_cst_parse(yyscan_t scanner, ::trees::parse::cst::start *&ret);

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
        using namespace trees::parse;

        try
        {
                return go(argc, argv);
        }
        catch(internal_error &e)
        {
                std::cerr << "E: " << e.what() << std::endl;
                return 1;
        }
        catch(input_error &e)
        {
                std::cerr << "E: " << e.what() << std::endl;
                return 1;
        }
        catch(std::exception &e)
        {
                std::cerr << "E: " << e.what() << std::endl;
                return 2;
        }
}

int go(int argc, char **argv)
{
        using namespace trees;

        typedef char const *const *arg_iterator;

        arg_iterator const args_begin = &argv[1];
        arg_iterator const args_end = &argv[argc];

        enum
        {
                header,
                source,
                yacc,
                lex
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

        bool verbose = false;

        for(arg_iterator i = args_begin; i != args_end; ++i)
        {
                std::string const arg(*i);

                switch(state)
                {
                case initial:
                        if(arg == "-v")
                                verbose = true;
                        else if(arg == "-y")
                                output_format = yacc;
                        else if(arg == "-l")
                                output_format = lex;
                        else if(arg == "-o")
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

        if(inputs.empty())
        {
                std::cerr << "E: No input file given" << std::endl;
                return 1;
        }

        if(output.empty())
        {
                std::cerr << "E: No output file given" << std::endl;
                return 1;
        }

        yyscan_t bison_scanner;
        yyscan_t cst_scanner;
        yyscan_t scanner;
        parse_cst_lex_init(&scanner);

        context bison_context;
        tree_bison_lex_init_extra(&bison_context, &bison_scanner);
        tree_cst_lex_init(&cst_scanner);

        tree::cst_to_ast_visitor cst_to_ast;
        tree::bison_to_ast_visitor bison_to_ast;
        parse::cst_to_ast_visitor v;

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
                        tree::bison::start *tree = 0;
                        if(tree_bison_parse(bison_scanner, tree) == 0)
                        {
                                tree->apply(bison_to_ast);
                        }
                        delete tree;
                }
                else if(extension(*i) == ".ftree")
                {
                        tree_cst_restart(f, cst_scanner);
                        tree::cst::start *tree = 0;
                        if(tree_cst_parse(cst_scanner, tree) == 0)
                        {
                                tree->apply(cst_to_ast);
                        }
                        delete tree;
                }
                else if(extension(*i) == ".fparse")
                {
                        parse_cst_restart(f, scanner);

                        parse::cst::start *start;
                        parse_cst_parse(scanner, start);

                        start->apply(v);
                        delete start;
                }

                fclose(f);
        }

        parse_cst_lex_destroy(scanner);
        tree_cst_lex_destroy(cst_scanner);
        tree_bison_lex_destroy(bison_scanner);

        parse::root_ptr r = v.get_root();

        parse::resolve_symbols_visitor resolve_symbols(verbose);
        r->apply(resolve_symbols);

        parse::resolve_literals_visitor resolve_literals(verbose);
        r->apply(resolve_literals);

        parse::resolve_regexes_visitor resolve_regexes(verbose);
        r->apply(resolve_regexes);

        parse::inline_simple_visitor inline_simple(verbose);
        r->apply(inline_simple);

        parse::unroll_repetitions_visitor unroll_repetitions(verbose);
        r->apply(unroll_repetitions);

        tree::root_ptr ast, ast2;

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

        tree::mark_nodes_visitor mark_nodes;
        mark_nodes(ast);

        tree::smartpointer_visitor smartptr;
        smartptr(ast);

        std::ofstream out(output.c_str());

        std::string::size_type const dot = output.rfind('.');

        std::string::size_type slash = output.rfind('/');
        if(slash == std::string::npos)
                slash = 0;
        else
                ++slash;

        std::string const basename = output.substr(slash, dot - slash);

        switch(output_format)
        {
        case header:
                {
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
                        tree::header_output_visitor write_header(out);
                        ast->apply(write_header);
                        out << "#endif" << std::endl;
                }
                break;
        case source:
                {
                        if(dot == std::string::npos)
                                break;
                        std::string ext = output.substr(dot);
                        if(ext == ".cpp")
                                ext = ".hpp";
                        else if(ext == ".cc")
                                ext = ".hh";
                        else
                                break;

                        out << "#include <" << basename << ext << ">" << std::endl
                                << std::endl;
                        tree::impl_output_visitor write_impl(out);
                        ast->apply(write_impl);
                }
                break;
        case yacc:
                {
                        parse::bison_output_visitor yaccout(basename, out);
                        r->apply(yaccout);
                }
                break;
        case lex:
                {
                        parse::lex_output_visitor lexout(basename, out);
                        r->apply(lexout);
                }
                break;
        }

        return 0;
}
