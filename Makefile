# Nome do executável
TARGET = Main

# Compilador
CC = gcc

# Arquivos fonte
SRCS = main.c \
       criacao_cadastro.c \
       gui.c \
       manipulador_texto.c \
	   manipulador_texto.h \
	   gui.h \
       

# Flags do GTK
CFLAGS  = -Wall -Wextra -g $(shell pkg-config --cflags gtk+-3.0)
LDFLAGS = $(shell pkg-config --libs gtk+-3.0)

# Regra principal
all: $(TARGET)

# Linkagem
$(TARGET): $(SRCS)
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

# Limpeza
clean:
	rm -f $(TARGET)

.PHONY: all clean
