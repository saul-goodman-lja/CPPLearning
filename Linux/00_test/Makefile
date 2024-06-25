SRCS := $(wildcard *.c)
OUTS := $(patsubst %.c,%,$(SRCS))
CC := gcc
COM_OP := -Wall -g -pthread  -ll8w8jwt -lssl -lcrypto

all: $(OUTS)
% : %.c
	$(CC) $^ -o $@ $(COM_OP)

.PHONY: clean rebuild
clean:
	$(RM) $(OUTS)
rebuild: clean all
