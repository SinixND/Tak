#######################################
### CORE
#######################################
RM 				:= rm -rf
MKDIR 			:= mkdir -p
CP 				:= cp -r

BIN 			:= main

MAKEFLAGS 		:= --no-print-directory

BIN_DIR 		:= bin
OBJ_DIR 		:= build
SRC_DIR 		:= src
EXTERN_DIR		:= external
EXTRA_DIR		:= extras
# LIB_DIR 		:= lib
# INC_DIR 		:= include
DATA_DIR 		:= data
TEST_DIR 		:= tests
DOCS_DIR 		:= docs
WEB_DIR 		:= web
TOOLS_DIR		:= tools

BIN_EXT 		:=
SRC_EXT 		:= .c


#######################################
### DEFAULTS
#######################################
# Options: debug release
BUILD 			:= debug
# Options: unix web
TARGET 			:= unix
FATAL 			:= false


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
### EXTERNAL
#######################################
LIBRARIES 		:= ncurses
INC_DIRS_SYS	+= $(EXTERN_DIR)

# ncurses
# INC_DIRS_SYS 	+= $(EXTERN_DIR)/ncurses/include
# LIB_DIRS 		+= $(EXTERN_DIR)/ncurses/lib


### raylib
# RAYLIB_DIR 		:= $(EXTERN_DIR)/raylib/src
# INC_DIRS_SYS 	+= $(RAYLIB_DIR)
# LIB_DIRS 		+=  $(RAYLIB_DIR)$(EXTRA_DIR)/raylib/$(TARGET)/$(BUILD)
#
# # catch2
#
# # emscripten
# ifeq ($(TARGET),web)
# LDLIBS 			+= --preload-file $(DATA_DIR)/ -sUSE_GLFW=3
# ifeq ($(BUILD),debug)
# LDLIBS 			+= --shell-file $(RAYLIB_DIR)/shell.html
# else
# LDLIBS 			+= --shell-file $(RAYLIB_DIR)/minshell.html
# endif
# endif


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

ifeq ($(FATAL),true)
CFLAGS 			+= -Wfatal-errors
endif


#######################################
### TARGET PLATFORM
#######################################
### WEB/EMSCRIPTEN
ifeq ($(TARGET),web)
CC 				:= emcc
CFLAGS			+= -Os
CPPFLAGS		+= -DEMSCRIPTEN -DPLATFORM_WEB
BIN_EXT			:= .html
USR_DIR			:=
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
ifneq ($(INC_DIR),)
INC_DIRS 		+= $(shell find $(INC_DIR) -type d)
endif

INC_DIRS_SYS	+= $(patsubst %,%/include,$(USR_DIRS))
INC_DIRS_SYS	+= $(LIB_DIRS)
# ifneq ($(EXTERN_DIR),)
# INC_DIRS 		+= $(shell find $(EXTERN_DIR) -type d)
# endif

INCFLAGS 		:= $(addprefix -I,$(INC_DIRS))
INCFLAGS 		+= $(addprefix -isystem,$(INC_DIRS_SYS))
LDFLAGS 		:= $(addprefix -L,$(LIB_DIRS))
LDLIBS 			+= $(addprefix -l,$(LIBRARIES))


#######################################
### TARGETS
#######################################
.PHONY: test all cppcheck build compiledb clean docker debug doxygen format host setup publish release run tests web

test: clean format doxygen compiledb cppcheck debug release web publish tests run host

all: debug release

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

build: $(BIN_DIR)/$(TARGET)/$(BUILD)/$(BIN)$(BIN_EXT)

compiledb:
	$(info )
	$(info === Build compile_commands.json ===)
	@compiledb -n make

clean:
	$(info )
	$(info === CLEAN ===)
	$(RM) $(OBJ_DIR)/* $(BIN_DIR)/*

debug: compiledb
	@$(MAKE) BUILD=debug build
	@$(MAKE) cppcheck

docker:
	docker run -it --rm tak:container

doxygen:
	doxygen Doxyfile

format:
	clang-format -i -- src/**

host:
	http-server -o . -c-1

setup:
	@$(TOOLS_DIR)/setup

publish:
	@$(MAKE) debug release web

release:
	@$(MAKE) BUILD=release build

run:
	$(BIN_DIR)/$(TARGET)/$(BUILD)/$(BIN)$(BIN_EXT)

tests:

web:
	@$(MKDIR) $(WEB_DIR)
	@$(MAKE) BUILD=release TARGET=web build
	@$(CP) $(BIN_DIR)/web/release/* $(WEB_DIR)


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
