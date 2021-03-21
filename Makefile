.PHONY: all clean test docs
all: clean test docs

GTEST_INC=google-test/googletest/include
GTEST_LIB=google-test/build/lib
GMOCK_INC=google-test/googlemock/include
GMOCK_LIB=google-test/build/lib

clean:
	rm -rf doxygen-output docs test/TestCircularBuffer

test: google-test test/TestCircularBuffer
	./test/TestCircularBuffer

test/TestCircularBuffer: test/TestCircularBuffer.cpp src/circular_buffer.h src/circular_buffer.tpp
	g++ -std=c++11 -Isrc -I${GTEST_INC} -L${GTEST_LIB} -o $@ $< -lgtest -pthread

google-test:
	git clone https://github.com/google/googletest.git -b release-1.10.0 $@
	mkdir $@/build
	cmake -B$@/build -S$@
	make -C$@/build

docs: doxygen.cfg
	doxygen $^
	cp -a doxygen-output/html docs
	make -C doxygen-output/latex
	cp -a doxygen-output/latex/refman.pdf doxygen-output/cpp-headers-reference.pdf
