CC = clang
CFLAGS = -Wall -Wextra -std=c23

BINDDIR = bin
OBJDIR = obj

MINGW_PREFIX = /usr/x86_64-w64-mingw32
TARGET_TRIPLE = x86_64-w64-mingw32

WIN_CFLAGS = --target=$(TARGET_TRIPLE) -I$(MINGW_PREFIX)/include -Wall -Wextra -std=c23
WIN_LDFLAGS = -L$(MINGW_PREFIX)/lib -lmingw32 -lmingwex -lkernel32 -luser32 -static

all: $(BINDDIR) $(OBJDIR) \
	$(BINDDIR)/todos \
	$(BINDDIR)/todos.exe

$(BINDDIR) $(OBJDIR):
	mkdir -p $@

$(BINDDIR)/todos: $(OBJDIR)/todos.o
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDDIR)/todos.exe: todos.c
	$(CC) $(WIN_CFLAGS) todos.c -o $@ $(WIN_LDFLAGS)

clean:
	rm -f *.o $(OBJDIR)/*.o

.PHONY: all clean
