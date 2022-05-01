CC?=gcc
SDL2FLAGS=$(shell pkg-config sdl2 --cflags --libs)
CFLAGS?=-std=c11 -Wall -pedantic -Werror -Wshadow -Wstrict-aliasing -Wstrict-overflow
SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin
ASM_DIR=asm
SRC=${SRC_DIR}/main.c
SRCS=${wildcard ${SRC_DIR}/*.c ${SRC_DIR}/**/*.c}
_=${patsubst ${SRC_DIR}%, ${OBJ_DIR}%, ${SRCS}}
OBJS=${patsubst %.c, %.o, ${_}}
BIN=${BIN_DIR}/main
ASM=${ASM_DIR}/main.asm

.PHONY: all msg clean

all: msg ${BIN}

msg:
	@echo '--- Building using C11 ---'
	@echo 'Object files: ${OBJS}'
	@echo 'Source files: ${SRCS}'

${BIN}: ${OBJS}
	mkdir -p dirname $(shell dirname $@)
	${CC} ${CFLAGS} -O2 -o $@ ${OBJS} ${SDL2FLAGS}

debug: ${SRC}
	${CC} ${CFLAGS} -O1 -g -o ${BIN} $< ${SDL2FLAGS}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
	mkdir -p dirname $(shell dirname $@)
	${CC} ${CFLAGS} -c $< -o $@


asm: main.asm

main.asm: ${SRC}
	${CC} ${CFLAGS} -S -masm=intel -Og -o ${ASM} $< ${SDL2FLAGS}

run: ${BIN}
	@echo '--- Running binary ---'
	time ./${BIN}

clean:
	rm -f ${BIN_DIR)/* ${ASM_DIR}/* ${OBJ_DIR}/*
