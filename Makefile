CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=--std=c++11
LDFLAGS=
LDLIBS=

SRCS=Edge.cpp  Feature.cpp  Game.cpp  Interface.cpp  main.cpp  Node.cpp  Object.cpp
OBJS=$(subst .cc,.o,$(SRCS))

all: cetus

cetus: $(OBJS)
	$(CXX) $(LDFLAGS) -o cetus $(OBJS) $(LDLIBS) 

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) *~ .depend

include .depend    
#    all: Edge.cpp  Feature.cpp  Game.cpp  Interface.cpp  main.cpp  Node.cpp  Object.cpp Edge.h  Feature.h  Game.h  Interface.h  Node.h  Object.h
#	g++ --std=c++11 -o cetus Edge.cpp  Feature.cpp  Game.cpp  Interface.cpp  main.cpp  Node.cpp  Object.cpp


