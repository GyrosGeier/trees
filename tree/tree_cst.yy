%{
#include <tree_cst_tree.hpp>

#include <iostream>

using namespace foundry::tree::cst;
%}

%union {
    foundry::tree::cst::start *start;
    foundry::tree::cst::declarations *declarations;
    foundry::tree::cst::declaration *declaration;
    foundry::tree::cst::namespace_member_declaration *namespace_member_declaration;
    foundry::tree::cst::namespace_declaration *namespace_declaration;
    foundry::tree::cst::group_declaration *group_declaration;
    foundry::tree::cst::group_member_declarations *group_member_declarations;
    foundry::tree::cst::group_member_declaration *group_member_declaration;
    foundry::tree::cst::node_declaration *node_declaration;
    foundry::tree::cst::visitor_declaration *visitor_declaration;
    foundry::tree::cst::member_declarations *member_declarations;
    foundry::tree::cst::member_declaration *member_declaration;
    foundry::tree::cst::member_directive *member_directive;
    foundry::tree::cst::data_member_declaration *data_member_declaration;
    foundry::tree::cst::constructor_declaration *constructor_declaration;
    foundry::tree::cst::parameter_list *parameter_list;
    foundry::tree::cst::parameters *parameters;
    foundry::tree::cst::parameter *parameter;
    foundry::tree::cst::destructor_declaration *destructor_declaration;
    foundry::tree::cst::void_or_nothing *void_or_nothing;
    foundry::tree::cst::declarator *declarator;
    foundry::tree::cst::reference *reference;
    foundry::tree::cst::pointer *pointer;
    foundry::tree::cst::type_qualifiers *type_qualifiers;
    foundry::tree::cst::type_qualifier *type_qualifier;
    foundry::tree::cst::arrays *arrays;
    foundry::tree::cst::bounded_arrays *bounded_arrays;
    foundry::tree::cst::bounded_array *bounded_array;
    foundry::tree::cst::unbounded_array *unbounded_array;
    foundry::tree::cst::type *type;
    foundry::tree::cst::template_name *template_name;
    foundry::tree::cst::template_argument_list *template_argument_list;
    foundry::tree::cst::template_arguments *template_arguments;
    foundry::tree::cst::template_argument *template_argument;
    foundry::tree::cst::scoped_name *scoped_name;
    foundry::tree::cst::scope *scope;
    foundry::tree::cst::literal *literal;
    foundry::tree::cst::boolean_literal *boolean_literal;
    foundry::tree::cst::integer_literal *integer_literal;
    struct {
        char const *data;
        unsigned int length;
    } string;
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

%name-prefix="tree_cst_"

%{
int tree_cst_lex(YYSTYPE *, YYLTYPE *, void *);
void tree_cst_error(YYLTYPE *, void *, start *&, char const *msg);
%}

%token <string> IDENTIFIER
%token <string> INTEGER
%token <string> QUOTED_NAME
%token <string> HEADER_NAME

%token LPAREN "("
%token RPAREN ")"
%token LBRACE "{"
%token RBRACE "}"
%token LBRACKET "["
%token RBRACKET "]"
%token LANGLE "<"
%token RANGLE ">"
%token COMMA ","
%token SEMICOLON ";"
%token DOUBLECOLON "::"
%token ASTERISK "*"
%token AMPERSAND "&"
%token TILDE "~"
%token ELLIPSIS "..."

%token VOID "void"

%token TRUE "true"
%token FALSE "false"

%token NAMESPACE "namespace"
%token GROUP "group"
%token NODE "node"
%token PARENT "parent"

%token VISITOR "visitor"
%token CONST "const"
%token VOLATILE "volatile"

%token PERCENT "%"

%token MULTIPARENT "multiparent"
%token SCOPED_PTR "scoped_ptr"
%token SHARED_PTR "shared_ptr"
%token INTRUSIVE_PTR "intrusive_ptr"
%token SMARTPOINTER "smartpointer"
%token INCLUDE "include"

%type <start> start
%type <declarations> declarations
%type <declaration> declaration
%type <namespace_member_declaration> namespace_member_declaration
%type <namespace_declaration> namespace_declaration
%type <group_declaration> group_declaration
%type <group_member_declarations> group_member_declarations
%type <group_member_declaration> group_member_declaration
%type <node_declaration> node_declaration
%type <visitor_declaration> visitor_declaration
%type <member_declarations> member_declarations
%type <member_declaration> member_declaration
%type <member_directive> member_directive
%type <data_member_declaration> data_member_declaration
%type <constructor_declaration> constructor_declaration
%type <parameter_list> parameter_list
%type <parameters> parameters
%type <parameter> parameter
%type <destructor_declaration> destructor_declaration
%type <void_or_nothing> void_or_nothing
%type <declarator> declarator
%type <reference> reference
%type <pointer> pointer
%type <type_qualifiers> type_qualifiers
%type <type_qualifier> type_qualifier
%type <arrays> arrays
%type <bounded_arrays> bounded_arrays
%type <bounded_array> bounded_array
%type <unbounded_array> unbounded_array
%type <type> type
%type <template_name> template_name
%type <template_argument_list> template_argument_list
%type <template_arguments> template_arguments
%type <template_argument> template_argument
%type <scoped_name> scoped_name
%type <scope> scope
%type <literal> literal
%type <boolean_literal> boolean_literal
%type <integer_literal> integer_literal

%%

start: declarations { ret = new start($1); }

declarations: /* empty */ { $$ = new declarations_1; } |
    declarations declaration { $$ = new declarations_2($1, $2); }

declaration: namespace_declaration { $$ = new declaration_1($1); } |
    namespace_member_declaration ";" { $$ = new declaration_2($1); }

namespace_member_declaration: group_declaration { $$ = new namespace_member_declaration_1($1); } |
    node_declaration { $$ = new namespace_member_declaration_2($1); } |
    visitor_declaration { $$ = new namespace_member_declaration_3($1); }

namespace_declaration: "namespace" IDENTIFIER "{" declarations "}" { $$ = new namespace_declaration(std::string($2.data, $2.length), $4); }

group_declaration: "group" IDENTIFIER "{" group_member_declarations "}" { $$ = new group_declaration(std::string($2.data, $2.length), $4); }

group_member_declarations: /* empty */ { $$ = new group_member_declarations_1; } |
    group_member_declarations group_member_declaration ";" { $$ = new group_member_declarations_2($1, $2); }

group_member_declaration: group_declaration { $$ = new group_member_declaration_1($1); } |
    node_declaration { $$ = new group_member_declaration_2($1); } |
    visitor_declaration { $$ = new group_member_declaration_3($1); }

node_declaration: "node" IDENTIFIER "{" member_declarations "}" { $$ = new node_declaration_1(std::string($2.data, $2.length), $4); } |
    "node" "{" member_declarations "}" { $$ = new node_declaration_2($3); }

visitor_declaration: "visitor" IDENTIFIER "{" member_declarations "}" { $$ = new visitor_declaration_1(std::string($2.data, $2.length), $4); } |
    "const" "visitor" IDENTIFIER "{" member_declarations "}" { $$ = new visitor_declaration_2(std::string($3.data, $3.length), $5); }

member_declarations: /* empty */ { $$ = new member_declarations_1; } |
    member_declarations member_declaration ";" { $$ = new member_declarations_2($1, $2); } |
    member_declarations "%" member_directive "%" { $$ = new member_declarations_3($1, $3); }

member_declaration: data_member_declaration { $$ = new member_declaration_1($1); } |
    constructor_declaration { $$ = new member_declaration_2($1); } |
    destructor_declaration { $$ = new member_declaration_3($1); }

member_directive: "multiparent" { $$ = new member_directive_1; } |
    "scoped_ptr" { $$ = new member_directive_2; } |
    "shared_ptr" { $$ = new member_directive_3; } |
    "intrusive_ptr" { $$ = new member_directive_4; } |
    "smartpointer" type reference { $$ = new member_directive_5($2, $3); } |
    "include" QUOTED_NAME { $$ = new member_directive_6(std::string($2.data, $2.length)); } |
    "include" HEADER_NAME { $$ = new member_directive_7(std::string($2.data, $2.length)); }

data_member_declaration: type type_qualifiers declarator { $$ = new data_member_declaration($1, $2, $3); }

constructor_declaration: scoped_name "(" parameter_list ")" { $$ = new constructor_declaration($1, $3); }

parameter_list: /* empty */ { $$ = new parameter_list_1; } |
    "void" { $$ = new parameter_list_2; } |
    parameters parameter { $$ = new parameter_list_3($1, $2); }

parameters: /* empty */ { $$ = new parameters_1; } |
    parameters parameter "," { $$ = new parameters_2($1, $2); }

parameter: type reference { $$ = new parameter_1($1, $2); } |
    type declarator { $$ = new parameter_2($1, $2); }

destructor_declaration: "~" IDENTIFIER "(" void_or_nothing ")" { $$ = new destructor_declaration(std::string($2.data, $2.length), $4); }

void_or_nothing: /* empty */ { $$ = new void_or_nothing_1; } |
    "void" { $$ = new void_or_nothing_2; }

declarator: reference IDENTIFIER arrays { $$ = new declarator_1($1, std::string($2.data, $2.length), $3); } |
    reference "parent" arrays { $$ = new declarator_2($1, $3); } |
    reference "group" arrays { $$ = new declarator_3($1, $3); }

reference: pointer { $$ = new reference_1($1); } |
    pointer "&" { $$ = new reference_2($1); }

pointer: /* empty */ { $$ = new pointer_1; } |
    pointer "*" type_qualifiers { $$ = new pointer_2($1, $3); }

type_qualifiers: /* empty */ { $$ = new type_qualifiers_1; } |
    type_qualifiers type_qualifier { $$ = new type_qualifiers_2($1, $2); }

type_qualifier: "const" { $$ = new type_qualifier_1; } |
    "volatile" { $$ = new type_qualifier_2; }

arrays: bounded_arrays { $$ = new arrays_1($1); } |
    bounded_arrays unbounded_array { $$ = new arrays_2($1, $2); }

bounded_arrays: /* empty */ { $$ = new bounded_arrays_1; } |
    bounded_arrays bounded_array { $$ = new bounded_arrays_2($1, $2); }

bounded_array: "[" integer_literal "]" { $$ = new bounded_array($2); }

unbounded_array: "[" "]" { $$ = new unbounded_array; }

type: template_name { $$ = new type_1($1); } |
    scoped_name { $$ = new type_2($1); } |
    "node" { $$ = new type_3; } |
    "parent" { $$ = new type_4; }

template_name: scoped_name "<" template_argument_list ">" { $$ = new template_name($1, $3); }

template_argument_list: /* empty */ { $$ = new template_argument_list_1; } |
    template_arguments { $$ = new template_argument_list_2($1); }

template_arguments: template_argument { $$ = new template_arguments_1($1); } |
    template_arguments "," template_argument { $$ = new template_arguments_2($1, $3); }

template_argument: type { $$ = new template_argument_1($1); } |
    "void" { $$ = new template_argument_2; } |
    "..." { $$ = new template_argument_3; } |
    literal { $$ = new template_argument_4($1); }

scoped_name: scope IDENTIFIER { $$ = new scoped_name($1, std::string($2.data, $2.length)); }

scope: /* empty */ { $$ = new scope_1; } |
    scope IDENTIFIER "::" { $$ = new scope_2($1, std::string($2.data, $2.length)); }

literal: boolean_literal { $$ = new literal_1($1); } |
    integer_literal { $$ = new literal_2($1); }

boolean_literal: "true" { $$ = new boolean_literal_1; } |
    "false" { $$ = new boolean_literal_2; }

integer_literal: INTEGER { $$ = new integer_literal(std::string($1.data, $1.length)); }
