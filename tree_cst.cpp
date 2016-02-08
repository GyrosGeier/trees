/* Copyright 2009 Simon Richter <Simon.Richter@hogyros.de>
 *
 * Released under the GNU General Public Licence version 3.
 */

#include <sstream>

#include <stdexcept>

#include "tree_cst_cst.hpp"
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
