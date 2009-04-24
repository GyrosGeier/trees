#include <iostream>

#include <cstdlib>

#include "tree_parse.hpp"

int tree_error(YYLTYPE *loc, void *, treecc::start *&, char const *msg)
{
    std::cerr << loc->first_line << ":" << loc->first_column << ":" << msg << std::endl;
    exit(1);
}
