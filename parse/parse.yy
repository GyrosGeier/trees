%{
#include "parse_cst.hpp"
#include "parse_parse.hpp"
#include "parse_lex.hpp"
using namespace foundry::parse::cst;
%}

%debug
%pure-parser
%defines
%error-verbose
%locations

%expect 0

%parse-param {void *scanner}
%parse-param {::foundry::parse::cst::start *&ret}
%lex-param {void *scanner}

%name-prefix="parse_"

%{
void parse_error(YYLTYPE *loc, void *, ::foundry::parse::cst::start *&, char const *msg)
{
        std::cerr << loc->first_line << ":" << msg << std::endl;
}
%}
%token DIRECTIVE;
%type<string> DIRECTIVE;
%token IDENTIFIER;
%type<string> IDENTIFIER;
%token STRING_LITERAL;
%type<string> STRING_LITERAL;
%token SEMICOLON ";"
%token COLON ":"
%token PIPE "|"
%union {
        char const *string;
        ::foundry::parse::cst::start *start;
        ::foundry::parse::cst::directives *directives;
        ::foundry::parse::cst::rules *rules;
        ::foundry::parse::cst::rule *rule;
        ::foundry::parse::cst::alternatives *alternatives;
        ::foundry::parse::cst::alternatives_tail *alternatives_tail;
        ::foundry::parse::cst::components *components;
        ::foundry::parse::cst::component *component;
}
%type<start> start;
%type<directives> directives;
%type<rules> rules;
%type<rule> rule;
%type<alternatives> alternatives;
%type<alternatives_tail> alternatives_tail;
%type<components> components;
%type<component> component;
%%
start: directives rules { ret = new start($1, $2); };
directives: DIRECTIVE directives { $$ = new directives_1($1, $2); } | { $$ = new directives_2(); };
rules: rule rules { $$ = new rules_1($1, $2); } | { $$ = new rules_2(); };
rule: IDENTIFIER ":" alternatives ";" { $$ = new rule($1, $3); };
alternatives: components alternatives_tail { $$ = new alternatives($1, $2); };
alternatives_tail: "|" alternatives { $$ = new alternatives_tail_1($2); } | { $$ = new alternatives_tail_2(); };
components: component components { $$ = new components_1($1, $2); } | { $$ = new components_2(); };
component: IDENTIFIER { $$ = new component_1($1); } | STRING_LITERAL { $$ = new component_2($1); };
