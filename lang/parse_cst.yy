%{
#include "parse_cst_cst.hpp"
#include "parse_cst_parse.hpp"
#include "parse_cst_lex.hpp"
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
%token REGEX_1
%type<string> REGEX_1;
%token REGEX_2
%type<string> REGEX_2;
%token REGEX_3
%type<string> REGEX_3;
%token REGEX_4
%type<string> REGEX_4;
%token LITERAL_1 ":"
%token LITERAL_2 ";"
%token LITERAL_3 "|"
%token LITERAL_4 "-"
%token LITERAL_5 "?"
%token LITERAL_6 "+"
%token LITERAL_7 "*"
%token LITERAL_8 "("
%token LITERAL_9 ")"
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
        ::foundry::parse::cst::repetition_qualifier *repetition_qualifier;
        ::foundry::parse::cst::component *component;
        ::foundry::parse::cst::components_elem *components_elem;
        ::foundry::parse::cst::components_list *components_list;
}
%type<start> start;
%type<directives> directives;
%type<rules> rules;
%type<rule> rule;
%type<alternatives> alternatives;
%type<alternatives_tail> alternatives_tail;
%type<alternative> alternative;
%type<components> components;
%type<repetition_qualifier> repetition_qualifier;
%type<component> component;
%type<components_elem> components_elem;
%type<components_list> components_list;
%%
start: /*-start-*/ directives rules { ret = new ::foundry::parse::cst::start($1, $2); };
directives: /*-directives_chain-*/ REGEX_3 directives { $$ = new ::foundry::parse::cst::directives_chain($1, $2); free($1); } | /*-end_of_directives-*/ { $$ = new ::foundry::parse::cst::end_of_directives(); };
rules: /*-rules_chain-*/ rule rules { $$ = new ::foundry::parse::cst::rules_chain($1, $2); } | /*-end_of_rules-*/ { $$ = new ::foundry::parse::cst::end_of_rules(); };
rule: /*-rule-*/ REGEX_1 ":" alternatives ";" { $$ = new ::foundry::parse::cst::rule($1, $3); free($1); };
alternatives: /*-alternatives-*/ alternative alternatives_tail { $$ = new ::foundry::parse::cst::alternatives($1, $2); };
alternatives_tail: /*-more_alternatives-*/ "|" alternatives { $$ = new ::foundry::parse::cst::more_alternatives($2); } | /*-end_of_alternatives-*/ { $$ = new ::foundry::parse::cst::end_of_alternatives(); };
alternative: /*-unnamed_alternative-*/ components { $$ = new ::foundry::parse::cst::unnamed_alternative($1); } | /*-named_alternative-*/ "-" REGEX_1 "-" components { $$ = new ::foundry::parse::cst::named_alternative($2, $4); free($2); };
components: /*-components-*/ components_list { $$ = new ::foundry::parse::cst::components($1); };
repetition_qualifier: /*-no_repetition-*/ { $$ = new ::foundry::parse::cst::no_repetition(); } | /*-zero_or_one-*/ "?" { $$ = new ::foundry::parse::cst::zero_or_one(); } | /*-one_or_more-*/ "+" { $$ = new ::foundry::parse::cst::one_or_more(); } | /*-zero_or_more-*/ "*" { $$ = new ::foundry::parse::cst::zero_or_more(); };
component: /*-symbol-*/ REGEX_1 { $$ = new ::foundry::parse::cst::symbol($1); free($1); } | /*-literal-*/ REGEX_4 { $$ = new ::foundry::parse::cst::literal($1); free($1); } | /*-group-*/ "(" components ")" { $$ = new ::foundry::parse::cst::group($2); } | /*-regex-*/ REGEX_2 { $$ = new ::foundry::parse::cst::regex($1); free($1); };
components_elem: /*-components_elem-*/ component repetition_qualifier { $$ = new ::foundry::parse::cst::components_elem($1, $2); };
components_list: /*-components_chain-*/ components_elem components_list { $$ = new ::foundry::parse::cst::components_chain($1, $2); } | /*-end_of_components-*/ { $$ = new ::foundry::parse::cst::end_of_components(); };
