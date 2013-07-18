export CXX LEX YACC

all %:
	$(MAKE) -C lang $@
	$(MAKE) -C parse $@
