# C compiler
CC = g++ -g
CC_FLAGS = -fopenmp

destDir = /tmp/conversor

all: gen_bin gen_data mv_bin

gen_bin: main.cpp data.cpp
	$(CC) $(CC_FLAGS) main.cpp data.cpp -o conversor

gen_data: gen_bin
	./conversor files/test_1.obj gold.foo

mv_bin: gen_data
	mkdir -p $(destDir)
	mkdir -p output
	cp gold.foo output
	cp files/test_1.obj $(destDir)
	mv conversor gold.foo $(destDir)
	@echo "All Done, executables should be in the $(destDir)"


