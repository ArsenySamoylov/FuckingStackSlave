CC=g++
STDNAME=a
CFLAGS= -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wmissing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_DEBUG -D_EJUDGE_CLIENT_SIDE
SRCDIR=
SRC=$(wildcard *.cpp)
INCLUDES=
OBJDIR=obj
OBJ=$(patsubst %.cpp, $(OBJDIR)/%.o, $(notdir $(SRC)) )


all: onega

onega: $(OBJ)
	@$(CC) $(OBJ) -o $(STDNAME)

$(STDNAME): $(OBJ)
	@$(CC) $(OBJ) -o $@

$(OBJDIR)/%.o: %.cpp
	@$(CC) -c $(CFLAGS) $< -o $@ 

run: clean $(STDNAME)
	@$(STDNAME)

clean:
	@rm -f $(OBJ) $(STDNAME)