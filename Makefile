# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

# Directories
INCDIR = include
SRCDIR = src
EXAMPLEDIR = examples
BUILDDIR = build

# Source files
SOURCES = $(SRCDIR)/Value.cpp
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)

# Example
EXAMPLE = $(EXAMPLEDIR)/value_example.cpp
EXAMPLE_TARGET = $(BUILDDIR)/value_example

# Targets
all: $(EXAMPLE_TARGET)

$(EXAMPLE_TARGET): $(EXAMPLE) $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)

.PHONY: all clean
