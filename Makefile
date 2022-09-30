CC=g++
STDNAME=POSHLA_MOCHA_PO_TRUBAM
CFLAGS= #-Wall -Wextra -Wpedantic
SRCDIR=src
SRC=$(wildcard $(addsuffix /*.cpp, $(SRCDIR)) )
INCLUDES=headers
OBJDIR=objects
OBJ=$(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SRC)) )


all: onega
VPATH = $(SRCDIR)

onega: $(OBJ)
	@$(CC) $(OBJ) -o $(STDNAME)

$(STDNAME): $(OBJ)
	@$(CC) $(OBJ) -o $@

$(OBJDIR)/%.o: %.cpp
	@$(CC) -c -I $(INCLUDES) $(CFLAGS) $< -o $@ 

run: clean $(STDNAME)
	@$(STDNAME)

clean:
	@rm -f $(OBJ) $(STDNAME)