CC = gcc
CFLAGS = -Wall -Wextra -O2

TARGET = crypt

all: $(TARGET)

$(TARGET): crypt.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)
