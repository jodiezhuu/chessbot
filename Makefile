CXX=g++
CXXFLAGS=-std=c++14 -MMD -Werror=vla
SRCS=$(wildcard *.cc)
OBJECTS=$(addsuffix .o,$(basename $(SRCS)))
DEPENDS=${OBJECTS:.o=.d}
EXEC=chess

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean
clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}