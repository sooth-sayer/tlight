define WATCHARGS
["trigger", "./", {
	"name": "tlight",
	"expression": ["anyof", ["match", "*.cpp"], ["match", "*.hpp"]],
	"command": ["make", "run"],
	"stdout": ">>build/.run_log",
	"stderr": ">>build/.run_log_err"
}]
endef
export WATCHARGS

HEADERS = lib/**/*.hpp include/**/*.hpp
SRCS = $(wildcard $(addsuffix /*.cpp, src)) $(wildcard $(addsuffix /**/*.cpp, src))
OBJS := $(patsubst src/%, build/%, $(SRCS))
OBJS := $(OBJS:.cpp=.o)

LIBEVENT_STATIC = ./deps/install/lib/libevent.a
STATIC_LIBS = $(LIBEVENT_STATIC)

SHFLAGS = -fdiagnostics-color=never -fno-elide-constructors
INCLUDE = -I./deps/install/include -I./include -I./lib/include
CFLAGS = $(SHFLAGS) $(INCLUDE) -Wno-c++1y-extensions -std=c++1y -g -O0 -fPIC
# LDFLAGS = $(SHFLAGS) -L./deps/install/lib -levent
LDFLAGS = $(SHFLAGS) -L./deps/install/lib

COMPILER=clang++

all: build/tlight

build/tlight: $(OBJS)
	$(COMPILER) $(LDFLAGS) $(OBJS) $(STATIC_LIBS) -o build/tlight

build/%.o: src/%.cpp $(HEADERS)
	$(COMPILER) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build/*.o build/tlight

run: build/tlight
	@build/tlight ${ARGS} 2>&1

watch:
	@echo $$WATCHARGS | watchman -j
	multitail --mark-interval 10 -C build/.run_log build/.run_log_err

unwatch:
	watchman trigger-del ./ tlight

test:
	@cd test && make run && cd ..

.PHONY: clean run watch unwatch test
