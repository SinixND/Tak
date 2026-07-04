### DEFAULT BUILD CONFIG
### Target platform ( default: unix | TM4C123G )
PLATFORM ?= unix
### Binary mode ( default: app | test )
BINARY   ?= app
### Backends ( ncurses | raylib )
BACKEND  ?= raylib
### Build mode ( default: debug | release | fatal )
BUILD    ?= fatal

### Targets
.PHONY: all ## Default make target
all: compiledb build test cppcheck

.PHONY: publish
publish: ## Build fatal, cppcheck and release targets
	$(info )
	$(info === Publish ===)
	@$(MAKE) fatal
	@$(MAKE) BUILD=fatal cppcheck
	@$(MAKE) release

### Include makefiles
include make/project.mk
include make/helper.mk
include make/host.mk
include make/flags.mk

include make/platform/$(PLATFORM).mk
include make/binary/$(BINARY).mk
include make/build/$(BUILD).mk
include make/backend/$(BACKEND).mk

include make/targets/core.mk
include make/targets/debug.mk
include make/targets/release.mk
include make/targets/fatal.mk
include make/targets/test.mk
include make/targets/clangformat.mk
include make/targets/compiledb.mk
include make/targets/cppcheck.mk
include make/targets/doxygen.mk

include make/derived.mk

include make/rules.mk

-include $(DEPS)

