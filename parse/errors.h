#ifndef foundry_parse_errors_h_
#define foundry_parse_errors_h_ 1

#include <stdexcept>

namespace foundry {
namespace parse {

class internal_error :
        public std::runtime_error
{
public:
        internal_error(std::string const &msg) :
                std::runtime_error("internal error: " + msg) { }
};

class input_error :
        public std::logic_error
{
public:
        input_error(std::string const &msg) : std::logic_error(msg) { }
};

class unhandled_directive :
        public input_error
{
public:
        unhandled_directive(std::string const &directive) :
                input_error("unhandled directive " + directive),
                directive(directive) { }
        std::string const directive;
};

class duplicate_rule :
        public input_error
{
public:
        duplicate_rule(std::string const &rule) :
                input_error("duplicate rule " + rule),
                rule(rule) { }
        std::string const rule;
};

}
}

#endif
