### Directories
TEST_DIR     := test
EXT_INC_DIRS += $(EXT_DIR)/Unity/src

include make/helper.mk

### Sources
local_EXT_SRC_DIR := $(EXT_DIR)/Unity/src

SRCS              := $(call fn_files,$(SRC_DIR),*.$(SRC_EXT))
SRCS              := $(filter-out $(SRC_DIR)/$(MAIN).$(SRC_EXT),$(SRCS)) \
                        $(call fn_files,$(TEST_DIR),*.$(SRC_EXT)) \
                        $(call fn_files,$(local_EXT_SRC_DIR),*.c) 

### Includes
INC_DIRS          := $(call fn_dirs,$(SRC_DIR)) \
                        $(call fn_dirs,$(TEST_DIR))

EXT_INC_DIRS      += $(local_EXT_SRC_DIR)
