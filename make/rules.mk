### === COMPILER COMMAND ===
$(BUILD_DIR)/%.$(OBJ_EXT): %.$(SRC_EXT)
	$(info )
	$(info === Compile: PLATFORM=$(PLATFORM), BINARY=$(BINARY), BUILD=$(BUILD) ===)
	@$(MKDIR) $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS) $(CPPFLAGS) $(INCFLAGS)

### === LINKER COMMAND ===
$(BIN_DIR)/$(BINARY): $(OBJS)
	$(info )
	$(info === Link: PLATFORM=$(PLATFORM), BINARY=$(BINARY), BUILD=$(BUILD) ===)
	@$(MKDIR) $(dir $@)
	$(LD) $^ -o $@ $(LDFLAGS) $(LIB_FLAGS) $(LDLIBS)

