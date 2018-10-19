CFLAGS = -g -Wall -Wextra -Werror -pedantic -std=c99 -fPIC -fvisibility=hidden
LDFLAGS = -shared
TARGET_LIB = libmalloc.so
OBJS = src/malloc.o src/size.o src/setup_and_free.o src/finder.o src/caster.o

.PHONY: all ${TARGET_LIB} clean

${TARGET_LIB}: ${OBJS}
	${CC} ${LDFLAGS} -o $@ $^

all: ${TARGET_LIB}

clean:
	${RM} ${TARGET_LIB} ${OBJS}
