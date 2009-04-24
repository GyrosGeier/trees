LEX = flex
YACC = bison

CXXFLAGS = -g -Wall -W -Werror -Wno-unused
LDFLAGS = -g -Wall -W -Werror

CXXSOURCES = $(wildcard *.cpp)
LEXSOURCES = $(wildcard *.ll)
YACCSOURCES = $(wildcard *.yy)

OBJECTS = $(CXXSOURCES:%.cpp=%.o) $(LEXSOURCES:%.ll=%_lex.o) $(YACCSOURCES:%.yy=%_parse.o)
DEPFILES = $(addprefix stage1/,$(OBJECTS:%.o=.%.d)) $(addprefix stage2/,$(OBJECTS:%.o=.%.d))

all: treecc $(YACCSOURCES:%.yy=update-%_tree.hpp) $(YACCSOURCES:%.yy=update-%_tree.cpp)

treecc: $(addprefix stage2/,$(OBJECTS))
	$(CXX) $(LDFLAGS) -o $@ $^

update-%_tree.hpp: %_tree.hpp update/%_tree.hpp stage2/%_tree.hpp
	cmp $(wordlist 1,2,$^) || (cmp $(wordlist 2,3,$^) && mv update/$< $<)

update-%_tree.cpp: %_tree.cpp update/%_tree.cpp stage2/%_tree.cpp
	cmp $(wordlist 1,2,$^) || (cmp $(wordlist 2,3,$^) && mv update/$< $<)

update/%_tree.hpp: %.yy treecc
	@mkdir -p update
	./treecc -o $@ $<

update/%_tree.cpp: %.yy treecc
	@mkdir -p update
	./treecc -c -o $@ $<

stage2/%_tree.hpp: %.yy stage1/treecc
	stage1/treecc -o $@ $<

stage2/%_tree.cpp: %.yy stage1/treecc
	stage1/treecc -c -o $@ $<

%_lex.cpp: %.ll
	$(LEX) -o $@ $<

%_parse.cpp: %.yy
	$(YACC) -o $@ $<

%_lex.hpp: %_lex.cpp
	@

%_parse.hpp: %_parse.cpp
	@

stage1/treecc: $(addprefix stage1/,$(OBJECTS))
	$(CXX) $(LDFLAGS) -o $@ $^

stage1/%.o: %.cpp $(YACCSOURCES:%.yy=%_parse.hpp) $(YACCSOURCES:%.yy=%_tree.hpp) $(LEXSOURCES:%.ll=%_lex.hpp)
	$(CXX) $(CXXFLAGS) -I. -o $@ -MD -MF stage1/.$*.d -c $<

stage2/%.o: %.cpp $(YACCSOURCES:%.yy=%_parse.hpp) $(addprefix stage2/,$(YACCSOURCES:%.yy=%_tree.hpp)) $(LEXSOURCES:%.ll=%_lex.hpp)
	$(CXX) $(CXXFLAGS) -Istage2 -I. -o $@ -MD -MF stage2/.$*.d -c $<

stage2/tree_tree.o: stage2/tree_tree.cpp tree_parse.hpp tree_lex.hpp stage2/tree_tree.hpp
	$(CXX) $(CXXFLAGS) -Istage2 -I. -o $@ -MD -MF stage2/.$(notdir $*).d -c $<

.%.d:
	@mkdir -p $(dir $*)
	touch $@

clean:
	$(RM) treecc
	$(RM) -r stage2 stage1 update

sinclude $(DEPFILES)
