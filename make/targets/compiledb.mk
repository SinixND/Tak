### TARGETS
.PHONY: compiledb
compiledb: ## Build compile_command.json
	$(info )
	$(info === Build compilation database ===)
	compiledb -n make

