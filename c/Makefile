CC ?= cc
CFLAGS ?= -std=c11 -O2 -Wall -Wextra -Wpedantic
CPPFLAGS ?= -Iinclude
SOURCES = src/main.c src/interface.c src/gerenciamento.c src/fila.c src/heap.c src/hash.c src/historico.c src/pilha.c
TARGET = build/chamados
.PHONY: all clean debug
all: $(TARGET)
$(TARGET): $(SOURCES) | build
	$(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCES) -o $@
build:
	mkdir -p build
debug: CFLAGS = -std=c11 -O0 -g3 -Wall -Wextra -Wpedantic -fsanitize=address,undefined
debug: clean all
clean:
	rm -rf build
