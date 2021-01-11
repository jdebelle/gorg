

browser := $(shell grep BROWSER MAKE-CONFIG.txt | sed -r "s/\S*\s*=\s*(.*)/\1/")
install_path := $(shell grep INSTALL_PATH MAKE-CONFIG.txt | sed -r "s/\S*\s*=\s*(.*)/\1/")
7zip := $(shell grep 7ZIP_PATH MAKE-CONFIG.txt | sed -r "s/\S*\s*=\s*(.*)/\1/")
candle := "$(shell grep WIX_CANDLE MAKE-CONFIG.txt | sed -r "s/\S*\s*=\s*(.*)/\1/")"
light := "$(shell grep WIX_LIGHT MAKE-CONFIG.txt | sed -r "s/\S*\s*=\s*(.*)/\1/")"
version := $(subst v,,$(shell git describe --tags --dirty))
version_pure := $(subst v,,$(shell git describe --tags | sed -r "s/v([0-9]+\.[0-9]+\.[0-9]+).*/\1/"))
index_template_output := gorg-index-template/build/template.html
index_template_dependencies := $(shell find gorg-index-template/src)
cli_dependencies := gorg-cli/templates/gorgindex.html.template
cli_dependencies += $(shell find gorg-cli/src -name *.cpp -o -name *.h -o -name *.hpp)
cli_dependencies += $(shell find gorg-cli/inc -name *.cpp -o -name *.h -o -name *.hpp)


.PHONY: index-template		# Build index template html file
index-template: gorg-index-template/build/template.html
gorg-index-template/build/template.html: $(index_template_dependencies)
	rm -rf gorg-index-template/build
	cd gorg-index-template ; npm run-script build 
	cd gorg-index-template/build; \
		cat index.html | inliner -n | sed -r "s/\"(\{\{\S*\}\})\"/\1/" > template.html

.PHONY: clean-index-template		# Clean the index template build folder
	

gorg-cli/templates/gorgindex.html.template: $(index_template_output)
	rm gorg-cli/templates/gorgindex.html.template
	cp $(index_template_output) gorg-cli/templates/gorgindex.html.template


.PHONY: cli-version			# Make the .h file that contains version information
cli-version: gorg-cli/inc/makefile.h.template
	cat gorg-cli/inc/makefile.h.template |\
		sed -r "s/\{\{VERSION_STRING\}\}/\"$(version)\"/" >\
		gorg-cli/inc/makefile.h

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
	rm -f gorg-cli/inc/makefile.h


.PHONY: build				# Generate binary version in build subfolder
build: build/gorg.zip
build/gorg.zip: gorg-cli/bin/gorg.exe
	rm -rf build/gorg/
	mkdir -p build/gorg/
	cp -r gorg-cli/bin/ build/gorg/bin/
	cp -r gorg-cli/templates/ build/gorg/templates/	


.PHONY: release				# Generate installers
release: clean-cli
	rm -rf gorg-installer/out
	mkdir -p gorg-installer/out
	cat gorg-installer/win-gorg.wxs |\
		sed "s/\{\{VERSION_STRING\}\}/$(version_pure)/" >\
		gorg-installer/out/win-gorg.wxs
	cp -r build/gorg/ gorg-installer/out/src/
	cd gorg-installer/out; $(candle) win-gorg.wxs
	cd gorg-installer/out; $(light) win-gorg.wixobj
	mkdir -p release
	cp gorg-installer/out/win-gorg.msi release/gorg-$(version).msi




.PHONY: install				# Install gorg to the specified path
install: release
	msiexec -i "release\gorg-0.0.0-1-g7cea406-dirty.msi"

install_old: cli-version gorg-cli/bin/gorg.exe
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

