
# utils/Makefile

CC := gcc
CFLAGS := -Wall -Wextra -std=c99
UTILDIR := $(CURDIR)
BINDIR := $(UTILDIR)/bin
SRCDIR := $(UTILDIR)/utils
INSTALLDIR := $(HOME)/bin/lshell

UTILS := cat ls wc
SOURCES := $(addsuffix .c, $(addprefix $(SRCDIR)/, $(UTILS)))
TARGETS := $(addprefix $(BINDIR)/, $(UTILS))

.PHONY: all clean install

all: $(TARGETS)

$(BINDIR)/%: $(SRCDIR)/%.c
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $<

install: all
	mkdir -p $(INSTALLDIR)
	cp $(BINDIR)/* $(INSTALLDIR)/

clean:
	rm -rf $(BINDIR)

