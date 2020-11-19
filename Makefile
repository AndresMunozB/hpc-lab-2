INC_DIRS = -Iinclude
CFLAGS = -Wall -c
FOPENMP = -fopenmp

compilation: obj/functions.o obj/heap.o obj/list.o obj/main.o obj/testsimdsort.o
	@ gcc -o bin/sort.out obj/main.o obj/functions.o obj/heap.o obj/utils.o $(FOPENMP)
	@ gcc -o bin/testsimdsort.out obj/testsimdsort.o obj/functions.o obj/heap.o obj/utils.o $(FOPENMP) 
	@ echo "Compilation success"

obj/functions.o: src/functions.c
	@ gcc $(CFLAGS) $(INC_DIRS) $(FOPENMP) src/functions.c -o obj/functions.o 

obj/heap.o: src/heap.c
	@ gcc $(CFLAGS) $(INC_DIRS) src/heap.c -o obj/heap.o

obj/list.o: src/utils.c
	@ gcc $(CFLAGS) $(INC_DIRS) src/utils.c -o obj/utils.o

obj/main.o: src/main.c
	@ gcc $(CFLAGS) $(INC_DIRS) src/main.c -o obj/main.o

obj/testsimdsort.o: src/testsimdsort.c
	@ gcc $(CFLAGS) $(INC_DIRS) src/testsimdsort.c -o obj/testsimdsort.o

clean:
	@ rm -rf obj/*
	@ rm -rf bin/*
	@ rm -rf output/*
	@ echo "Clean success"

run:
	@ echo "Running sort..."
	@ ./bin/sort.out -i ./data/160000floats.raw -o 160000floatssorted.raw -N 160000l -d 1 -l 2 -h 4

run_testsimdsort:
	@ echo "Running testsimdsort..."
	@ ./bin/testsimdsort.out -i ./data/160000floats.raw -o 160000floatssorted.raw -N 160000l -d 1 -l 2 -h 4

start_sort: clean compilation run

start_testsimdsort: clean compilation run_testsimdsort