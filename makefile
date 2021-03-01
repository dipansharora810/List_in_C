
all:
	gcc -g -Wall -Werror -o run list.c sampleTest.c

clean:
	rm run

