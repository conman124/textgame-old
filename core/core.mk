DIR=core/

$(BINDIR)game: LDLIBS=-lpthread -lcommands
$(BINDIR)game: $(patsubst $(DIR)%.cpp,$(BUILDDIR)$(DIR)%.o,$(wildcard $(DIR)*.cpp)) $(BUILDDIR)core/commands/libcommands.a
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LOADLIBES) $(LDLIBS)

include $(DIR)/commands/commands.mk
