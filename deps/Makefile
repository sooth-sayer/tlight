PWD = $(shell pwd)

test_deps: curlcpp cxxtest

cxxtest:
	@tar -xf cxxtest.tar.gz

curlcpp:
	@tar -xf curlcpp.tar.gz &&\
	cd curlcpp/build &&\
	cmake .. && make &&\
	mkdir -p ../../install/lib ../../install/include &&\
	cp ./src/libcurlcpp.a ../../install/lib/libcurlcpp.a &&\
	cp -r ../include/* ../../install/include/

libevent:
	@tar -xf libevent-2.0.22-stable.tar.gz &&\
  mv libevent-2.0.22-stable libevent &&\
	cd libevent &&\
	./configure --prefix=$(PWD)/install LDFLAGS=-fPIC &&\
	make all install

all: libevent

.PHONY: all libevent cxxtest curlcpp
