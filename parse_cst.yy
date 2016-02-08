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
%parse-param {::trees::parse::cst::start *&ret}
%lex-param {void *scanner}

%name-prefix "parse_cst_"

%{
void parse_cst_error(YYLTYPE *loc, void *, ::trees::parse::cst::start *&, char const *msg)
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
        ::trees::parse::cst::start *start;
        ::trees::parse::cst::directives *directives;
        ::trees::parse::cst::rules *rules;
        ::trees::parse::cst::rule *rule;
        ::trees::parse::cst::alternatives *alternatives;
        ::trees::parse::cst::alternatives_tail *alternatives_tail;
        ::trees::parse::cst::alternative *alternative;
        ::trees::parse::cst::components *components;
        ::trees::parse::cst::repetition_qualifier *repetition_qualifier;
        ::trees::parse::cst::component *component;
        ::trees::parse::cst::components_1_elem *components_1_elem;
        ::trees::parse::cst::components_1_list *components_1_list;
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
%type<components_1_elem> components_1_elem;
%type<components_1_list> components_1_list;
%%
start: /*-start-*/ directives rules { ret = new ::trees::parse::cst::start($1, $2); };
directives: /*-directives_chain-*/ REGEX_3 directives { $$ = new ::trees::parse::cst::directives_chain($1, $2); free($1); } | /*-end_of_directives-*/ { $$ = new ::trees::parse::cst::end_of_directives(); };
rules: /*-rules_chain-*/ rule rules { $$ = new ::trees::parse::cst::rules_chain($1, $2); } | /*-end_of_rules-*/ { $$ = new ::trees::parse::cst::end_of_rules(); };
rule: /*-rule-*/ REGEX_1 ":" alternatives ";" { $$ = new ::trees::parse::cst::rule($1, $3); free($1); };
alternatives: /*-alternatives-*/ alternative alternatives_tail { $$ = new ::trees::parse::cst::alternatives($1, $2); };
alternatives_tail: /*-more_alternatives-*/ "|" alternatives { $$ = new ::trees::parse::cst::more_alternatives($2); } | /*-end_of_alternatives-*/ { $$ = new ::trees::parse::cst::end_of_alternatives(); };
alternative: /*-unnamed_alternative-*/ components { $$ = new ::trees::parse::cst::unnamed_alternative($1); } | /*-named_alternative-*/ "-" REGEX_1 "-" components { $$ = new ::trees::parse::cst::named_alternative($2, $4); free($2); };
components: /*-components-*/ components_1_list { $$ = new ::trees::parse::cst::components($1); };
repetition_qualifier: /*-no_repetition-*/ { $$ = new ::trees::parse::cst::no_repetition(); } | /*-zero_or_one-*/ "?" { $$ = new ::trees::parse::cst::zero_or_one(); } | /*-one_or_more-*/ "+" { $$ = new ::trees::parse::cst::one_or_more(); } | /*-zero_or_more-*/ "*" { $$ = new ::trees::parse::cst::zero_or_more(); };
component: /*-symbol-*/ REGEX_1 { $$ = new ::trees::parse::cst::symbol($1); free($1); } | /*-literal-*/ REGEX_4 { $$ = new ::trees::parse::cst::literal($1); free($1); } | /*-group-*/ "(" components ")" { $$ = new ::trees::parse::cst::group($2); } | /*-regex-*/ REGEX_2 { $$ = new ::trees::parse::cst::regex($1); free($1); };
components_1_elem: /*-components_1_elem-*/ component repetition_qualifier { $$ = new ::trees::parse::cst::components_1_elem($1, $2); };
components_1_list: /*-components_1_chain-*/ components_1_elem components_1_list { $$ = new ::trees::parse::cst::components_1_chain($1, $2); } | /*-end_of_components_1-*/ { $$ = new ::trees::parse::cst::end_of_components_1(); };
