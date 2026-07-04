.PHONY: build 
build: $(BIN_DIR)/$(BINARY) ## Build binary

.PHONY: clean 
clean: ## Delete binary and object files
	$(info )
	$(info === Clean ===)
	$(RM) $(OBJ_DIR) $(BIN_DIR)

.PHONY: run
run: ## Run binary
	$(info )
	$(info === Execute $(BINARY) ===)
	$(BIN_DIR)/$(BINARY)

# Put to bottom due to syntax highlight issues
.PHONY: help
help: ## Show this help message
	@grep --no-filename -E '^[a-zA-Z_-]+:.*?##.*$$' $(MAKEFILE_LIST) | awk 'BEGIN { \
	   FS = ":.*?## "; \
	   printf "\033[1m%-30s\033[0m %s\n", "TARGET", "DESCRIPTION" \
	} \
	{ printf "\033[32m%-30s\033[0m %s\n", $$1, $$2 }'

