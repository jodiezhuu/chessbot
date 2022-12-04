CXX=g++
CXXFLAGS=-std=c++14 -MMD
SRCS=$(wildcard Pieces/*.cc) $(wildcard *.cc)
OBJECTS=$(addsuffix .o,$(basename $(SRCS)))
DEPENDS=${OBJECTS:.o=.d}
EXEC=chess -lX11

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean
clean:
	del /s *.o
	del /s *.d