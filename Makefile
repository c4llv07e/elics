
BIN_NAME := main
CC = clang++
SRC_POSTFIX := cc
SRC_PATH := src
BUILD_PATH := _build
LIBS = gl glew glfw3
CCFLAGS = 
LDFLAGS = 

rwildcard = $(foreach d, $(wildcard $1*), $(call rwildcard,$d/,$2) \
						$(filter $(subst *,%,$2), $d))
CCFLAGS += `pkg-config --libs --cflags ${LIBS}`
SOURCES := $(call rwildcard, $(SRC_PATH), *.$(SRC_POSTFIX))
OBJECTS = $(SOURCES:$(SRC_PATH)/%.$(SRC_POSTFIX)=$(BUILD_PATH)/%.o)

${BIN_NAME}: ${OBJECTS}
	${CC} ${CCFLAGS} ${OBJECTS} -o $@

${BUILD_PATH}/%.o: ${SRC_PATH}/%.${SRC_POSTFIX}
	${CC} ${LDFLAGS} -c $< -o $@

.PHONY: all build run clean dirs

all: build

build: dirs main

run: ${BIN_NAME}
	./${BIN_NAME}

dirs:
	mkdir -p $(dir ${OBJECTS})

clean:
	rm -r ${BUILD_PATH}
