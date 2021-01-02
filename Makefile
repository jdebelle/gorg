

browser := $(shell grep BROWSER MAKE-CONFIG.txt | sed -r "s/\S*\s*=\s*(.*)/\1/")
install_path := $(shell grep INSTALL_PATH MAKE-CONFIG.txt | sed -r "s/\S*\s*=\s*(.*)/\1/")
version := 0.0.0
index_template_output := gorg-index-template/bin/template.html
index_template_dependencies := gorg-index-template/template.html
index_template_dependencies += $(shell find gorg-index-template/js)
index_template_dependencies += $(shell find gorg-index-template/css)
cli_dependencies := gorg-cli/templates/gorgindex.html.template
cli_dependencies += $(shell find gorg-cli/src -name *.cpp -o -name *.h -o -name *.hpp)
cli_dependencies += $(shell find gorg-cli/inc -name *.cpp -o -name *.h -o -name *.hpp)




.PHONY: index-template
index-template: gorg-index-template/bin/template.html
gorg-index-template/bin/template.html: $(index_template_dependencies)
	rm -rf gorg-index-template/bin
	mkdir -p gorg-index-template/bin
	cd gorg-index-template ; cat template.html | sed -r "s/(.*)assets-mockup.js(.*)/\1assets.js\2/" | inliner -n > template.html.out
	mv gorg-index-template/template.html.out $(index_template_output)
	

gorg-cli/templates/gorgindex.html.template: gorg-index-template/bin/template.html
	rm gorg-cli/templates/gorgindex.html.template
	cp $(index_template_output) gorg-cli/templates/gorgindex.html.template

.PHONY: cli					# Build the gorg CLI binaries
cli: gorg-cli/bin/gorg.exe
gorg-cli/bin/gorg.exe: $(cli_dependencies)
	mkdir -p gorg-cli/build
	cd gorg-cli/build ; cmake .. ; cmake --build .
	

.PHONY: clean-cli			# Clean the gorg CLI binaries
clean-cli:
	rm -rf gorg-cli/build
	rm -rf gorg-cli/out
	rm -rf gorg-cli/bin


.PHONY: install				# Install gorg to the specified path
install: gorg-cli/bin/gorg.exe
	mkdir -p "$(install_path)"
	rm -rf "$(install_path)/bin/"
	rm -rf "$(install_path)/templates/"
	cp -r gorg-cli/bin/ "$(install_path)/bin/"
	cp -r gorg-cli/templates/ "$(install_path)/templates/"


.PHONY: docs				# Build Documentation for the Project
docs: gorg-docs/_build/html/index.html
	"$(browser)" gorg-docs/_build/html/index.html
gorg-docs/_build/html/index.html: $(shell find gorg-docs -name *.rst)
	cd gorg-docs ; make html

.PHONY: clean-docs			# Clean the Generated Documentation
clean-docs:
	rm -rf gorg-docs/_build/*


.PHONY: help				# Print the help text
help:
	@grep "^.PHONY:" Makefile | sed -r "s/.PHONY:\s*(\S*)\s*#\s*(.*)/\1\t\2/" | expand -t 30

