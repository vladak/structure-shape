
PROG=shapeup
TEST=./$(PROG) -t

all: $(PROG)

$(PROG): struct.c
	$(CC) -o $(PROG) $?

clean:
	rm -f *.o $(PROG)

test:
	chmod +x ./testit.sh
	./testit.sh
