all: build

.PHONY: build
build:
	gcc orca-bytebeat.c -o orca-bytebeat
