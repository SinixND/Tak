### Build config
CONFIG_PATH := $(PLATFORM)/$(BINARY)/$(BACKEND)/$(BUILD)

### Objects and dependencies
BUILD_DIR := $(OBJ_DIR)/$(CONFIG_PATH)
OBJS      := $(patsubst %.$(SRC_EXT),$(BUILD_DIR)/%.$(OBJ_EXT),$(SRCS))
DEPS      := $(OBJS:.$(OBJ_EXT)=.$(DEP_EXT))

LDLIBS    := $(addprefix -l,$(LIBS))
LIB_FLAGS := $(addprefix -L,$(LIB_DIRS))

INCFLAGS  += $(addprefix -I,$(INC_DIRS))
INCFLAGS  += $(addprefix -isystem,$(EXT_INC_DIRS))


