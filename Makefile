SHELL := /usr/bin/zsh

CC := gcc
CFLAGS := -std=c99 -I ./include/ ./include/Crypt_utils/ -fPIC -c
CFLAGS_RELEASE := -O2
CFLAGS_DEBUG := -O0 -g2 -fsanitize=leak -fstack-protector-all -Wall -D__DEBUG__
CFLAGS_LIBS :=

SRC := ./src
BIN := ./bin
DIRECTORIES := $(shell ls $(SRC))
TARGETS_SRCS := $(wildcard $(SRC)/*/*.c)
TARGETS_OBJS := ${TARGETS_SRCS:%.c=%.o}

SDL_FLAGS := `pkg-config --cflags --libs sdl2`

.PHONY: debug_build release_build all clean build_flags

debug_build: CFLAGS := $(CFLAGS) $(CFLAGS_DEBUG)
debug_build: $(DIRECTORIES)

release_build: CFLAGS := $(CFLAGS) $(CFLAGS_RELEASE)
release_build: all

build_flags:
	@make clean
	@bear make

all: $(DIRECTORIES)

.SECONDEXPANSION:
$(DIRECTORIES): $$(filter $(SRC)/$$@/%.o, $(TARGETS_OBJS))
	$(CC) -shared -o $(BIN)/lib$@.so $^ $(CFLAGS_LIBS) $(SDL_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $^ $(CFLAGS_LIBS) $(SDL_FLAGS)

clean:
	@for obj_file in $(TARGETS_OBJS) ; do \
		if [ -f $$obj_file ] ; then \
			rm $$obj_file ; \
		fi; \
	done;
	@rm -rf $(BIN)
	@mkdir $(BIN)
