CXX=g++
CPPFLAGS=-I.
CXXFLAGS=-Wall -pedantic -Wextra -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wzero-as-null-pointer-constant -Weffc++ -Wdelete-non-virtual-dtor -Wno-unused-local-typedefs -Werror -Wno-error=unused-parameter
LDFLAGS=-Wl,-rpath,.

BUILDDIR=./build/
BINDIR=./bin/

.PHONY: all
all: bin/game

$(BUILDDIR)%.o: %.cpp %.h
	mkdir -p $(@D)
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@

$(BUILDDIR)%.o: %.cpp
	mkdir -p $(@D)
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@

.PHONY: clean
clean:
	@rm -Rf build/* bin/*

include core/core.mk