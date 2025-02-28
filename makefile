.PHONY: native tests arm all

all: native tests arm
native: build/native/tigo-parser
arm: build/armv5/tigo-parser
tests: build/native/tigo-parser-tests

build/native/tigo-parser: tigo-parser.cpp
	mkdir -p build/native
	g++ -g -std=c++20 -Ithird_party/async-mqtt5/include tigo-parser.cpp -o build/native/tigo-parser

build/native/tigo-parser-tests: tigo-parser.cpp tigo-parser-tests.cpp
	mkdir -p build/native
	g++ -g -std=c++20 -Ithird_party/async-mqtt5/include -DBUILD_TESTS tigo-parser.cpp -o build/native/tigo-parser-tests

build/armv5/tigo-parser: tigo-parser.cpp
	mkdir -p build/armv5
	arm-linux-gnueabi-g++ -s -Os -mcpu=arm926ej-s -static -std=c++20 -Ithird_party/async-mqtt5/include tigo-parser.cpp -o build/armv5/tigo-parser
