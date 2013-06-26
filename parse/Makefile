CXX ?= g++
CPPFLAGS ?=
CXXFLAGS ?= -W -Wall -Werror -g
LDFLAGS ?= -W -Wall -Werror -g

MKDIR ?= mkdir -p

CXXSOURCES = $(wildcard *.cpp)
YACCSOURCES = $(wildcard *.yy)
LEXSOURCES = $(wildcard *.ll)
TREESOURCES = $(wildcard *.ftree)

BUILT_SOURCES = $(YACCSOURCES:%.yy=%_parse.cpp) $(YACCSOURCES:%.yy=%_cst.cpp) $(LEXSOURCES:%.ll=%_lex.cpp) $(TREESOURCES:%.ftree=%_tree.cpp)
BUILT_HEADERS = $(YACCSOURCES:%.yy=%_parse.hpp) $(YACCSOURCES:%.yy=%_cst.hpp) $(LEXSOURCES:%.ll=%_lex.hpp) $(TREESOURCES:%.ftree=%_tree.hpp)

OBJECTS = $(CXXSOURCES:%.cpp=%.o) $(BUILT_SOURCES:%.cpp=%.o)

all: foundry-parse

foundry-parse: $(addprefix stage2/,$(OBJECTS))
	$(CXX) $(LDFLAGS) -o $@ $^

check: parse.yy.update parse.ll.update

update: parse.yy.update parse.ll.update
	cmp -s parse.ll.update parse.ll || cp parse.ll.update parse.ll
	cmp -s parse.yy.update parse.yy || cp parse.yy.update parse.yy

parse.ll.update: parse.fparse foundry-parse stage2/parse.ll
	./foundry-parse -l $< -o $@
	cmp -s stage2/parse.ll $@

parse.yy.update: parse.fparse foundry-parse stage2/parse.yy
	./foundry-parse -y $< -o $@
	cmp -s stage2/parse.yy $@

clean:
	$(RM) foundry-parse
	$(RM) -r stage1
	$(RM) -r stage2
	$(RM) *.update

stage1/foundry-parse: $(addprefix stage1/,$(OBJECTS))
	$(CXX) $(LDFLAGS) -o $@ $^

stage1/%_cst.cpp: %.yy
	../tree/foundry-tree -n foundry -n parse -n cst -o $@ -c $<

stage1/%_cst.hpp: %.yy
	../tree/foundry-tree -n foundry -n parse -n cst -o $@ $<

stage1/%_lex.cpp: %.ll
	cd stage1 && flex -o $(notdir $@) --header-file=$(basename $(notdir $@)).hpp ../$(notdir $<)

stage1/%_lex.hpp: stage1/%_lex.cpp
	test -f $@ || ($(RM) $< && $(MAKE) $<)
	touch $@

stage1/%_parse.cpp: %.yy
	bison -d $< -o $@

stage1/%_parse.hpp: stage1/%_parse.cpp
	test -f $@ || ($(RM) $< && $(MAKE) $<)
	touch $@

stage1/%_tree.hpp: %.ftree
	../tree/foundry-tree -o $@ $<

stage1/%_tree.cpp: %.ftree
	../tree/foundry-tree -o $@ -c $<

stage1/%.o: %.cpp
	@$(MKDIR) stage1
	$(CXX) $(CPPFLAGS) -Istage1 $(CXXFLAGS) -MD -MF stage1/.$*.d -o $@ -c $<

stage1/%.o: stage1/%.cpp
	$(CXX) $(CPPFLAGS) -Istage1 $(CXXFLAGS) -MD -MF stage1/.$*.d -o $@ -c $<

stage1/%_lex.o: CXXFLAGS+=-Wno-unused

stage2/%.ll: %.fparse stage1/foundry-parse
	stage1/foundry-parse -o $@ -l $<

stage2/%.yy: %.fparse stage1/foundry-parse
	stage1/foundry-parse -o $@ -y $<

stage2/%_cst.cpp: stage2/%.yy
	../tree/foundry-tree -n foundry -n parse -n cst -o $@ -c $<

stage2/%_cst.hpp: stage2/%.yy
	../tree/foundry-tree -n foundry -n parse -n cst -o $@ $<

stage2/%_lex.cpp: stage2/%.ll
	cd stage2 && flex -o $(notdir $@) --header-file=$(basename $(notdir $@)).hpp ../$(notdir $<)

stage2/%_lex.hpp: stage2/%_lex.cpp
	test -f $@ || ($(RM) $< && $(MAKE) $<)
	touch $@

stage2/%_parse.cpp: stage2/%.yy
	bison -d $< -o $@

stage2/%_parse.hpp: stage2/%_parse.cpp
	test -f $@ || ($(RM) $< && $(MAKE) $<)
	touch $@

stage2/%_tree.cpp: %.ftree
	../tree/foundry-tree -o $@ -c $<

stage2/%_tree.hpp: %.ftree
	../tree/foundry-tree -o $@ $<

stage2/%.o: %.cpp
	@$(MKDIR) stage2
	$(CXX) $(CPPFLAGE) -Istage2 $(CXXFLAGS) -MD -MF stage2/.$*.d -o $@ -c $<

stage2/%.o: stage2/%.cpp
	$(CXX) $(CPPFLAGS) -Istage2 $(CXXFLAGS) -MD -MF stage2/.$*.d -o $@ -c $<

stage2/%_lex.o: CXXFLAGS+=-Wno-unused

DEPENDS = $(OBJECTS:%.o=.%.d)

stage1/.%.d:
	@mkdir -p stage1
	echo >$@ stage1/$*.o: $(addprefix stage1/,$(BUILT_HEADERS))

stage2/.%.d:
	@mkdir -p stage2
	echo >$@ stage2/$*.o: $(addprefix stage2/,$(BUILT_HEADERS))

sinclude $(addprefix stage1/,$(DEPENDS)) $(addprefix stage2/,$(DEPENDS))
