#######################################
# UTILITY
#######################################

fn_rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call fn_rwildcard,$d,$2)$(filter $(subst *,%,$2),$d)) # Trailing space required
fn_files    = $(sort $(call fn_rwildcard,$1,$2))
fn_dirs     = $(sort $(dir $(call fn_rwildcard,$1,*)))

#######################################
# CORE CONFIG 
#######################################

# Commands
RM       := rm -rf
MKDIR    := mkdir -p

# Directories
SRC_DIR  := src
EXT_DIR  := external
BIN_DIR  := bin
OBJ_DIR  := build

# File extentions
SRC_EXT  := c
HDR_EXT  := h
OBJ_EXT  := o
DEP_EXT  := d

# Flags
MAKEFLAGS := --no-print-directory


#######################################
# PROJECT CONFIG 
#######################################

# Target platform ( unix | TM4C123G )
TARGET ?= unix
# Binary mode ( app | test )
MODE   ?= app
# Build config ( fatal | debug | release )
BUILD  ?= fatal
# Backend ( ncurses | raylib )
BACKEND ?= ncurses

# Compiler & toolchain
CC := clang
LD := $(CC)

# Entrypoint files
MAIN_app  := main

BIN_app  := $(MAIN_app)

# Libraries
LIBS_CORE :=

# External includes
EXT_INC_DIR :=
EXT_SRC_DIR :=

# Core flags
CFLAGS_CORE   := -std=c99
CPPFLAGS_CORE := -MMD -MP
LDFLAGS_CORE  :=

# Build-specific flags
CFLAGS_debug     := -g -O0 -Wall -Wextra -Wshadow # -fsanitize=address,undefined
CPPFLAGS_debug   := -DDEBUG
LDFLAGS_debug    := # -fsanitize=address,undefined
CPPCHECK_debug   := --error-exitcode=0

CFLAGS_fatal     := -g -O0 -Wall -Wextra -Wshadow -Wpedantic -Werror -Wfatal-errors # -fsanitize=address,undefined
CPPFLAGS_fatal   := -DDEBUG
LDFLAGS_fatal    := # -fsanitize=address,undefined
CPPCHECK_fatal   := --error-exitcode=1

CFLAGS_release   := -Os
CPPFLAGS_release := -DNDEBUG
LDFLAGS_release  :=

# Targets
.PHONY: all ## Default make target
all: compiledb build test cppcheck


#######################################
# AUTOMATIC VARIABLES
#######################################

# Sources
SRCS_app  := $(call fn_files,$(SRC_DIR),*.$(SRC_EXT))

# Includes
INC_app  := $(call fn_dirs,$(SRC_DIR))


#######################################
# MODULE: NCURSES
#######################################

LIBS_ncurses := ncurses

CPPFLAGS_ncurses   := -DBACKEND_NCURSES

#######################################
# MODULE: TEST
#######################################

# include $(MAKE_DIR)/test.mk

# Directories
TEST_DIR := test

# Entrypoint files
MAIN_test := test
BIN_test  := $(MAIN_test)

# External includes
EXT_INC_DIR += $(EXT_DIR)/Unity/src
EXT_SRC_DIR += $(EXT_DIR)/Unity/src

# Sources
SRCS_test := $(filter-out $(SRC_DIR)/$(MAIN_app).$(SRC_EXT),$(SRCS_app)) \
             $(call fn_files,$(TEST_DIR),*.$(SRC_EXT)) \
             $(call fn_files,$(EXT_SRC_DIR),*.$(SRC_EXT)) 

# Includes
INC_test := $(call fn_dirs,$(SRC_DIR)) \
            $(call fn_dirs,$(TEST_DIR))

# Targets
.PHONY: build-test
build-test: ## Build tests
	@$(MAKE) BUILD=debug MODE=test build

.PHONY: run-test
run-test: ## Run tests
	@$(MAKE) BUILD=debug MODE=test run

.PHONY: test
test: build-test run-test ## Build and run tests


#######################################
# DEPENDENT VARIABLES
#######################################

# Build config
BUILD_CONFIG := $(TARGET)/$(MODE)/$(BACKEND)/$(BUILD)

# Objects and dependencies
OBJROOT := $(OBJ_DIR)/$(BUILD_CONFIG)
OBJS    := $(patsubst %.$(SRC_EXT),$(OBJROOT)/%.$(OBJ_EXT),$(SRCS_$(MODE)))
DEPS    := $(OBJS:.$(OBJ_EXT)=.$(DEP_EXT))

# Flags
CFLAGS   := $(CFLAGS_CORE) $(CFLAGS_$(BUILD))
CPPFLAGS := $(CPPFLAGS_CORE) $(CPPFLAGS_$(BUILD)) $(CPPFLAGS_$(BACKEND))
LIBS 	 := $(LIBS_CORE) $(LIBS_$(BACKEND))
LDLIBS   := $(addprefix -l,$(LIBS))
LDFLAGS  := $(LDFLAGS_CORE) $(LDFLAGS_$(BUILD))
INCFLAGS += $(addprefix -I,$(INC_$(MODE)))
INCFLAGS += $(addprefix -isystem,$(EXT_INC_DIR))


#######################################
# TARGETS
#######################################

.PHONY: build 
build: $(BIN_DIR)/$(BIN_$(MODE)) ## Build binary

.PHONY: clean 
clean: ## Delete binary and object files
	$(info )
	$(info === Clean ===)
	$(RM) $(OBJ_DIR) $(BIN_DIR)

.PHONY: cppcheck 
cppcheck: ## Static code checking
	$(info )
	$(info === Run cppcheck: BUILD=$(BUILD) ===)
	@$(MKDIR) $(OBJ_DIR)/cppcheck
	@cppcheck \
	  --quiet \
	  --enable=all \
	  --suppress=missingIncludeSystem \
	  --suppress=unmatchedSuppression \
	  --suppress=missingInclude \
	  --inconclusive \
	  --check-level=exhaustive \
	  $(CPPCHECK_$(BUILD)) \
	  --cppcheck-build-dir=$(OBJ_DIR)/cppcheck \
	  --template=gcc \
	  --std=c99 \
	  -i $(EXT_DIR)/ \
	  -i $(TEST_DIR)/ \
	  $(SRC_DIR) \

.PHONY: compiledb
compiledb: ## Build compile_command.json
	$(info )
	$(info === Build compilation database ===)
	compiledb -n make

.PHONY: debug
debug: ## Debug build config
	$(info )
	$(info === Build app/debug ===)
	@$(MAKE) BUILD=debug MODE=app build

.PHONY: doxygen 
doxygen: ## Build doxygen documentation
	$(info )
	$(info === Create documentation ===)
	doxygen Doxyfile

.PHONY: fatal
fatal: ## Pedantic debug build, abort on first error
	$(info )
	$(info === Build app/fatal ===)
	@$(MAKE) BUILD=fatal MODE=app build

.PHONY: format
format: ## Format all code files
	$(info )
	$(info === Format code ===)
	clang-format -i `find $(SRC_DIR) $(TEST_DIR) -name '*.$(SRC_EXT)' -o -name '*.$(HDR_EXT)'`

.PHONY: help
help: ## Show this help message
	@grep --no-filename -E '^[a-zA-Z_-]+:.*?##.*$$' $(MAKEFILE_LIST) | awk 'BEGIN { \
	 FS = ":.*?## "; \
	 printf "\033[1m%-30s\033[0m %s\n", "TARGET", "DESCRIPTION" \
	} \
	{ printf "\033[32m%-30s\033[0m %s\n", $$1, $$2 }'

.PHONY: init
init: ## Setup project: Update submodules
	$(info )
	$(info === Update git submodules ===)
	@git submodule update --init --recursive

.PHONY: publish
publish: ## Build fatal, static checker and release configs
	$(info )
	$(info === Publish ===)
	@$(MAKE) fatal
	@$(MAKE) BUILD=fatal cppcheck
	@$(MAKE) release

.PHONY: release
release: ## Build release config
	$(info )
	$(info === Build app/release ===)
	@$(MAKE) BUILD=release MODE=app build

.PHONY: run
run: ## Run binary
	$(info )
	$(info === Execute $(BIN_$(MODE)) ===)
	$(BIN_DIR)/$(BIN_$(MODE))


#######################################
# RULES
#######################################

# === COMPILER COMMAND ===
$(OBJROOT)/%.$(OBJ_EXT): %.$(SRC_EXT)
	$(info )
	$(info === Compile: TARGET=$(TARGET), MODE=$(MODE), BUILD=$(BUILD) ===)
	@$(MKDIR) $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS) $(CPPFLAGS) $(INCFLAGS)

# === LINKER COMMAND ===
$(BIN_DIR)/$(BIN_$(MODE)): $(OBJS)
	$(info )
	$(info === Link: TARGET=$(TARGET), MODE=$(MODE), BUILD=$(BUILD) ===)
	@$(MKDIR) $(dir $@)
	$(LD) $^ -o $@ $(LDFLAGS) $(LDLIBS)


#######################################
# DEPENDENCIES
#######################################

-include $(DEPS)

