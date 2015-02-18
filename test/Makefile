SUITES = $(wildcard $(addsuffix /**/*.hpp, src)) $(wildcard $(addsuffix /**/*.hpp, lib))
COMPILER = g++ -std=
SHFLAGS = -fdiagnostics-color=never
CFLAGS = $(SHFLAGS) -I../deps/cxxtest -Wno-c++1y-extensions -std=c++1y -g -O0

all: run

run: build/suites
	build/suites

build/suites: build/suites.cpp
	$(COMPILER) $(CFLAGS) -o build/suites build/suites.cpp

build/suites.cpp: $(SUITES)
	../deps/cxxtest/bin/cxxtestgen --error-printer -o build/suites.cpp $(SUITES)

.PHONY: run all
