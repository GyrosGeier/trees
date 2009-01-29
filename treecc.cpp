#include <tree_context.hpp>
#include <tree_parse.hpp>
#include <tree_lex.hpp>
#include <tree_tree.hpp>

#include "output_visitor.hpp"

#include <boost/ptr_container/ptr_list.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <list>

//extern int tree_debug;

int tree_parse(void *scanner, start *&ret);

int main(int argc, char **argv)
{
  //  tree_debug = 1;

    typedef char const *const *arg_iterator;

    arg_iterator const args_begin = &argv[1];
    arg_iterator const args_end = &argv[argc];

    typedef std::string file;
    typedef std::list<file> file_list;
    
    file_list files;

    file outfile;
    std::string outns;

    yyscan_t scanner;

    context ctx;

    tree_lex_init_extra(&ctx, &scanner);

    enum
    {
        header,
        source
    } outmode = header;

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
            outns = arg;
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

    std::ofstream out(outfile.c_str());

    switch(outmode)
    {
    case header:
        {
            std::string cppsymbol(outfile);
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

    for(file_list::const_iterator i = files.begin(); i != files.end(); ++i)
    {
        FILE *f = fopen(i->c_str(), "r");
        if(!f)
        {
            std::cerr << "E: file not found: " << *i << std::endl;
            return 1;
        }

        tree_restart(f, scanner);

        start *tree = 0;

        if(tree_parse(scanner, tree) == 0)
        {
            tree->apply(write);
        }

        //print_visitor print(cout);
        //tree->apply(print);



        delete tree;

        fclose(f);
    }

    if(!outns.empty())
        out << endl
            << "}" << endl;

    if(outmode == header)
        out << endl
            << "#endif" << endl;

    tree_lex_destroy(scanner);
}

