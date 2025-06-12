
# Lshell_setup/Makefile

INSTALLDIR := $(HOME)/bin/lshell

.PHONY: all clean install utils lshell

all: install

# This ensures lshell is built before trying to copy
install: lshell/build/lshell utils
	mkdir -p $(INSTALLDIR)
	cp lshell/build/lshell $(INSTALLDIR)/
	$(MAKE) -C utils install

lshell/build/lshell:
	$(MAKE) -C lshell

utils:
	$(MAKE) -C utils

clean:
	$(MAKE) -C lshell clean
	$(MAKE) -C utils clean
	rm -f $(INSTALLDIR)/lshell
	rm -f $(INSTALLDIR)/cat $(INSTALLDIR)/ls $(INSTALLDIR)/wc

