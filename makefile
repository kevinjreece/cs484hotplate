.PHONY: all project clean

all: project

project: bin/project_cpp.o bin/project_c.o


bin/project_cpp.o: src/*.cpp src/*.h
	@echo "Compiling C++ project"
	@g++ src/*.cpp -o bin/project_cpp.o

bin/project_c.o: src/*.c src/*.h
	@echo "Compiling C project"
	@gcc src/*.c -o bin/project_c.o

clean:
	@rm -f bin/*
