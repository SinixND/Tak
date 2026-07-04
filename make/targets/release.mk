.PHONY: release
release: ## Build config
	$(info )
	$(info === Build app/release ===)
	@$(MAKE) BINARY=app BUILD=release build

