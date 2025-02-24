CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = bflip
SRC = src/bflip.c

PREFIX = /usr/local
DEPS = libssl-dev

all: check-dependencies $(TARGET)

check-dependencies:
	@which $(CC) > /dev/null || (echo "Error: gcc is not installed." && exit 1)
	@dpkg -s $(DEPS) > /dev/null 2>&1 || (echo "Error: Required package $(DEPS) is not installed. Install it using 'sudo apt install $(DEPS)'." && exit 1)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) -lssl -lcrypto

install: $(TARGET)
	mkdir -p $(PREFIX)/bin
	cp $(TARGET) $(PREFIX)/bin/

uninstall:
	rm -f $(PREFIX)/bin/$(TARGET)

clean:
	rm -f $(TARGET)
