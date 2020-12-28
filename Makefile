

browser := $(shell grep BROWSER MAKE-CONFIG.txt | sed -r "s/BROWSER\s*=\s*(.*)/\1/")


.PHONY: docs
docs: sam-docs/_build/html/index.html
	$(browser) sam-docs/_build/html/index.html
sam-docs/_build/html/index.html: $(shell find sam-docs -name *.rst)
	cd sam-docs ; make html

.PHONY: clean-docs
clean-docs:
	rm -rf sam-docs/_build/*
