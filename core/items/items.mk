_DIR=core/items/

$(BUILDDIR)$(_DIR)libitems.a: $(patsubst $(_DIR)%.cpp,$(BUILDDIR)$(_DIR)%.o,$(wildcard $(_DIR)*.cpp))
	@mkdir -p $(@D)
	$(AR) rcs $@ $^

LDFLAGS := $(LDFLAGS) -L$(BUILDDIR)$(_DIR)