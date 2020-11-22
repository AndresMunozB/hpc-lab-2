INC_DIRS = -Iinclude
CFLAGS = -Wall -c
FOPENMP = -fopenmp

# ./sort -i 16floats.raw -o 16floatssorted2.raw -N 16 -d 1 -l 2 -h 2
# ./sort -i 64floats.raw -o 64floatssorted2.raw -N 64 -d 1 -l 2 -h 2
# ./sort -i 65536floats.raw -o 65536floatssorted2.raw -N 65536 -d 1 -l 2 -h 2


compilation: obj/functions.o obj/heap.o obj/list.o obj/main.o obj/test.o
	@ gcc -o sort obj/main.o obj/functions.o obj/heap.o obj/utils.o $(FOPENMP)
	@ gcc -o test obj/test.o obj/functions.o obj/heap.o obj/utils.o $(FOPENMP)

obj/functions.o: src/functions.c
	@ gcc $(CFLAGS) $(INC_DIRS) $(FOPENMP) src/functions.c -o obj/functions.o 

obj/heap.o: src/heap.c
	@ gcc $(CFLAGS) $(INC_DIRS) src/heap.c -o obj/heap.o

obj/list.o: src/utils.c
	@ gcc $(CFLAGS) $(INC_DIRS) src/utils.c -o obj/utils.o

obj/main.o: src/main.c
	@ gcc $(CFLAGS) $(INC_DIRS) src/main.c -o obj/main.o

obj/test.o: src/test.c
	@ gcc $(CFLAGS) $(INC_DIRS) src/test.c -o obj/test.o

clean:
	@ rm -rf obj/*
	@ rm -rf *.csv
	@ rm -rf sort
	@ rm -rf test

run:
	@ ./sort -i 16floats.raw -o 16floatssorted2.raw -N 16 -d 1 -l 30 -h 1
	@ ./sort -i 64floats.raw -o 64floatssorted2.raw -N 64 -d 1 -l 30 -h 2
	@ ./sort -i 65536floats.raw -o 65536floatssorted2.raw -N 65536 -d 1 -l 30 -h 2
	@ ./sort -i 2097152floats.raw -o 2097152floatssorted2.raw -N 2097152 -d 1 -l 30 -h 1

diff:
	@ diff  16floatssorted2.raw 16floatssorted.raw 
	@ diff  64floatssorted2.raw 64floatssorted.raw 
	@ diff  65536floatssorted2.raw 65536floatssorted.raw 
	@ diff  2097152floatssorted2.raw 2097152floatssorted.raw 

start: clean compilation run diff

test: clean compilation run_test

run_test:
	@ echo "Running tests..."
	@ ./test -i 2097152floats.raw -o 0 -N 2097152 -d 0 -l 0 -h 0
