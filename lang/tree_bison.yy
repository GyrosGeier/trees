%{
#include <tree_bison_tree.hpp>

#include <iostream>
#include <cstdio>

using std::cout;
using std::endl;

using namespace foundry::tree::bison;
%}

%union {
    foundry::tree::bison::rules *rules;
    foundry::tree::bison::rule *rule;
    foundry::tree::bison::alternative *alternative;
    foundry::tree::bison::alternatives *alternatives;
    foundry::tree::bison::components *components;
    foundry::tree::bison::component *component;
    char *string;
}

%debug
%pure-parser
%defines
%error-verbose
%locations

%expect 0

%parse-param {void *scanner}
%parse-param {foundry::tree::bison::start *&ret}
%lex-param {void *scanner}

%name-prefix="tree_bison_"

%{
int tree_bison_lex(YYSTYPE *, YYLTYPE *, void *);
void tree_bison_error(YYLTYPE *, void *, foundry::tree::bison::start *&, char const *msg);
%}

%token <string> IDENTIFIER
%token <string> IDENTIFIER_COLON
%token <string> NAME_HINT
%token <string> STRING

%token SEMICOLON ";"
%token BAR "|"

%token INVALID

%type <rules> rules
%type <rule> rule
%type <alternative> alternative
%type <alternatives> alternatives
%type <components> components
%type <component> component

%%

start:          rules { ret = new start($1); }

rules:          /*-empty_rules-*/ { $$ = new empty_rules; } |
                /*-chained_rules-*/ rules rule { $$ = new chained_rules($1, $2); }

rule:           IDENTIFIER_COLON alternatives { $$ = new rule($1, $2); free($1); }

alternatives:   /*-single_alternative-*/ alternative { $$ = new single_alternative($1); } |
                /*-chained_alternatives-*/ alternatives "|" alternative { $$ = new chained_alternatives($1, $3); } |
                /*-terminated_alternatives-*/ alternatives ";" { $$ = new terminated_alternatives($1); }

alternative:    /*-unnamed_alternative-*/ components { $$ = new unnamed_alternative($1); } |
                /*-named_alternative-*/ NAME_HINT components { $$ = new named_alternative($1, $2); }

components:     /*-empty_components-*/ { $$ = new empty_components; } |
                /*-chained_components-*/ components component { $$ = new chained_components($1, $2); }

component:      /*-symbol-*/ IDENTIFIER { $$ = new symbol($1); free($1); } |
                /*-literal-*/ STRING { $$ = new literal($1); free($1); }
