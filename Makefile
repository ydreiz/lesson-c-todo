CC = clang
CFLAGS = -Wall -Wextra -std=c23

BINDDIR = bin
OBJDIR = obj

all: $(BINDDIR) $(OBJDIR) \
	$(BINDDIR)/array \
	$(BINDDIR)/fopen \
	$(BINDDIR)/functions \
	$(BINDDIR)/if_else_iter \
	$(BINDDIR)/malloc \
	$(BINDDIR)/pointers \
	$(BINDDIR)/strings \
	$(BINDDIR)/structs \
	$(BINDDIR)/structs_array \
	$(BINDDIR)/structs_functions \
	$(BINDDIR)/types \
	$(BINDDIR)/consts

$(BINDDIR) $(OBJDIR):
	mkdir -p $@

$(BINDDIR)/array: $(OBJDIR)/array.o
	$(CC) $(CFLAGS) -o $@ $^

$(BINDDIR)/fopen: $(OBJDIR)/fopen.o
	$(CC) $(CFLAGS) -o $@ $^

$(BINDDIR)/functions: $(OBJDIR)/functions.o
	$(CC) $(CFLAGS) -o $@ $^

$(BINDDIR)/if_else_iter: $(OBJDIR)/if_else_iter.o
	$(CC) $(CFLAGS) -o $@ $^

$(BINDDIR)/malloc: $(OBJDIR)/malloc.o
	$(CC) $(CFLAGS) -o $@ $^

$(BINDDIR)/pointers: $(OBJDIR)/pointers.o
	$(CC) $(CFLAGS) -o $@ $^

$(BINDDIR)/strings: $(OBJDIR)/strings.o
	$(CC) $(CFLAGS) -o $@ $^

$(BINDDIR)/structs: $(OBJDIR)/structs.o
	$(CC) $(CFLAGS) -o $@ $^

$(BINDDIR)/structs_array: $(OBJDIR)/structs_array.o
	$(CC) $(CFLAGS) -o $@ $^

$(BINDDIR)/structs_functions: $(OBJDIR)/structs_functions.o $(OBJDIR)/person.o
	$(CC) $(CFLAGS) -o $@ $^

$(BINDDIR)/types: $(OBJDIR)/types.o
	$(CC) $(CFLAGS) -o $@ $^

$(BINDDIR)/consts: $(OBJDIR)/consts.o
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(OBJDIR)/*.o

.PHONY: all clean
