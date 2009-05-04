LEX = flex
YACC = bison

CXXFLAGS = -g -Wall -W -Werror -Wno-unused
LDFLAGS = -g -Wall -W -Werror

CXXSOURCES = $(wildcard *.cpp)
LEXSOURCES = $(wildcard *.ll)
YACCSOURCES = $(wildcard *.yy)
TREESOURCES = $(wildcard *.ftree)

OBJECTS = $(CXXSOURCES:%.cpp=%.o) $(LEXSOURCES:%.ll=%_lex.o) $(YACCSOURCES:%.yy=%_parse.o) $(YACCSOURCES:%.yy=%_tree.o)
DEPFILES = $(addprefix stage1/,$(OBJECTS:%.o=.%.d)) $(addprefix stage2/,$(OBJECTS:%.o=.%.d))

all: foundry-tree update-tree_tree.hpp update-tree_tree.cpp

foundry-tree: $(addprefix stage2/,$(OBJECTS))
	$(CXX) $(LDFLAGS) -o $@ $^

stage1/foundry-tree: $(addprefix stage1/,$(OBJECTS))
	$(CXX) $(LDFLAGS) -o $@ $^

stage2/%_tree.hpp: %.ftree stage1/foundry-tree
	stage1/foundry-tree -o $@ $<

stage2/%_tree.cpp: %.ftree stage1/foundry-tree
	stage1/foundry-tree -c -o $@ $<

update-%: % update/% stage2/%
	cmp $(wordlist 1,2,$^) || (cmp $(wordlist 2,3,$^) && mv update/$< $<)

update/%_tree.hpp: %.ftree foundry-tree
	@mkdir -p update
	./foundry-tree -o $@ $<

update/%_tree.cpp: %.ftree foundry-tree
	@mkdir -p update
	./foundry-tree -c -o $@ $<

%_tree.hpp: %.yy treecc/treecc
	treecc/treecc -n foundry -n $(subst _, -n ,$*) -o $@ $<

%_tree.cpp: %.yy treecc/treecc
	treecc/treecc -n foundry -n $(subst _, -n ,$*) -c -o $@ $<

treecc/treecc:
	$(MAKE) -C treecc

%_lex.cpp: %.ll
	$(LEX) -o $@ $<

%_parse.cpp: %.yy
	$(YACC) -o $@ $<

%_lex.hpp: %_lex.cpp
	@

%_parse.hpp: %_parse.cpp
	@

stage1/%.o: %.cpp $(YACCSOURCES:%.yy=%_parse.hpp) $(YACCSOURCES:%.yy=%_tree.hpp) $(LEXSOURCES:%.ll=%_lex.hpp) $(TREESOURCES:%.ftree=%_tree.hpp)
	$(CXX) $(CXXFLAGS) -I. -o $@ -MD -MF stage1/.$*.d -c $<

stage2/%.o: %.cpp $(YACCSOURCES:%.yy=%_parse.hpp) $(YACCSOURCES:%.yy=%_tree.hpp) $(LEXSOURCES:%.ll=%_lex.hpp) $(addprefix stage2/,$(TREESOURCES:%.ftree=%_tree.hpp))
	$(CXX) $(CXXFLAGS) -Istage2 -I. -o $@ -MD -MF stage2/.$*.d -c $<

stage2/tree_tree.o: stage2/tree_tree.cpp $(addprefix stage2/,$(TREESOURCES:%.ftree=%_tree.hpp))
	$(CXX) $(CXXFLAGS) -Istage2 -I. -o $@ -MD -MF stage2/.$*.d -c $<

.%.d:
	@mkdir -p $(@D)
	touch $@

clean:
	$(RM) foundry-tree
	$(RM) -r update stage2 stage1
	$(MAKE) -C treecc $@

sinclude $(DEPFILES)

.SUFFIXES:
.DELETE_ON_ERROR:
