%{
#include <tree_bison_cst.hpp>

#include <iostream>
#include <cstdio>

using std::cout;
using std::endl;

using namespace trees::tree::bison;
%}

%union {
    trees::tree::bison::rules *rules;
    trees::tree::bison::rule *rule;
    trees::tree::bison::alternative *alternative;
    trees::tree::bison::alternatives *alternatives;
    trees::tree::bison::components *components;
    trees::tree::bison::component *component;
    char *string;
}

%debug
%pure-parser
%defines
%error-verbose
%locations

%expect 0

%parse-param {void *scanner}
%parse-param {trees::tree::bison::start *&ret}
%lex-param {void *scanner}

%name-prefix "tree_bison_"

%{
int tree_bison_lex(YYSTYPE *, YYLTYPE *, void *);
void tree_bison_error(YYLTYPE *, void *, trees::tree::bison::start *&, char const *msg);
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

start:          rules { ret = new start(std::unique_ptr<rules>($1)); }

rules:          /*-empty_rules-*/ { $$ = new empty_rules; } |
                /*-chained_rules-*/ rules rule { $$ = new chained_rules(std::unique_ptr<rules>($1), std::unique_ptr<rule>($2)); }

rule:           IDENTIFIER_COLON alternatives { $$ = new rule($1, std::unique_ptr<alternatives>($2)); free($1); }

alternatives:   /*-single_alternative-*/ alternative { $$ = new single_alternative(std::unique_ptr<alternative>($1)); } |
                /*-chained_alternatives-*/ alternatives "|" alternative { $$ = new chained_alternatives(std::unique_ptr<alternatives>($1), std::unique_ptr<alternative>($3)); } |
                /*-terminated_alternatives-*/ alternatives ";" { $$ = new terminated_alternatives(std::unique_ptr<alternatives>($1)); }

alternative:    /*-unnamed_alternative-*/ components { $$ = new unnamed_alternative(std::unique_ptr<components>($1)); } |
                /*-named_alternative-*/ NAME_HINT components { $$ = new named_alternative($1, std::unique_ptr<components>($2)); free($1); }

components:     /*-empty_components-*/ { $$ = new empty_components; } |
                /*-chained_components-*/ components component { $$ = new chained_components(std::unique_ptr<components>($1), std::unique_ptr<component>($2)); }

component:      /*-symbol-*/ IDENTIFIER { $$ = new symbol($1); free($1); } |
                /*-literal-*/ STRING { $$ = new literal($1); free($1); }
