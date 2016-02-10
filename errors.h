#ifndef trees_parse_errors_h_
#define trees_parse_errors_h_ 1

#include <stdexcept>

namespace trees {
namespace parse {

class internal_error :
        public std::runtime_error
{
public:
        internal_error(std::string const &msg) :
                std::runtime_error("internal error: " + msg) { }
        virtual ~internal_error() throw() { }
};

class input_error :
        public std::logic_error
{
public:
        input_error(std::string const &msg) : std::logic_error(msg) { }
        virtual ~input_error() throw() { }
};

class unknown_production :
        public input_error
{
public:
        unknown_production() : input_error("unknown production") { }
        virtual ~unknown_production() throw() { }
};

class unhandled_directive :
        public input_error
{
public:
        unhandled_directive(std::string const &directive) :
                input_error("unhandled directive " + directive),
                directive(directive) { }
        virtual ~unhandled_directive() throw() { }
        std::string const directive;
};

class duplicate_rule :
        public input_error
{
public:
        duplicate_rule(std::string const &rule) :
                input_error("duplicate rule " + rule),
                rule(rule) { }
        virtual ~duplicate_rule() throw() { }
        std::string const rule;
};

}
}

#endif
