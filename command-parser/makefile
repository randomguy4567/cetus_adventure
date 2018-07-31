VPATH = src:inc:obj
SRCDIR = src
INCDIR = inc
OBJDIR = obj
OBJS = parser_demo.o ParsedCommand.o Parser.o
CFLAGS = -I$(INCDIR) -g
CXXFLAGS = -I$(INCDIR) -g -std=c++11

default: 

parser_demo: $(addprefix $(OBJDIR)/, $(OBJS))
	clang++ $(LDFLAGS) $^ -o $@

$(OBJDIR)/parser_demo.o: parser_demo.cpp Parser.hpp ParsedCommand.hpp Tag.hpp
	clang++ -c $(CXXFLAGS) $< -o $@

$(OBJDIR)/%.o: %.cpp %.hpp Tag.hpp
	clang++ -c $(CXXFLAGS) $< -o $@

clean:
	rm -f ./obj/*
	rm -f ./parser_demo
