.PHONY: all project clean

all: project

project: bin/project.o
bin/project.o: src/*.cpp src/*.h
	@echo "Compiling project"
	@g++ src/*.cpp -o bin/project.o

clean:
	@rm -f bin/*
