#include <iostream>
#include <exception>

#include <list>
#include <fstream>

#include "cst_to_ast_visitor.hpp"
#include "bison_to_ast_visitor.hpp"

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

extern int tree_bison_parse(void *scanner, foundry::tree::bison::start *&ret);
extern int tree_cst_parse(void *scanner, foundry::tree::cst::start *&ret);

std::string extension(std::string const &s)
{
    std::string::size_type const dot = s.rfind('.');
    if(dot == std::string::npos)
        return "";
    return s.substr(dot);
}

int main(int argc, char **argv)
try
{
    using foundry::tree::cst::start;
    using namespace foundry::tree;
    using std::endl;

    typedef char const *const *arg_iterator;

    arg_iterator const args_begin = &argv[1];
    arg_iterator const args_end = &argv[argc];

    typedef std::string file;
    typedef std::list<file> file_list;
    
    file_list files;

    file outfile;

    yyscan_t bison_scanner;
    yyscan_t cst_scanner;

    context bison_context;
    tree_bison_lex_init_extra(&bison_context, &bison_scanner);
    tree_cst_lex_init(&cst_scanner);

    enum
    {
        header,
        source
    } outmode = header;

    std::list<std::string> outns;

    enum
    {
        initial,
        ns,
        output
    } state = initial;

    for(arg_iterator i = args_begin; i != args_end; ++i)
    {
        std::string arg(*i);

        switch(state)
        {
        case initial:
            if(arg == "-o")
                state = output;
            else if(arg == "-n")
                state = ns;
            else if(arg == "-c")
                outmode = source;
            else
                files.push_back(arg);
            break;

        case ns:
            outns.push_back(arg);
            state = initial;
            break;

        case output:
            outfile = arg;
            state = initial;
            break;
        }
    }

    if(state != initial)
    {
        std::cerr << "E: missing parameter" << std::endl;
        return 1;
    }

    if(outfile.empty())
    {
        std::cerr << "E: no output file given" << std::endl;
        return 1;
    }

    cst_to_ast_visitor cst_to_ast;
    bison_to_ast_visitor bison_to_ast;
    for(std::list<std::string>::const_iterator i = outns.begin();
            i != outns.end(); ++i)
        bison_to_ast.push_initial_namespace(*i);

    for(file_list::const_iterator i = files.begin(); i != files.end(); ++i)
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
            start *tree = 0;
            if(tree_cst_parse(cst_scanner, tree) == 0)
            {
                tree->apply(cst_to_ast);
            }
            delete tree;
        }

        fclose(f);
    }

    /*

    if(!outns.empty())
        out << endl
            << "}" << endl;

    if(outmode == header)
        out << endl
            << "#endif" << endl;

    */

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

    smartpointer_visitor smartptr;
    ast->apply(smartptr);

    std::ofstream out(outfile.c_str());

    switch(outmode)
    {
    case header:
        {
            std::string::size_type slash = outfile.rfind('/');
            if(slash == std::string::npos)
                slash = 0;
            else
                ++slash;

            std::string cppsymbol(outfile, slash);
            for(unsigned int i = 0; i < cppsymbol.size(); ++i)
            {
                char c = cppsymbol[i];
                if(c < '0' || (c > '9' && c < 'A') || (c > 'Z' && c < 'a') || c > 'z')
                    cppsymbol[i] = '_';
            }
            out << "#ifndef " << cppsymbol << "_" << endl
                << "#define " << cppsymbol << "_ 1" << endl
                << endl;
            header_output_visitor write_header(out);
            ast->apply(write_header);
            out << "#endif" << endl;
        }
        break;
    case source:
        {
            std::string::size_type dot = outfile.rfind('.');
            if(dot == std::string::npos)
                break;
            std::string ext = outfile.substr(dot);
            if(ext == ".cpp")
                ext = ".hpp";
            else if(ext == ".cc")
                ext = ".hh";
            else
                break;
            std::string::size_type slash = outfile.rfind('/');
            if(slash == std::string::npos)
                slash = 0;
            else
                ++slash;
            std::string basename = outfile.substr(slash, dot - slash);
            out << "#include <" << basename << ext << ">" << endl
                << endl;
            impl_output_visitor write_impl(out);
            ast->apply(write_impl);
        }
        break;
    }

    /*
            std::string::size_type slash = outfile.rfind('/');
            if(slash == std::string::npos)
                slash = 0;
            else
                ++slash;

            std::string cppsymbol(outfile, slash);
            for(unsigned int i = 0; i < cppsymbol.size(); ++i)
            {
                char c = cppsymbol[i];
                if(c < '0' || (c > '9' && c < 'A') || (c > 'Z' && c < 'a') || c > 'z')
                    cppsymbol[i] = '_';
            }
            out << "#ifndef " << cppsymbol << "_" << endl
                << "#define " << cppsymbol << "_ 1" << endl
                << endl
                << "#include <string>" << endl
                << "#include <typeinfo>" << endl
                << "#include <stdexcept>" << endl
                << endl;
        }
        break;
    case source:
        {
            std::string::size_type dot = outfile.rfind('.');
            if(dot == std::string::npos)
                break;
            std::string ext = outfile.substr(dot);
            if(ext == ".cpp")
                ext = ".hpp";
            else if(ext == ".cc")
                ext = ".hh";
            else
                break;
            std::string::size_type slash = outfile.rfind('/');
            if(slash == std::string::npos)
                slash = 0;
            else
                ++slash;
            std::string basename = outfile.substr(slash, dot - slash);
            out << "#include <" << basename << ext << ">" << endl
                << endl;
        }
    }

    if(!outns.empty())
        out << "namespace " << outns << " {" << endl
            << endl;

    output_visitor write(out, (outmode == header)?write.header:write.source);

    */

    return 0;
}
catch(std::exception &e)
{
    std::cerr << "E: " << e.what() << std::endl;
    return 1;
}
