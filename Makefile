_GUI = $(if $(NOGUI),,-D GUI -Werror)
_DEBUG = $(if $(DEBUG),-D DEBUG,)
_OPT = $(if $(OPT),-O3 -flto,)
CC = gcc
CFLAGS = -g -std=c99 -Wall $(_OPT) $(_GUI) $(_DEBUG) -I./include
LDFLAGS = -lSDL -lm

.PHONY: clean doc check-syntax compile-all launch-tests

# rule to generate the doxygen documentation
doc:
	doxygen conf/doxygen.conf

# rule to remove all .o files and all executables
clean:
	- rm -f *.o
	- find . -maxdepth 1 -executable -type f \( ! -name "Makefile" \) -delete

# compile rules
%.o: ./src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

%.o: ./tests/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

# you should put all the .o files corresponding to your .c files as prerequisites of
# this rule (see examples)
# \ allows to go on the next line
check-syntax: example-main.o read-file-formatted.o read-file-text.o \
	write-fact.o test-dummy.o disc.o snow.o test-particle.o particle.o \
	test-vector.o vector.o event.o test-event.o loader.o test-loader.o \
	simulation-naive.o clash-of-particles-naive.o heap.o test-correctness-heap.o \
	test-complexity-heap.o simulation-bh.o clash-of-particles-bh.o calculate-pi-coll.o \

# put all the rules to build your applications and tests here (see examples)
example-main: example-main.o
	$(CC) $(CFLACS) -o example-main example-main.o

example-string: example-string.o
	$(CC) $(CFLACS) -o example-string example-string.o

read-file-formatted: read-file-formatted.o
	$(CC) $(CFLACS) -o read-file-formatted read-file-formatted.o

read-file-text: read-file-text.o
	$(CC) $(CFLACS) -o read-file-text read-file-text.o

write-fact: write-fact.o
	$(CC) $(CFLAGS) -o write-fact write-fact.o

test-dummy: test-dummy.o
	$(CC) $(CFLACS) -o test-dummy test-dummy.o

particle: particle.o
	$(CC) $(CFLACS) -o particle particle.o vector.o $(LDFLAGS)

test-particle: test-particle.o particle.o vector.o
	$(CC) $(CFLACS) -o test-particle test-particle.o particle.o vector.o $(LDFLAGS)

vector: vector.o
	$(CC) $(CFLACS) -o vector vector.o

test-vector: test-vector.o vector.o
	$(CC) $(CFLACS) -o test-vector test-vector.o vector.o

event: event.o particle.o
	$(CC) $(CFLACS) -o event event.o particle.o 

test-event: test-event.o event.o particle.o vector.o
	$(CC) $(CFLACS) -o test-event test-event.o event.o particle.o vector.o $(LDFLAGS)

loader: loader.o
	$(CC) $(CFLACS) -o loader loader.o particle.o 

test-loader: test-loader.o loader.o particle.o vector.o
	$(CC) $(CFLACS) -o test-loader test-loader.o loader.o particle.o vector.o $(LDFLAGS)

simulation-naive: simulation-naive.o particle.o loader.o event.o disc.o
	$(CC) $(CFLACS) -o simulation-naive simulation-naive.o particle.o loader.o event.o disc.o $(LDFLAGS)

clash-of-particles-naive: clash-of-particles-naive.o simulation-naive.o particle.o event.o loader.o vector.o disc.o
	$(CC) $(CFLACS) -o clash-of-particles-naive clash-of-particles-naive.o simulation-naive.o particle.o event.o loader.o vector.o disc.o $(LDFLAGS)

heap: heap.o
	$(CC) $(CFLACS) -o heap heap.o event.o 

test-correctness-heap: test-correctness-heap.o heap.o event.o
	$(CC) $(CFLACS) -o test-correctness-heap test-correctness-heap.o heap.o event.o $(LDFLAGS)

test-complexity-heap: test-complexity-heap.o heap.o event.o
	$(CC) $(CFLACS) -o test-complexity-heap test-complexity-heap.o heap.o event.o $(LDFLAGS)

simulation-bh: simulation-bh.o particle.o loader.o heap.o event.o disc.o
	$(CC) $(CFLACS) -o simulation-bh simulation-bh.o particle.o loader.o heap.o event.o disc.o $(LDFLAGS)

clash-of-particles-bh: clash-of-particles-bh.o simulation-bh.o particle.o event.o loader.o heap.o vector.o disc.o
	$(CC) $(CFLACS) -o clash-of-particles-bh clash-of-particles-bh.o simulation-bh.o particle.o event.o loader.o heap.o vector.o disc.o $(LDFLAGS)

calculate-pi-coll: calculate-pi-coll.o simulation-bh-pi.o particle.o event.o loader.o heap.o vector.o disc.o
	$(CC) $(CFLACS) -o calculate-pi-coll calculate-pi-coll.o simulation-bh-pi.o particle.o event.o loader.o heap.o vector.o disc.o $(LDFLAGS)

# the snow app. Beware, for graphical applications, you MUST add $(LDFLAGS)!
snow: snow.o disc.o ./include/disc.h
	$(CC) $(CFLAGS) -o snow snow.o disc.o $(LDFLAGS)

# put all your applications and tests executables as prerequisite of this rule
# \ allows to go to the next line
compile-all: example-main read-file-formatted read-file-text \
	write-fact test-dummy snow test-particle test-vector test-event \
	test-loader clash-of-particles-naive test-correctness-heap \
	test-complexity-heap clash-of-particles-bh calculate-pi-coll

# add all your test executables in the following variable. You should respect
# the order given in the project text
# \ allows to go to the next line
ALL_TESTS = test-dummy test-particle test-vector test-event test-correctness-heap test-complexity-heap

launch-tests: $(ALL_TESTS)
	for x in $(ALL_TESTS); do ./$$x --all; done

# add all .c, .h and .txt files in repository
svn-add-all-files:
	svn add --force src/*.c include/*.h data/*.txt --auto-props --parents --depth infinity -q
