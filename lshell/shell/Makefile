
# src/shell/Makefile

CC := gcc
CFLAGS := -Wall -Wextra -g -std=c99 -I.. -Isrc
OBJDIR := build
SRCS := alias.c execution.c shell_ast.c shell_utils.c shell.c
OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(OBJDIR) $(OBJS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

