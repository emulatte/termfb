CC = gcc
SRCDIR = src
SRC = $(wildcard $(SRCDIR)/*)
INCDIR = include
BINDIR = bin
BIN = termfb

default:
	$(CC) $(SRC) -o $(BINDIR)/$(BIN) -I$(INCDIR) 

debug:
	$(CC) -g -o $(BINDIR)/debug_$(BIN) -I$(INCDIR) $(SRC)
