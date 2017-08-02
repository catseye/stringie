# GNU Makefile for stringie.

PROG=../bin/stringie
CC?=gcc
STRIP?=strip
O?=.o
EXE?=

WARNS?=

ifeq ($(CC),pcc)
  CFLAGS+=-I/usr/include/linux -I/usr/lib/gcc/x86_64-linux-gnu/4.6/include/
else
  ifdef ANSI
    CFLAGS+= -ansi -pedantic
  else
    CFLAGS+= -std=c99 -D_POSIX_C_SOURCE=200112L
  endif
endif

CFLAGS+= ${WARNS} ${EXTRA_CFLAGS}

ifdef DEBUG
  CFLAGS+= -g
endif

OBJS=	stringie${O}

all: ${PROG}${EXE}

${PROG}${EXE}: $(OBJS)
	mkdir -p ../bin/
	$(CC) $(OBJS) -o ${PROG} $(LIBS)

stringie${O}: stringie.c
	$(CC) $(CFLAGS) -c stringie.c -o stringie${O}

clean:
	rm -f *.o *.core *.exe ${PROG}${EXE}
