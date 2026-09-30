.PHONY: procinfo

build:
	chmod u+x procinfo.sh && ./procinfo.sh;

prerequisites: procinfo

target: prerequisites
