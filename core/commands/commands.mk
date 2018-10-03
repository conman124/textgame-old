_DIR=core/commands/

$(BUILDDIR)$(_DIR)libcommands.a: $(patsubst $(_DIR)%.cpp,$(BUILDDIR)$(_DIR)%.o,$(wildcard $(_DIR)*.cpp))
	@mkdir -p $(@D)
	$(AR) rcs $@ $^

LDFLAGS := $(LDFLAGS) -L$(BUILDDIR)$(_DIR)