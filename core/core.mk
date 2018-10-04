DIR=core/

$(BINDIR)game: LDLIBS=-lcommands -litems
$(BINDIR)game: $(patsubst $(DIR)%.cpp,$(BUILDDIR)$(DIR)%.o,$(wildcard $(DIR)*.cpp)) $(BUILDDIR)core/commands/libcommands.a $(BUILDDIR)core/items/libitems.a
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LOADLIBES) $(LDLIBS)

include $(DIR)/commands/commands.mk
include $(DIR)/items/items.mk
