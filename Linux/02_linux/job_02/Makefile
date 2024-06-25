SRCS := $(wildcard *.c)
OUTS := $(patsubst %.c,%,$(SRCS))
CC := gcc
COM_OP := -Wall -g

all: $(OUTS)
% : %.c
	$(CC) $^ -O $@ $(COM_OP)

.PHONY: clean rebuild
clean:
	$(RM) $(OUTS)
rebuild: clean all
