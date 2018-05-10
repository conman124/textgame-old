DIR=core/commands/

$(BUILDDIR)$(DIR)libcommands.a: $(patsubst $(DIR)%.cpp,$(BUILDDIR)$(DIR)%.o,$(wildcard $(DIR)*.cpp))
	@mkdir -p $(@D)
	$(AR) rcs $@ $^

LDFLAGS += -L$(BUILDDIR)$(DIR)