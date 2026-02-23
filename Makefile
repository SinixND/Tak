#######################################
# CORE CONFIG 
#######################################

# Commands
RM        := rm -rf
MKDIR     := mkdir -p

# Directories
SRC_DIR  := src
EXT_DIR  := external
BIN_DIR  := bin
OBJ_DIR  := build
MAKE_DIR := tools/make

# File extentions
SRC_EXT  := c
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
# Build config ( debug | release )
BUILD  ?= debug

# Compiler & toolchain
CC := clang
LD := $(CC)

# Entrypoint files
MAIN_app  := main

BIN_app  := $(MAIN_app)

# Libraries
LDLIBS_CORE :=

# External includes
EXT_INC_DIR :=
EXT_SRC_DIR :=

# Core flags
CFLAGS_CORE   := -std=c99
CPPFLAGS_CORE := -MMD -MP
LDFLAGS_CORE  :=

# Build-specific flags
CFLAGS_debug     := -g -O0 -Wall -Wextra -Wshadow -Wpedantic -Werror # -fsanitize=address,undefined
CPPFLAGS_debug   := -DDEBUG
LDFLAGS_debug    := # -fsanitize=address,undefined

CFLAGS_fatal     := -g -O0 -Wall -Wextra -Wshadow -Wpedantic -Werror -Wfatal-errors # -fsanitize=address,undefined
CPPFLAGS_fatal   := -DDEBUG
LDFLAGS_fatal    := # -fsanitize=address,undefined

CFLAGS_release   := -O2
CPPFLAGS_release := -DNDEBUG
LDFLAGS_release  :=

# Targets
all: compiledb debug test cppcheck run-test run

# To test all targets
checkhealth: clean doxygen format compiledb fatal debug release test cppcheck run-test run


#######################################
# AUTOMATIC VARIABLES
#######################################

# Sources
SRCS_app  := $(shell find $(SRC_DIR) -name '*.$(SRC_EXT)')

# Includes
INC_app  := $(shell find $(SRC_DIR) -type d)


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
             $(shell find $(TEST_DIR) -name '*.$(SRC_EXT)') \
             $(shell find $(EXT_SRC_DIR) -name '*.$(SRC_EXT)') 

# Includes
INC_test := $(shell find $(SRC_DIR) -type d) \
            $(shell find $(TEST_DIR) -type d)

# Targets
.PHONY: test

test:
	@$(MAKE) MODE=test build

run-test:
	@$(MAKE) MODE=test run


#######################################
# DEPENDENT VARIABLES
#######################################

# Objects and dependencies
OBJROOT := $(OBJ_DIR)/$(TARGET)/$(MODE)/$(BUILD)
OBJS    := $(patsubst %.$(SRC_EXT),$(OBJROOT)/%.$(OBJ_EXT),$(SRCS_$(MODE)))
DEPS    := $(OBJS:.$(OBJ_EXT)=.$(DEP_EXT))

# Flags
CFLAGS   := $(CFLAGS_CORE) $(CFLAGS_$(BUILD))
CPPFLAGS := $(CPPFLAGS_CORE) $(CPPFLAGS_$(BUILD))
LDLIBS   := $(LDLIBS_CORE)
LDFLAGS  := $(LDFLAGS_CORE) $(LDFLAGS_$(BUILD))
INCFLAGS += $(addprefix -I,$(INC_$(MODE)))
INCFLAGS += $(addprefix -isystem,$(EXT_INC_DIR))


#######################################
# TARGETS
#######################################

build: $(BIN_DIR)/$(TARGET)/$(MODE)/$(BUILD)/$(BIN_$(MODE))

clean:
	$(info )
	$(info === Clean ===)
	$(RM) $(OBJ_DIR) $(BIN_DIR)

cppcheck:
	$(info )
	$(info === Run cppcheck ===)
	@$(MKDIR) $(OBJ_DIR)/cppcheck
	cppcheck \
	  --quiet \
	  --enable=all \
	  --suppress=missingIncludeSystem \
	  --suppress=unmatchedSuppression \
	  --suppress=missingInclude \
	  --inconclusive \
	  --check-level=exhaustive \
	  --error-exitcode=1 \
	  --cppcheck-build-dir=$(OBJ_DIR)/cppcheck \
	  --template=gcc \
	  --std=c99 \
	  -i $(EXT_DIR)/ \
	  -i $(TEST_DIR)/ \
	  $(SRC_DIR)/ \
	  $(BIN_DIR)/$(BIN_app)

compiledb:
	$(info )
	$(info === Build compilation database ===)
	compiledb -n make

debug:
	@$(MAKE) BUILD=debug MODE=app build

doxygen:
	$(info )
	$(info === Create documentation ===)
	doxygen Doxyfile

fatal:
	@$(MAKE) BUILD=fatal MODE=app build test

format:
	$(info )
	$(info === Format code ===)
	clang-format -i -- $(SRC_DIR)/**.* $(TEST_DIR)/**.*

init:
	$(info )
	$(info === Update git submodulds ===)
	@git submodule update --init --recursive

release:
	@$(MAKE) BUILD=release MODE=app build

run:
	$(info )
	$(info === Execute $(BIN_$(MODE)) ===)
	$(BIN_DIR)/$(TARGET)/$(MODE)/$(BUILD)/$(BIN_$(MODE))

.PHONY: all build checkhealth clean cppcheck compiledb debug doxygen fatal format init release run run-test


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
$(BIN_DIR)/$(TARGET)/$(MODE)/$(BUILD)/$(BIN_$(MODE)): $(OBJS)
	$(info )
	$(info === Link: TARGET=$(TARGET), MODE=$(MODE), BUILD=$(BUILD) ===)
	@$(MKDIR) $(dir $@)
	$(LD) $^ -o $@ $(LDFLAGS) $(LDLIBS)


#######################################
# DEPENDENCIES
#######################################

-include $(DEPS)

