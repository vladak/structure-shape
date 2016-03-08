
PROG=shapeup

all: $(PROG)

$(PROG): struct.c
	gcc -o $(PROG) $?

clean:
	rm -f *.o $(PROG)

test: test1 test2 test3

test1: $(PROG)
	./$(PROG) 0 0 0 0
test2: $(PROG)
	./$(PROG) 0 14000 0 0
test3: $(PROG)
	./$(PROG) 0 0 200 100
