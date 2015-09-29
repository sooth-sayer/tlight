LIBCURL_STATIC = ../deps/install/lib/libcurlcpp.a
LIBEVENT_STATIC = ../deps/install/lib/libevent.a
STATIC_LIBS = $(LIBCURL_STATIC) $(LIBEVENT_STATIC)

SOURCES = ../src/http_server/libevent_http_request.cpp ../src/http_server/libevent_http_server.cpp
SUITES = $(wildcard $(addsuffix /*.hpp, src)) $(wildcard $(addsuffix /**/*.hpp, src)) $(wildcard $(addsuffix /*.hpp, lib)) $(wildcard $(addsuffix /**/*.hpp, lib))
COMPILER = clang++
SHFLAGS = -fdiagnostics-color=never
INCLUDE=-I../deps/cxxtest -I../deps/install/include -I./test_helper -I../include -I../lib/include
CFLAGS = $(SHFLAGS) $(INCLUDE) -Wno-c++1y-extensions -std=c++1y -g -O0
# LDFLAGS = $(SHFLAGS) -L../deps/install/lib -levent -lcurl
LDFLAGS = $(SHFLAGS) -L../deps/install/lib -lcurl

all: clean run

run: build/suites
	build/suites

build/suites: build/suites.cpp
	$(COMPILER) $(CFLAGS) $(LDFLAGS) -o build/suites build/suites.cpp $(SOURCES) $(STATIC_LIBS)

build/suites.cpp: $(SUITES)
	../deps/cxxtest/bin/cxxtestgen --error-printer -o build/suites.cpp $(SUITES)

clean:
	rm -rf build/*

.PHONY: run all clean
