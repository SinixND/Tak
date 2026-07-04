### Commands
RM    := rm -rf
MKDIR := mkdir -p

### Default host OS
OS ?= linux

ifdef TERMUX_VERSION
    OS	:= termux
endif

### Directories
ifeq ($(OS),termux)
    USR := $(PREFIX)
else
    USR := /usr
endif

LIB_DIRS     := $(USR)/lib
EXT_INC_DIRS := $(USR)/include
