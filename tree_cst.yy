%{
#include "tree_cst_cst.hpp"
#include "tree_cst_parse.hpp"
#include "tree_cst_lex.hpp"
%}

%debug
%pure-parser
%defines
%error-verbose
%locations

%expect 0

%parse-param {void *scanner}
%parse-param {::trees::tree::cst::start *&ret}
%lex-param {void *scanner}

%name-prefix "tree_cst_"

%{
void tree_cst_error(YYLTYPE *loc, void *, ::trees::tree::cst::start *&, char const *msg)
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
%token LITERAL_1 ";"
%token LITERAL_2 "namespace"
%token LITERAL_3 "{"
%token LITERAL_4 "}"
%token LITERAL_5 "group"
%token LITERAL_6 "node"
%token LITERAL_7 "visitor"
%token LITERAL_8 "const"
%token LITERAL_9 "%multiparent"
%token LITERAL_10 "%scoped_ptr"
%token LITERAL_11 "%shared_ptr"
%token LITERAL_12 "%intrusive_ptr"
%token LITERAL_13 "%smartpointer"
%token LITERAL_14 "("
%token LITERAL_15 ")"
%token LITERAL_16 "void"
%token LITERAL_17 ","
%token LITERAL_18 "~"
%token LITERAL_19 "parent"
%token LITERAL_20 "&"
%token LITERAL_21 "*"
%token LITERAL_22 "volatile"
%token LITERAL_23 "["
%token LITERAL_24 "]"
%token LITERAL_25 "<"
%token LITERAL_26 ">"
%token LITERAL_27 "..."
%token LITERAL_28 "::"
%token LITERAL_29 "true"
%token LITERAL_30 "false"
%union {
        char *string;
        ::trees::tree::cst::start *start;
        ::trees::tree::cst::declarations *declarations;
        ::trees::tree::cst::declaration *declaration;
        ::trees::tree::cst::namespace_member_declaration *namespace_member_declaration;
        ::trees::tree::cst::namespace_declaration *namespace_declaration;
        ::trees::tree::cst::group_declaration *group_declaration;
        ::trees::tree::cst::group_member_declarations *group_member_declarations;
        ::trees::tree::cst::group_member_declaration *group_member_declaration;
        ::trees::tree::cst::node_declaration *node_declaration;
        ::trees::tree::cst::visitor_declaration *visitor_declaration;
        ::trees::tree::cst::member_declarations *member_declarations;
        ::trees::tree::cst::member_declaration *member_declaration;
        ::trees::tree::cst::member_directive *member_directive;
        ::trees::tree::cst::data_member_declaration *data_member_declaration;
        ::trees::tree::cst::constructor_declaration *constructor_declaration;
        ::trees::tree::cst::parameter_list *parameter_list;
        ::trees::tree::cst::parameters *parameters;
        ::trees::tree::cst::parameter *parameter;
        ::trees::tree::cst::destructor_declaration *destructor_declaration;
        ::trees::tree::cst::void_or_nothing *void_or_nothing;
        ::trees::tree::cst::declarator *declarator;
        ::trees::tree::cst::reference *reference;
        ::trees::tree::cst::pointer *pointer;
        ::trees::tree::cst::type_qualifiers *type_qualifiers;
        ::trees::tree::cst::type_qualifier *type_qualifier;
        ::trees::tree::cst::arrays *arrays;
        ::trees::tree::cst::bounded_arrays *bounded_arrays;
        ::trees::tree::cst::bounded_array *bounded_array;
        ::trees::tree::cst::unbounded_array *unbounded_array;
        ::trees::tree::cst::type *type;
        ::trees::tree::cst::template_name *template_name;
        ::trees::tree::cst::template_argument_list *template_argument_list;
        ::trees::tree::cst::template_arguments *template_arguments;
        ::trees::tree::cst::template_argument *template_argument;
        ::trees::tree::cst::scoped_name *scoped_name;
        ::trees::tree::cst::scope *scope;
        ::trees::tree::cst::literal *literal;
        ::trees::tree::cst::boolean_literal *boolean_literal;
}
%type<start> start;
%type<declarations> declarations;
%type<declaration> declaration;
%type<namespace_member_declaration> namespace_member_declaration;
%type<namespace_declaration> namespace_declaration;
%type<group_declaration> group_declaration;
%type<group_member_declarations> group_member_declarations;
%type<group_member_declaration> group_member_declaration;
%type<node_declaration> node_declaration;
%type<visitor_declaration> visitor_declaration;
%type<member_declarations> member_declarations;
%type<member_declaration> member_declaration;
%type<member_directive> member_directive;
%type<data_member_declaration> data_member_declaration;
%type<constructor_declaration> constructor_declaration;
%type<parameter_list> parameter_list;
%type<parameters> parameters;
%type<parameter> parameter;
%type<destructor_declaration> destructor_declaration;
%type<void_or_nothing> void_or_nothing;
%type<declarator> declarator;
%type<reference> reference;
%type<pointer> pointer;
%type<type_qualifiers> type_qualifiers;
%type<type_qualifier> type_qualifier;
%type<arrays> arrays;
%type<bounded_arrays> bounded_arrays;
%type<bounded_array> bounded_array;
%type<unbounded_array> unbounded_array;
%type<type> type;
%type<template_name> template_name;
%type<template_argument_list> template_argument_list;
%type<template_arguments> template_arguments;
%type<template_argument> template_argument;
%type<scoped_name> scoped_name;
%type<scope> scope;
%type<literal> literal;
%type<boolean_literal> boolean_literal;
%%
start: /*-start-*/ declarations { ret = new ::trees::tree::cst::start(std::unique_ptr< ::trees::tree::cst::declarations>($1)); };
declarations: /*-declarations_1-*/ { $$ = new ::trees::tree::cst::declarations_1(); } | /*-declarations_2-*/ declarations declaration { $$ = new ::trees::tree::cst::declarations_2(std::unique_ptr< ::trees::tree::cst::declarations>($1), std::unique_ptr< ::trees::tree::cst::declaration>($2)); };
declaration: /*-declaration_1-*/ namespace_declaration { $$ = new ::trees::tree::cst::declaration_1(std::unique_ptr< ::trees::tree::cst::namespace_declaration>($1)); } | /*-declaration_2-*/ namespace_member_declaration ";" { $$ = new ::trees::tree::cst::declaration_2(std::unique_ptr< ::trees::tree::cst::namespace_member_declaration>($1)); };
namespace_member_declaration: /*-namespace_member_declaration_1-*/ group_declaration { $$ = new ::trees::tree::cst::namespace_member_declaration_1(std::unique_ptr< ::trees::tree::cst::group_declaration>($1)); } | /*-namespace_member_declaration_2-*/ node_declaration { $$ = new ::trees::tree::cst::namespace_member_declaration_2(std::unique_ptr< ::trees::tree::cst::node_declaration>($1)); } | /*-namespace_member_declaration_3-*/ visitor_declaration { $$ = new ::trees::tree::cst::namespace_member_declaration_3(std::unique_ptr< ::trees::tree::cst::visitor_declaration>($1)); };
namespace_declaration: /*-namespace_declaration-*/ "namespace" REGEX_1 "{" declarations "}" { $$ = new ::trees::tree::cst::namespace_declaration($2, std::unique_ptr< ::trees::tree::cst::declarations>($4)); free($2); };
group_declaration: /*-group_declaration-*/ "group" REGEX_1 "{" group_member_declarations "}" { $$ = new ::trees::tree::cst::group_declaration($2, std::unique_ptr< ::trees::tree::cst::group_member_declarations>($4)); free($2); };
group_member_declarations: /*-group_member_declarations_1-*/ { $$ = new ::trees::tree::cst::group_member_declarations_1(); } | /*-group_member_declarations_2-*/ group_member_declarations group_member_declaration ";" { $$ = new ::trees::tree::cst::group_member_declarations_2(std::unique_ptr< ::trees::tree::cst::group_member_declarations>($1), std::unique_ptr< ::trees::tree::cst::group_member_declaration>($2)); };
group_member_declaration: /*-group_member_declaration_1-*/ group_declaration { $$ = new ::trees::tree::cst::group_member_declaration_1(std::unique_ptr< ::trees::tree::cst::group_declaration>($1)); } | /*-group_member_declaration_2-*/ node_declaration { $$ = new ::trees::tree::cst::group_member_declaration_2(std::unique_ptr< ::trees::tree::cst::node_declaration>($1)); } | /*-group_member_declaration_3-*/ visitor_declaration { $$ = new ::trees::tree::cst::group_member_declaration_3(std::unique_ptr< ::trees::tree::cst::visitor_declaration>($1)); };
node_declaration: /*-node_declaration_1-*/ "node" REGEX_1 "{" member_declarations "}" { $$ = new ::trees::tree::cst::node_declaration_1($2, std::unique_ptr< ::trees::tree::cst::member_declarations>($4)); free($2); } | /*-node_declaration_2-*/ "node" "group" "{" member_declarations "}" { $$ = new ::trees::tree::cst::node_declaration_2(std::unique_ptr< ::trees::tree::cst::member_declarations>($4)); } | /*-node_declaration_3-*/ "node" "{" member_declarations "}" { $$ = new ::trees::tree::cst::node_declaration_3(std::unique_ptr< ::trees::tree::cst::member_declarations>($3)); };
visitor_declaration: /*-visitor_declaration_1-*/ "visitor" REGEX_1 "{" member_declarations "}" { $$ = new ::trees::tree::cst::visitor_declaration_1($2, std::unique_ptr< ::trees::tree::cst::member_declarations>($4)); free($2); } | /*-visitor_declaration_2-*/ "const" "visitor" REGEX_1 "{" member_declarations "}" { $$ = new ::trees::tree::cst::visitor_declaration_2($3, std::unique_ptr< ::trees::tree::cst::member_declarations>($5)); free($3); } | /*-visitor_declaration_3-*/ "visitor" REGEX_1 { $$ = new ::trees::tree::cst::visitor_declaration_3($2); free($2); } | /*-visitor_declaration_4-*/ "const" "visitor" REGEX_1 { $$ = new ::trees::tree::cst::visitor_declaration_4($3); free($3); } | /*-visitor_declaration_5-*/ "visitor" { $$ = new ::trees::tree::cst::visitor_declaration_5(); } | /*-visitor_declaration_6-*/ "const" "visitor" { $$ = new ::trees::tree::cst::visitor_declaration_6(); };
member_declarations: /*-member_declarations_1-*/ { $$ = new ::trees::tree::cst::member_declarations_1(); } | /*-member_declarations_2-*/ member_declarations member_declaration ";" { $$ = new ::trees::tree::cst::member_declarations_2(std::unique_ptr< ::trees::tree::cst::member_declarations>($1), std::unique_ptr< ::trees::tree::cst::member_declaration>($2)); } | /*-member_declarations_3-*/ member_declarations member_directive { $$ = new ::trees::tree::cst::member_declarations_3(std::unique_ptr< ::trees::tree::cst::member_declarations>($1), std::unique_ptr< ::trees::tree::cst::member_directive>($2)); };
member_declaration: /*-member_declaration_1-*/ data_member_declaration { $$ = new ::trees::tree::cst::member_declaration_1(std::unique_ptr< ::trees::tree::cst::data_member_declaration>($1)); } | /*-member_declaration_2-*/ constructor_declaration { $$ = new ::trees::tree::cst::member_declaration_2(std::unique_ptr< ::trees::tree::cst::constructor_declaration>($1)); } | /*-member_declaration_3-*/ destructor_declaration { $$ = new ::trees::tree::cst::member_declaration_3(std::unique_ptr< ::trees::tree::cst::destructor_declaration>($1)); };
member_directive: /*-member_directive_1-*/ "%multiparent" { $$ = new ::trees::tree::cst::member_directive_1(); } | /*-member_directive_2-*/ "%scoped_ptr" { $$ = new ::trees::tree::cst::member_directive_2(); } | /*-member_directive_3-*/ "%shared_ptr" { $$ = new ::trees::tree::cst::member_directive_3(); } | /*-member_directive_4-*/ "%intrusive_ptr" { $$ = new ::trees::tree::cst::member_directive_4(); } | /*-member_directive_5-*/ "%smartpointer" type reference { $$ = new ::trees::tree::cst::member_directive_5(std::unique_ptr< ::trees::tree::cst::type>($2), std::unique_ptr< ::trees::tree::cst::reference>($3)); } | /*-member_directive_6-*/ REGEX_3 { $$ = new ::trees::tree::cst::member_directive_6($1); free($1); };
data_member_declaration: /*-data_member_declaration-*/ type type_qualifiers declarator { $$ = new ::trees::tree::cst::data_member_declaration(std::unique_ptr< ::trees::tree::cst::type>($1), std::unique_ptr< ::trees::tree::cst::type_qualifiers>($2), std::unique_ptr< ::trees::tree::cst::declarator>($3)); };
constructor_declaration: /*-constructor_declaration-*/ scoped_name "(" parameter_list ")" { $$ = new ::trees::tree::cst::constructor_declaration(std::unique_ptr< ::trees::tree::cst::scoped_name>($1), std::unique_ptr< ::trees::tree::cst::parameter_list>($3)); };
parameter_list: /*-parameter_list_1-*/ { $$ = new ::trees::tree::cst::parameter_list_1(); } | /*-parameter_list_2-*/ "void" { $$ = new ::trees::tree::cst::parameter_list_2(); } | /*-parameter_list_3-*/ parameters parameter { $$ = new ::trees::tree::cst::parameter_list_3(std::unique_ptr< ::trees::tree::cst::parameters>($1), std::unique_ptr< ::trees::tree::cst::parameter>($2)); };
parameters: /*-parameters_1-*/ { $$ = new ::trees::tree::cst::parameters_1(); } | /*-parameters_2-*/ parameters parameter "," { $$ = new ::trees::tree::cst::parameters_2(std::unique_ptr< ::trees::tree::cst::parameters>($1), std::unique_ptr< ::trees::tree::cst::parameter>($2)); };
parameter: /*-parameter_1-*/ type reference { $$ = new ::trees::tree::cst::parameter_1(std::unique_ptr< ::trees::tree::cst::type>($1), std::unique_ptr< ::trees::tree::cst::reference>($2)); } | /*-parameter_2-*/ type declarator { $$ = new ::trees::tree::cst::parameter_2(std::unique_ptr< ::trees::tree::cst::type>($1), std::unique_ptr< ::trees::tree::cst::declarator>($2)); };
destructor_declaration: /*-destructor_declaration-*/ "~" REGEX_1 "(" void_or_nothing ")" { $$ = new ::trees::tree::cst::destructor_declaration($2, std::unique_ptr< ::trees::tree::cst::void_or_nothing>($4)); free($2); };
void_or_nothing: /*-void_or_nothing_1-*/ { $$ = new ::trees::tree::cst::void_or_nothing_1(); } | /*-void_or_nothing_2-*/ "void" { $$ = new ::trees::tree::cst::void_or_nothing_2(); };
declarator: /*-declarator_1-*/ reference REGEX_1 arrays { $$ = new ::trees::tree::cst::declarator_1(std::unique_ptr< ::trees::tree::cst::reference>($1), $2, std::unique_ptr< ::trees::tree::cst::arrays>($3)); free($2); } | /*-declarator_2-*/ reference "parent" arrays { $$ = new ::trees::tree::cst::declarator_2(std::unique_ptr< ::trees::tree::cst::reference>($1), std::unique_ptr< ::trees::tree::cst::arrays>($3)); } | /*-declarator_3-*/ reference "group" arrays { $$ = new ::trees::tree::cst::declarator_3(std::unique_ptr< ::trees::tree::cst::reference>($1), std::unique_ptr< ::trees::tree::cst::arrays>($3)); } | /*-declarator_4-*/ reference "node" arrays { $$ = new ::trees::tree::cst::declarator_4(std::unique_ptr< ::trees::tree::cst::reference>($1), std::unique_ptr< ::trees::tree::cst::arrays>($3)); };
reference: /*-reference_1-*/ pointer { $$ = new ::trees::tree::cst::reference_1(std::unique_ptr< ::trees::tree::cst::pointer>($1)); } | /*-reference_2-*/ pointer "&" { $$ = new ::trees::tree::cst::reference_2(std::unique_ptr< ::trees::tree::cst::pointer>($1)); };
pointer: /*-pointer_1-*/ { $$ = new ::trees::tree::cst::pointer_1(); } | /*-pointer_2-*/ pointer "*" type_qualifiers { $$ = new ::trees::tree::cst::pointer_2(std::unique_ptr< ::trees::tree::cst::pointer>($1), std::unique_ptr< ::trees::tree::cst::type_qualifiers>($3)); };
type_qualifiers: /*-type_qualifiers_1-*/ { $$ = new ::trees::tree::cst::type_qualifiers_1(); } | /*-type_qualifiers_2-*/ type_qualifiers type_qualifier { $$ = new ::trees::tree::cst::type_qualifiers_2(std::unique_ptr< ::trees::tree::cst::type_qualifiers>($1), std::unique_ptr< ::trees::tree::cst::type_qualifier>($2)); };
type_qualifier: /*-type_qualifier_1-*/ "const" { $$ = new ::trees::tree::cst::type_qualifier_1(); } | /*-type_qualifier_2-*/ "volatile" { $$ = new ::trees::tree::cst::type_qualifier_2(); };
arrays: /*-arrays_1-*/ bounded_arrays { $$ = new ::trees::tree::cst::arrays_1(std::unique_ptr< ::trees::tree::cst::bounded_arrays>($1)); } | /*-arrays_2-*/ bounded_arrays unbounded_array { $$ = new ::trees::tree::cst::arrays_2(std::unique_ptr< ::trees::tree::cst::bounded_arrays>($1), std::unique_ptr< ::trees::tree::cst::unbounded_array>($2)); };
bounded_arrays: /*-bounded_arrays_1-*/ { $$ = new ::trees::tree::cst::bounded_arrays_1(); } | /*-bounded_arrays_2-*/ bounded_arrays bounded_array { $$ = new ::trees::tree::cst::bounded_arrays_2(std::unique_ptr< ::trees::tree::cst::bounded_arrays>($1), std::unique_ptr< ::trees::tree::cst::bounded_array>($2)); };
bounded_array: /*-bounded_array-*/ "[" REGEX_2 "]" { $$ = new ::trees::tree::cst::bounded_array($2); free($2); };
unbounded_array: /*-unbounded_array-*/ "[" "]" { $$ = new ::trees::tree::cst::unbounded_array(); };
type: /*-type_1-*/ template_name { $$ = new ::trees::tree::cst::type_1(std::unique_ptr< ::trees::tree::cst::template_name>($1)); } | /*-type_2-*/ scoped_name { $$ = new ::trees::tree::cst::type_2(std::unique_ptr< ::trees::tree::cst::scoped_name>($1)); } | /*-type_3-*/ "node" { $$ = new ::trees::tree::cst::type_3(); } | /*-type_4-*/ "group" { $$ = new ::trees::tree::cst::type_4(); } | /*-type_5-*/ "parent" { $$ = new ::trees::tree::cst::type_5(); };
template_name: /*-template_name-*/ scoped_name "<" template_argument_list ">" { $$ = new ::trees::tree::cst::template_name(std::unique_ptr< ::trees::tree::cst::scoped_name>($1), std::unique_ptr< ::trees::tree::cst::template_argument_list>($3)); };
template_argument_list: /*-template_argument_list_1-*/ { $$ = new ::trees::tree::cst::template_argument_list_1(); } | /*-template_argument_list_2-*/ template_arguments { $$ = new ::trees::tree::cst::template_argument_list_2(std::unique_ptr< ::trees::tree::cst::template_arguments>($1)); };
template_arguments: /*-template_arguments_1-*/ template_argument { $$ = new ::trees::tree::cst::template_arguments_1(std::unique_ptr< ::trees::tree::cst::template_argument>($1)); } | /*-template_arguments_2-*/ template_arguments "," template_argument { $$ = new ::trees::tree::cst::template_arguments_2(std::unique_ptr< ::trees::tree::cst::template_arguments>($1), std::unique_ptr< ::trees::tree::cst::template_argument>($3)); };
template_argument: /*-template_argument_1-*/ type { $$ = new ::trees::tree::cst::template_argument_1(std::unique_ptr< ::trees::tree::cst::type>($1)); } | /*-template_argument_2-*/ "void" { $$ = new ::trees::tree::cst::template_argument_2(); } | /*-template_argument_3-*/ "..." { $$ = new ::trees::tree::cst::template_argument_3(); } | /*-template_argument_4-*/ literal { $$ = new ::trees::tree::cst::template_argument_4(std::unique_ptr< ::trees::tree::cst::literal>($1)); };
scoped_name: /*-scoped_name-*/ scope REGEX_1 { $$ = new ::trees::tree::cst::scoped_name(std::unique_ptr< ::trees::tree::cst::scope>($1), $2); free($2); };
scope: /*-scope_1-*/ { $$ = new ::trees::tree::cst::scope_1(); } | /*-scope_2-*/ scope REGEX_1 "::" { $$ = new ::trees::tree::cst::scope_2(std::unique_ptr< ::trees::tree::cst::scope>($1), $2); free($2); };
literal: /*-literal_1-*/ boolean_literal { $$ = new ::trees::tree::cst::literal_1(std::unique_ptr< ::trees::tree::cst::boolean_literal>($1)); } | /*-literal_2-*/ REGEX_2 { $$ = new ::trees::tree::cst::literal_2($1); free($1); };
boolean_literal: /*-boolean_literal_1-*/ "true" { $$ = new ::trees::tree::cst::boolean_literal_1(); } | /*-boolean_literal_2-*/ "false" { $$ = new ::trees::tree::cst::boolean_literal_2(); };
