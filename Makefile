export CXX LEX YACC

all %:
	$(MAKE) -C tree $@
	$(MAKE) -C parse $@
