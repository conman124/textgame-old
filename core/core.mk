DIR=core/

$(BINDIR)game: LDLIBS=-lpthread
$(BINDIR)game: $(patsubst $(DIR)%.cpp,$(BUILDDIR)$(DIR)%.o,$(wildcard $(DIR)*.cpp))
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LOADLIBES) $(LDLIBS)