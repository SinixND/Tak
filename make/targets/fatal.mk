.PHONY: fatal
fatal: ## Debug build config (pedantic, fatal)
	$(info )
	$(info === Build app/fatal ===)
	@$(MAKE) BINARY=app BUILD=fatal build
