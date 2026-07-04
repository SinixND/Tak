### TARGETS
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

