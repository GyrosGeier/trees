cmake_minimum_required(VERSION 3.0)

project(trees)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCES
	bison_output_visitor.cpp bison_output_visitor.h
	bison_to_ast_visitor.cpp bison_to_ast_visitor.hpp
	errors.h
	header_output_visitor.cpp header_output_visitor.hpp
	impl_output_visitor.cpp impl_output_visitor.hpp
	inline_simple_visitor.cpp inline_simple_visitor.h
	lex_output_visitor.cpp lex_output_visitor.h
	mark_nodes_visitor.cpp mark_nodes_visitor.hpp
	parse_cst_to_ast_visitor.cpp parse_cst_to_ast_visitor.h
	parse.h
	resolve_literals_visitor.cpp resolve_literals_visitor.h
	resolve_regexes_visitor.cpp resolve_regexes_visitor.h
	resolve_symbols_visitor.cpp resolve_symbols_visitor.h
	smartpointer_visitor.cpp smartpointer_visitor.hpp
	tree_bison_context.hpp
	tree_bison.cpp
	tree_cst.cpp
	tree_cst_to_ast_visitor.cpp tree_cst_to_ast_visitor.hpp
	tree.h
	trees.cpp
	tree_tree.cpp tree_tree.hpp
	unroll_repetitions_visitor.cpp unroll_repetitions_visitor.h)

set(INPUT_FILES
	parse_cst.ll
	parse_cst.yy
	parse.ftree
	tree_bison.ll
	tree_bison.yy
	tree_cst.ll
	tree_cst.yy
	tree.ftree)

# TODO generate this
set(BUILT_SOURCES
	parse_cst_cst.cpp parse_cst_cst.hpp
	parse_cst_lex.cpp parse_cst_lex.hpp
	parse_cst_parse.cpp parse_cst_parse.hpp
	parse_tree.cpp parse_tree.hpp
	tree_bison_cst.cpp tree_bison_cst.hpp
	tree_bison_lex.cpp tree_bison_lex.hpp
	tree_bison_parse.cpp tree_bison_parse.hpp
	tree_cst_cst.cpp tree_cst_cst.hpp
	tree_cst_lex.cpp tree_cst_lex.hpp
	tree_cst_parse.cpp tree_cst_parse.hpp
	tree_tree.cpp tree_tree.hpp)

foreach(_src ${BUILT_SOURCES})
	list(APPEND BUILT_SOURCES_STAGE1 "stage1/${_src}")
	list(APPEND BUILT_SOURCES_STAGE2 "stage2/${_src}")
endforeach()

add_executable(trees-stage1 ${SOURCES} ${BUILT_SOURCES_STAGE1})
target_include_directories(trees-stage1 PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/stage1 .)

add_executable(trees ${SOURCES} ${BUILT_SOURCES_STAGE2})
target_include_directories(trees PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/stage2 .)

function(shipped _stage _file)
	add_custom_command(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_file}
		COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/
		COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${_file} ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/
		MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${_file})
endfunction()

function(flex _stage _file)
	get_filename_component(_tmp ${_file} NAME_WE)
	add_custom_command(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_tmp}_lex.cpp ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_tmp}_lex.hpp
		COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/
		COMMAND flex -o ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_tmp}_lex.cpp --header-file=${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_tmp}_lex.hpp ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_file}
		MAIN_DEPENDENCY ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_file})
endfunction()

function(bison _stage _file)
	get_filename_component(_tmp ${_file} NAME_WE)
	add_custom_command(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_tmp}_parse.cpp ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_tmp}_parse.hpp
		COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/
		COMMAND bison -d ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_file} -o ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_tmp}_parse.cpp
		MAIN_DEPENDENCY ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_file})
endfunction()

function(gen_flex _stage _file)
	get_filename_component(_tmp ${_file} NAME_WE)
	add_custom_command(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_tmp}.ll
		COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/
		COMMAND trees-stage1 -l -o ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_tmp}.ll ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_file}
		MAIN_DEPENDENCY ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_file}
		DEPENDS trees-stage1)
endfunction()

function(gen_bison _stage _file)
	get_filename_component(_tmp ${_file} NAME_WE)
	add_custom_command(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_tmp}.yy
		COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/
		COMMAND trees-stage1 -y -o ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_tmp}.yy ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_file}
		MAIN_DEPENDENCY ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_file}
		DEPENDS trees-stage1)
endfunction()

function(gen_cst _stage _file)
	get_filename_component(_tmp ${_file} NAME_WE)
	set(_namespace "")
	foreach(ns ${ARGN})
		list(APPEND _namespace "-n" "${ns}")
	endforeach()
	add_custom_command(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_tmp}_cst.cpp ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_tmp}_cst.hpp
		COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/
		COMMAND trees-stage1 ${_namespace} -c -o ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_tmp}_cst.cpp ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_file}
		COMMAND trees-stage1 ${_namespace} -o ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_tmp}_cst.hpp ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_file}
		MAIN_DEPENDENCY ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_file}
		DEPENDS trees-stage1)
endfunction()

function(gen_tree _stage _file)
	get_filename_component(_tmp ${_file} NAME_WE)
	add_custom_command(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_tmp}_tree.cpp ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_tmp}_tree.hpp
		COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/
		COMMAND trees-stage1 ${_namespace} -c -o ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_tmp}_tree.cpp ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_file}
		COMMAND trees-stage1 ${_namespace} -o ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_tmp}_tree.hpp ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_file}
		MAIN_DEPENDENCY ${CMAKE_CURRENT_BINARY_DIR}/${_stage}/${_file}
		DEPENDS trees-stage1)
endfunction()

shipped(stage1 parse_cst.ll)
shipped(stage1 parse_cst.yy)
shipped(stage1 tree_bison.ll)
shipped(stage1 tree_bison.yy)
shipped(stage1 tree_cst.ll)
shipped(stage1 tree_cst.yy)

flex   (stage1 parse_cst.ll)
bison  (stage1 parse_cst.yy)
flex   (stage1 tree_bison.ll)
bison  (stage1 tree_bison.yy)
flex   (stage1 tree_cst.ll)
bison  (stage1 tree_cst.yy)

shipped(stage1 parse_cst_cst.cpp)
shipped(stage1 parse_cst_cst.hpp)
shipped(stage1 parse_tree.cpp)
shipped(stage1 parse_tree.hpp)
shipped(stage1 tree_bison_cst.cpp)
shipped(stage1 tree_bison_cst.hpp)
shipped(stage1 tree_cst_cst.cpp)
shipped(stage1 tree_cst_cst.hpp)
shipped(stage1 tree_tree.cpp)
shipped(stage1 tree_tree.hpp)

shipped(stage2 parse_cst.fparse)
shipped(stage2 parse.ftree)
shipped(stage2 tree.ftree)

gen_flex(stage2 parse_cst.fparse)
gen_bison(stage2 parse_cst.fparse)
shipped(stage2 tree_bison.ll)
shipped(stage2 tree_bison.yy)
shipped(stage2 tree_cst.ll)
shipped(stage2 tree_cst.yy)

flex   (stage2 parse_cst.ll)
bison  (stage2 parse_cst.yy)
flex   (stage2 tree_bison.ll)
bison  (stage2 tree_bison.yy)
flex   (stage2 tree_cst.ll)
bison  (stage2 tree_cst.yy)

gen_cst(stage2 parse_cst.yy trees parse cst)
gen_tree(stage2 parse.ftree)
gen_cst(stage2 tree_bison.yy trees tree bison)
gen_cst(stage2 tree_cst.yy trees tree cst)
gen_tree(stage2 tree.ftree)
