### TARGETS
.PHONY: format
format: ## Format all code files
	$(info )
	$(info === Format code ===)
	clang-format -i `find $(SRC_DIR) $(TEST_DIR) -name '*.$(SRC_EXT)' -o -name '*.$(HDR_EXT)'`

