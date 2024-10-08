CC = gcc

CFLAGS = -std=c99 -Wall

TARGET = exe

TARGET_EXTRA = extra

SRCS = main.c lista.c

SRCS_EXTRA = extra.c lista.c

OBJS = $(SRCS:.c=.o)

OBJS_EXTRA = $(SRCS_EXTRA:.c=.o)

# Regra para compilar o TARGET
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regra para compilar o TARGET_EXTRA
$(TARGET_EXTRA): $(OBJS_EXTRA)
	$(CC) $(CFLAGS) -o $(TARGET_EXTRA) $(OBJS_EXTRA)

# Regra genérica para compilar arquivos .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpa arquivos objetos e executáveis
clean:
	rm -f $(OBJS) $(TARGET) $(OBJS_EXTRA) $(TARGET_EXTRA)
