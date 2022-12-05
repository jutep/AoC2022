CC=gcc
IDIR=  src/helpers/include/
CFLAGS=-I$(IDIR)
C_FILES= src/main.c src/helpers/input.c src/helpers/menu.c src/day1/day1.c src/day2/day2.c src/day3/day3.c src/day4/day4.c src/day5/day5.c

aoc2022: $(C_FILES)
	$(CC) $(C_FILES) $(CFLAGS) -o aoc2022
