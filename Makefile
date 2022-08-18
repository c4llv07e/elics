
BIN_NAME := main
CC = clang++
SRC_POSTFIX := cc
SRC_PATH := src
BUILD_PATH := _build
LIBS = gl glew glfw3 stb
SANITIZER= -fsanitize=address,leak,undefined,pointer-compare,pointer-subtract,shadow-call-stack
CCFLAGS = -Wall -Wpedantic ${SANITIZER}
LDFLAGS = -Wall -Wpedantic ${SANITIZER}

rwildcard = $(foreach d, $(wildcard $1*), $(call rwildcard,$d/,$2) \
						$(filter $(subst *,%,$2), $d))
CCFLAGS += `pkg-config --libs ${LIBS}`
LDFLAGS += `pkg-config --cflags ${LIBS}`
SOURCES := $(call rwildcard, $(SRC_PATH), *.$(SRC_POSTFIX))
OBJECTS = $(SOURCES:$(SRC_PATH)/%.$(SRC_POSTFIX)=$(BUILD_PATH)/%.o)

${BIN_NAME}: ${OBJECTS}
	${CC} ${CCFLAGS} ${OBJECTS} -o $@

${BUILD_PATH}/%.o: ${SRC_PATH}/%.${SRC_POSTFIX}
	mkdir -p $(@D) 
	${CC} ${LDFLAGS} -c $< -o $@

.PHONY: all build run clean dirs debug

all: build

build: ${BIN_NAME}

run: ${BIN_NAME}
	./$^

debug: CCFLAGS += -g
debug: LDFLAGS += -g

debug: ${BIN_NAME}
	gdb -tui $^

clean:
	rm -rf ${BUILD_PATH}
