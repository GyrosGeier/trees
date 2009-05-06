%{
#include <tree_bison_tree.hpp>

#include <iostream>

using std::cout;
using std::endl;

using namespace foundry::tree::bison;
%}

%union {
    foundry::tree::bison::rules *rules;
    foundry::tree::bison::rule *rule;
    foundry::tree::bison::alternatives *alternatives;
    foundry::tree::bison::components *components;
    foundry::tree::bison::component *component;
    foundry::tree::bison::symbol *symbol;
    char const *string;
}

%debug
%pure-parser
%defines
%error-verbose
%locations

%expect 0

%parse-param {void *scanner}
%parse-param {start *&ret}
%lex-param {void *scanner}

%name-prefix="tree_bison_"

%{
int tree_bison_lex(YYSTYPE *, YYLTYPE *, void *);
void tree_bison_error(YYLTYPE *, void *, start *&, char const *msg);
%}

%token <string> IDENTIFIER
%token <string> IDENTIFIER_COLON

%token <string> STRING

%token <string> TYPE
%token ACTION

%token SEMICOLON ";"
%token BAR "|"

%token PREC "%prec"
%token DPREC "%dprec"
%token MERGE "%merge"

%token INVALID

%type <rules> rules
%type <rule> rule
%type <alternatives> alternatives
%type <components> components
%type <component> component
%type <symbol> symbol

%%

start: rules { ret = new start($1); }

rules: /* empty */ { $$ = new rules_1; } |
    rules rule { $$ = new rules_2($1, $2); }

rule: IDENTIFIER_COLON alternatives { $$ = new rule($1, $2); }

alternatives: components { $$ = new alternatives_1($1); } |
    alternatives "|" components { $$ = new alternatives_2($1, $3); } |
    alternatives ";" { $$ = new alternatives_3($1); }

components: /* empty */ { $$ = new components_1; } |
    components component { $$ = new components_2($1, $2); }

component: symbol { $$ = new component_1($1); } |
    ACTION { $$ = new component_2(std::string()); }

symbol: IDENTIFIER { $$ = new symbol_1($1); } |
    STRING { $$ = new symbol_2($1); }