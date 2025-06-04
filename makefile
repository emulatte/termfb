CC = gcc

HEADERSDIR = include
HEADERS = $(wildcard $(HEADERSDIR)/*.h)

SRCDIR = src
SRC = $(wildcard $(SRCDIR)/*.c)

OBJ = $(notdir $(SRC:.c=.o))
BINDIR = bin
OBJ := $(addprefix $(BINDIR)/, $(OBJ))

$(BINDIR)/termfb: $(OBJ)
	$(CC) -o $@ $^

$(BINDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	$(CC) -c -o $@ $<
