INC_DIRS = -Iinclude
CFLAGS = -Wall -c
FOPENMP = -fopenmp

compilation: obj/functions.o obj/heap.o obj/list.o obj/main.o obj/testopenmpsort.o
	@ gcc -o bin/sort.out obj/main.o obj/functions.o obj/heap.o obj/utils.o $(FOPENMP)
	@ gcc -o bin/testopenmpsort.out obj/testopenmpsort.o obj/functions.o obj/heap.o obj/utils.o $(FOPENMP) 
	@ echo "Compilation success"

obj/functions.o: src/functions.c
	@ gcc $(CFLAGS) $(INC_DIRS) $(FOPENMP) src/functions.c -o obj/functions.o 

obj/heap.o: src/heap.c
	@ gcc $(CFLAGS) $(INC_DIRS) src/heap.c -o obj/heap.o

obj/list.o: src/utils.c
	@ gcc $(CFLAGS) $(INC_DIRS) src/utils.c -o obj/utils.o

obj/main.o: src/main.c
	@ gcc $(CFLAGS) $(INC_DIRS) src/main.c -o obj/main.o

obj/testopenmpsort.o: src/testopenmpsort.c
	@ gcc $(CFLAGS) $(INC_DIRS) src/testopenmpsort.c -o obj/testopenmpsort.o

clean:
	@ rm -rf obj/*
	@ rm -rf bin/*
	@ rm -rf output/*
	@ echo "Clean success"

run:
	@ echo "Running sort..."
	@ ./bin/sort.out -i ./data/16777216.raw -o 16777216sorted.raw -N 16777216l -d 1 -l 20 -h 1

run_testsimdsort:
	@ echo "Running testopenmpsort..."
	@ ./bin/testopenmpsort.out -i ./data/160000floats.raw -o 160000_2l_1h.csv -N 160000l -d 1 -l 2 -h 1
	@ ./bin/testopenmpsort.out -i ./data/160000floats.raw -o 160000_2l_4h.csv -N 160000l -d 1 -l 2 -h 4
	@ ./bin/testopenmpsort.out -i ./data/160000floats.raw -o 160000_2l_10h.csv -N 160000l -d 1 -l 2 -h 10
	@ ./bin/testopenmpsort.out -i ./data/160000floats.raw -o 160000_2l_15h.csv -N 160000l -d 1 -l 2 -h 15

	@ ./bin/testopenmpsort.out -i ./data/160000floats.raw -o 160000_3l_1h.csv -N 160000l -d 1 -l 3 -h 1
	@ ./bin/testopenmpsort.out -i ./data/160000floats.raw -o 160000_3l_4h.csv -N 160000l -d 1 -l 3 -h 4
	@ ./bin/testopenmpsort.out -i ./data/160000floats.raw -o 160000_3l_10h.csv -N 160000l -d 1 -l 3 -h 10
	@ ./bin/testopenmpsort.out -i ./data/160000floats.raw -o 160000_3l_15h.csv -N 160000l -d 1 -l 3 -h 15

	@ ./bin/testopenmpsort.out -i ./data/160000floats.raw -o 160000_4l_1h.csv -N 160000l -d 1 -l 4 -h 1
	@ ./bin/testopenmpsort.out -i ./data/160000floats.raw -o 160000_4l_4h.csv -N 160000l -d 1 -l 4 -h 4
	@ ./bin/testopenmpsort.out -i ./data/160000floats.raw -o 160000_4l_10h.csv -N 160000l -d 1 -l 4 -h 10
	@ ./bin/testopenmpsort.out -i ./data/160000floats.raw -o 160000_4l_15h.csv -N 160000l -d 1 -l 4 -h 15

	@ ./bin/testopenmpsort.out -i ./data/160000floats.raw -o 160000_5l_1h.csv -N 160000l -d 1 -l 5 -h 1
	@ ./bin/testopenmpsort.out -i ./data/160000floats.raw -o 160000_5l_4h.csv -N 160000l -d 1 -l 5 -h 4
	@ ./bin/testopenmpsort.out -i ./data/160000floats.raw -o 160000_5l_10h.csv -N 160000l -d 1 -l 5 -h 10
	@ ./bin/testopenmpsort.out -i ./data/160000floats.raw -o 160000_5l_15h.csv -N 160000l -d 1 -l 5 -h 15

start_sort: clean compilation run

start_testsimdsort: clean compilation run_testsimdsort