# default:
# 	gcc -Wall -o prog main.c input.c
# debug:
# 	gcc -Wall -o prog -g main.c input.c
# clean:
# 	rm -f prog

# Define folder structure
CC = gcc
CFLAGS = -Wall -Iinclude
OBJDIR = obj
BINDIR = bin
SRCDIR = src

# Define source and object files
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SOURCES))


default: $(BINDIR)/prog

debug: CFLAGS += -g
debug: $(BINDIR)/prog

# Executable build rule
$(BINDIR)/prog: $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) -o $@ $^

# Object file build rule
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJDIR)/*.o $(BINDIR)/prog

# Phony targets
.PHONY: default debug clean
