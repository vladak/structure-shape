/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * Copyright 2009 Jan Pechanec, Vladimir Kotal.  All rights reserved.
 * Use is subject to license terms.
 */

/*
 * Example for testing. How many bugs are in the code ? How to construct
 * test cases to capture them all ? Adapt the code so that it can be tested
 * by automated program and write a simple fuzzer and run it - how many
 * problematic cases it discovered ? What about smart fuzzing ?
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <err.h>

/* minimum difference (in seconds) */
#define MINDIFF	60
/* assume 1 MB/s */
#define	SECS2KBYTES(x)	((x) << 20)
/* defaults */
#define	DEFAULT_HARD	28800	/* 8 hours */
#define DEFAULT_SOFT	25200	/* 7 hours */

/*
 * Rules:
 *
 *   soft_sec < hard_sec
 *   soft_kb  < hard_kb
 *   diff(soft_*, hard_*) >= MINDIFF
 *
 */
typedef struct entry_s {
	unsigned timer_hard_sec;
	unsigned timer_soft_sec;
	unsigned timer_hard_kb;
	unsigned timer_soft_kb;
} entry_t;

/* Shape up the structure from the input data according to the rules above. */
entry_t
run(char *hard_sec, char *soft_sec, char *hard_kb, char *soft_kb)
{
	entry_t e;

	if (atoi(hard_sec) == 0)
		e.timer_hard_sec = DEFAULT_HARD;
	else
		e.timer_hard_sec = atoi(hard_sec);

	if (atoi(soft_sec) == 0)
		e.timer_soft_sec = DEFAULT_SOFT;
	else
		e.timer_soft_sec = atoi(soft_sec);

	if (atoi(hard_kb) == 0)
		e.timer_hard_kb = SECS2KBYTES(e.timer_hard_sec);
	else
		e.timer_hard_kb = atoi(hard_kb);
	if (atoi(soft_kb) == 0)
		e.timer_soft_kb = SECS2KBYTES(e.timer_hard_sec);
	else
		e.timer_soft_kb = atoi(soft_kb);

	if (e.timer_hard_sec - e.timer_soft_sec < MINDIFF)
		e.timer_soft_sec -= MINDIFF;
	if (e.timer_hard_kb - e.timer_soft_kb < MINDIFF)
		e.timer_soft_kb -= MINDIFF;

	return (e);
}

int
runtest(entry_t e)
{
	if (!((e.timer_soft_sec < e.timer_hard_sec) &&
	    (e.timer_soft_kb < e.timer_hard_kb) &&
	    (e.timer_hard_sec - e.timer_soft_sec >= MINDIFF) &&
	    (e.timer_hard_kb - e.timer_soft_kb >= SECS2KBYTES(MINDIFF)))) {
		return (1);
	}

	return (0);
}

int
main(int argc, char *argv[])
{
	int testit = 0;
	entry_t e;
	int opt;

	if (argc < 5) {
		errx(1, "usage: %s [-t] <hard_sec> <soft_sec> <hard_kb> "
		    "<soft_kb>", argv[0]);
	}

	while ((opt = getopt(argc, argv, "t")) != -1) {
		switch (opt) {
		case 't':
			testit = 1;
			break;
		default: /* '?' */
			exit(EXIT_FAILURE);
		}
	}

	if (testit)
		argv++;

	e = run(argv[1], argv[2], argv[3], argv[4]);

	printf("Resulting structure:\n"
	    "hard_sec = %u\n"
	    "soft_sec = %u\n"
	    "hard_kb = %u\n"
	    "soft_kb = %u\n",
	    e.timer_hard_sec, e.timer_soft_sec,
	    e.timer_hard_kb, e.timer_soft_kb);

	if (testit)
		return (runtest(e));

	return (0);
}
