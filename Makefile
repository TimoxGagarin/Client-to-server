CC = gcc
CFLAGS = -g2 -ggdb -I./headers -D_POSIX_C_SOURCE=200809L -D_XOPEN_SOURCE -W -Wall -Wno-unused-parameter -Wno-unused-variable -std=c11 -pedantic -lpthread

.SUFFIXES:
.SUFFIXES: .c .o

DEBUG = ./build/debug
RELEASE = ./build/release

OUT_DIR = $(DEBUG)
vpath %.c src
vpath %.h src
vpath %.o build/debug

ifeq ($(MODE), release)
	CFLAGS = -I./headers -W -Wall -Wno-unused-parameter -Wno-unused-variable -std=c11 -pedantic -lpthread
	OUT_DIR = $(RELEASE)
	vpath %.o build/release
endif

server_objects = $(OUT_DIR)/server.o $(OUT_DIR)/server_lib.o
server_prog = $(OUT_DIR)/server

client_objects = $(OUT_DIR)/client.o
client_prog = $(OUT_DIR)/client

all: $(server_prog) $(client_prog)

$(client_prog) : $(client_objects)
	@$(CC) $(CFLAGS) $(client_objects) -o $@

$(server_prog) : $(server_objects)
	@$(CC) $(CFLAGS) $(server_objects) -o $@
	
$(OUT_DIR)/%.o : %.c
	@$(CC) -c $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	@rm -rf $(DEBUG)/* $(RELEASE)/* test