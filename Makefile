#######################################
### CORE
#######################################
RM 				:= rm -rf
MKDIR 			:= mkdir -p

BIN 			:= main

MAKEFLAGS 		:= --no-print-directory

BIN_DIR 		:= bin
OBJ_DIR 		:= build
SRC_DIR 		:= src

BIN_EXT 		:=
SRC_EXT 		:= .c


#######################################
### DEFAULTS
#######################################
# Options: debug release
BUILD 			:= debug
# Options: unix web
TARGET 			:= unix


#######################################
### HOST OS
#######################################
# Linux is default
CC 				:= clang
CFLAGS 			:= -MMD -MP -std=c99
# -MMD 				provides dependency information (header files) for make in .d files
# -pg 				ADD FOR gprof analysis TO BOTH COMPILE AND LINK COMMAND!!
# -MJ 				CLANG ONLY: compile-database
# -MP 				Multi-threaded compilation
# -Wfatal-errors 	Stop at first error

USR_DIR 		:= /usr

ifdef TERMUX_VERSION
CPPFLAGS 		+= -DTERMUX
USR_DIR 		:= $(PREFIX)
ifeq ($(TARGET),unix)
LIBRARIES 		+= log
endif
endif


#######################################
### BUILD CONFIGS
#######################################
ifeq ($(BUILD),debug)
CFLAGS 			+= -g -ggdb -O0 -Wall -Wextra -Wshadow -Werror -Wpedantic -pedantic-errors
CPPFLAGS 		+= -DDEBUG
endif

ifeq ($(BUILD),release)
CFLAGS 			+= -O2
CPPFLAGS 		+= -DNDEBUG
endif

#######################################
### Automatic variables
#######################################
SRCS 			:= $(foreach e,\
					$(shell find $(SRC_DIR) -type f),\
					$(filter $(addprefix %,$(SRC_EXT)),\
						$e))
OBJS 			:= $(SRCS:%=$(OBJ_DIR)/$(TARGET)/$(BUILD)/%.o)
DEPS 			:= $(OBJS:.o=.d)

USR_DIRS 		:= $(USR_DIR) $(patsubst %,%/local,$(USR_DIR))

LIB_DIRS 		+= $(patsubst %,%/lib,$(USR_DIRS))
ifneq ($(LIB_DIR),)
LIB_DIRS 		+= $(shell find $(LIB_DIR) -type d)
endif

INC_DIRS 		+= $(shell find $(SRC_DIR) -type d)

INC_DIRS_SYS	+= $(patsubst %,%/include,$(USR_DIRS))
INC_DIRS_SYS	+= $(LIB_DIRS)

INCFLAGS 		:= $(addprefix -I,$(INC_DIRS))
INCFLAGS 		+= $(addprefix -isystem,$(INC_DIRS_SYS))
LDFLAGS 		:= $(addprefix -L,$(LIB_DIRS))
LDLIBS 			+= $(addprefix -l,$(LIBRARIES))


#######################################
### TARGETS
#######################################
.PHONY: all build clean compiledb cppcheck debug doxygen format publish release run

all: debug
	@$(MAKE) run

build: $(BIN_DIR)/$(TARGET)/$(BUILD)/$(BIN)$(BIN_EXT)

clean:
	$(info )
	$(info === CLEAN ===)
	$(RM) $(OBJ_DIR)/* $(BIN_DIR)/*

compiledb:
	$(info )
	$(info === Build compile_commands.json ===)
	@compiledb -n make

cppcheck:
	@$(MKDIR) $(OBJ_DIR)/cppcheck
	@cppcheck \
		--quiet \
		--enable=all \
		--suppress=missingIncludeSystem \
		--suppress=missingInclude \
		--suppress=selfAssignment \
		--suppress=cstyleCast \
		--suppress=unmatchedSuppression \
		--inconclusive \
		--check-level=exhaustive \
		--error-exitcode=1 \
		--cppcheck-build-dir=$(OBJ_DIR)/cppcheck \
		--template=gcc \
		-I src/ \
		src/

debug: compiledb
	@$(MAKE) BUILD=debug build
	@$(MAKE) cppcheck

doxygen:
	doxygen Doxyfile

format:
	$(info === FORMAT CODE ===)
	@clang-format -i -- src/**

publish: format release cppcheck

release:
	@$(MAKE) BUILD=release build

run:
	$(BIN_DIR)/$(TARGET)/$(BUILD)/$(BIN)$(BIN_EXT)


#######################################
### Rules
#######################################
# === COMPILER COMMAND ===
$(OBJ_DIR)/$(TARGET)/$(BUILD)/%.c.o : %.c
	$(info )
	$(info === Compile: TARGET=$(TARGET), BUILD=$(BUILD) ===)
	@$(MKDIR) $(dir $@)
	$(CC) -o $@ -c $< $(CFLAGS) $(CPPFLAGS) $(INCFLAGS)


# === LINKER COMMAND ===
$(BIN_DIR)/$(TARGET)/$(BUILD)/$(BIN)$(BIN_EXT): $(OBJS)
	$(info )
	$(info === Link: TARGET=$(TARGET), BUILD=$(BUILD) ===)
	@$(MKDIR) $(dir $@)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)


### "-" surpresses error for initial missing .d files
-include $(DEPS)
