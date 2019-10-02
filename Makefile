
PROG=shapeup
TEST=./$(PROG) -t
CFLAGS=-Wall -Wextra -std=c99

all: $(PROG)

$(PROG): struct.c
	$(CC) $(CFLAGS) -o $(PROG) $?

clean:
	rm -f *.o $(PROG)

test:
	chmod +x ./testit.sh
	./testit.sh
