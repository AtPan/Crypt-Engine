SHELL := /usr/bin/zsh

CC := gcc
CFLAGS := -std=c99 -I./include -fPIC -c -nostdlib
CFLAGS_RELEASE := -O2
CFLAGS_DEBUG := -O0 -g2 -fsanitize=leak -fstack-protector-all -Wall -D__DEBUG__

SRC := ./src
BIN := ./bin
DIRECTORIES := $(shell ls $(SRC))
TARGETS_SRCS := $(wildcard $(SRC)/*/*.c)
TARGETS_OBJS := ${TARGETS_SRCS:%.c=%.o}

SDL_FLAGS := `pkg-config --cflags --libs sdl2`

.PHONY: debug_build release_build all clean

debug_build: CFLAGS := $(CFLAGS) $(CFLAGS_DEBUG)
debug_build: $(DIRECTORIES)

release_build: CFLAGS := $(CFLAGS) $(CFLAGS_RELEASE)
release_build: all

all: $(DIRECTORIES)

.SECONDEXPANSION:
$(DIRECTORIES): $$(filter $(SRC)/$$@/%.o, $(TARGETS_OBJS))
	$(CC) -shared -o $(BIN)/lib$@.so $^ $(SDL_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $^ $(SDL_FLAGS)

clean:
	@for obj_file in $(TARGETS_OBJS) ; do \
		if [ -f $$obj_file ] ; then \
			rm $$obj_file ; \
		fi; \
	done;
	@rm $(BIN)/*.so
