CXX=g++
CPPFLAGS=-I.
CXXFLAGS=-std=c++17 -Wall -pedantic -Wextra -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow=global -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wzero-as-null-pointer-constant -Weffc++ -Wdelete-non-virtual-dtor -Wno-unused-local-typedefs -Werror -Wno-error=unused-parameter -Wno-error=shadow
LDFLAGS=-Wl,-rpath,.

BUILDDIR=build/
BINDIR=bin/
DEPDIR=deps/


.PHONY: debug
debug: CXXFLAGS += -g
debug: all

.PHONY: all
all: bin/game

$(BUILDDIR)%.o: %.cpp
	@mkdir -p $(@D)
	@mkdir -p $(DEPDIR)$(patsubst $(BUILDDIR)%,%,$(@D))
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -MMD -MF $(DEPDIR)$(patsubst $(BUILDDIR)%,%,$@).d -o $@ 

.PHONY: clean
clean:
	rm -rf build bin deps

include core/core.mk
-include $(shell find $(DEPDIR) -name "*.d" 2>/dev/null)