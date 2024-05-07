CXX = g++-11 -std=c++20
CXXFLAGS = -Wall -g -O -MMD -Werror=vla # use -MMD to generate dependencies
SOURCES = $(wildcard *.cc)   # Enter the name of your .cc files
OBJECTS = ${SOURCES:.cc=.o}  # .o files depend upon .cc files with same names
DEPENDS = ${OBJECTS:.o=.d}   # .d file is list of dependencies for corresponding .cc file
EXEC = evanchess		# Enter the executable name

# First target in the makefile is the default target.
$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC) $(LIBFLAGS) -lX11 
	strip $(EXEC)

%.o: %.cc 
	$(CXX) -c -o $@ $< $(CXXFLAGS) $(LIBFLAGS)

-include ${DEPENDS}

.PHONY: clean
clean:
	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)
