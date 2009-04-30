#include <iostream>
#include <exception>

#include <list>
#include <fstream>

#include "cst_to_ast_visitor.hpp"

#include "smartpointer_visitor.hpp"
#include "header_output_visitor.hpp"
#include "impl_output_visitor.hpp"

#include "tree_description_tree.hpp"
#include "tree_description_parse.hpp"
#include "tree_description_lex.hpp"

extern int tree_description_parse(void *scanner, tree_description::start *&ret);

int main(int argc, char **argv)
try
{
    using tree_description::start;
    using namespace foundry::tree;
    using std::endl;

    typedef char const *const *arg_iterator;

    arg_iterator const args_begin = &argv[1];
    arg_iterator const args_end = &argv[argc];

    typedef std::string file;
    typedef std::list<file> file_list;
    
    file_list files;

    file outfile;

    yyscan_t scanner;

    tree_description_lex_init(&scanner);

    enum
    {
        header,
        source
    } outmode = header;

    enum
    {
        initial,
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
            else if(arg == "-c")
                outmode = source;
            else
                files.push_back(arg);
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

    cst_to_ast_visitor generate_ast;

    for(file_list::const_iterator i = files.begin(); i != files.end(); ++i)
    {
        FILE *f = fopen(i->c_str(), "r");
        if(!f)
        {
            std::cerr << "E: file not found: " << *i << std::endl;
            return 1;
        }

        tree_description_restart(f, scanner);

        start *tree = 0;

        if(tree_description_parse(scanner, tree) == 0)
        {
            tree->apply(generate_ast);
            // tree->apply(write);
        }

        //print_visitor print(cout);
        //tree->apply(print);



        delete tree;

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

    tree_description_lex_destroy(scanner);

    boost::intrusive_ptr<node> ast;

    ast = generate_ast.get_ast();

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
