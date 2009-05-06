#include <iostream>

#include <cstdlib>

#include "tree_bison_tree.hpp"
#include "tree_bison_parse.hpp"

int tree_bison_error(YYLTYPE *loc, void *, foundry::tree::bison::start *&, char const *msg)
{
    std::cerr << loc->first_line << ":" << loc->first_column << ":" << msg << std::endl;
    exit(1);
}