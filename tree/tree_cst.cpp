#include <sstream>

#include <stdexcept>

#include "tree_cst_tree.hpp"
#include "tree_cst_parse.hpp"

class parse_error :
    public std::logic_error
{
public:
    parse_error(std::string const &msg);
};

parse_error::parse_error(std::string const &msg) :
    std::logic_error(msg)
{
    return;
}

int tree_cst_error(YYLTYPE *loc, void *, foundry::tree::cst::start *&, char const *msg)
{
    std::ostringstream msgstr;

    msgstr << loc->first_line << ":" << loc->first_column << ":" << msg;
    throw parse_error(msgstr.str());
}
