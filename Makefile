#######################################
### PROJECT CONFIG 
#######################################

### DEFAULT BUILD CONFIG
### Target platform ( default: unix | TM4C123G )
PLATFORM ?= unix
### Binary mode ( default: app | test )
TARGET   ?= app
### Backends ( default: noBackend | ncurses | raylib )
BACKEND  ?= ncurses
### Build mode ( default: core | release | debug | fatal )
BUILD    ?= fatal

### Entrypoint files
MAIN_app  := main

### Flags
MAKEFLAGS := --no-print-directory

CFLAGS_core   := -std=c99
CPPFLAGS_core := -MMD -MP
LDFLAGS_core  :=

### Targets
.PHONY: all ## Default make target
all: compiledb build test cppcheck

### Directories
SRC_DIR := src
BIN_DIR := bin
OBJ_DIR := build
EXT_DIR := external

### File extentions
SRC_EXT := c
HDR_EXT := h
OBJ_EXT := o
DEP_EXT := d

#######################################
### AUTOMATIC VARIABLES
#######################################

### Helper functions
fn_rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call fn_rwildcard,$d,$2)$(filter $(subst *,%,$2),$d)) # Trailing space required
fn_files     = $(sort $(call fn_rwildcard,$1,$2))
fn_dirs      = $(sort $(dir $(call fn_rwildcard,$1,*)))

### Sources
SRCS_app  := $(call fn_files,$(SRC_DIR),*.$(SRC_EXT))

### Includes
INC_DIRS_core  := $(call fn_dirs,$(SRC_DIR))


#######################################
### HOST SYSTEM CONFIG 
#######################################

### Commands
RM    := rm -rf
MKDIR := mkdir -p


#######################################
### BUILD MODES
#######################################

### RELEASE

### Flags
CFLAGS_release   := -Os
CPPFLAGS_release := -DNDEBUG
LDFLAGS_release  :=

### DEBUG

### Flags
CFLAGS_debug     := -g -O0 -Wall -Wextra -Wshadow # -fsanitize=address,undefined
CPPFLAGS_debug   := -DDEBUG
LDFLAGS_debug    := # -fsanitize=address,undefined
CPPCHECK_debug   := --error-exitcode=0

### FATAL

### Flags
CFLAGS_fatal     := -g -O0 -Wall -Wextra -Wshadow -Wpedantic -Werror -Wfatal-errors # -fsanitize=address,undefined
CPPFLAGS_fatal   := -DDEBUG
LDFLAGS_fatal    := # -fsanitize=address,undefined
CPPCHECK_fatal   := --error-exitcode=1


#######################################
### PLATFORMS
#######################################

### UNIX

CC_unix := clang
LD_unix := clang

CPPFLAGS_unix   := -DPLATFORM_UNIX

#######################################
### TARGETS
#######################################

### TEST

### Directories
TEST_DIR := test

### Entrypoint file
MAIN_test := test

### External includes
EXT_SRC_DIR_test := $(EXT_DIR)/Unity/src
EXT_INC_DIR_test := $(EXT_DIR)/Unity/src

### Sources
SRCS_test := $(filter-out $(SRC_DIR)/$(MAIN_app).$(SRC_EXT),$(SRCS_app)) \
             $(call fn_files,$(TEST_DIR),*.$(SRC_EXT)) \
             $(call fn_files,$(EXT_SRC_DIR_test),*.c) 

### Includes
INC_DIRS_test := $(call fn_dirs,$(SRC_DIR)) \
            $(call fn_dirs,$(TEST_DIR))

### Targets
.PHONY: test-build
test-build: ## Build tests
	@$(MAKE) TARGET=test BUILD=debug build

.PHONY: test-run
test-run: ## Run tests
	@$(MAKE) TARGET=test BUILD=debug run

.PHONY: test
test: test-build test-run ## Build and run tests


#######################################
### BACKENDS
#######################################

### RAYLIB

RAYLIB_SRC_DIR     := /usr/lib/raylib/src

LIBS_raylib        := raylib
LIB_DIR_raylib    := $(RAYLIB_SRC_DIR)
CPPFLAGS_raylib    := -DBACKEND_RAYLIB
EXT_INC_DIR_raylib := $(RAYLIB_SRC_DIR)

### NCURSES

### Libraries
LIBS_ncurses := ncurses

### Flags
CPPFLAGS_ncurses := -DBACKEND_NCURSES


#######################################
### DERIVED VARIABLES
#######################################

### Build config
CONFIG_PATH := $(PLATFORM)/$(TARGET)/$(BACKEND)/$(BUILD)

### Objects and dependencies
BUILD_DIR := $(OBJ_DIR)/$(CONFIG_PATH)
OBJS      := $(patsubst %.$(SRC_EXT),$(BUILD_DIR)/%.$(OBJ_EXT),$(SRCS_$(TARGET)))
DEPS      := $(OBJS:.$(OBJ_EXT)=.$(DEP_EXT))

### Flags
CFLAGS    := $(CFLAGS_core) $(CFLAGS_$(BUILD))
CPPFLAGS  := $(CPPFLAGS_core) $(CPPFLAGS_$(BUILD)) $(CPPFLAGS_$(BACKEND)) $(CPPFLAGS_$(PLATFORM))

LIBS 	  := $(LIBS_$(BACKEND))
LDLIBS    := $(addprefix -l,$(LIBS))
LIB_DIRS  := $(LIB_DIR_$(BACKEND))
LIB_FLAGS := $(addprefix -L,$(LIB_DIRS))
LDFLAGS   := $(LDFLAGS_core) $(LDFLAGS_$(BUILD))

INCFLAGS  += $(addprefix -I,$(INC_DIRS_core) $(INC_DIRS_$(TARGET)))
INCFLAGS  += $(addprefix -isystem,$(EXT_INC_DIR_$(TARGET)) $(EXT_INC_DIR_$(BACKEND)))


#######################################
### TARGETS
#######################################

.PHONY: build 
build: $(BIN_DIR)/$(TARGET) ## Build binary

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
debug: ## Debug build config (default)
	$(info )
	$(info === Build app/debug ===)
	@$(MAKE) TARGET=app BUILD=debug build

.PHONY: doxygen 
doxygen: ## Build doxygen documentation
	$(info )
	$(info === Create documentation ===)
	doxygen Doxyfile

.PHONY: fatal
fatal: ## Debug build config (pedantic, fatal)
	$(info )
	$(info === Build app/fatal ===)
	@$(MAKE) TARGET=app BUILD=fatal build

.PHONY: format
format: ## Format all code files
	$(info )
	$(info === Format code ===)
	clang-format -i `find $(SRC_DIR) $(TEST_DIR) -name '*.$(SRC_EXT)' -o -name '*.$(HDR_EXT)'`

.PHONY: publish
publish: ## Build fatal, cppcheck and release targets
	$(info )
	$(info === Publish ===)
	@$(MAKE) fatal
	@$(MAKE) BUILD=fatal cppcheck
	@$(MAKE) release

.PHONY: release
release: ## Build config
	$(info )
	$(info === Build app/release ===)
	@$(MAKE) TARGET=app BUILD=release build

.PHONY: run
run: ## Run binary
	$(info )
	$(info === Execute $(TARGET) ===)
	$(BIN_DIR)/$(TARGET)

#######################################
### RULES
#######################################

### === COMPILER COMMAND ===
$(BUILD_DIR)/%.$(OBJ_EXT): %.$(SRC_EXT)
	$(info )
	$(info === Compile: PLATFORM=$(PLATFORM), TARGET=$(TARGET), BUILD=$(BUILD) ===)
	@$(MKDIR) $(dir $@)
	$(CC_$(PLATFORM)) -c $< -o $@ $(CFLAGS) $(CPPFLAGS) $(INCFLAGS)

### === LINKER COMMAND ===
$(BIN_DIR)/$(TARGET): $(OBJS)
	$(info )
	$(info === Link: PLATFORM=$(PLATFORM), TARGET=$(TARGET), BUILD=$(BUILD) ===)
	@$(MKDIR) $(dir $@)
	$(LD_$(PLATFORM)) $^ -o $@ $(LDFLAGS) $(LIB_FLAGS) $(LDLIBS)


#######################################
### DEPENDENCIES
#######################################

-include $(DEPS)

#######################################
### MISC
#######################################

# Put to bottom due to syntax highlight issues
.PHONY: help
help: ## Show this help message
	@grep --no-filename -E '^[a-zA-Z_-]+:.*?##.*$$' $(MAKEFILE_LIST) | awk 'BEGIN { \
	   FS = ":.*?## "; \
	   printf "\033[1m%-30s\033[0m %s\n", "TARGET", "DESCRIPTION" \
	} \
	{ printf "\033[32m%-30s\033[0m %s\n", $$1, $$2 }'


