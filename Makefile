CXX ?= g++
LEX ?= flex
YACC ?= bison
INSTALL ?= install

CPPFLAGS ?=
CXXFLAGS ?= -W -Wall -Werror -g
LDFLAGS ?= -W -Wall -Werror -g

CXXFLAGS += -std=c++0x

MKDIR ?= mkdir -p

CXXSOURCES = $(wildcard *.cpp)
LEXSOURCES = $(wildcard *.ll)
YACCSOURCES = $(wildcard *.yy) $(PARSESOURCES:%.fparse=%.yy)
TREESOURCES = $(wildcard *.ftree)
PARSESOURCES = $(wildcard *.fparse)

BOOTSTRAP_SOURCES = $(YACCSOURCES:%.yy=%_cst.cpp) $(TREESOURCES:%.ftree=%_tree.cpp)
BOOTSTRAP_HEADERS = $(YACCSOURCES:%.yy=%_cst.hpp) $(TREESOURCES:%.ftree=%_tree.hpp)
BOOTSTRAP_MISC = $(PARSESOURCES:%.fparse=%.ll) $(PARSESOURCES:%.fparse=%.yy)

BOOTSTRAP = $(BOOTSTRAP_SOURCES) $(BOOTSTRAP_HEADERS) $(BOOTSTRAP_MISC)

BUILT_SOURCES = $(YACCSOURCES:%.yy=%_parse.cpp) $(LEXSOURCES:%.ll=%_lex.cpp)
BUILT_HEADERS = $(YACCSOURCES:%.yy=%_parse.hpp) $(LEXSOURCES:%.ll=%_lex.hpp)
BUILT_MISC = $(PARSESOURCES:%.fparse=%.ll) $(PARSESOURCES:%.fparse=%.yy)

STAGE1_BUILT_HEADERS = $(addprefix stage1/,$(YACCSOURCES:%.yy=%_parse.hpp) $(LEXSOURCES:%.ll=%_lex.hpp))
STAGE2_BUILT_HEADERS = $(addprefix stage2/,$(BUILT_HEADERS))

OBJECTS = $(sort $(CXXSOURCES:%.cpp=%.o) $(BUILT_SOURCES:%.cpp=%.o))
DEPFILES = $(addprefix stage1/,$(OBJECTS:%.o=.%.d)) $(addprefix stage2/,$(OBJECTS:%.o=.%.d))

.PHONY: all

all: foundry-lang

.PHONY: install

install: foundry-lang
	$(INSTALL) -d $(DESTDIR)/usr/bin
	$(INSTALL) $^ $(DESTDIR)/usr/bin/

.PHONY: update

update: $(addprefix update/,$(BOOTSTRAP))
	@for i in $(BOOTSTRAP); do \
	  if cmp -s $$i update/$$i; then \
	    echo "$$i is unchanged."; \
	  else \
	    echo "updating $$i."; \
	    mv update/$$i $$i; \
	  fi; \
	done

.PHONY: check test

check test: $(addprefix update/,$(BOOTSTRAP))

.PHONY: clean

clean:
	$(RM) foundry-lang
	$(RM) -r stage1
	$(RM) -r stage2
	$(RM) -r update

foundry-lang: $(addprefix stage2/,$(OBJECTS))
	$(CXX) $(LDFLAGS) -o $@ $^

update/parse_cst.ll: parse_cst.fparse foundry-lang stage2/parse_cst.ll
	@mkdir -p update
	./foundry-lang -l $< -o $@
	cmp -s $@ stage2/$(notdir $@)

update/parse_cst.yy: parse_cst.fparse foundry-lang stage2/parse_cst.yy
	@mkdir -p update
	./foundry-lang -y $< -o $@
	cmp -s $@ stage2/$(notdir $@)

update/%_tree.hpp: %.ftree foundry-lang stage2/%_tree.hpp
	@mkdir -p update
	./foundry-lang -o $@ $<
	cmp -s $@ stage2/$(notdir $@)

update/%_tree.cpp: %.ftree foundry-lang stage2/%_tree.cpp
	@mkdir -p update
	./foundry-lang -c -o $@ $<
	cmp -s $@ stage2/$(notdir $@)

update/%_cst.hpp: %.yy foundry-lang stage2/%_cst.hpp
	@mkdir -p update
	./foundry-lang -n foundry -n $(subst _, -n ,$*) -o $@ $<
	cmp -s $@ stage2/$(notdir $@)

update/%_cst.cpp: %.yy foundry-lang stage2/%_cst.cpp
	@mkdir -p update
	./foundry-lang -n foundry -n $(subst _, -n ,$*) -c -o $@ $<
	cmp -s $@ stage2/$(notdir $@)

stage2/%_tree.hpp: %.ftree stage1/foundry-lang
	stage1/foundry-lang -o $@ $<

stage2/%_tree.cpp: %.ftree stage1/foundry-lang
	stage1/foundry-lang -c -o $@ $<

stage2/%_cst.hpp: stage2/%.yy stage1/foundry-lang
	stage1/foundry-lang -n foundry -n $(subst _, -n ,$*) -o $@ $<

stage2/%_cst.cpp: stage2/%.yy stage1/foundry-lang
	stage1/foundry-lang -n foundry -n $(subst _, -n ,$*) -c -o $@ $<

stage2/%_cst.hpp: stage2/%.yy stage1/foundry-lang
	stage1/foundry-lang -n foundry -n $(subst _, -n ,$*) -o $@ $<

stage2/%_cst.cpp: stage2/%.yy stage1/foundry-lang
	stage1/foundry-lang -n foundry -n $(subst _, -n ,$*) -c -o $@ $<

stage2/%_lex.hpp: stage2/%_lex.cpp
	test -f $@ || ($(RM) $< && $(MAKE) $<)
	touch $@

stage2/%_lex.cpp: stage2/%.ll
	cd stage2 && flex -o $(notdir $@) --header-file=$(basename $(notdir $@)).hpp $(notdir $<)

stage2/%_parse.hpp: stage2/%_parse.cpp
	test -f $@ || ($(RM) $< && $(MAKE) $<)
	touch $@

stage2/%_parse.cpp: stage2/%.yy
	bison -d $< -o $@

stage2/%.ll: %.fparse stage1/foundry-lang
	stage1/foundry-lang -o $@ -l $<

stage2/%.yy: %.fparse stage1/foundry-lang
	stage1/foundry-lang -o $@ -y $<

stage2/tree_%.ll: tree_%.ll
	cp $< $@

stage2/tree_%.yy: tree_%.yy
	cp $< $@

stage2/%.o: %.cpp
	@$(MKDIR) stage2
	$(CXX) $(CPPFLAGE) -Istage2 -I. $(CXXFLAGS) -MD -MF stage2/.$*.d -o $@ -c $<

stage2/%.o: stage2/%.cpp
	$(CXX) $(CPPFLAGS) -Istage2 -I. $(CXXFLAGS) -MD -MF stage2/.$*.d -o $@ -c $<

stage2/parse_cst.o: stage2/parse_cst.cpp

stage1/foundry-lang: $(addprefix stage1/,$(OBJECTS))
	$(CXX) $(LDFLAGS) -o $@ $^

stage1/%_lex.hpp: stage1/%_lex.cpp
	test -f $@ || ($(RM) $< && $(MAKE) $<)
	touch $@

stage1/%_lex.cpp: %.ll
	cd stage1 && flex -o $(notdir $@) --header-file=$(basename $(notdir $@)).hpp ../$(notdir $<)

stage1/%_parse.hpp: stage1/%_parse.cpp
	test -f $@ || ($(RM) $< && $(MAKE) $<)
	touch $@

stage1/%_parse.cpp: %.yy
	bison -d $< -o $@

stage1/%.o: %.cpp
	@$(MKDIR) stage1
	$(CXX) $(CPPFLAGS) -Istage1 -I. $(CXXFLAGS) -MD -MF stage1/.$*.d -o $@ -c $<

stage1/%.o: stage1/%.cpp
	$(CXX) $(CPPFLAGS) -Istage1 -I. $(CXXFLAGS) -MD -MF stage1/.$*.d -o $@ -c $<

%_lex.cpp: %.ll
	$(LEX) -o $@ $<

%_parse.cpp: %.yy
	$(YACC) -o $@ $<

stage1/%_lex.o: CXXFLAGS+=-Wno-unused-parameter
stage2/%_lex.o: CXXFLAGS+=-Wno-unused-parameter

stage1/.%.d:
	@mkdir -p $(@D)
	@echo >$@ "stage1/$*.o: $(STAGE1_BUILT_HEADERS)"

stage2/.%.d:
	@mkdir -p $(@D)
	@echo >$@ "stage2/$*.o: $(STAGE2_BUILT_HEADERS)"

.SUFFIXES:
.DELETE_ON_ERROR:

DEPENDS = $(OBJECTS:%.o=.%.d)

sinclude $(addprefix stage1/,$(DEPENDS)) $(addprefix stage2/,$(DEPENDS))
