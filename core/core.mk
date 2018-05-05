DIR=core/

$(BINDIR)game: LDLIBS=-lpthread
$(BINDIR)game: $(patsubst $(DIR)%.cpp,$(BUILDDIR)$(DIR)%.o,$(wildcard $(DIR)*.cpp))
	$(CXX) $(LDFLAGS) $^ -o $@ $(LOADLIBES) $(LDLIBS)