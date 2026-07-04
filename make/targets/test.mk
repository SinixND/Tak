.PHONY: test-build
test-build: ## Build tests
	@$(MAKE) BINARY=test BUILD=debug build

.PHONY: test-run
test-run: ## Run tests
	@$(MAKE) BINARY=test BUILD=debug run

.PHONY: test
test: test-build test-run ## Build and run tests

