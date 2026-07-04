include make/helper.mk

### Sources
SRCS := $(call fn_files,$(SRC_DIR),*.$(SRC_EXT))

### Includes
INC_DIRS := $(call fn_dirs,$(SRC_DIR))

