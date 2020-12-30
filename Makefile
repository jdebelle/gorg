

browser := $(shell grep BROWSER MAKE-CONFIG.txt | sed -r "s/BROWSER\s*=\s*(.*)/\1/")










.PHONY: cli					# Build the gorg CLI binaries
cli: 
	mkdir -p gorg-cli/build
	cd gorg-cli/build ; cmake .. ; cmake --build .

.PHONY: clean-cli			# Clean the gorg CLI binaries
clean-cli:
	rm -rf gorg-cli/build
	rm -rf gorg-cli/out
	rm -rf gorg-cli/bin






.PHONY: docs				# Build Documentation for the Project
docs: gorg-docs/_build/html/index.html
	$(browser) gorg-docs/_build/html/index.html
gorg-docs/_build/html/index.html: $(shell find gorg-docs -name *.rst)
	cd gorg-docs ; make html

.PHONY: clean-docs			# Clean the Generated Documentation
clean-docs:
	rm -rf gorg-docs/_build/*


.PHONY: help				# Print the help text
help:
	@grep "^.PHONY:" Makefile | sed -r "s/.PHONY:\s*(\S*)\s*#\s*(.*)/\1\t\2/" | expand -t 30

