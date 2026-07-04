.PHONY: debug
debug: ## Debug build config (default)
	$(info )
	$(info === Build app/debug ===)
	@$(MAKE) BINARY=app BUILD=debug build
