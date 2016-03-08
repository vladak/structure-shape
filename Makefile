
PROG=shapeup
TEST=./$(PROG) -t

all: $(PROG)

$(PROG): struct.c
	gcc -o $(PROG) $?

clean:
	rm -f *.o $(PROG)

test:
	chmod +x ./testit.sh
	./testit.sh
