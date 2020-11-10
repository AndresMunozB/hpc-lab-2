INC_DIRS = -Iinclude
CFLAGS = -Wall -c

compilation: obj/functions.o obj/utils.o obj/listlist.o obj/list.o obj/simdsort.o obj/bubblesort.o obj/testsimdsort.o obj/testbubblesort.o
	@ gcc obj/functions.o obj/utils.o obj/listlist.o obj/list.o obj/simdsort.o -o bin/simdsort.out
	@ gcc obj/functions.o obj/utils.o obj/listlist.o obj/list.o obj/bubblesort.o -o bin/bubblesort.out
	@ gcc obj/functions.o obj/utils.o obj/listlist.o obj/list.o obj/testsimdsort.o -o bin/testsimdsort.out
	@ gcc obj/functions.o obj/utils.o obj/listlist.o obj/list.o obj/testbubblesort.o -o bin/testbubblesort.out
	@ echo "Compilation success"

obj/functions.o: src/functions.c
	@ gcc $(CFLAGS) $(INC_DIRS) src/functions.c -o obj/functions.o

obj/listlist.o: src/listlist.c
	@ gcc $(CFLAGS) $(INC_DIRS) src/listlist.c -o obj/listlist.o

obj/list.o: src/list.c
	@ gcc $(CFLAGS) $(INC_DIRS) src/list.c -o obj/list.o

obj/utils.o: src/utils.c
	@ gcc $(CFLAGS) $(INC_DIRS) src/utils.c -o obj/utils.o

obj/simdsort.o: src/simdsort.c
	@ gcc $(CFLAGS) $(INC_DIRS) src/simdsort.c -o obj/simdsort.o

obj/testsimdsort.o: src/testsimdsort.c
	@ gcc $(CFLAGS) $(INC_DIRS) src/testsimdsort.c -o obj/testsimdsort.o

obj/bubblesort.o: src/bubblesort.c
	@ gcc $(CFLAGS) $(INC_DIRS) src/bubblesort.c -o obj/bubblesort.o

obj/testbubblesort.o: src/testbubblesort.c
	@ gcc $(CFLAGS) $(INC_DIRS) src/testbubblesort.c -o obj/testbubblesort.o

clean:
	@ rm -rf obj/*
	@ rm -rf bin/*
	@ rm -rf output/*
	@ echo "Clean success"

run:
	@ echo "Running..."
	@ ./bin/simdsort.out -i ./data/65536floats.raw -o output_simd_sort.raw -N 65536 -d 1

start: clean compilation run

run_bubblesort:
	@ echo "Running..."
	@ ./bin/bubblesort.out -i ./data/65536floats.raw -o output_bubble_sort.raw -N 65536 -d 1
run_test_simdsort:
	@ echo "Running test 1600..."
	@ ./bin/testsimdsort.out -i ./data/1600floats.raw -o output.raw -N 1600 -d 0
	@ echo "Running test 16000..."
	@ ./bin/testsimdsort.out -i ./data/16000floats.raw -o output.raw -N 16000 -d 0
	@ echo "Running test 160000..."
	@ ./bin/testsimdsort.out -i ./data/160000floats.raw -o output.raw -N 160000 -d 0
run_test_bubblesort:
	@ echo "Running test 1600..."
	@ ./bin/testbubblesort.out -i ./data/1600floats.raw -o output.raw -N 1600 -d 0
	@ echo "Running test 16000..."
	@ ./bin/testbubblesort.out -i ./data/16000floats.raw -o output.raw -N 16000 -d 0
	@ echo "Running test 160000..."
	@ ./bin/testbubblesort.out -i ./data/160000floats.raw -o output.raw -N 160000 -d 0
start_bubblesort: clean compilation run_bubblesort
