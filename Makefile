.PHONY: all clean docs
all: clean docs

clean:
	rm -rf doxygen-output docs

docs: doxygen.cfg
	doxygen $^
	cp -a doxygen-output/html docs
	#make -C doxygen-output/latex
	#cp -a doxygen-output/latex/refman.pdf docs/cpp-headers-reference.pdf

