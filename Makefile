CC = gcc
CFLAGS = -Wall -O2

SRCS = main.c utils.c page.c table.c
OBJS = $(SRCS:.c=.o)
TARGET = main

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<
