### TARGETS
.PHONY: doxygen 
doxygen: ## Build doxygen documentation
	$(info )
	$(info === Create documentation ===)
	doxygen Doxyfile

