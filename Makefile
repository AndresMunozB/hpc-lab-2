INC_DIRS = -Iinclude
CFLAGS = -Wall -c
FOPENMP = -fopenmp

# ./sort -i 16floats.raw -o 16floatssorted2.raw -N 16 -d 1 -l 2 -h 2
# ./sort -i 64floats.raw -o 64floatssorted2.raw -N 64 -d 1 -l 2 -h 2
# ./sort -i 65536floats.raw -o 65536floatssorted2.raw -N 65536 -d 1 -l 2 -h 2


compilation: obj/functions.o obj/heap.o obj/list.o obj/main.o obj/testopenmpsort.o
	@ gcc -o sort obj/main.o obj/functions.o obj/heap.o obj/utils.o $(FOPENMP)
	@ gcc -o test obj/testopenmpsort.o obj/functions.o obj/heap.o obj/utils.o $(FOPENMP)

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
	@ rm -rf *.csv
	@ rm -rf sort
	@ rm -rf test

run:
	@ ./sort -i 16floats.raw -o 16floatssorted2.raw -N 16 -d 1 -l 2 -h 1
	@ ./sort -i 64floats.raw -o 64floatssorted2.raw -N 64 -d 1 -l 2 -h 2
	@ ./sort -i 65536floats.raw -o 65536floatssorted2.raw -N 65536 -d 1 -l 2 -h 2

diff:
	@ diff  16floatssorted2.raw 16floatssorted.raw 
	@ diff  64floatssorted2.raw 64floatssorted.raw 
	@ diff  65536floatssorted2.raw 65536floatssorted.raw 
start: clean compilation run

run_test_16:
	@ ./test -i 16floats.raw -o 16_2l_1h.csv -N 16 -d 1 -l 2 -h 1
	@ ./test -i 16floats.raw -o 16_2l_4h.csv -N 16 -d 1 -l 2 -h 4
	@ ./test -i 16floats.raw -o 16_2l_10h.csv -N 16 -d 1 -l 2 -h 10
	@ ./test -i 16floats.raw -o 16_2l_15h.csv -N 16 -d 1 -l 2 -h 15

	@ ./test -i 16floats.raw -o 16_3l_1h.csv -N 16 -d 1 -l 3 -h 1
	@ ./test -i 16floats.raw -o 16_3l_4h.csv -N 16 -d 1 -l 3 -h 4
	@ ./test -i 16floats.raw -o 16_3l_10h.csv -N 16 -d 1 -l 3 -h 10
	@ ./test -i 16floats.raw -o 16_3l_15h.csv -N 16 -d 1 -l 3 -h 15

	@ ./test -i 16floats.raw -o 16_4l_1h.csv -N 16 -d 1 -l 4 -h 1
	@ ./test -i 16floats.raw -o 16_4l_4h.csv -N 16 -d 1 -l 4 -h 4
	@ ./test -i 16floats.raw -o 16_4l_10h.csv -N 16 -d 1 -l 4 -h 10
	@ ./test -i 16floats.raw -o 16_4l_15h.csv -N 16 -d 1 -l 4 -h 15

	@ ./test -i 16floats.raw -o 16_5l_1h.csv -N 16 -d 1 -l 5 -h 1
	@ ./test -i 16floats.raw -o 16_5l_4h.csv -N 16 -d 1 -l 5 -h 4
	@ ./test -i 16floats.raw -o 16_5l_10h.csv -N 16 -d 1 -l 5 -h 10
	@ ./test -i 16floats.raw -o 16_5l_15h.csv -N 16 -d 1 -l 5 -h 15

run_test_64:
	@ ./test -i 64floats.raw -o 64_2l_1h.csv -N 64 -d 1 -l 2 -h 1
	@ ./test -i 64floats.raw -o 64_2l_4h.csv -N 64 -d 1 -l 2 -h 4
	@ ./test -i 64floats.raw -o 64_2l_10h.csv -N 64 -d 1 -l 2 -h 10
	@ ./test -i 64floats.raw -o 64_2l_15h.csv -N 64 -d 1 -l 2 -h 15

	@ ./test -i 64floats.raw -o 64_3l_1h.csv -N 64 -d 1 -l 3 -h 1
	@ ./test -i 64floats.raw -o 64_3l_4h.csv -N 64 -d 1 -l 3 -h 4
	@ ./test -i 64floats.raw -o 64_3l_10h.csv -N 64 -d 1 -l 3 -h 10
	@ ./test -i 64floats.raw -o 64_3l_15h.csv -N 64 -d 1 -l 3 -h 15

	@ ./test -i 64floats.raw -o 64_4l_1h.csv -N 64 -d 1 -l 4 -h 1
	@ ./test -i 64floats.raw -o 64_4l_4h.csv -N 64 -d 1 -l 4 -h 4
	@ ./test -i 64floats.raw -o 64_4l_10h.csv -N 64 -d 1 -l 4 -h 10
	@ ./test -i 64floats.raw -o 64_4l_15h.csv -N 64 -d 1 -l 4 -h 15

	@ ./test -i 64floats.raw -o 64_5l_1h.csv -N 64 -d 1 -l 5 -h 1
	@ ./test -i 64floats.raw -o 64_5l_4h.csv -N 64 -d 1 -l 5 -h 4
	@ ./test -i 64floats.raw -o 64_5l_10h.csv -N 64 -d 1 -l 5 -h 10
	@ ./test -i 64floats.raw -o 64_5l_15h.csv -N 64 -d 1 -l 5 -h 15

run_test_65536:
	@ ./test -i 65536floats.raw -o 65536_2l_1h.csv -N 65536 -d 1 -l 2 -h 1
	@ ./test -i 65536floats.raw -o 65536_2l_4h.csv -N 65536 -d 1 -l 2 -h 4
	@ ./test -i 65536floats.raw -o 65536_2l_10h.csv -N 65536 -d 1 -l 2 -h 10
	@ ./test -i 65536floats.raw -o 65536_2l_15h.csv -N 65536 -d 1 -l 2 -h 15

	@ ./test -i 65536floats.raw -o 65536_3l_1h.csv -N 65536 -d 1 -l 3 -h 1
	@ ./test -i 65536floats.raw -o 65536_3l_4h.csv -N 65536 -d 1 -l 3 -h 4
	@ ./test -i 65536floats.raw -o 65536_3l_10h.csv -N 65536 -d 1 -l 3 -h 10
	@ ./test -i 65536floats.raw -o 65536_3l_15h.csv -N 65536 -d 1 -l 3 -h 15

	@ ./test -i 65536floats.raw -o 65536_4l_1h.csv -N 65536 -d 1 -l 4 -h 1
	@ ./test -i 65536floats.raw -o 65536_4l_4h.csv -N 65536 -d 1 -l 4 -h 4
	@ ./test -i 65536floats.raw -o 65536_4l_10h.csv -N 65536 -d 1 -l 4 -h 10
	@ ./test -i 65536floats.raw -o 65536_4l_15h.csv -N 65536 -d 1 -l 4 -h 15

	@ ./test -i 65536floats.raw -o 65536_5l_1h.csv -N 65536 -d 1 -l 5 -h 1
	@ ./test -i 65536floats.raw -o 65536_5l_4h.csv -N 65536 -d 1 -l 5 -h 4
	@ ./test -i 65536floats.raw -o 65536_5l_10h.csv -N 65536 -d 1 -l 5 -h 10
	@ ./test -i 65536floats.raw -o 65536_5l_15h.csv -N 65536 -d 1 -l 5 -h 15