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
        char *string;
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
start: /*-start-*/ directives rules { ret = new ::foundry::parse::cst::start($1, $2); };
directives: /*-directives_1-*/ DIRECTIVE directives { $$ = new ::foundry::parse::cst::directives_1($1, $2); free($1); } | /*-directives_2-*/ { $$ = new ::foundry::parse::cst::directives_2(); };
rules: /*-rules_1-*/ rule rules { $$ = new ::foundry::parse::cst::rules_1($1, $2); } | /*-rules_2-*/ { $$ = new ::foundry::parse::cst::rules_2(); };
rule: /*-rule-*/ IDENTIFIER ":" alternatives ";" { $$ = new ::foundry::parse::cst::rule($1, $3); free($1); };
alternatives: /*-alternatives-*/ alternative alternatives_tail { $$ = new ::foundry::parse::cst::alternatives($1, $2); };
alternatives_tail: /*-alternatives_tail_1-*/ "|" alternatives { $$ = new ::foundry::parse::cst::alternatives_tail_1($2); } | /*-alternatives_tail_2-*/ { $$ = new ::foundry::parse::cst::alternatives_tail_2(); };
alternative: /*-alternative_1-*/ components { $$ = new ::foundry::parse::cst::alternative_1($1); } | /*-alternative_2-*/ "-" IDENTIFIER "-" components { $$ = new ::foundry::parse::cst::alternative_2($2, $4); free($2); };
components: /*-components_1-*/ component components { $$ = new ::foundry::parse::cst::components_1($1, $2); } | /*-components_2-*/ { $$ = new ::foundry::parse::cst::components_2(); };
component: /*-component_1-*/ IDENTIFIER { $$ = new ::foundry::parse::cst::component_1($1); free($1); } | /*-component_2-*/ STRING_LITERAL { $$ = new ::foundry::parse::cst::component_2($1); free($1); };
