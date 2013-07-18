#include "cst_to_ast_visitor.h"

#include "resolve_symbols_visitor.h"
#include "resolve_literals_visitor.h"
#include "resolve_regexes_visitor.h"
#include "inline_simple_visitor.h"

#include "unroll_repetitions_visitor.h"

#include "bison_output_visitor.h"
#include "lex_output_visitor.h"

#include "parse_parse.hpp"
#include "parse_lex.hpp"

#include "errors.h"

#include <iostream>
#include <fstream>
#include <list>
#include <string>

extern int parse_parse(yyscan_t scanner, ::foundry::parse::cst::start *&ret);

int go(int argc, char **argv);

int main(int argc, char **argv)
{
        using namespace foundry::parse;

        try
        {
                return go(argc, argv);
        }
        catch(internal_error &e)
        {
                std::cerr << e.what() << std::endl;
                return 2;
        }
        catch(input_error &e)
        {
                std::cerr << e.what() << std::endl;
                return 1;
        }
}

int go(int argc, char **argv)
{
        using namespace foundry::parse;

        enum {
                yacc,
                lex
        } output_format = yacc;

        enum {
                initial,
                expect_output
        } state = initial;

        std::list<std::string> inputs;
        std::string output;
        bool verbose = false;

        for(char **i = &argv[1]; i != &argv[argc]; ++i)
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
                        else
                                inputs.push_back(arg);
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
        case expect_output:
                std::cerr << "E: Option -o requires an argument" << std::endl;
                return 1;
        }

        if(output.empty())
        {
                std::cerr << "E: No output file given" << std::endl;
                return 1;
        }

        yyscan_t scanner;

        parse_lex_init(&scanner);

        cst_to_ast_visitor v;

        for(std::list<std::string>::const_iterator i = inputs.begin(); i != inputs.end(); ++i)
        {
                FILE *f = fopen(i->c_str(), "r");
                if(!f)
                        continue;

                parse_restart(f, scanner);

                cst::start *start;
                parse_parse(scanner, start);

                start->apply(v);

        }

        parse_lex_destroy(scanner);

        root_ptr r = v.get_root();

        resolve_symbols_visitor resolve_symbols(verbose);
        r->apply(resolve_symbols);

        resolve_literals_visitor resolve_literals(verbose);
        r->apply(resolve_literals);

        resolve_regexes_visitor resolve_regexes(verbose);
        r->apply(resolve_regexes);

        inline_simple_visitor inline_simple(verbose);
        r->apply(inline_simple);

        unroll_repetitions_visitor unroll_repetitions(verbose);
        r->apply(unroll_repetitions);

        std::ofstream out(output.c_str());

        switch(output_format)
        {
        case yacc:
                {
                        bison_output_visitor yaccout(out);
                        r->apply(yaccout);
                }
                break;
        case lex:
                {
                        lex_output_visitor lexout(out);
                        r->apply(lexout);
                }
                break;
        }

        return 0;
}
