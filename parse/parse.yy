%{
#include "parse_cst.hpp"
#include "parse_parse.hpp"
#include "parse_lex.hpp"
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
%token LITERAL_1 ":"
%token LITERAL_2 ";"
%token LITERAL_3 "|"
%token LITERAL_4 "-"
%union {
        char const *string;
        ::foundry::parse::cst::start *start;
        ::foundry::parse::cst::directives *directives;
        ::foundry::parse::cst::rules *rules;
        ::foundry::parse::cst::rule *rule;
        ::foundry::parse::cst::alternatives *alternatives;
        ::foundry::parse::cst::alternatives_tail *alternatives_tail;
        ::foundry::parse::cst::alternative *alternative;
        ::foundry::parse::cst::components *components;
        ::foundry::parse::cst::component *component;
}
%type<start> start;
%type<directives> directives;
%type<rules> rules;
%type<rule> rule;
%type<alternatives> alternatives;
%type<alternatives_tail> alternatives_tail;
%type<alternative> alternative;
%type<components> components;
%type<component> component;
%%
start: directives rules { ret = new ::foundry::parse::cst::start($1, $2); };
directives: DIRECTIVE directives { $$ = new ::foundry::parse::cst::directives_1($1, $2); } | { $$ = new ::foundry::parse::cst::directives_2(); };
rules: rule rules { $$ = new ::foundry::parse::cst::rules_1($1, $2); } | { $$ = new ::foundry::parse::cst::rules_2(); };
rule: IDENTIFIER ":" alternatives ";" { $$ = new ::foundry::parse::cst::rule($1, $3); };
alternatives: alternative alternatives_tail { $$ = new ::foundry::parse::cst::alternatives($1, $2); };
alternatives_tail: "|" alternatives { $$ = new ::foundry::parse::cst::alternatives_tail_1($2); } | { $$ = new ::foundry::parse::cst::alternatives_tail_2(); };
alternative: components { $$ = new ::foundry::parse::cst::alternative_1($1); } | "-" IDENTIFIER "-" components { $$ = new ::foundry::parse::cst::alternative_2($2, $4); };
components: component components { $$ = new ::foundry::parse::cst::components_1($1, $2); } | { $$ = new ::foundry::parse::cst::components_2(); };
component: IDENTIFIER { $$ = new ::foundry::parse::cst::component_1($1); } | STRING_LITERAL { $$ = new ::foundry::parse::cst::component_2($1); };
