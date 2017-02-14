SOURCE = $(wildcard *.cpp)

OBJS = $(SOURCE:.cpp=.o)

#GNU C/C++ Compiler
GCC = g++

# GNU C/C++ Linker
LINK = g++

# Compiler flags
CFLAGS = -Wall -O -std=c++11 -c
CXXFLAGS = $(CFLAGS)

# Fill in special libraries needed here
LIBS = -lglut -lGLU -lGL -lm
MACLIBS = -framework OpenGL -framework GLUT

.PHONY: clean

# Targets include all, clean, debug, tar

all : main

main: $(OBJS)
	$(LINK) -o $@ $^ $(LIBS)

clean:
	rm -rf *.o *.d core main

debug: CXXFLAGS += -DDEBUG -g
debug: main

dmac: CXXFLAGS += -DDEBUG -g
dmac: mac

mac: $(OBJS)
	$(LINK) -o $@ $^ $(MACLIBS)

tar:
	tar cvf main_Tarball.tar *.cpp *.h Makefile

help:
	@echo "	make main  - same as make all"
	@echo "	make all   - builds the main target"
	@echo "	make       - same as make all"
	@echo "	make mac   - builds the main target for mac"
	@echo "	make dmac  - make mac with -g and -DDEBUG"
	@echo "	make clean - remove .o .d core main"
	@echo "	make debug - make all with -g and -DDEBUG"
	@echo "	make tar   - make a tarball of .cpp and .h files"
	@echo "	make help  - this message"

-include $(SOURCE:.cpp=.d)

%.d: %.cpp
	@set -e; rm -rf $@;$(GCC) -MM $< $(CXXFLAGS) > $@

