SOURCES = ../src/http_server/libevent_http_request.cpp
SUITES = $(wildcard $(addsuffix /*.hpp, src)) $(wildcard $(addsuffix /**/*.hpp, src)) $(wildcard $(addsuffix /*.hpp, lib)) $(wildcard $(addsuffix /**/*.hpp, lib))
COMPILER = g++
SHFLAGS = -fdiagnostics-color=never
INCLUDE=-I../deps/cxxtest -I../deps/install/include -I./test_helper -I../include -I../lib/include
CFLAGS = $(SHFLAGS) $(INCLUDE) -Wno-c++1y-extensions -std=c++1y -g -O0
LDFLAGS = $(SHFLAGS) -L../deps/install/include -L../deps/install/lib -lcurlcpp -lcurl -levent

all: clean run

run: build/suites
	build/suites

build/suites: build/suites.cpp
	$(COMPILER) $(CFLAGS) $(LDFLAGS) -o build/suites build/suites.cpp $(SOURCES)

build/suites.cpp: $(SUITES)
	../deps/cxxtest/bin/cxxtestgen --error-printer -o build/suites.cpp $(SUITES)

clean:
	rm -rf build/*

.PHONY: run all clean
